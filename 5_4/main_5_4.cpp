#include <stdio.h>


struct List1 {
    explicit List1(int val) : next(NULL), value(val) {
    }

    List1 *next;
    int value;
};


// end -> begin
class Queue {
    public:
    Queue() : _begin(NULL), _end(NULL) {
    }
    ~Queue() {
        if (_end != NULL)
            delete _end;
    }
    void PushFront(int value) {
        if (_begin == NULL) {
            _begin = new List1(value);
            _end = _begin;
            return;
        }

        _begin->next = new List1(value);
        _begin = _begin->next;
    }
    int PopBack() {
        if (_end == NULL)
            return -1;

        int val = _end->value;
        List1 *ptr = _end->next;
        delete _end;

        if (_begin == _end) {
            _begin = NULL;
            _end = NULL;
            return val;
        }

        _end = ptr;
        return val;
    }

    private:
    List1 *_begin, *_end;
};


using namespace std;
int main() {
    int n = 0;
    scanf("%d", &n);
    int a, b;
    Queue q;
    bool allCmpIsGood = true;

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a, &b);
        switch (a) {
        case 2:
            if (q.PopBack() != b)
                allCmpIsGood = false;
            break;
        case 3:
            q.PushFront(b);
            break;
        }
    }
    printf("%s", allCmpIsGood ? "YES" : "NO");
    return 0;
}
