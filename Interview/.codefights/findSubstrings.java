/**
 * You have two arrays of strings, words and parts. Return an array that contains the strings from words, modified so that any occurrences of the substrings from parts are surrounded by square brackets [], following these guidelines:

If several parts substrings occur in one string in words, choose the longest one. If there is still more than one such part, then choose the one that appears first in the string.

Example

For words = ["Apple", "Melon", "Orange", "Watermelon"] and parts = ["a", "mel", "lon", "el", "An"], the output should be
findSubstrings(words, parts) = ["Apple", "Me[lon]", "Or[a]nge", "Water[mel]on"].

While "Watermelon" contains three substrings from the parts array, "a", "mel", and "lon", "mel" is the longest substring that appears first in the string.
 */

class Trie {
    char value;
    boolean terminal;
    private Map<Character, Trie> next;
    
    Trie() {
        this('#');
    }
    
    Trie(final char value) {
        this.value = value;
    }
    
    Trie lay(char layChar) {
        if (null != next && next.containsKey(layChar)) {
            return next.get(layChar);
        } else {
            final Trie layTrie = new Trie(layChar);
            if (null == next) {
                next = new HashMap<>();
            }
            next.put(layChar, layTrie);
            return layTrie;
        }
    }
    
    Trie go(char goChar) {
        if (null != next && next.containsKey(goChar)) {
            return next.get(goChar);
        } else {
            return null;
        }
    }
}

String[] findSubstrings(String[] words, String[] parts) {
    final String [] result = new String [words.length];
    final Trie trie = new Trie();
    
    // lay all parts out
    for (final String part : parts) {
        Trie sufTrie = trie;
        for (int i = 0; i < part.length(); ++ i) {
            sufTrie = sufTrie.lay(part.charAt(i));
        }
        sufTrie.terminal = true;
    }
    
    // iterate words' suffixes
    int index = 0;
    for (final String word : words) {
        int bestLeft = -1;
        int bestRight = -2;
        
        for (int start = 0; start < word.length(); ++ start) {
            Trie sufTrie = trie;
            for (int i = start; i < word.length(); ++ i) {
                sufTrie = sufTrie.go(word.charAt(i));
                if (null == sufTrie) break;
                
                if (sufTrie.terminal) {
                    if (i - start > bestRight - bestLeft) {
                        bestLeft = start;
                        bestRight = i;
                    }
                }
            }
        }
        
        final StringBuilder wordBuilder = new StringBuilder(word.length() + 2 * (bestLeft >= 0 ? 1 : 0));
        for (int i = 0; i < word.length(); ++ i) {
            if (i == bestLeft) wordBuilder.append('[');
            wordBuilder.append(word.charAt(i));
            if (i == bestRight) wordBuilder.append(']');
        }
        result [index ++] = wordBuilder.toString();
    }
    return result;
}
