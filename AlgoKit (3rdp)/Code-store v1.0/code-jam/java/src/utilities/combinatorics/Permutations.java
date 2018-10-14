package utilities.combinatorics;

import java.util.*;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Permutations
{
    public static void main(String args[])
    {
        permuteString("", "String");
    }

    public static void permuteString(String beginningString, String endingString)
    {
        if (endingString.length() <= 1)
            System.out.println(beginningString + endingString);
        else
            for (int i = 0; i < endingString.length(); i++) {
                try {
                    String newString = endingString.substring(0, i)
                                    + endingString.substring(i + 1);

                    permuteString(beginningString + endingString.charAt(i),
                        newString);
                } catch (StringIndexOutOfBoundsException exception) {
                    exception.printStackTrace();
                }
            }
    }

    public static void permuteRecursive(String[] pie)
    {
        String input = "";
        // if there are no arguments, prompt the user
        if (pie.length > 0) {
            // Get all the arguments, gets rid of the need for pesky quotes
            for (String temp : pie)
                input += " " + temp;
        } else {
            System.out.println("Please enter the string: ");
            input = (new Scanner(System.in).nextLine());
        }
        Permutations p = new Permutations();
        p.begin(input);
        System.out.print(factorial(input.length()));
    }

    public static long factorial(int n)
    {
        int result = 1;
        while (n > 1) {
            result *= n;
            n--;
        }
        return result;
    }

    public void begin(final String myString)
    {
        // Number of threads, probably best to set it just over the number of
        // cores you have
        final int THREADS = 4;

        // Create a thread safe queue, add initialize it with a blank string.
        Queue<String> myQueue = new ConcurrentLinkedQueue<String>();
        myQueue.add("");

        // Used to execute the threads
        ExecutorService ex = Executors.newFixedThreadPool(THREADS);

        Runnable myRunnable = new PermutWorker(myQueue, myString);

        // make sure there is enough in the queue so that it doesn't end early
        final int SEED = 2;
        for (int x = 0; x < SEED; x++)
            seedQueue(myRunnable, ex);

        // continue to execute the worker
        while (myQueue.peek() != null) {
            ex.execute(myRunnable);
        }

        // shutdown the executor
        ex.shutdown();

    }

    private void seedQueue(Runnable run, ExecutorService ex)
    {
        ex.execute(run);

        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            // give up / sad panda
            return;
        }
    }

    // Main content of the thread
    private class PermutWorker
        implements Runnable
    {
        private final Queue<String> queue;
        private final String original;

        PermutWorker(Queue<String> queue, final String original)
        {
            this.queue = queue;
            this.original = original;
        }

        @Override
        public void run()
        {

            // get the current state of permutations from the queue
            String current = queue.poll();

            // if we get null then wait for awhile then try again
            if (current == null) {
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    return;
                }

                current = queue.poll();

                // if it is still null then just return
                if (current == null) {
                    return;
                }
            }

            // create List of current characters
            List<Character> currentList = new ArrayList<Character>();
            for (Character c : current.toCharArray())
                currentList.add(c);

            // create list of characters in original
            List<Character> remaining = new ArrayList<Character>();
            for (Character c : original.toCharArray())
                remaining.add(c);

            // remove current from the original to get the remaining
            for (Character c : currentList)
                remaining.remove(c);

            // for every remaining character, add it to current
            // if it is the same length as the original then print it
            // else add it to the queue
            for (Character c : remaining) {
                String result = current + c;
                if (result.length() == original.length()) {
                    // change this as needed
                    System.out.println(result);
                } else {
                    queue.add(result);
                }
            }
        }
    }
}
