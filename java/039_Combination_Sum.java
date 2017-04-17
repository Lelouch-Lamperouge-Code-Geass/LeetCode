public class Solution {
    public List<List<Integer>> combinationSum(int[] candidates, int target) {
        List<List<Integer>> reval = new ArrayList<List<Integer>>();
        Arrays.sort(candidates);
        checkWithBacktracking(reval, new ArrayList<Integer>(), candidates, target, 0);
        return reval;
    }

    private void checkWithBacktracking(List<List<Integer>> reval,
                                       ArrayList<Integer> temp,
                                       int[] candidates,
                                       int target,
                                       int start) {
        if (target == 0 && !temp.isEmpty()) {
            reval.add(new ArrayList<Integer>(temp));
        } else {
            for (int i = start; i < candidates.length && target >= candidates[i]; ++i) {
                temp.add(candidates[i]);
                checkWithBacktracking(reval, temp, candidates, target - candidates[i], i);
                temp.remove(temp.size()-1); // Revert back
            }
        }
    }
}
