class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int left = std::max(A,E),down = std::max(B,F),right = std::min(C,G), top = std::min(D,H);
        int overlap(0);
        if(right > left && top > down)
             overlap = (right - left) * (top - down);
        return (C-A)*(D-B) + (G-E)*(H-F) - overlap;
    }
};
