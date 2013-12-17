#include <vector>
#include <iostream>
using namespace std;

// f(n, m) = sum(k=1..m, f(n-k, k[-1]))

class TriangleMatrix
{
public:
    TriangleMatrix(int n) : _triangle(n)
    {
        for(int i = 0; i < n; ++i)
            _triangle[i].resize(n-i);
    }
    // if res == NULL, set matrix value else save value in the "res"
    void set_reccur(int x, int y, int *res = NULL)
    {
        if(x < 1 || y < 1)
            return;

        int sum = 0;
        for(int i = 1; i <= y; ++i)
            sum += get(x-i, i);

        if(res == NULL)
            _triangle[x-1][y-1] = sum;
        else
            *res = sum;
    }
private:
    int get(int x, int y)
    {
        if(x < 0 || y < 0)
            return 0;
        if(x == 0)
            return 1;
        if(y == 0)
            return 0;

        return _triangle[x-1][y-1];
    }
    vector< vector<int> > _triangle;
};


int variations_of_the_pyramids(int n)
{
    if(n < 0)
        return 0;
    if(n == 0) // maybe zero?
        return 1;
    
    TriangleMatrix trm(n);

    for(int y = 1; y <= n; ++y)
        for(int x = 1; x <= n-y+1; ++x)
            trm.set_reccur(x, y);
    
    int res;
    trm.set_reccur(n, n, &res);
    return res;
}


int main()
{
    int n;
    cin >> n;
    cout << variations_of_the_pyramids(n);
    //cout << "\n\n"; system("pause");
    return 0;
}