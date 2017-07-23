You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -, you and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a move and therefore the other person will be the winner.

Write a function to determine if the starting player can guarantee a win.

For example, given s = "++++", return true. The starting player can guarantee a win by flipping the middle "++" to become "+--+".

# Solution

### Solution one : Backtracking

The idea is try to replace every "++" in the current string s to "--" and see if the opponent can win or not, if the opponent cannot win, great, we win!

For the time complexity, here is what I thought, let's say the length of the input string s is n, there are at most n - 1 ways to replace "++" to "--" (imagine s is all "+++..."), once we replace one "++", there are at most (n - 2) - 1 ways to do the replacement, it's a little bit like solving the N-Queens problem, the time complexity is (n - 1) x (n - 3) x (n - 5) x ..., so it's O(n!!), double factorial.

```java
public boolean canWin(String s) {
  if (s == null || s.length() < 2) {
    return false;
  }
    
  for (int i = 0; i < s.length() - 1; i++) {
    if (s.startsWith("++", i)) {
      String t = s.substring(0, i) + "--" + s.substring(i + 2);
      
      if (!canWin(t)) {
        return true;
      }
    }
  }
    
  return false;
}
```

If we use HashMap to memorize both win string & lose string, we can further reduce time from 208ms to 18ms:

```java
public boolean canWin(String s) {
    if(s == null || s.length() < 2) return false;
    Map<String, Boolean> map = new HashMap<>();
    return canWin(s, map);
}

public boolean canWin(String s, Map<String, Boolean> map){
    if(map.containsKey(s)) return map.get(s);
    for(int i = 0; i < s.length() - 1; i++) {
        if(s.charAt(i) == '+' && s.charAt(i + 1) == '+') {
            String opponent = s.substring(0, i) + "--" + s.substring(i + 2);
            if(!canWin(opponent, map)) {
                map.put(s, true);
                return true;
            }
        }
    }
    map.put(s, false);
    return false;
}
```
