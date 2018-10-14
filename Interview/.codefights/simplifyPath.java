String toString(final List<String> list) {
    final StringBuilder all = new StringBuilder();
    for (final String part : list) {
        all.append(part);
    }
    return all.toString();
}

String simplifyPath(String path) {
    final LinkedList<String> files = new LinkedList<>();
    files.addLast("/"); // define root
    path = path + "/";
    
    for (int i = 0; i < path.length(); ++ i) {
        // System.out.println("Files: " + toString(files));
        
        // try to go deeper
        if ('/' == path.charAt(i)) {
            if (files.isEmpty()) { // root
                files.addLast("/");
                continue;
            }
            if (files.getLast().equals("/")) { // current to the current
                continue;
            }
            if (files.getLast().equals(".")) { // mark current
                files.removeLast();
                continue;
            }            
            if (files.getLast().equals("..")) { // mark parent
                files.removeLast();
                if (files.size() > 1) {
                    files.removeLast();
                    files.removeLast(); // go to parent
                }
                continue;
            }
            files.addLast("/"); // go deeper
            continue;
        }
        
        // mark
        if ('.' == path.charAt(i)) {
            if (files.getLast().equals(".")) {
                files.removeLast();
                files.addLast(".."); // pending parent mark
                continue;
            }
            files.addLast("."); // pending mark
            continue;
        }
        
        // folder's part
        if (!files.isEmpty() && files.getLast().equals("/")) {
            files.addLast(String.valueOf(path.charAt(i)));
            continue;
        }
        String folder = files.getLast();
        files.removeLast();
        files.addLast(folder + path.charAt(i)); // continue folder
    }
    
    if (files.size() > 1 && files.getLast().equals("/")) {
        files.removeLast(); // redundant separator
    }
    
    return toString(files); // merge all parts
}
