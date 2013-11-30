#include <iostream>
#include <vector>
#include <cmath>
using std::cout;
using std::cin;
using std::vector;
typedef std::pair<int, int> MinPair;


double lb(size_t x) {
    return log(x)/log(2);
}


class SparseTable
{
public:
    SparseTable(const std::vector<int>& v);
    int RMQ(int l, int r);
private:
    MinPair findMinPair(const MinPair& m1, const MinPair& m2);
    MinPair findMinPair(const vector<MinPair>& row, int ind1, int ind2);
    vector<MinPair> convertToMinPairVec(const vector<int>& vec);

    vector<vector<MinPair> > table;
};

SparseTable::SparseTable(const std::vector<int>& v)
{
    vector<MinPair> vec = convertToMinPairVec(v);
    table.push_back(vec); // first row

    for (int i = 1; i < (lb(vec.size())) + 1; ++i)
    {
        int offset = (1 << (i - 1));
        vector<MinPair> row;
        for (size_t j = 0; j + offset < table[i-1].size(); ++j)
            row.push_back(findMinPair(table[i-1], j, j + offset));
        table.push_back(row);
    }
}

int SparseTable::RMQ(int l, int r)
{
    if (l == r)
        return table[0][l - 1].first;
    int k = lb(r-l);
    return findMinPair(table[k][l - 1], table[k][r - (1 << k)]).second;
}

MinPair SparseTable::findMinPair(const MinPair& m1, const MinPair& m2)
{
    int a[2] = { m1.first, m1.second };
    int b[2] = { m2.first, m2.second };
    int res[2] = { 0 };

    if (a[0] == a[1] && b[0] == b[1])
    {
        if (a[0] < b[0]) {
            res[0] = a[0];
            res[1] = b[0];
        } else {
            res[0] = b[0];
            res[1] = a[0];
        }
    } else {
        int i = 0, j = 0, k = 0;
        for ( ; k < 2; ++k)
        {
            if (a[i] == b[j])
            {
                res[k] = a[i++];
                ++j;
            } else if (a[i] < b[j]) {
                res[k] = a[i++];
            } else {
                res[k] = b[j++];
            }
        }
    }
    return MinPair(res[0], res[1]);
}

MinPair SparseTable::findMinPair(const vector<MinPair>& row, int ind1, int ind2)
{
    const MinPair& m1 = row[ind1];
    const MinPair& m2 = row[ind2];
    return findMinPair(m1, m2);
}

std::vector<MinPair> SparseTable::convertToMinPairVec(const std::vector<int>& vec)
{
    std::vector<MinPair> res;
    for (size_t i = 0; i < vec.size(); ++i)
        res.push_back(MinPair(vec[i], vec[i]));
    return res;
}


int main() {
    int n, m;
    cin >> n >> m;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
        cin >> nums[i];

    SparseTable st(nums);
    int l, r;
    for (int i = 0; i < m; ++i) {
        cin >> l >> r;
        cout << st.RMQ(l, r) << "\n";
    }

    return 0;
}

