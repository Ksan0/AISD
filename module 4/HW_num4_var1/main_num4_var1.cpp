#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// pair<int, int> : pair<s, m>
#define get_s(p) p.second
#define get_m(p) p.first


bool operator<(const pair<int, int> &p1, const pair<int, int> &p2) {
    if (get_s(p1) == get_s(p2))
        return get_m(p1) <= get_m(p2);
    return get_s(p1) < get_s(p2);
}

int MakeTower(vector< pair<int, int> > &vec) {
    sort(vec.begin(), vec.end());

    int height = 0;
    for (int i = 0, m = 0; i < vec.size(); ++i) {
        if (get_s(vec[i]) >= m) {
            ++height;
            m += get_m(vec[i]);
        }
    }
    
    return height;
}

int main() {
    vector < pair <int, int> > vec;
    int m, s;
    
    while (cin >> m >> s)
        vec.push_back(pair<int, int>(m, s));
    
    int count = MakeTower(vec);
    cout << count;

    return 0;
}
