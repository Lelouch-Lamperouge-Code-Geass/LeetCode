There is a fence with n posts, each post can be painted with one of the k colors.

You have to paint all the posts such that __no more than two adjacent fence posts have the same color__.

Return the total number of ways you can paint the fence.

Note:  
n and k are non-negative integers.


# Solution

Let's use A[i] to represent the total numbers of painting options we have for i-th fence.
Then we have two scenarios:

1. Paint the same color as i - 1 , the amount is diff_color[i-1].
2. Paint a different color from i - 1, the amount is (diff_color[i-1] + same_color[i-1]) * (k - 1)

So the total options is A[i] = diff_color[i] +　same_color[i] = diff_color[i-1] + (diff_color[i-1] + same_color[i-1]) * (k - 1).

```cpp
int numWays(int n, int k) {
  if (n <= 0 || k <= 0) return 0;
  if (n == 1) return k;

  vector<int> same_color = {0, 0, k};
  vector<int> diff_color = {0, k, k * (k-1)};
  same_color.insert(same_color.end(), n - 3, 0);
  diff_color.insert(diff_color.end(), n - 3, 0);

  for (int i = 3; i <= n; ++i) {
    int temp = same_color[i - 1];
    same_color[i] = diff_color[i-1];
    diff_color[i] = (diff_color[i-1] + same_color[i-1]) * (k - 1);
  }

  return diff_color[n] + same_color[n];
}
```


We can optimize above solution's space complexity to be O(1).

We divided it into two cases.

1. the last two posts have the same color, the number of ways to paint in this case is sameColorCounts.

2. the last two posts have different colors, and the number of ways in this case is diffColorCounts.

__The reason why we have these two cases is that we can easily compute both of them, and that is all I do.__ When adding a new post, we can use the same color as the last one (if allowed) or different color. If we use different color, there're k-1 options, and the outcomes shoule belong to the diffColorCounts category. If we use same color, there's only one option, and we can only do this when the last two have different colors (which is the diffColorCounts). There we have our induction step.

Here is an example, let's say we have 3 posts and 3 colors. The first two posts we have 9 ways to do them, (1,1), (1,2), (1,3), (2,1), (2,2), (2,3), (3,1), (3,2), (3,3). Now we know that ```diffColorCounts = 6;```, And ```sameColorCounts = 3;```.

Now for the third post, we can compute these two variables like this:

If we use different colors than the last one (the second one), these ways can be added into diffColorCounts, so if the last one is 3, we can use 1 or 2, if it's 1, we can use 2 or 3, etc. Apparently there are ```(diffColorCounts + sameColorCounts) * (k-1)``` possible ways.

If we use the same color as the last one, we would trigger a violation in these three cases (1,1,1), (2,2,2) and (3,3,3). This is because they already used the same color for the last two posts. So is there a count that rules out these kind of cases? YES, the diffColorCounts. So in cases within diffColorCounts, we can use the same color as the last one without worrying about triggering the violation. And now as we append a same-color post to them, the former diffColorCounts becomes the current sameColorCounts.

Then we can keep going until we reach the n. And finally just sum up these two variables as result.


```java
public int numWays(int n, int k) {
    if(n == 0) return 0;
    else if(n == 1) return k;
    int diffColorCounts = k*(k-1); // fence 1 have k ways, fence 2 have (k-1)
    int sameColorCounts = k; // fence 1 have k ways, fence 2 use the same color
    for(int i=3; i<=n; i++) {
        int temp = diffColorCounts;
        diffColorCounts = (diffColorCounts + sameColorCounts) * (k-1); // Use different color
        sameColorCounts = temp; // Use same color
    }
    return diffColorCounts + sameColorCounts;
}
```








