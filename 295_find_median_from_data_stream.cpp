class MedianFinder {
public:

    // Adds a number into the data structure.
    void addNum(int num) {
        if (max_heap.size()<=min_heap.size()) {
            min_heap.push(num);
            max_heap.push(min_heap.top());
            min_heap.pop();
        } else {
            max_heap.push(num);
            min_heap.push(max_heap.top());
            max_heap.pop();
        }
    }

    // Returns the median of current data stream
    double findMedian() {
        double reval = max_heap.top();
        if (max_heap.size() == min_heap.size()) reval = reval+ (min_heap.top() -reval) / 2.0;
        return reval;
    }
private:
    std::priority_queue< int,vector<int>,std::greater<int> > min_heap;
    std::priority_queue< int,vector<int>,std::less<int> > max_heap;
};

int main(){
	string str("1,8,3,5,4,2,6,7,9");
	 std::istringstream iss(str);
	 MedianFinder mf;
	 
	 while(std::getline(iss,str,',')) {
		 mf.addNum( std::stoi(str));
	 }
   double val = mf.findMedian();
    return 0;
}

