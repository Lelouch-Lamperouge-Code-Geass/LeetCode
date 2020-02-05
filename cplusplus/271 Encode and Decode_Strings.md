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

The rule is, for each str in strs, encode it as `<length> + '@' + str`.  

What if str itself contains @ ?  

It does not matter because, for each encoded string, decode only looks for the first @ char and then read the whole string as a whole: even though the string has @ char in it, it is considered as a part of the string as decoder knows the length of the string.


##### Encoding

```
""  => "0@"
"  " => "2@  "
"A@@@AA" => "6@A@@@AA"
```

##### Decoding

```
"0@"  =>  ""  
"2@  " => "  "
"6@A@@@AA" => "A@@@AA" 
```


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

# Knowledge

__Encoding__ is the process of converting the data or a given sequence of characters, symbols, alphabets etc., into a specified format, for the secured transmission of data. __Decoding__ is the reverse process of encoding which is to extract the information from the converted format.


### Encoding

Encoding is the process of converting data into a format required for a number of information processing needs, including:

* Program compiling and execution
* Data transmission, storage and compression/decompression
* Application data processing, such as file conversion

Encoding can have two meanings:

* In computer technology, encoding is the process of applying a specific code, such as letters, symbols and numbers, to data for conversion into an equivalent cipher.
* In electronics, encoding refers to analog to digital conversion.


Techopedia explains Encoding

Encoding involves the use of a code to change original data into a form that can be used by an external process. 

The type of code used for converting characters is known as American Standard Code for Information Interchange (ASCII), the most commonly used encoding scheme for files that contain text. ASCII contains printable and nonprintable characters that represent uppercase and lowercase letters, symbols, punctuation marks and numbers. A unique number is assigned to some characters. 

The standard ASCII scheme has only zero to 127 character positions; 128 through 255 are undefined. The problem of undefined characters is solved by Unicode encoding, which assigns a number to every character used worldwide. Other types of codes include BinHex, Uuencode (UNIX to UNIX encoding) and Multipurpose Internet Mail Extensions (MIME).

Encoding is also used to reduce the size of audio and video files. Each audio and video file format has a corresponding coder-decoder (codec) program that is used to code it into the appropriate format and then decodes for playback.

Encoding should not be confused with encryption, which hides content. Both techniques are used extensively in the networking, software programming, wireless communication and storage fields.
