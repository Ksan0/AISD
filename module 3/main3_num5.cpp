#include <iostream>
#include <vector>
#include <cmath>
using std::cout;
using std::cin;
using std::vector;


typedef struct {
    int data[2];
} MinPair;


double lb(size_t x) {
    return log(x)/log(2);
}


class SparseTable {
public:
    SparseTable(const vector<int> &v);
    int SecontOrderStatistic(int l, int r);
private:
    MinPair findMinPair(const MinPair m1, const MinPair m2);
    MinPair findMinPair(const vector<MinPair> &row, int ind1, int ind2);
    vector<MinPair> convertToMinPairVec(const vector<int> &vec);

    vector< vector<MinPair> > table;
};

SparseTable::SparseTable(const vector<int> &v) {
    vector<MinPair> vec = convertToMinPairVec(v);
    table.push_back(vec); // first row

    for (int i = 1; i < lb(vec.size()) + 1; ++i)
    {
        int offset = (1 << (i - 1));
        vector<MinPair> row;
        for (size_t j = 0; j + offset < table[i-1].size(); ++j)
            row.push_back(findMinPair(table[i-1], j, j + offset));
        table.push_back(row);
    }
}

int SparseTable::SecontOrderStatistic(int l, int r) {
    if (l == r)
        return table[0][l - 1].data[0];
    int k = lb(r-l);
    return findMinPair(table[k][l - 1], table[k][r - (1 << k)]).data[1];
}

MinPair SparseTable::findMinPair(const MinPair a, const MinPair b) {
    MinPair res;

    if (a.data[0] == a.data[1] && b.data[0] == b.data[1])
    {
        if (a.data[0] < b.data[0]) {
            res.data[0] = a.data[0];
            res.data[1] = b.data[0];
        } else {
            res.data[0] = b.data[0];
            res.data[1] = a.data[0];
        }
    } else {
        for (int i = 0, j = 0, k = 0; k < 2; ++k) {
            if (a.data[i] == b.data[j]) {
                res.data[k] = a.data[i++];
                ++j;
            } else if (a.data[i] < b.data[j]) {
                res.data[k] = a.data[i++];
            } else {
                res.data[k] = b.data[j++];
            }
        }
    }

    return res;
}

MinPair SparseTable::findMinPair(const vector<MinPair>& row, int ind1, int ind2) {
    return findMinPair(row[ind1], row[ind2]);
}

vector<MinPair> SparseTable::convertToMinPairVec(const vector<int> &vec) {
    vector<MinPair> res;
    for (size_t i = 0; i < vec.size(); ++i) {
        MinPair pair = { {vec[i], vec[i]} };
        res.push_back(pair);
    }
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
        cout << st.SecontOrderStatistic(l, r) << "\n";
    }

    return 0;
}

