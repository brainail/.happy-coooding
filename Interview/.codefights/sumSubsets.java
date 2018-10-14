private void genAll(
        final int pos,
        final int sum,
        final int target,
        final int[] nums,
        final LinkedList<Integer> buff,
        final Set<ArrayList<Integer>> result) {
        
        if (sum > target) {
            return;
        }
        
        if (sum == target) {
            final ArrayList<Integer> comb = new ArrayList<> (buff.size());
            for (final Integer item : buff) {
                comb.add(item);
            }
            result.add(comb);
            return;
        }
        
        if (pos >= nums.length) {
            return;
        }
        
        if (sum + nums [pos] > target) {
            return;
        }

        buff.addLast(nums [pos]);
        genAll(pos + 1, sum + nums [pos], target, nums, buff, result);
        buff.removeLast();

        genAll(pos + 1, sum, target, nums, buff, result);
    }

class ListComparator implements Comparator<int[]> {
  @Override
  public int compare(int[] o1, int[] o2) {
    for (int i = 0; i < Math.min(o1.length, o2.length); i++) {
      int c = o1 [i] - o2 [i];
      if (c != 0) {
        return c < 0 ? -1 : +1;
      }
    }
    return Integer.compare(o1.length, o2.length);
  }

}

int[][] sumSubsets(int[] arr, int num) {
    final Set<ArrayList<Integer>> result 
        = new HashSet<ArrayList<Integer>> ();
    genAll(0, 0, num, arr, new LinkedList<Integer> (), result);
    int [][] resultArr = new int [result.size()][];
    int i = 0;
    for (final ArrayList<Integer> rrr : result) {
        resultArr [i] = new int [rrr.size()];
        for (int j = 0; j < rrr.size(); ++ j) {
            resultArr [i][j] = rrr.get(j);
        }
        ++ i;
    }
    Arrays.sort(resultArr, new ListComparator());
    return resultArr;
}
