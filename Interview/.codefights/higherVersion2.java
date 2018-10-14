int higherVersion2(String ver1, String ver2) {
    String [] verA = ver1.split("\\.");
    String [] verB = ver2.split("\\.");
    for (int i = 0; i < verA.length; ++ i) {
        if (Integer.valueOf(verA [i]) < Integer.valueOf(verB [i])) {
            return -1;
        } else if (Integer.valueOf(verA [i]) > Integer.valueOf(verB [i])) {
            return +1;
        }
    }
    return 0;
}
