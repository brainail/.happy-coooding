class MimimiStack {
    Stack<Integer> s = new Stack<Integer>();
    Integer minEle;
 
    int getMin() {
        return minEle;
    }
 
    int peek() {
        return (s.peek() < minEle) ? minEle : s.peek();
    }
 
    void pop() {
        Integer t = s.pop();
        if (t < minEle) {
            minEle = 2*minEle - t;
        }
    }
 
    void push(Integer x) {
        if (s.isEmpty()) {
            minEle = x;
            s.push(x);
            return;
        }
 
        if (x < minEle) {
            s.push(2*x - minEle);
            minEle = x;
            return;
        } 
        
        s.push(x);
    }
};

int[] minimumOnStack(String[] operations) {
    Stack<Integer> values = new Stack<>();
    int min = Integer.MAX_VALUE;
    List<Integer> output = new ArrayList<>();
    /* #1
    for (String op : operations) {
        switch (op) {
            case "min":
                output.add(min);
                break;
            case "pop":
                final int top = values.peek();
                values.pop();
                if (top == min) {
                    min = values.peek();
                    values.pop();
                }
                break;
            default:
                final int value = Integer.valueOf(op.substring(op.indexOf(" ") + 1));
                if (value <= min) {
                    values.push(min);
                    min = value;
                }
                values.push(value);
                break;
        }
    }
    */
    
    /* #2 */
    MimimiStack mimimi = new MimimiStack(); 
    for (String op : operations) {
        switch (op) {
            case "min":
                output.add(mimimi.getMin());
                break;
            case "pop":
                mimimi.pop();
                break;
            default:
                final int value = Integer.valueOf(op.substring(op.indexOf(" ") + 1));
                mimimi.push(value);
                break;
        }
    }
    
    return output.stream().mapToInt(i -> i).toArray();
}
