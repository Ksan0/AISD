#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::cin;


struct Box {
    size_t x, y, z;

    // rotate box. After it x - max side, z - min side
    void Rotate() {
        size_t arr[3] = {x, y, z};

        bool bad;
        do {
            bad = false;

            for (size_t i = 1; i < 3; ++i) {
                if (arr[i-1] < arr[i]) {
                    size_t tmp = arr[i-1];
                    arr[i-1] = arr[i];
                    arr[i] = tmp;
                    bad = true;
                }
            }
        } while (bad);

        x = arr[0];
        y = arr[1];
        z = arr[2];
    }
};



void SelectSortBoxWithIndexes(Box *boxes, size_t *indexes, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        size_t min_i = i;

        for (size_t j = i + 1; j < len; ++j) {
            if (boxes[j].x < boxes[min_i].x)
                min_i = j;
        }

        if (min_i != i) {
            Box tmpBox = boxes[i];
            boxes[i] = boxes[min_i];
            boxes[min_i] = tmpBox;
            size_t tmpInd = indexes[i];
            indexes[i] = indexes[min_i];
            indexes[min_i] = tmpInd;
        }
    }
}


size_t* GetOrder(Box *boxes, size_t len) {
    size_t *indexes = new size_t[len];
    for (size_t i = 0; i < len; ++i) {
        indexes[i] = i;
        boxes[i].Rotate();
    }

    SelectSortBoxWithIndexes(boxes, indexes, len);

    return indexes;
}


int main() {
    size_t len;
    cin >> len;
    Box *boxes = new Box[len];

    for (size_t i = 0; i < len; ++i)
        cin >> boxes[i].x >> boxes[i].y >> boxes[i].z;

    size_t *indexes = GetOrder(boxes, len);

    for (size_t i = 0; i < len; ++i)
        cout << indexes[i] << " ";

    delete [] boxes;
    delete [] indexes;

    return 0;
}
