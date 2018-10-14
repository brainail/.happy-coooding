String decodeString(String s) {
    final Stack<StringBuilder> stack = new Stack<>();
    for (int i = 0; i < s.length(); ++ i) {
        final char ch = s.charAt(i);
        
        if (Character.isLetter(ch)) {
            if (stack.empty() || '[' == stack.peek().charAt(0)) {
                stack.push(new StringBuilder(String.valueOf(ch)));
            } else {
                stack.peek().append(ch);
            }
            continue;
        }
        
        if (Character.isDigit(ch)) {
            if (stack.empty() || !Character.isDigit(stack.peek().charAt(0))) {
                stack.push(new StringBuilder(String.valueOf(ch)));
            } else {
                stack.peek().append(ch);
            }
            continue;
        }
        
        if (ch == '[') { 
            stack.peek().insert(0, ch);
            continue; // we use just digits
        }
        
        StringBuilder expandedOnce = new StringBuilder();
        while ('[' != stack.peek().charAt(0)) {
            stack.peek().append(expandedOnce.toString());
            expandedOnce = stack.peek();
            stack.pop();
        }
        final String sexpandedOnce = expandedOnce.toString();
        final int times = Integer.valueOf(stack.peek().toString().substring(1));
        stack.pop();
        StringBuilder expanded = new StringBuilder();
        if (expandedOnce.length() > 0) {
            for (int t = 0; t < times; ++ t) {
                expanded.append(sexpandedOnce);
            }
        }
        stack.push(expanded);
    }
    StringBuilder collapsed = new StringBuilder();
    while (!stack.empty()) {
        stack.peek().append(collapsed.toString());
        collapsed = stack.peek();
        stack.pop();
    }
    return collapsed.toString();
}
