public class Solution {
    public int evalRPN(ArrayList<String> ops) {
        final Stack<Integer> exp = new Stack<> ();
        for (int i = 0, size = ops.size(); i < size; ++ i) {
            final String item = ops.get(i);
            switch (item) {
                case "+": {
                    final int y = exp.pop();
                    final int x = exp.pop();
                    exp.push(x + y);
                    break;
                }
                case "*": {
                    final int y = exp.pop();
                    final int x = exp.pop();
                    exp.push(x * y);
                    break;
                }
                case "/": {
                    final int y = exp.pop();
                    final int x = exp.pop();
                    exp.push(x / y);
                    break;
                }
                case "-": {
                    final int y = exp.pop();
                    final int x = exp.pop();
                    exp.push(x - y);
                    break;
                }
                default:
                    exp.push(Integer.valueOf(item));
                    break;
            }
        }
        return exp.empty() ? 0 : exp.pop();
    }
}
