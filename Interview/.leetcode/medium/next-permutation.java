/**
 * Implement next permutation, which rearranges numbers into the
 * lexicographically next greater permutation of numbers.
 * 
 * If such arrangement is not possible, it must rearrange it as the lowest
 * possible order (ie, sorted in ascending order).
 * 
 * The replacement must be in-place and use only constant extra memory.
 * 
 * Here are some examples. Inputs are in the left-hand column and its
 * corresponding outputs are in the right-hand column.
 * 
 * 1,2,3 → 1,3,2 3,2,1 → 1,2,3 1,1,5 → 1,5,1
 */
class Solution {
  public void nextPermutation(int[] num) {  
    int downIndex = num.length - 2;
    while (downIndex >= 0 && num[downIndex] >= num[downIndex + 1]) -- downIndex;
    if (downIndex < 0) {
      reverse(num, 0, num.length - 1);
      return;
    }
    for (int i = num.length - 1; ; --i) 
      if (num[i] > num[downIndex]) {
        swap(num, i, downIndex); 
        break;
      }      
    reverse(num, downIndex + 1, num.length - 1);
  }
  
  private void reverse(int[] items, int i, int j) {
    for (; i < j; ++ i, -- j) {
      swap(items, i, j);
    }
  }

  private void swap(int[] items, int i, int j) {
    int buff = items[i]; 
    items[i] = items[j];
    items[j] = buff;
  }
}


