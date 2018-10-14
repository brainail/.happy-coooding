package utilities.graph.struct;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * A generic bag or multiset, implemented using a linked list
 * 
 * The <tt>Bag</tt> class represents a bag (or multiset) of
 * generic items. It supports insertion and iterating over the
 * items in arbitrary order.
 * <p>
 * The <em>add</em>, <em>isEmpty</em>, and <em>size</em> operation take constant
 * time. Iteration takes time proportional to the number of items.
 * <p>
 */
public class Bag<Item>
    implements Iterable<Item>
{
    private int N; // number of elements in bag
    private Node first; // beginning of bag

    // helper linked list class
    private class Node
    {
        private Item item;
        private Node next;
    }

    /**
     * Create an empty stack.
     */
    public Bag()
    {
        first = null;
        N = 0;
    }

    /**
     * Is the BAG empty?
     */
    public boolean isEmpty()
    {
        return first == null;
    }

    /**
     * Return the number of items in the bag.
     */
    public int size()
    {
        return N;
    }

    /**
     * Add the item to the bag.
     */
    public void add(Item item)
    {
        Node oldfirst = first;
        first = new Node();
        first.item = item;
        first.next = oldfirst;
        N++;
    }

    /**
     * Return an iterator that iterates over the items in the bag.
     */
    @Override
    public Iterator<Item> iterator()
    {
        return new ListIterator();
    }

    /**
     * an iterator, doesn't implement remove() since it's optional
     */
    private class ListIterator
        implements Iterator<Item>
    {
        private Node current = first;

        @Override
        public boolean hasNext()
        {
            return current != null;
        }

        @Override
        public void remove()
        {
            throw new UnsupportedOperationException();
        }

        @Override
        public Item next()
        {
            if (!hasNext()) throw new NoSuchElementException();
            Item item = current.item;
            current = current.next;
            return item;
        }
    }

}
