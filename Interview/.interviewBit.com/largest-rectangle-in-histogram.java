public class Solution {
    private int calcRectSquare(final ArrayList<Integer> heights, final Stack<Integer> heightsStack, final int index) {
        final int leftIndex = heightsStack.pop();
        final int count = heightsStack.empty() ? index : index - 1 - heightsStack.peek();
        final int rectSquare = heights.get(leftIndex) * count;
        return rectSquare;
    }
    
    public int largestRectangleArea(final ArrayList<Integer> heights) {
        final int n = heights.size();
        final Stack<Integer> heightsStack = new Stack<> ();
        int index = 0;
        int bestRectSquare = 0;
        
        while (index < n) {
            if (heightsStack.empty() || heights.get(index) >= heights.get(heightsStack.peek())) {
                heightsStack.push(index ++);
            } else {
                bestRectSquare = Math.max(bestRectSquare, calcRectSquare(heights, heightsStack, index));
            }
        }
        
        while (!heightsStack.empty()) {
            bestRectSquare = Math.max(bestRectSquare, calcRectSquare(heights, heightsStack, n));
        }
        
        return bestRectSquare;
    }
}
