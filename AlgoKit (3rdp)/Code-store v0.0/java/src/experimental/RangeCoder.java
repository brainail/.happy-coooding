package experimental;
import static java.util.Arrays.fill;

import java.util.Arrays;
import java.util.Random;

public class RangeCoder {

    public static class RC {
        static final int CODE_BITS = 32;
        static final long TOP = 1L << CODE_BITS;
        static final long BOTTOM = TOP >> 8;
        static final long SHIFT_BITS = CODE_BITS - 8;
        int[] buffer = new int[10000];
        int bits_to_follow;
        int bytes_to_follow;
        int bufferLen;
        int bufferPos;
        int[] cumFreq = new int[257];
        int[] symbol2index = new int[257];
        int[] index2symbol = new int[257];
        int symbolCount;

        private void outputByte(int value) {
            buffer[bufferLen++] = value;
        }

        private int inputByte() {
            if (bufferPos == bufferLen) {
                bufferPos--;
            }
            return buffer[bufferPos++];
        }

        private void init() {
            bits_to_follow = 0;
            bufferLen = 0;
            bufferPos = 0;
            fill(cumFreq, 0);
            fill(buffer, 0);
            symbolCount = 0;
        }

        public void encode(int[] a) {
            init();
            int n = a.length;
            int[] freq = new int[256];
            for (int i = 0; i < n; i++) {
                freq[a[i]]++;
            }
            for (int i = 0; i < freq.length; i++) {
                if (freq[i] > 0) {
                    symbolCount++;
                    cumFreq[symbolCount] = freq[i];
                    symbol2index[i] = symbolCount;
                    index2symbol[symbolCount] = i;
                }
            }
            for (int i = 1; i <= symbolCount; i++) {
                cumFreq[i] += cumFreq[i - 1];
            }
            int totalfreq = cumFreq[symbolCount];
            long lo = 0;
            long range = TOP;
            int next_char = 0;
            for (int k = 0; k < n; k++) {
                int j = symbol2index[a[k]];
                long r = range / totalfreq;
                lo += r * cumFreq[j - 1];
                range = r * (cumFreq[j] - cumFreq[j - 1]);
                while (range < BOTTOM) {
                    if (lo < 0xFFL << SHIFT_BITS) {
                        outputByte(next_char);
                        for (; bytes_to_follow > 0; bytes_to_follow--) {
                            outputByte(0xFF);
                        }
                        next_char = (int) (lo >> SHIFT_BITS) & 255;
                    } else if (lo >= TOP) {
                        outputByte(next_char + 1);
                        for (; bytes_to_follow > 0; bytes_to_follow--) {
                            outputByte(0);
                        }
                        next_char = (int) (lo >> SHIFT_BITS) & 255;
                    } else {
                        bytes_to_follow++;
                    }
                    range <<= 8;
                    lo = (lo << 8) & (0xFFFFFFFFL);
                }
            }
            //flush
            for (int i = 0; i < 5; i++) {
                if (lo < 0xFFL << SHIFT_BITS) {
                    outputByte(next_char);
                    for (; bytes_to_follow > 0; bytes_to_follow--) {
                        outputByte(0xFF);
                    }
                    next_char = (int) (lo >> SHIFT_BITS) & 255;
                } else if (lo >= TOP) {
                    outputByte(next_char + 1);
                    for (; bytes_to_follow > 0; bytes_to_follow--) {
                        outputByte(0);
                    }
                    next_char = (int) (lo >> SHIFT_BITS) & 255;
                } else {
                    bytes_to_follow++;
                }
                lo = (lo << 8) & (0xFFFFFFFFL);
            }
        }

        public int[] decode(int n) {
            long value = 0;
            long range = TOP;
            for (int i = 0; i < 5; i++) {
                value = (value << 8) + inputByte();
            }
            int[] res = new int[n];
            int totalFreq = cumFreq[symbolCount];
            for (int k = 0; k < n; k++) {
                long r = range / totalFreq;
                long cFreq = value / r;
                int j = 1;
                while (cFreq >= cumFreq[j]) {
                    j++;
                }
                value -= cumFreq[j - 1] * r;
                range = r * (cumFreq[j] - cumFreq[j - 1]);
                res[k] = index2symbol[j];
                while (range < BOTTOM) {
                    value = (value << 8) & 0xFFFFFFFFL | inputByte();
                    range <<= 8;
                }
            }
            return res;
        }
    }

    public static void main(String[] args) {
        Random rnd = new Random(1);
        RC codec = new RC();
        for (int i = 0; i < 50; i++) {
            int n = rnd.nextInt(1000) + 1;
            int[] a = new int[n];
            for (int j = 0; j < n; j++) {
                a[j] = rnd.nextInt(200);
            }
            //a = new int[] { 8,3,7,2,5,4,0,6,3,5 };
            //n = a.length;
            codec.encode(a);
            int[] b = codec.decode(n);
            boolean ok = Arrays.equals(a, b);
            if (!ok) {
                debug(a);
                debug(b);
            }
        }
    }

    public static void debug(Object... o) {
        System.err.println(Arrays.deepToString(o));
    }
}
