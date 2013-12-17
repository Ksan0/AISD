#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long Sint64;


Sint64 min_roads_dist(vector<Sint64> &coords)
{
    if(coords.empty() || coords.size() == 1)  // impossible to calculate
        return 0;
    
    sort(coords.begin(), coords.end());

    Sint64 a0 = coords[1] - coords[0];
    Sint64 a1 = a0;
    Sint64 a2 = 0;

    for(unsigned int i = 1; i < coords.size() - 1 ; ++i)
    {
        a2 = coords[i+1] - coords[i] + min(a0, a1);
        
        // move left
        a0 = a1;
        a1 = a2;
        a2 = 0;
    }

    return a1;
}


int main()
{
    int n;
    cin >> n;
    vector<Sint64> towns(n);
    for(unsigned int i = 0; i < towns.size(); i++)
        cin >> towns[i];

    Sint64 res = min_roads_dist(towns);
    cout << res;

    // cout << "\n\n"; system("pause");
    return 0;
}
