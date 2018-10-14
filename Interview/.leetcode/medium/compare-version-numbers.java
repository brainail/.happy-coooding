/**
 * Compare two version numbers version1 and version2. If version1 > version2
 * return 1; if version1 < version2 return -1;otherwise return 0.
 * 
 * You may assume that the version strings are non-empty and contain only digits
 * and the . character. The . character does not represent a decimal point and
 * is used to separate number sequences. For instance, 2.5 is not "two and a
 * half" or "half way to version three", it is the fifth second-level revision
 * of the second first-level revision.
 * 
 * Example 1:
 * 
 * Input: version1 = "0.1", version2 = "1.1" Output: -1 Example 2:
 * 
 * Input: version1 = "1.0.1", version2 = "1" Output: 1 Example 3:
 * 
 * Input: version1 = "7.5.2.4", version2 = "7.5.3" Output: -1
 */
class Solution {
    public int compareVersion(String version1, String version2) {
        String[] v1 = version1.split("\\.");
        String[] v2 = version2.split("\\.");
        for (int i = 0, size = Math.max(v1.length, v2.length); i < size; ++i) {
            String vd1 = i < v1.length ? v1[i] : "0";
            String vd2 = i < v2.length ? v2[i] : "0";
            int compareResult = Long.valueOf(vd1).compareTo(Long.valueOf(vd2));
            if (compareResult != 0)
                return compareResult < 0 ? -1 : (compareResult > 0 ? 1 : 0);
        }
        return 0;
    }
}
