class Solution {
public:
  int myAtoi(string str) {
    long long res(0);
    int sign(1), index(0);
    //handle white space
    while(str[index] == ' ') ++index;
    //handle sign
    if(str[index] == '-' || str[index] == '+')
      sign = str[index++] == '-'? -1:1;

    while(std::isdigit(str[index])){
      if(res > INT_MAX/10)
        return sign ==1? INT_MAX:INT_MIN;
      res = res * 10 + (str[index] - '0');
      ++ index;
    }

    res = sign * res;

    if(res>INT_MAX)
      return INT_MAX;
    if(res<INT_MIN)
      return INT_MIN;
    return res;
  }
};
