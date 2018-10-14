import java.util.*;
import java.util.Map.Entry;

public class GCJ_2012_1B_C
{
    public <T> Set<Set<T>> powerSet(Set<T> originalSet)
    {
        Set<Set<T>> sets = new HashSet<Set<T>>();
        if (originalSet.isEmpty()) {
            sets.add(new HashSet<T>());
            return sets;
        }
        List<T> list = new ArrayList<T>(originalSet);
        T head = list.get(0);
        Set<T> rest = new HashSet<T>(list.subList(1, list.size()));
        for (Set<T> set : powerSet(rest)) {
            Set<T> newSet = new HashSet<T>();
            newSet.add(head);
            newSet.addAll(set);
            sets.add(newSet);
            sets.add(set);
        }
        return sets;
    }

    public void run()
    {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for (int cc = 0; cc < T; cc++) {
            int N = sc.nextInt();

            Set<Integer> original = new HashSet<Integer>();
            for (int i = 0; i < N; i++) {
                original.add(sc.nextInt());
            }

            HashMap<Set<Integer>, Integer> lookup = new HashMap<Set<Integer>, Integer>();
            Set<Set<Integer>> powerset = powerSet(original);
            for (Set<Integer> s : powerset) {
                int sum = 0;
                for (Integer i : s) {
                    sum += i;
                }
                lookup.put(s, sum);
            }

            System.out.println("Case #" + (cc + 1));
            boolean found = false;
            Set<Integer> subset1 = new HashSet<Integer>();
            Set<Integer> subset2 = new HashSet<Integer>();
            for (Entry<Set<Integer>, Integer> entry : lookup.entrySet()) {
                Set<Integer> key = entry.getKey();
                Integer value = entry.getValue();

                if (key.size() <= 0) continue;
                // System.out.println(entry.getKey().size());

                for (Entry<Set<Integer>, Integer> entry2 : lookup.entrySet()) {
                    if (!entry2.getKey().equals(key)
                                    && entry2.getValue().equals(value)) {
                        found = true;
                        for (Integer i : key) {
                            System.out.print(i + " ");
                        }
                        System.out.println();
                        for (Integer i : entry2.getKey()) {
                            System.out.print(i + " ");
                        }

                        break;
                    }
                }
                if (found) break;
            }
            if (!found) {
                System.out.println("Impossible");
            }
        }
    }

    public static void main(String[] args)
    {
        new GCJ_2012_1B_C().run();
    }
}
