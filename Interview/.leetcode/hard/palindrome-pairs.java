/**
 * Given a list of unique words, find all pairs of distinct indices (i, j) in
 * the given list, so that the concatenation of the two words, i.e. words[i] +
 * words[j] is a palindrome.
 * 
 * Example 1:
 * 
 * Input: ["abcd","dcba","lls","s","sssll"] Output: [[0,1],[1,0],[3,2],[2,4]]
 * Explanation: The palindromes are ["dcbaabcd","abcddcba","slls","llssssll"]
 * Example 2:
 * 
 * Input: ["bat","tab","cat"] Output: [[0,1],[1,0]] Explanation: The palindromes
 * are ["battab","tabbat"]
 */

 /**
 * Using Glenn Manacher will make it optimal
 */
class Solution {
    public List<List<Integer>> palindromePairs(String[] words) {
        List<List<Integer>> ret = new ArrayList<>();
        if (words == null || words.length < 2)
            return ret;
        Map<String, Integer> map = new HashMap<String, Integer>();
        for (int i = 0; i < words.length; i++)
            map.put(words[i], i);
        for (int i = 0; i < words.length; i++) {
            for (int j = 0; j <= words[i].length(); j++) {
                String str1 = words[i].substring(0, j);
                String str2 = words[i].substring(j);
                if (isPalindrome(str1)) {
                    String str2rvs = new StringBuilder(str2).reverse().toString();
                    if (map.containsKey(str2rvs) && map.get(str2rvs) != i) {
                        List<Integer> list = new ArrayList<Integer>();
                        list.add(map.get(str2rvs));
                        list.add(i);
                        ret.add(list);
                    }
                }
                if (isPalindrome(str2)) {
                    String str1rvs = new StringBuilder(str1).reverse().toString();
                    if (map.containsKey(str1rvs) && map.get(str1rvs) != i && str2.length() != 0) {
                        List<Integer> list = new ArrayList<Integer>();
                        list.add(i);
                        list.add(map.get(str1rvs));
                        ret.add(list);
                    }
                }
            }
        }
        return ret;
    }

    private boolean isPalindrome(String str) {
        int left = 0;
        int right = str.length() - 1;
        while (left <= right) {
            if (str.charAt(left++) != str.charAt(right--))
                return false;
        }
        return true;
    }
}

/**
 * Trie - too complex
 * Time: O(sum {words[i].len} + number of pair in result)
 * Memo: O(words.len * average {words[i].len})
 */
class Solution {
    public List<List<Integer>> palindromePairs(String[] words) {
        Set<List<Integer>> ret = new HashSet<>();
        TrieNode root = new TrieNode();
        int n = words.length;
        ArrayList<Boolean>[][] pali = new ArrayList[2][n];
        for (int i = 0; i < n; ++i) {
            initPali(words[i], i, pali);
            int len = words[i].length();
            addWord(words[i], -i - 1, root);
            addWord(reverse(words[i]), i + 1, root);
        }
        for (int i = 0; i < n; ++i) {
            int len = words[i].length();
            String word = words[i]; // from beginning [word | ..word2]
            TrieNode node = goWord(word, root);
            for (Integer index : node.wordIndex[1]) {
                int j = index - 1;
                int lenRev = words[j].length();
                if (i != j && pali[0][j].get(lenRev - len))
                    ret.add(Arrays.asList(i, j));
            }
            word = reverse(words[i]); // from end [word2.. | word]
            node = goWord(word, root);
            for (Integer index : node.wordIndex[0]) {
                int j = index - 1;
                if (i != j && pali[1][j].get(len))
                    ret.add(Arrays.asList(j, i));
            }
        }
        List<List<Integer>> retList = new ArrayList<>();
        retList.addAll(ret);
        return retList;
    }

    private void initPali(String word, int index, ArrayList<Boolean>[][] pali) {
        int n = word.length();
        char[] s = word.toCharArray();
        for (int t = 0; t < 2; ++t)
            pali[t][index] = listOfSize(n + 1);
        int[] d = new int[n];
        Arrays.fill(d, 0);
        int l = 0, r = -1;
        pali[0][index].set(0, true);
        pali[1][index].set(n, true);
        for (int i = 0; i < n; ++i) {
            int k = (i > r ? 0 : Math.min(d[l + r - i] - 1, r - i)) + 1;
            while (i + k < n && i - k >= 0 && s[i + k] == s[i - k])
                ++k;
            d[i] = k--;
            if (i + k > r) {
                l = i - k;
                r = i + k;
            }
            if (i - d[i] + 1 == 0)
                pali[0][index].set(i + d[i], true);
            if (i + d[i] == n)
                pali[1][index].set(i - d[i] + 1, true);
        }
        Arrays.fill(d, 0);
        l = 0;
        r = -1;
        for (int i = 0; i < n; ++i) {
            int k = (i > r ? 0 : Math.min(d[l + r - i + 1], r - i + 1)) + 1;
            while (i + k - 1 < n && i - k >= 0 && s[i + k - 1] == s[i - k])
                ++k;
            d[i] = --k;
            if (i + k - 1 > r) {
                l = i - k;
                r = i + k - 1;
            }
            if (i - d[i] == 0)
                pali[0][index].set(i + d[i], true);
            if (i + d[i] == n)
                pali[1][index].set(i - d[i], true);
        }
    }

    public static ArrayList<Boolean> listOfSize(int size) {
        ArrayList<Boolean> list = new ArrayList<>();
        while (list.size() < size)
            list.add(false);
        return list;
    }

    private boolean checkPali(String word, int left, int right) {
        for (int i = left, j = right; i < j; ++i, --j)
            if (word.charAt(i) != word.charAt(j))
                return false;
        return true;
    }

    private void addWord(String word, int index, TrieNode cur) {
        cur.wordIndex[index < 0 ? 0 : 1].add(Math.abs(index)); // root caontains all to support empty words
        for (int i = 0, length = word.length(); i < length; ++i) {
            cur = cur.add(word.charAt(i), index);
        }
    }

    private TrieNode goWord(String word, TrieNode cur) {
        for (int i = 0, length = word.length(); i < length; ++i) {
            cur = cur.go(word.charAt(i));
            if (null == cur)
                break;
        }
        return cur;
    }

    private String reverse(String text) {
        return new StringBuilder(text).reverse().toString();
    }

    private static class TrieNode {
        private Map<Character, TrieNode> nextNodes = new HashMap<>();
        private ArrayList<Integer>[] wordIndex = new ArrayList[2];

        TrieNode() {
            for (int i = 0; i < 2; ++i)
                wordIndex[i] = new ArrayList<Integer>();
        }

        TrieNode go(char ch) {
            return nextNodes.get(ch);
        }

        TrieNode add(char ch, int index) {
            TrieNode nextNode = nextNodes.get(ch);
            if (null == nextNode)
                nextNode = new TrieNode();
            nextNode.wordIndex[index < 0 ? 0 : 1].add(Math.abs(index));
            nextNodes.put(ch, nextNode);
            return nextNode;
        }
    }
}
