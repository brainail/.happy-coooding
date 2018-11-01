/**
 * Given a nested list of integers represented as a string, implement a parser
 * to deserialize it.
 * 
 * Each element is either an integer, or a list -- whose elements may also be
 * integers or other lists.
 * 
 * Note: You may assume that the string is well-formed:
 * 
 * String is non-empty. String does not contain white spaces. String contains
 * only digits 0-9, [, - ,, ]. Example 1:
 * 
 * Given s = "324",
 * 
 * You should return a NestedInteger object which contains a single integer 324.
 * Example 2:
 * 
 * Given s = "[123,[456,[789]]]",
 * 
 * Return a NestedInteger object containing a nested list with 2 elements:
 * 
 * 1. An integer containing value 123. 2. A nested list containing two elements:
 * i. An integer containing value 456. ii. A nested list with one element: a. An
 * integer containing value 789.
 */
public class Solution {
    public NestedInteger deserialize(String s) {
        int len = s.length();
        if (!s.startsWith("[")) return new NestedInteger(Integer.parseInt(s));
        NestedInteger root = new NestedInteger();
        Stack<NestedInteger> stack = new Stack<>();
        stack.push(root);
        for (int i = 1; i < len - 1; ++ i) {
            if (s.charAt(i) == '[') {
                NestedInteger nestedInt = new NestedInteger();
                stack.peek().add(nestedInt);
                stack.push(nestedInt);
            } else if (s.charAt(i) == ',') {
                continue;
            } else if (s.charAt(i) == ']') {
                stack.pop();
            } else {
                int start = i;
                while (i + 1 < len && Character.isDigit(s.charAt(i + 1))) ++i;
                stack.peek().add(new NestedInteger(Integer.parseInt(s.substring(start, i + 1))));
            }
        }
        return stack.pop();
    }
}