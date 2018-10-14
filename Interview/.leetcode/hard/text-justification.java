/**
 * Given an array of words and a width maxWidth, format the text such that each
 * line has exactly maxWidth characters and is fully (left and right) justified.
 * 
 * You should pack your words in a greedy approach; that is, pack as many words
 * as you can in each line. Pad extra spaces ' ' when necessary so that each
 * line has exactly maxWidth characters.
 * 
 * Extra spaces between words should be distributed as evenly as possible. If
 * the number of spaces on a line do not divide evenly between words, the empty
 * slots on the left will be assigned more spaces than the slots on the right.
 * 
 * For the last line of text, it should be left justified and no extra space is
 * inserted between words.
 * 
 * Note:
 * 
 * A word is defined as a character sequence consisting of non-space characters
 * only. Each word's length is guaranteed to be greater than 0 and not exceed
 * maxWidth. The input array words contains at least one word. Example 1:
 * 
 * Input: words = ["This", "is", "an", "example", "of", "text",
 * "justification."] maxWidth = 16 
 * Output: [ "This is an", "example of text",
 * "justification. " ]
 */
class Solution {
    public List<String> fullJustify(String[] words, int maxWidth) {
        List<String> result = new ArrayList<String>();
        if (words == null || words.length == 0)
            return result;

        int count = 0;
        int last = 0;
        ArrayList<String> list = new ArrayList<String>();
        for (int i = 0; i < words.length; i++) {
            count = count + words[i].length();

            if (count + i - last > maxWidth) {
                int wordsLen = count - words[i].length();
                int spaceLen = maxWidth - wordsLen;
                int eachLen = 1;
                int extraLen = 0;

                if (i - last - 1 > 0) {
                    eachLen = spaceLen / (i - last - 1);
                    extraLen = spaceLen % (i - last - 1);
                }

                StringBuilder sb = new StringBuilder();

                for (int k = last; k < i - 1; k++) {
                    sb.append(words[k]);

                    int ce = 0;
                    while (ce < eachLen) {
                        sb.append(" ");
                        ce++;
                    }

                    if (extraLen > 0) {
                        sb.append(" ");
                        extraLen--;
                    }
                }

                sb.append(words[i - 1]);
                while (sb.length() < maxWidth) {
                    sb.append(" ");
                }

                result.add(sb.toString());

                last = i;
                count = words[i].length();
            }
        }

        int lastLen = 0;
        StringBuilder sb = new StringBuilder();

        for (int i = last; i < words.length - 1; i++) {
            count = count + words[i].length();
            sb.append(words[i] + " ");
        }

        sb.append(words[words.length - 1]);
        int d = 0;
        while (sb.length() < maxWidth) {
            sb.append(" ");
        }
        result.add(sb.toString());

        return result;
    }
}