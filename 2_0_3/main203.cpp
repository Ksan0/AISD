#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::stringstream;
using std::getline;


void BubbleSort(vector<int> &arr) {
    bool bad;
    do {
        bad = false;

        for (size_t i = 1; i < arr.size(); ++i) {
            if(arr[i - 1] > arr[i]) {
                int tmp = arr[i - 1];
                arr[i - 1] = arr[i];
                arr[i] = tmp;
                bad = true;
            }
        }

    } while(bad);
}


int main() {
    vector<int> arr;
    string s;
    stringstream ss;
    int tmp;
    while(1) {
        getline(cin, s);

        if (cin.eof())
            break;
        if (!s.empty()) {
            ss << s;
            ss >> tmp;
            s.clear();
            ss.clear();
            arr.push_back(tmp);
        }
    }

    BubbleSort(arr);

    for (size_t i = 0; i < arr.size(); ++i)
        cout << arr[i] << "\n";

    return 0;
}
