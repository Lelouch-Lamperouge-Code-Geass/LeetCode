class Solution {
public:
  string numberToWords(int num) {
    if (num<=0) return "Zero";
    string reval("");
    int i(0);
    while (num) {
      reval = getNumberBelowTenThousand(num%1000) + THOUSANDS[i] + " "+reval;
      num /= 1000;
      ++ i;
    }
    return reval;
  }
private:
  string getNumberBelowTenThousand(int num) {
    string reval("");
    if (num<=0) return "";
    else if (num<20) return LESS_THAN_20[num];
    else if (num<100) return TENS[num/10];
    else return LESS_THAN_20[num/100] + " Hundred " + getNumberBelowTenThousand(num%100); 
  }
  static string LESS_THAN_20[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
  static  string TENS[] = {"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
  static string THOUSANDS[] = {"","Thousand","Million","Billion"};
  
};
