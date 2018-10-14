private void genAll(
        final int pos,
        final int sum,
        final int target,
        final List<Integer> nums,
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

String combinationSum(int[] a, int target) {
        List<Integer> nums = Arrays.stream(a).boxed().collect(Collectors.toList());
        final Set<Integer> duplRemover = new HashSet<>();
        duplRemover.addAll(nums);
        nums.clear();
        nums.addAll(duplRemover);

        final ArrayList<ArrayList<Integer>> result = new ArrayList<ArrayList<Integer>> ();
        Collections.sort(nums);
        genAll(0, 0, target, nums, new LinkedList<Integer> (), result);
        StringBuilder combinations = new StringBuilder();
        if (result.isEmpty()) combinations.append("Empty");
        for (final ArrayList<Integer> combItem : result) {
            combinations.append('(');        
            for (int i = 0; i < combItem.size(); ++ i) {
                combinations.append(combItem.get(i));      
                if (i + 1 < combItem.size()) combinations.append(' ');  
            }
            combinations.append(')');        
        }
        return combinations.toString();
}
