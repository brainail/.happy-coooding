boolean areFollowingPatterns(String[] strings, String[] patterns) {
    if (strings.length != patterns.length) {
        return false;
    }
    
    final HashMap<String, Integer> mapStrings = new HashMap<>();
    final HashMap<String, Integer> mapPatterns = new HashMap<>();
    for (int index = 0; index < strings.length; ++ index) {
        Integer stringId = mapStrings.get(strings [index]);            
        if (null == stringId) {
            stringId = mapStrings.size();
            mapStrings.put(strings [index], stringId);
        }
        Integer patternId = mapPatterns.get(patterns [index]);            
        if (null == patternId) {
            patternId = mapPatterns.size();
            mapPatterns.put(patterns [index], patternId);
        }
        if (!stringId.equals(patternId)) {
            return false;
        }
    }
    return true;
}
