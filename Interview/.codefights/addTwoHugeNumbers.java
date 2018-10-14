/**
 * You're given 2 huge integers represented by linked lists. Each linked list
 * element is a number from 0 to 9999 that represents a number with exactly 4
 * digits. The represented number might have leading zeros. Your task is to add
 * up these huge integers and return the result in the same format.
 * 
 * Example
 * 
 * For a = [9876, 5432, 1999] and b = [1, 8001], the output should be
 * addTwoHugeNumbers(a, b) = [9876, 5434, 0].
 * 
 * Explanation: 987654321999 + 18001 = 987654340000.
 * 
 * For a = [123, 4, 5] and b = [100, 100, 100], the output should be
 * addTwoHugeNumbers(a, b) = [223, 104, 105].
 * 
 * Explanation: 12300040005 + 10001000100 = 22301040105.
 * 
 * Input/Output
 * 
 * [execution time limit] 3 seconds (java)
 * 
 * [input] linkedlist.integer a
 * 
 * The first number, without its leading zeros.
 * 
 * Guaranteed constraints: 0 ≤ a size ≤ 104, 0 ≤ element value ≤ 9999.
 * 
 * [input] linkedlist.integer b
 * 
 * The second number, without its leading zeros.
 * 
 * Guaranteed constraints: 0 ≤ b size ≤ 104, 0 ≤ element value ≤ 9999.
 * 
 * [output] linkedlist.integer
 * 
 * The result of adding a and b together, returned without leading zeros in the
 * same format.
 */

// Definition for singly-linked list:
class ListNode<T> {
  ListNode(T x) {
    value = x;
  }
  T value;
  ListNode<T> next;
}

ListNode<Integer> reverse(ListNode<Integer> node) {
    ListNode<Integer> prev = null;
    ListNode<Integer> current = node;
    ListNode<Integer> next = null;
    while (current != null) {
        next = current.next;
        current.next = prev;
        prev = current;
        current = next;
    }
    node = prev;
    return node;
}

private int calcNextDigit(
    final int carry, final ListNode<Integer> a, final ListNode<Integer> b) {
        final int valA = null != a ? a.value : 0;
        final int valB = null != b ? b.value : 0;
        return valA + valB + carry;
    }

public ListNode addTwoNumbers(
    ListNode<Integer> a, ListNode<Integer> b, boolean removeLeading) {
        ListNode<Integer> rawResult = null;
        ListNode<Integer> lastDigit = null;
        ListNode<Integer> lastPositiveDigit = null;
        int carry = 0;
        
        while (null != a || null != b || carry > 0) {
            int valDigit = calcNextDigit(carry, a, b);
            a = null != a ? a.next : null;
            b = null != b ? b.next : null;
            
            carry = valDigit / 10000;
            valDigit %= 10000;
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
        
        if (removeLeading) {
            ListNode result = rawResult;
            rawResult = rawResult.next;
            while (null != rawResult) {
                if (rawResult == lastPositiveDigit) {
                    rawResult.next = null;
                    break;
                }            
                rawResult = rawResult.next;
            }
            rawResult = result;
        }
        
        return rawResult;
    }

ListNode<Integer> addTwoHugeNumbers(ListNode<Integer> a, ListNode<Integer> b) {
    a = reverse(a);
    b = reverse(b);
    ListNode<Integer> c = addTwoNumbers(a, b, true);
    c = reverse(c);
    return c;
}

public static void main(String[] args) {
    // ...
}
