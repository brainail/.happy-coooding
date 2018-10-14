package utilities;

import java.util.*;

public class BSTUtils
{
    // invoke with node=starting node, num1,num2=value of nodes
    public BSTNode findLowestCommonAncestor(BSTNode node, int num1, int num2)
    {
        while (node != null) {
            if (node.value > num1 && node.value > num2)
                node = node.left;
            else if (node.value < num1 && node.value < num2)
                node = node.right;
            else
                return node;
        }
        return null;
    }

    /* iterative */
    // each node is examined only once and pushed on the stack only once
    // so still O(n)
    public void preOrder(BSTNode root)
    {
        Stack<BSTNode> al = new Stack<BSTNode>();
        al.add(root);

        while (!al.isEmpty()) {
            BSTNode node = al.pop();
            if (node != null) System.out.println(node.value);
            if (node.right != null) al.push(node.right);
            if (node.left != null) al.push(node.left);
        }
    }

    public void recInOrder(BSTNode start)
    {
        if (start == null) return;
        recInOrder(start.left);
        System.out.println(start.value);
        recInOrder(start.right);
    }

    public void recPostOrder(BSTNode start)
    {
        if (start == null) return;
        recPostOrder(start.left);
        recPostOrder(start.right);
        System.out.println(start.value);
    }

    /* recursive */
    // every node is examined once - O(n)
    public void recPreOrder(BSTNode start)
    {
        if (start == null) return;
        System.out.println(start.value);
        recPreOrder(start.left);
        recPreOrder(start.right);
    }
}

class BSTNode
{
    BSTNode left, right;
    int value;

    public BSTNode(int value)
    {
        this.value = value;
    }
}