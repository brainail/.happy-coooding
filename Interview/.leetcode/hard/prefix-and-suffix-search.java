/**
 * Given many words, words[i] has weight i.
 * 
 * Design a class WordFilter that supports one function, WordFilter.f(String
 * prefix, String suffix). It will return the word with given prefix and suffix
 * with maximum weight. If no word exists, return -1.
 * 
 * Examples: Input: WordFilter(["apple"]) WordFilter.f("a", "e") // returns 0
 * WordFilter.f("b", "") // returns -1 Note: words has length in range [1,
 * 15000]. For each test case, up to words.length queries WordFilter.f may be
 * made. words[i] has length in range [1, 10]. prefix, suffix have lengths in
 * range [0, 10]. words[i] and prefix, suffix queries consist of lowercase
 * letters only.
 */

class WordFilter {
    TrieNode trie;

    public WordFilter(String[] words) {
        trie = new TrieNode();
        for (int weight = 0; weight < words.length; ++weight) {
            String word = words[weight] + "{";
            for (int i = 0; i < word.length(); ++i) {
                TrieNode cur = trie;
                cur.weight = weight;
                for (int j = i; j < 2 * word.length() - 1; ++j) {
                    int k = word.charAt(j % word.length()) - 'a';
                    if (cur.children[k] == null) cur.children[k] = new TrieNode();
                    cur = cur.children[k];
                    cur.weight = weight;
                }
            }
        }
    }

    public int f(String prefix, String suffix) {
        TrieNode cur = trie;
        for (char letter : (suffix + '{' + prefix).toCharArray()) {
            if (cur.children[letter - 'a'] == null) return -1;
            cur = cur.children[letter - 'a'];
        }
        return cur.weight;
    }
}

class TrieNode {
    TrieNode[] children;
    int weight;

    public TrieNode() {
        children = new TrieNode[27];
        weight = 0;
    }
}

// Basic tree approach, slower because we pair each prefix with each suffix 
class WordFilter {
    private static class Trie {
        private Map<Character, Trie> next;
        private int weight;

        Trie go(char ch, boolean createIfNoWay, int weight) {
            if (!createIfNoWay)
                return null != next ? next.get(ch) : null;
            if (next == null)
                next = new HashMap<>();
            Trie node = next.get(ch);
            if (node == null)
                node = new Trie();
            node.weight = Math.max(node.weight, weight);
            next.put(ch, node);
            return node;
        }

        int getWeight() {
            return weight;
        }
    }

    Trie trie;

    public WordFilter(String[] words) {
        trie = new Trie();
        int weight = -1;
        for (final String word : words) {
            ++weight;
            int n = word.length();
            for (int i = 0; i <= n; ++i) {
                for (int j = 0; j <= n; ++j) {
                    Trie cur = trie;
                    for (int q = 0; q <= i + j; ++q) {
                        char ch = '#';
                        if (q < i)
                            ch = word.charAt(q);
                        else if (q > i)
                            ch = word.charAt(n - (q - i));
                        cur = cur.go(ch, true, q == i + j ? weight : -1);
                    }
                }
            }
        }
    }

    public int f(String prefix, String suffix) {
        int n = prefix.length(), m = suffix.length();
        Trie cur = trie;
        for (int q = 0; q <= n + m; ++q) {
            char ch = '#';
            if (q < n)
                ch = prefix.charAt(q);
            else if (q > n)
                ch = suffix.charAt(m - (q - n));
            cur = cur.go(ch, false, -1);
            if (null == cur)
                break;
        }
        return null != cur ? cur.getWeight() : -1;
    }
}
