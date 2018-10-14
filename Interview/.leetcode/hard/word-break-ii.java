/**
 * Given a non-empty string s and a dictionary wordDict containing a list of
 * non-empty words, add spaces in s to construct a sentence where each word is a
 * valid dictionary word. Return all such possible sentences.
 * 
 * Note:
 * 
 * The same word in the dictionary may be reused multiple times in the
 * segmentation. You may assume the dictionary does not contain duplicate words.
 * Example 1:
 * 
 * Input: s = "catsanddog" wordDict = ["cat", "cats", "and", "sand", "dog"]
 * Output: [ "cats and dog", "cat sand dog" ]
 */
class Solution {
    public List<String> wordBreak(String s, List<String> wordDict) {
        return breaker(s, wordDict, new HashMap<String, List<String>>());
    }

    public List<String> breaker(String s, List<String> wordDict, Map<String, List<String>> memo) {
        if (memo.containsKey(s))
            return memo.get(s);
        List<String> result = new ArrayList<String>();
        for (String word : wordDict) // trie will be better, we don't need to run through the collection every time
            if (s.startsWith(word)) {
                String next = s.substring(word.length());
                if (next.isEmpty()) {
                    result.add(word);
                } else {
                    for (String tailSolution : breaker(next, wordDict, memo))
                        result.add(word + " " + tailSolution);
                }
            }
        memo.put(s, result);
        return result;
    }
}

/**
 * private static class Node {
    private Map<Character, Node> next;
    private String wordMark;

    public void mark(String wordMark) {
      this.wordMark = wordMark;
    }

    public String wordMark() {
      return wordMark;
    }

    public Node getNext(char ch) {
      return null == next ? null : next.get(ch);
    }

    public Node makeNext(char ch) {
      Node u = new Node();  
      if (null == next) {
        next = new HashMap<>(1);
      }
      next.put(ch, u);
      return u;
    }
  }

  for (String word : wordDict) {
      Node u = trie;
      for (int i = 0, size = word.length(); i < size; ++ i) {
        Node nextU = u.getNext(word.charAt(i));
        u = null == nextU ? u.makeNext(word.charAt(i)) : nextU;
      }
      u.mark(word);
    } 
 */