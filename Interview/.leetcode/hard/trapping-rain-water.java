/**
 * Given n non-negative integers representing an elevation map where the width
 * of each bar is 1, compute how much water it is able to trap after raining.
 * 
 * 
 * The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In
 * this case, 6 units of rain water (blue section) are being trapped. Thanks
 * Marcos for contributing this image!
 * 
 * Example:
 * 
 * Input: [0,1,0,2,1,0,1,3,2,1,2,1] Output: 6
 */
class Solution {
    private static class Trap {
        public final int left, right;

        public Trap(final int left, final int right) {
            this.left = left;
            this.right = right;
        }
    }

    public int trap(int[] height) {
        int n = height.length;
        Stack<Integer> columns = new Stack<>();
        Stack<Trap> traps = new Stack<>();
        for (int i = 0; i < n; ++i) {
            int left = -1;
            while (!columns.isEmpty() && height[i] > height[columns.peek()]) {
                left = columns.pop();
            }
            if (!columns.isEmpty()) {
                left = columns.peek();
            }
            columns.push(i);
            if (i > 0 && height[i] > height[i - 1]) {
                while (!traps.isEmpty() && traps.peek().right > left)
                    traps.pop();
                traps.push(new Trap(left, i));
            }
        }

        int waterAmount = 0;
        while (!traps.isEmpty()) {
            Trap trap = traps.pop();
            int barrierHeight = Math.min(height[trap.left], height[trap.right]);
            for (int i = trap.left + 1; i < trap.right; ++i) {
                waterAmount += barrierHeight - height[i];
            }
        }
        return waterAmount;
    }
}

// Approach 1: Brute force
/*
int trap(vector<int>& height)
{
    int ans = 0;
    int size = height.size();
    for (int i = 1; i < size - 1; i++) {
        int max_left = 0, max_right = 0;
        for (int j = i; j >= 0; j--) { //Search the left part for max bar size
            max_left = max(max_left, height[j]);
        }
        for (int j = i; j < size; j++) { //Search the right part for max bar size
            max_right = max(max_right, height[j]);
        }
        ans += min(max_left, max_right) - height[i];
    }
    return ans;
}
*/

// Approach 2: Dynamic Programming
/*
int trap(vector<int>& height)
{
	if(height == null)
		return 0;
    int ans = 0;
    int size = height.size();
    vector<int> left_max(size), right_max(size);
    left_max[0] = height[0];
    for (int i = 1; i < size; i++) {
        left_max[i] = max(height[i], left_max[i - 1]);
    }
    right_max[size - 1] = height[size - 1];
    for (int i = size - 2; i >= 0; i--) {
        right_max[i] = max(height[i], right_max[i + 1]);
    }
    for (int i = 1; i < size - 1; i++) {
        ans += min(left_max[i], right_max[i]) - height[i];
    }
    return ans;
}
*/

// Approach 3: Using stacks
/*
int trap(vector<int>& height)
{
    int ans = 0, current = 0;
    stack<int> st;
    while (current < height.size()) {
        while (!st.empty() && height[current] > height[st.top()]) {
            int top = st.top();
            st.pop();
            if (st.empty())
                break;
            int distance = current - st.top() - 1;
            int bounded_height = min(height[current], height[st.top()]) - height[top];
            ans += distance * bounded_height;
        }
        st.push(current++);
    }
    return ans;
}
*/

// Approach 4: Using 2 pointers
/*
int trap(vector<int>& height)
{
    int left = 0, right = height.size() - 1;
    int ans = 0;
    int left_max = 0, right_max = 0;
    while (left < right) {
        if (height[left] < height[right]) {
            height[left] >= left_max ? (left_max = height[left]) : ans += (left_max - height[left]);
            ++left;
        }
        else {
            height[right] >= right_max ? (right_max = height[right]) : ans += (right_max - height[right]);
            --right;
        }
    }
    return ans;
}
*/
