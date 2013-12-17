#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int min_roads_dist(vector<int> coords)
{
    if(coords.empty() || coords.size() == 1)
        return 0;
    if(coords.size() == 2)
        return coords[1] - coords[0];

    sort(coords.begin(), coords.end());
    vector<int> road(coords.size(), 0);

	road[0] = coords[1] - coords[0];
    road[1] = road[0];

    for(int i = 1; i < coords.size() - 1 ; ++i)
		road[i+1] = coords[i+1] - coords[i] + min(road[i-1], road[i]);

    return road.back();
}


int main()
{
	int n;
	cin >> n;
	vector<int> towns(n);
    for( int i = 0; i < towns.size(); i++)
		cin >> towns[i];

    int res = min_roads_dist(towns);
    cout << res;

	//system("pause");
	return 0;
}