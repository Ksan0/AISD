#include <vector>
#include <iostream>
using namespace std;

typedef long long Sint64;


// f(n, m) = sum(k=1..m, f(n-k, k))

// Can't do task with only vector: main diagonal calculate with the use 
// of most of the cells of the matrix
class TriangleMatrix {
public:
    explicit TriangleMatrix(int n) : _triangle(n) {
        for (int i = 0; i < n; ++i)
            _triangle[i].resize(n-i);
    }
    // if res == NULL, set matrix value else save value in the "res"
    void set_reccur(int x, int y, Sint64 *res = NULL) {
        if (x < 1 || y < 1)
            return;

        Sint64 sum = 0;
        for (int i = 1; i <= y; ++i)
            sum += get(x-i, i);

        if (res == NULL)
            _triangle[x-1][y-1] = sum;
        else
            *res = sum;
    }

private:
    Sint64 get(int x, int y) {
        if (x < 0 || y < 0)
            return 0;
        if (x == 0)
            return 1;
        if (y == 0)
            return 0;

        return _triangle[x-1][y-1];
    }
    vector< vector<Sint64> > _triangle;
};


Sint64 variations_of_the_pyramids(int n) {
    if (n < 0)
        return 0;
    if (n == 0)  // maybe zero?
        return 1;
    
    TriangleMatrix trm(n);

    for (int y = 1; y <= n; ++y)
        for (int x = 1; x <= n-y+1; ++x)
            trm.set_reccur(x, y);
    
    Sint64 res;
    trm.set_reccur(n, n, &res);
    return res;
}


int main() {
    int n;
    cin >> n;
    cout << variations_of_the_pyramids(n);
    // cout << "\n\n"; system("pause");
    return 0;
}
