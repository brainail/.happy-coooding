/**
 * Definition for singly-linked list.
 * class ListNode {
 *     public int val;
 *     public ListNode next;
 *     ListNode(int x) { val = x; next = null; }
 * }
 */
public class Solution {
    public ListNode mergeKLists(ArrayList<ListNode> arr) {
        int n = arr.size();
        if (0 == n) {
            return null;
        }
        
        while (n > 1) {
            for (int first = 0; n - first - 1 > first; ++ first) {
                ListNode headOfFirst = arr.get(first);
                ListNode headOfSecond = arr.get(n - first - 1);
                
                if (null == headOfFirst) {
                    arr.set(first, headOfSecond);
                    continue;
                } else if (null == headOfSecond) {
                    continue;
                }
                
                arr.set(first, null);
                ListNode rootNode = null;
                
                while (true) {
                    if (null == headOfFirst) {
                        arr.get(first).next = headOfSecond;
                        break;
                    } else if (null == headOfSecond) {
                        arr.get(first).next = headOfFirst;
                        break;
                    }
                    
                    ListNode nextNode;
                    if (headOfFirst.val <= headOfSecond.val) {
                        nextNode = headOfFirst;
                        headOfFirst = headOfFirst.next;
                    } else {
                        nextNode = headOfSecond;
                        headOfSecond = headOfSecond.next;
                    }
                    
                    if (null != arr.get(first)) {
                        arr.get(first).next = nextNode;
                    } else {
                        rootNode = nextNode;
                    }
                    arr.set(first, nextNode);
                }
                
                arr.set(first, rootNode);
            }
            
            n = (n + 1) >> 1;
        }
        
        return arr.get(0);
    }
}
