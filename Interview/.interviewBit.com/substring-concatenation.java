public class Solution {
    public ArrayList<Integer> findSubstring(String sample, final List<String> words) {
        final int n = words.size();
        final HashMap<String, Integer> wordsCount = new HashMap<> (n);
        final HashMap<String, Integer> currentWordsCount = new HashMap<> (n);
        for (final String word : words) {
            if (!wordsCount.containsKey(word)) {
                wordsCount.put(word, 0);
            }
            wordsCount.put(word, wordsCount.get(word) + 1);
        }
        final int jumpLength = words.get(0).length();
        final int substringLength = jumpLength * n;
        final int length = sample.length();
        final ArrayList<Integer> result = new ArrayList<> ();
        for (int startIndex = 0; startIndex <= length - substringLength; ++ startIndex) {
            for (final Map.Entry<String, Integer> wordEntry : wordsCount.entrySet()) {
                currentWordsCount.put(wordEntry.getKey(), wordEntry.getValue());
            }
            int currentIndex = startIndex;
            int nLeft = wordsCount.size();
            for (int i = 0; i < n; ++ i) {
                final int nextIndex = currentIndex + jumpLength;
                final String possibleWord = sample.substring(currentIndex, nextIndex);
                if (!currentWordsCount.containsKey(possibleWord)) {
                    break;
                }
                final int count = currentWordsCount.get(possibleWord) - 1;
                if (count < 0) {
                    break;
                } else if (0 == count) {
                    -- nLeft;
                }
                currentWordsCount.put(possibleWord, count);
                currentIndex = nextIndex;
            }
            if (0 == nLeft) {
                result.add(startIndex);
            }
        }
        return result;
    }
}
