/**
 * You are given two non-empty linked lists representing two non-negative
 * integers. The digits are stored in reverse order and each of their nodes
 * contain a single digit. Add the two numbers and return it as a linked list.
 * 
 * You may assume the two numbers do not contain any leading zero, except the
 * number 0 itself.
 * 
 * Example:
 * 
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4) Output: 7 -> 0 -> 8 Explanation: 342 +
 * 465 = 807.
 */
class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        final int base = 10;
        ListNode ret = new ListNode(0);
        ListNode cur = ret;
        int carry = 0;
        while (l1 != null || l2 != null || carry != 0) {
            int a = l1 != null ? l1.val : 0;
            int b = l2 != null ? l2.val : 0;
            int c = a + b + carry;
            cur.next = new ListNode(c % base);
            cur = cur.next;
            carry = c / base;
            l1 = null != l1 ? l1.next : l1;
            l2 = null != l2 ? l2.next : l2;
        }
        return ret.next;
    }
}
