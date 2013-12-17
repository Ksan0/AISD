#include <vector>
#include <iostream>
using namespace std;

struct TriangleMatrix;
typedef long long cell_t;
typedef cell_t (*fill_function)(const TriangleMatrix &matrix, int x, int y);


// coord x is 1..size
// coord y is 1..size
class TriangleMatrix {
public:
    explicit TriangleMatrix(int n) : arr(n*(n+1)/2, 0) {
        size = n;
    }
    void fill(fill_function func) {
        for(int y = 1; y <= size; ++y)
            for(int x = 1; x <= size-y+1; ++x)
                arr[xy_to_index(x, y)] = func(*this, x, y);
    }
    cell_t get(int x, int y) const {
        return arr[xy_to_index(x, y)];
    }
private:
    int xy_to_index(int x, int y) const {
        return (2*size - (y-1))*(y-1)/2 + (x-1);
    }

    vector<cell_t> arr;
    int size;
};


// fill_function
cell_t calculate_variation_of_pyramids(const TriangleMatrix &matrix, int x, int y) {
    cell_t sum = 0;
    for (int i = 1; i <= y; ++i) {
        if (x-i < 0)
            break;
        if (x-i == 0)
            sum += 1;
        else
            sum += matrix.get(x-i, i);
    }
    return sum;
}


cell_t get_number_of_variations_of_pyramids(int n) {
    if (n < 0)
        return 0;
    if (n == 0)
        return 1;

    TriangleMatrix matrix(n);
    matrix.fill(calculate_variation_of_pyramids);
    cell_t res = calculate_variation_of_pyramids(matrix, n, n);

    return res;
}


int main() {
    int n;
    cin >> n;
    cout << get_number_of_variations_of_pyramids(n);
    // cout << "\n\n"; system("pause");
    return 0;
}
