/**
 * Implement a basic calculator to evaluate a simple expression string.
 * 
 * The expression string contains only non-negative integers, +, -, *, /
 * operators and empty spaces . The integer division should truncate toward
 * zero.
 * 
 * Example 1:
 * 
 * Input: "3+2*2" Output: 7 Example 2:
 * 
 * Input: " 3/2 " Output: 1 Example 3:
 * 
 * Input: " 3+5 / 2 " Output: 5 Note:
 * 
 * You may assume that the given expression is always valid. Do not use the eval
 * built-in library function.
 */

class Solution {
    public int calculate(String s) {
        int num = 0, temp = 0, res = 0;
        char sign = '+';
        for (char c : s.toCharArray()) {
            if (c >= '0' && c <= '9') {
                temp = temp * 10 + (c - '0');
            } else if (c != ' ') {
                num = calc(num, temp, sign);
                if (c == '+' || c == '-') {
                    res += num;
                    num = 0;
                }
                temp = 0;
                sign = c;
            }
        }
        return res + calc(num, temp, sign);
    }

    private int calc(int a, int b, char s) {
        if (s == '+')
            return a + b;
        if (s == '-')
            return a - b;
        if (s == '*')
            return a * b;
        return a / b;
    }
}

// #2 - polish notation (support lots of operations)
class Solution {
    public int calculate(String s) {
        if (s.length() == 0) {
            return 0;
        }
        HashMap<Character, Integer> order = new HashMap<>();
        order.put('+', 1);
        order.put('-', 1);
        order.put('/', 2);
        order.put('*', 2);
        order.put('^', 3);
        order.put('(', 0);
        if (s.charAt(0) == '-') {
            s = "0" + s;
        }
        s = s.replace("(-", "(0-");
        Stack<Character> ops = new Stack<>();
        Stack<Integer> nums = new Stack<>();
        int num = 0;
        for (int i = 0; i < s.length(); ++i) {
            char c = s.charAt(i);
            if (c == ' ') {
                continue;
            } else if (Character.isDigit(c)) {
                num = num * 10 + (c - '0');
            } else if (c == '(') {
                ops.push(c);
            } else if (c == ')') {
                while (!ops.isEmpty() && ops.peek() != '(') {
                    num = calc(nums.pop(), num, ops.pop());
                }
                ops.pop();
            } else {
                int curOrder = order.get(c);
                while (!ops.isEmpty() && curOrder <= order.get(ops.peek())) {
                    num = calc(nums.pop(), num, ops.pop());
                }
                nums.push(num);
                ops.push(c);
                num = 0;
            }
        }
        while (!ops.isEmpty()) {
            num = calc(nums.pop(), num, ops.pop());
        }
        return num;
    }

    private int calc(int n1, int n2, char op) {
        if (op == '+') {
            return n1 + n2;
        } else if (op == '-') {
            return n1 - n2;
        } else if (op == '*') {
            return n1 * n2;
        } else if (op == '/') {
            return n1 / n2;
        }
        return (int) Math.pow(n1, n2);
    }
}