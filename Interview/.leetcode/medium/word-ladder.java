/**
 * Given two words (beginWord and endWord), and a dictionary's word list, find
 * the length of shortest transformation sequence from beginWord to endWord,
 * such that:
 * 
 * Only one letter can be changed at a time. Each transformed word must exist in
 * the word list. Note that beginWord is not a transformed word. Note:
 * 
 * Return 0 if there is no such transformation sequence. All words have the same
 * length. All words contain only lowercase alphabetic characters. You may
 * assume no duplicates in the word list. You may assume beginWord and endWord
 * are non-empty and are not the same. Example 1:
 * 
 * Input: beginWord = "hit", endWord = "cog", wordList =
 * ["hot","dot","dog","lot","log","cog"]
 * 
 * Output: 5
 * 
 * Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" ->
 * "dog" -> "cog", return its length 5.
 */
class Solution {
    public int ladderLength(String beginWord, String endWord, List<String> wordList) {
        Set<String> words = new HashSet<>();
        words.addAll(wordList);
        Map<String, Integer> path = new HashMap<>();
        Queue<String> queue = new ArrayDeque<>();
        queue.add(beginWord);
        path.put(beginWord, 1);
        while (!queue.isEmpty()) {
            int curPath = path.get(queue.peek());
            StringBuilder cur = new StringBuilder(queue.remove());
            for (int i = 0; i < cur.length(); ++i) {
                char chBack = cur.charAt(i);
                for (char ch = 'a'; ch <= 'z'; ++ch) {
                    if (chBack == ch)
                        continue;
                    cur.setCharAt(i, ch);
                    String nextWord = cur.toString();
                    if (path.containsKey(nextWord))
                        continue;
                    if (!words.contains(nextWord))
                        continue;
                    if (nextWord.equals(endWord))
                        return curPath + 1;
                    path.put(nextWord, curPath + 1);
                    queue.add(nextWord);
                }
                cur.setCharAt(i, chBack);
            }
        }
        return 0;
    }
}
