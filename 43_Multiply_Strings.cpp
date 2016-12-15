// We have to begin backwards since if we handle
// the most siginificant position first, how can we
// update if the product of lower position is 10~ , in which case
// the higher position need +1?
// Another thing need to be pointed out is, for example,
// let's say the higher position's value is 9, and we just
// calculated the product of lower position is 10.
// In this case, the higher position's value +1 ==10.
// But we don't need to worry about that since we're going to
// process the higher position later.

class Solution {
public:
  string multiply(string num1, string num2) {
    const int num1_size(num1.size()), num2_size(num2.size());
    std::string reval(num1_size+num2_size,'0');

    for (int i=num1_size-1;i>=0;--i) {
      for (int j=num2_size-1;j>=0;--j) {
        int pos1(i+j),pos2(i+j+1);
        int val = (reval[pos2]-'0')+(num1[i]-'0') * (num2[j]-'0');
        reval[pos2] = '0' + (val%10);
        reval[pos1] += val/10;
      }
    }
    size_t startpos = reval.find_first_not_of("0");
    if (string::npos != startpos) {
      return reval.substr(startpos);
    }
    return "0";
  }
};
