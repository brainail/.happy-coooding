public class Solution {
    private void genAll(
        final int pos,
        final int sum,
        final int target,
        final ArrayList<Integer> nums,
        final LinkedList<Integer> buff,
        final ArrayList<ArrayList<Integer>> result) {
        
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
        
        if (pos >= nums.size()) {
            return;
        }
        
        if (sum + nums.get(pos) > target) {
            return;
        }

        buff.addLast(nums.get(pos));
        genAll(pos, sum + nums.get(pos), target, nums, buff, result);
        buff.removeLast();

        genAll(pos + 1, sum, target, nums, buff, result);
    }
    
    public ArrayList<ArrayList<Integer>> combinationSum(ArrayList<Integer> nums, int target) {
        final Set<Integer> duplRemover = new HashSet<>();
        duplRemover.addAll(nums);
        nums.clear();
        nums.addAll(duplRemover);

        final ArrayList<ArrayList<Integer>> result = new ArrayList<ArrayList<Integer>> ();
        Collections.sort(nums);
        genAll(0, 0, target, nums, new LinkedList<Integer> (), result);
        return result;
    }
}
