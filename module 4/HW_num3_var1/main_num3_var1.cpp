#include <vector>
#include <iostream>
using namespace std;

struct TriangleMatrix;
typedef long long cell_t;
typedef cell_t (*fill_function)(const TriangleMatrix *matrix, int x, int y);


// coord x is 1..size
// coord y is 1..size
struct TriangleMatrix {
    vector<cell_t> arr;
    int size;
};


TriangleMatrix* allocate_triangle_matrix(int n) {
    TriangleMatrix *matrix = new TriangleMatrix;
    matrix->size = n;
    matrix->arr.resize(n*(n+1)/2);
    fill(matrix->arr.begin(), matrix->arr.end(), 0);
    return matrix;
}


int xy_to_triangle_matrix_array_index(const TriangleMatrix *matrix, int x, int y) {
    return (2*matrix->size - (y-1))*(y-1)/2 + (x-1);
}


void fill_triangle_matrix(TriangleMatrix *matrix, fill_function func) {
    for(int y = 1; y <= matrix->size; ++y)
        for(int x = 1; x <= matrix->size-y+1; ++x)
            matrix->arr[xy_to_triangle_matrix_array_index(matrix, x, y)] = func(matrix, x, y);
}


cell_t calculate_variation_of_pyramids(const TriangleMatrix *matrix, int x, int y) {
    cell_t sum = 0;
    for (int i = 1; i <= y; ++i) {
        if (x-i < 0)
            break;
        if (x-i == 0)
            sum += 1;
        else
            sum += matrix->arr[xy_to_triangle_matrix_array_index(matrix, x-i, i)];
    }
    return sum;
}


cell_t get_number_of_variations_of_pyramids(int n) {
    if (n < 0)
        return 0;
    if (n == 0)
        return 1;

    TriangleMatrix *matrix = allocate_triangle_matrix(n);
    fill_triangle_matrix(matrix, calculate_variation_of_pyramids);
    cell_t res = calculate_variation_of_pyramids(matrix, n, n);
    delete matrix;

    return res;
}


int main() {
    int n;
    cin >> n;
    cout << get_number_of_variations_of_pyramids(n);
    // cout << "\n\n"; system("pause");
    return 0;
}
