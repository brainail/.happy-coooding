/**
 * Definition for singly-linked list.
 * class ListNode {
 *     public int val;
 *     public ListNode next;
 *     ListNode(int x) { val = x; next = null; }
 * }
 */
public class Solution {
    private int calcNextDigit(final int carry, final ListNode a, final ListNode b) {
        final int valA = null != a ? a.val : 0;
        final int valB = null != b ? b.val : 0;
        return valA + valB + carry;
    }
    
    public ListNode addTwoNumbers(ListNode a, ListNode b) {
        ListNode rawResult = null;
        ListNode lastDigit = null;
        ListNode lastPositiveDigit = null;
        int carry = 0;
        
        while (null != a || null != b || carry > 0) {
            int valDigit = calcNextDigit(carry, a, b);
            a = null != a ? a.next : null;
            b = null != b ? b.next : null;
            
            carry = valDigit / 10;
            valDigit %= 10;
            final ListNode digit = new ListNode(valDigit);
            if (valDigit > 0) {
                lastPositiveDigit = digit;
            }
            
            if (null == rawResult) {
                rawResult = digit;
                lastDigit = digit;
            } else {
                lastDigit.next = digit;
                lastDigit = digit;
            }
        }
        
        rawResult = null != rawResult ? rawResult : new ListNode(0);
        ListNode result = rawResult;
        rawResult = rawResult.next;
        while (null != rawResult) {
            if (rawResult == lastPositiveDigit) {
                rawResult.next = null;
                break;
            }
            
            rawResult = rawResult.next;
        }
        
        return result;
    }
}
