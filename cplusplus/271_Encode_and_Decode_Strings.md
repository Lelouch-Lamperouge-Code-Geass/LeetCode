Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings. Machine 1 (sender) has the function:

```
string encode(vector<string> strs) {
  // ... your code
  return encoded_string;
}
```

Machine 2 (receiver) has the function:

```
vector<string> decode(string s) {
  //... your code
  return strs;
}
```

So Machine 1 does:

```
string encoded_string = encode(strs);
```

and Machine 2 does:

```
vector<string> strs2 = decode(encoded_string);
```

strs2 in Machine 2 should be the same as strs in Machine 1.

Implement the encode and decode methods.  

Note:
* The string may contain any possible characters out of 256 valid ascii characters. Your algorithm should be generalized enough to work on any possible characters.  
* Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.  
* Do not rely on any library method such as eval or serialize methods. You should implement your own encode/decode algorithm.  

# Solution

The rule is, for each str in strs, encode it as <length> + '@' + str.  

What if str itself contains @ ?  

It does not matter because, for each encoded string, decode only looks for the first @ char and then read the whole string as a whole: even though the string has @ char in it, it is considered as a part of the string as decoder knows the length of the string.


```cpp
class Codec {
public:

    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        std::ostringstream oss;
        for (const std::string &str : strs) {
            oss << str.size() << '@' << str;
        }
        return oss.str();
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> reval;
        std::size_t pos(0), s_size(s.size());
        
        while (pos < s_size) {
            std::size_t at_sign = s.find_first_of('@', pos);
            std::size_t str_len = std::stoi(s.substr(pos, at_sign - pos));
            reval.emplace_back(s.substr(at_sign + 1, str_len));
            pos = at_sign + str_len + 1;
        }
        
        return reval;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));
```



