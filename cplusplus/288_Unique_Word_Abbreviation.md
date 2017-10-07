An abbreviation of a word follows the form <first letter><number><last letter>. Below are some examples of word abbreviations:
```
a) it                      --> it    (no abbreviation)

     1
b) d|o|g                   --> d1g

              1    1  1
     1---5----0----5--8
c) i|nternationalizatio|n  --> i18n

              1
     1---5----0
d) l|ocalizatio|n          --> l10n
```

Assume you have a dictionary and given a word, find whether its abbreviation is unique in the dictionary. A word's abbreviation is unique if no other word from the dictionary has the same abbreviation.
Example: 

```
Given dictionary = [ "deer", "door", "cake", "card" ]

isUnique("dear") -> false
isUnique("cart") -> true
isUnique("cane") -> false
isUnique("make") -> true
```

The description (A word's abbreviation is unique if no other word from the dictionary has the same abbreviation) 
is clear however a bit twisting. It took me a few "Wrong Answer"s to finally understand what it's asking for.
We are trying to search for a word in a dictionary. If this word (also this word’s abbreviation) 
is not in the dictionary OR this word and only it’s abbreviation in the dictionary. 
We call a word’s abbreviation unique.
EX:
```
1) [“dog”]; isUnique(“dig”);   
//False, because “dig” has the same abbreviation with “dog" and “dog” is already in the dictionary. It’s not unique.

2) [“dog”, “dog"]; isUnique(“dog”);  
//True, because “dog” is the only word that has “d1g” abbreviation.

3) [“dog”, “dig”]; isUnique(“dog”);   
//False, because if we have more than one word match to the same abbreviation, this abbreviation will never be unique.
```

# Solution

思路: 将字典中的单词按照缩写为key, 将具有相同缩写的放进一个hash表中. 当判断一个给定单词是否唯一的时候,可以先计算出其缩写, 然后去hash表中查, 如果hash表中这个缩写对应几个单词, 那么肯定是不唯一的, 如果只对应一个单词, 则看这个单词是不是我们要判断的单词, 如果是的话,则唯一, 否则不唯一. 如果这个缩写在hash表中没有对应单词, 那么肯定唯一了.

```cpp
class ValidWordAbbr {  
public:  
    ValidWordAbbr(vector<string> &dictionary) {  
        for (string& d : dictionary) {  
            int n = d.length();  
            string abbr = d[0] + to_string(n) + d[n - 1];  
            mp[abbr].insert(d);  
        }  
    }  
  
    bool isUnique(string word) {  
        int n = word.length();  
        string abbr = word[0] + to_string(n) + word[n - 1];  
        return mp[abbr].count(word) == mp[abbr].size();   // If mp[abbr].size() > 1 or mp[abbr].count(word) == 0, will return false. 
    }  
private:  
    unordered_map<string, unordered_set<string>> mp;  
};   
```
