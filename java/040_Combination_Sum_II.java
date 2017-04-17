// Solution one, backtracking
public class Solution {
    public List<List<Integer>> combinationSum2(int[] candidates, int target) {
        List<List<Integer>> reval = new ArrayList<List<Integer>>();
        Arrays.sort(candidates);
        checkWithBacktracking(reval, new ArrayList<Integer>(), candidates, 0, target);
        return reval;
    }

    private void checkWithBacktracking(List<List<Integer>> reval,
                                       ArrayList<Integer> temp,
                                       int[] candidates,
                                       int start,
                                       int target) {
        if (target == 0 && !temp.isEmpty()) {
            reval.add(new ArrayList<Integer>(temp));
        } else {
            for (int i = start; i < candidates.length && target >= candidates[i]; ++i) {
                if (i > start && candidates[i] == candidates[i-1]) continue; // Avoid duplicates
                temp.add(candidates[i]);
                checkWithBacktracking(reval, temp, candidates, i + 1, target - candidates[i]);
                temp.remove(temp.size() - 1);
            }
        }
    }
}

