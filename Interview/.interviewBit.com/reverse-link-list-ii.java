/**
 * Definition for singly-linked list.
 * class ListNode {
 *     public int val;
 *     public ListNode next;
 *     ListNode(int x) { val = x; next = null; }
 * }
 */
public class Solution {
    public ListNode reverseBetween(ListNode list, int m, int n) {
        if (null == list) {
            return null;
        }
        
        ListNode root = new ListNode(-1); 
        root.next = list;
        
        ListNode prev = root; 
        for (int i = 0; i < m - 1; ++ i) {
            prev = prev.next;
        }
    
        ListNode from = prev.next; 
        ListNode current = from.next; 
    
        for (int i = 0; i < n - m; ++ i) {
            from.next = current.next; // move `from` to the end step-by-step
            current.next = prev.next; // reverse single arrow `->` -> `<-`
            prev.next = current; // move `last` to the begining
            current = from.next; // current = current.next
        }
    
        return root.next;
    }
}
