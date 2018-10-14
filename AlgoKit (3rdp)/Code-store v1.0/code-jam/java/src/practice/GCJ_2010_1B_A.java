package practice;

import java.util.*;

public class GCJ_2010_1B_A
{
    private class Tree
    {
        String name;
        ArrayList<Tree> children;

        public Tree(String name)
        {
            this.name = name;
            children = new ArrayList<Tree>();
        }
    }

    public void run()
    {
        Scanner sc = new Scanner(System.in);
        HashMap<String, Tree> dirTree = new HashMap<String, Tree>();
        int T = sc.nextInt();
        for (int cc = 0; cc < T; cc++) {
            dirTree.clear();
            int N = sc.nextInt();
            int M = sc.nextInt();
            for (int i = 0; i < N; i++) {
                String path = sc.next();
                String[] dirs = path.substring(1).split("/");
                if (!dirTree.containsKey(dirs[0])) {
                    dirTree.put(dirs[0], new Tree(dirs[0]));
                }
                Tree t = dirTree.get(dirs[0]);
                for (int j = 1; j < dirs.length; j++) {
                    boolean found = false;
                    for (Tree c : t.children) {
                        if (c.name.equals(dirs[j])) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        t.children.add(new Tree(dirs[j]));
                    }

                    for (Tree c : t.children) {
                        if (c.name.equals(dirs[j])) {
                            t = c;
                            break;
                        }
                    }

                }
            }

            int numMkdirs = 0;
            for (int i = 0; i < M; i++) {
                String path = sc.next();
                String[] dirs = path.substring(1).split("/");
                Tree t = dirTree.get(dirs[0]);
                if (t == null) {
                    numMkdirs += dirs.length;

                    dirTree.put(dirs[0], new Tree(dirs[0]));
                    t = dirTree.get(dirs[0]);
                    for (int j = 1; j < dirs.length; j++) {
                        boolean found = false;
                        for (Tree c : t.children) {
                            if (c.name.equals(dirs[j])) {
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            t.children.add(new Tree(dirs[j]));
                        }

                        for (Tree c : t.children) {
                            if (c.name.equals(dirs[j])) {
                                t = c;
                                break;
                            }
                        }
                    }
                } else {
                    for (int j = 1; j < dirs.length; j++) {
                        boolean found = false;
                        for (Tree c : t.children) {
                            if (c.name.equals(dirs[j])) {
                                found = true;
                                break;
                            }
                        }

                        if (!found) {
                            t.children.add(new Tree(dirs[j]));
                            numMkdirs++;
                        }

                        for (Tree c : t.children) {
                            if (c.name.equals(dirs[j])) {
                                t = c;
                                break;
                            }
                        }

                    }
                }
            }
            System.out.println(String.format("Case #%d: %d", cc + 1, numMkdirs));
        }
    }

    public static void main(String[] args)
    {
        new GCJ_2010_1B_A().run();
    }
}
