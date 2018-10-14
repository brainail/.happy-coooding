/**
 * A linked list is given such that each node contains an additional random
 * pointer which could point to any node in the list or null.
 * 
 * Return a deep copy of the list.
 */
public class Solution {
    IdentityHashMap<RandomListNode, RandomListNode> memo = new IdentityHashMap<RandomListNode, RandomListNode>();

    public RandomListNode copyRandomList(RandomListNode head) {
        if (head == null)
            return null;
        if (memo.containsKey(head))
            return memo.get(head); // memo

        RandomListNode node = new RandomListNode(head.label);
        memo.put(head, node);
        node.next = copyRandomList(head.next);
        node.random = copyRandomList(head.random);
        return node;
    }
}

// #region no extra space
public class Solution {
    public RandomListNode copyRandomList(RandomListNode head) {
        if (head == null) return null;

        // Creating of A->A'->B->B'->C->C'
        RandomListNode ptr = head;
        while (ptr != null) {
            RandomListNode newNode = new RandomListNode(ptr.label);
            newNode.next = ptr.next;
            ptr.next = newNode;
            ptr = newNode.next;
        }

        // copy randoms
        ptr = head;
        while (ptr != null) {
            ptr.next.random = (ptr.random != null) ? ptr.random.next : null;
            ptr = ptr.next.next;
        }

        // split A->A'->B->B'->C->C' to A->B->C and A'->B'->C'
        RandomListNode ptr_old_list = head; // A->B->C
        RandomListNode ptr_new_list = head.next; // A'->B'->C'
        RandomListNode head_old = head.next;
        while (ptr_old_list != null) {
            ptr_old_list.next = ptr_old_list.next.next;
            ptr_new_list.next = (ptr_new_list.next != null) ? ptr_new_list.next.next : null;
            ptr_old_list = ptr_old_list.next;
            ptr_new_list = ptr_new_list.next;
        }
        return head_old;
    }
}
// #endregion