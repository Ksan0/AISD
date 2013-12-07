#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using std::cout;
using std::cin;
using std::vector;
using std::max;


struct Line {
    size_t beg, end;

    bool IsInLine(size_t x) {
        return x >= beg && x <= end;
    }
};


size_t WhatLen(const vector<Line> &lines) {
    size_t len = 0;
    for (size_t i = 0; i < lines.size(); ++i)
        len += lines[i].end - lines[i].beg;
    return len;
}


void QuickSort(vector<Line> &arr, size_t first, size_t last) {
    size_t i = first;
    size_t j = last;
    size_t x = arr[first + (last - first) / 2].beg;

    do {
        while (arr[i].beg < x) ++i;
        while (arr[j].beg > x) --j;

        if (i <= j) {
            if (i != j) {
                Line tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
            ++i;
            --j;
        }
    } while (j != -1 && i <= j);

    if (i < last)
        QuickSort(arr, i, last);
    if (j != -1 && first < j)
        QuickSort(arr, first, j);
}


void ConvertToLineWithoutOverlappingSegments(vector<Line> &lines) {
    vector<Line> tmplines = lines;
    lines.clear();

    QuickSort(tmplines, 0, tmplines.size() - 1);

    lines.push_back(tmplines[0]);

    for (size_t i = 1; i < tmplines.size(); ++i) {
        if (lines.back().beg == tmplines[i].beg) {
            lines.back().end = max(lines.back().end, tmplines[i].end);
        } else if (lines.back().IsInLine(tmplines[i].beg)) {
            if (!lines.back().IsInLine(tmplines[i].end))
                lines.back().end = tmplines[i].end;
        } else {
            lines.push_back(tmplines[i]);
        }
    }
}


int main() {
    size_t n;
    cin >> n;
    vector<Line> lines(n), newlines;
    for (size_t i = 0; i < n; ++i)
        cin >> lines[i].beg >> lines[i].end;

    ConvertToLineWithoutOverlappingSegments(lines);
    cout << WhatLen(lines);

    return 0;
}
