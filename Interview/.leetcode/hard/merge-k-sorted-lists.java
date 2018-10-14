/**
 * Merge k sorted linked lists and return it as one sorted list. Analyze and
 * describe its complexity.
 * 
 * Example:
 * 
 * Input: [ 1->4->5, 1->3->4, 2->6 ] Output: 1->1->2->3->4->4->5->6
 */
class Solution {
    public ListNode mergeKLists(ListNode[] lists) {
        int n = lists.length;
        if (n == 0)
            return null;
        while (n > 1) {
            int i = 0, j = n - 1;
            while (i < j) {
                ListNode merge = new ListNode(0);
                ListNode root = merge;
                while (lists[i] != null || lists[j] != null) {
                    if (null == lists[j] || (null != lists[i] && lists[i].val < lists[j].val)) {
                        merge.next = new ListNode(lists[i].val);
                        lists[i] = lists[i].next;
                    } else {
                        merge.next = new ListNode(lists[j].val);
                        lists[j] = lists[j].next;
                    }
                    merge = merge.next;
                }
                lists[i] = root.next;
                ++i;
                --j;
            }
            n = j + 1;
        }
        return lists[0];
    }
}
