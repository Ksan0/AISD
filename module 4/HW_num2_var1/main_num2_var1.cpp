#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long Sint64;


Sint64 min_roads_dist(vector<Sint64> coords)
{
    if(coords.empty() || coords.size() == 1)
        return 0;
    if(coords.size() == 2)
        return coords[1] - coords[0];

    sort(coords.begin(), coords.end());
    vector<Sint64> road(coords.size(), 0);

	road[0] = coords[1] - coords[0];
    road[1] = road[0];

    for(unsigned int i = 1; i < coords.size() - 1 ; ++i)
		road[i+1] = coords[i+1] - coords[i] + min(road[i-1], road[i]);

    return road.back();
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