class FileItem {
    final int level;
    final String name;
    final int pathLength;
    
    FileItem(final String name, final int level, final int parentPathLength) {
        this.name = name;
        this.level = level;
        this.pathLength = parentPathLength + name.length();
    }
}

int longestPath(String fileSystem) {
    Stack<FileItem> files = new Stack<>();
    int i = 0;
    int maxPathLength = 0;
    while (i < fileSystem.length()) {
        int level = 0;
        int t = i;
        while ('\t' == fileSystem.charAt(t) 
               || '\f' == fileSystem.charAt(t)) {
            if (fileSystem.charAt(t) != '\f') {
                ++ level;
            }
            ++ t;
        }
        i = t;
        while (t < fileSystem.length() 
               && '\t' != fileSystem.charAt(t) 
               && '\f' != fileSystem.charAt(t)) {
            ++ t;
        }
        final String name = fileSystem.substring(i, t);
        i = t;
        while (!files.empty() && level <= files.peek().level) {
            files.pop();
        }
        int parentPathLength = files.empty() ? 0 : files.peek().pathLength;
        files.push(new FileItem(name, level, parentPathLength));
        if (name.contains(".")) {
            maxPathLength = Math.max(maxPathLength, files.peek().pathLength + files.peek().level);
        }
    }
    return maxPathLength;
}
