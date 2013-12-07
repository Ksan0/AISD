#include <iostream>
#include <string>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;
using std::reverse;
using std::string;


struct List2 {
    explicit List2(char ch) : next(NULL), prev(NULL), val(ch) {
    }
    List2 *next, *prev;
    char val;
};


class Stack {
    public:
    Stack() :_list(NULL) {
    }
    ~Stack() {
        if (_list == NULL)
            return;
        List2 *tmp;
        do {
            tmp = _list->prev;
            delete _list;
            _list = tmp;
        } while (_list != NULL);
    }
    void Push(char ch) {
        if (_list == NULL) {
            _list = new List2(ch);
            return;
        }

        List2 *newlist = new List2(ch);
        newlist->prev = _list;
        _list->next = newlist;
        _list = newlist;
    }
    char Pop() {
        if (_list == NULL)
            return 0;

        char ch = _list->val;
        if (_list->prev == NULL) {
            delete _list;
            _list = NULL;
            return ch;
        }

        List2 *prevlist = _list->prev;
        prevlist->next = NULL;
        delete _list;
        _list = prevlist;
        return ch;
    }

    private:
    List2 *_list;
};


int OperatorPriority(char ch, int brackets) {
    // + -> 1
    // * -> 2
    // ^ -> 3
    // (+) -> 4
    // (*) -> 5
    // (^) -> 6
    // ((+)) -> 7
    // ((*)) -> 8
    // etc
    int result = brackets*3;

    switch (ch) {
    case '+':
    case '-':
        return result + 1;
    case '*':
    case '/':
    case '%':
        return result + 2;
    case '^':
        return result + 3;
    }

    return 0;
}


string InfixToPostfix(string str) {
    const string operators = "+-*/%^";
    string result;
    Stack deadlock_value, deadlock_priority;
    int brackets = 0;

    for (string::size_type i = 0; i < str.length(); ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            result.push_back(str[i]);
            continue;
        }
        switch (str[i]) {
        case '(':
            ++brackets;
            break;
        case ')':
            --brackets;
            break;
        }
        if (operators.find(str[i]) != string::npos) {
            result.push_back(' ');

            int priority = OperatorPriority(str[i], brackets);
            int dl_priority = deadlock_priority.Pop();

            while (dl_priority > priority) {
                result.push_back(deadlock_value.Pop());
                result.push_back(' ');
                dl_priority = deadlock_priority.Pop();
            }
            if (dl_priority != 0)
                deadlock_priority.Push(dl_priority);
            deadlock_priority.Push(priority);
            deadlock_value.Push(str[i]);
        }
    }

    int val = deadlock_value.Pop();
    while (val != 0) {
        result.push_back(' ');
        result.push_back(val);
        val = deadlock_value.Pop();
    }

    return result;
}


string InfixToPrefix(string str) {
    string::size_type find = 0;
    while ((find = str.find(' ', find)) != string::npos)
        str.erase(find, 1);

    reverse(str.begin(), str.end());
    for (string::size_type i = 0; i < str.length(); ++i) {
        switch (str[i]) {
        case ')':
            str[i] = '(';
            break;
        case '(':
            str[i] = ')';
            break;
        }
    }
    str = InfixToPostfix(str);
    reverse(str.begin(), str.end());

    return str;
}


int main() {
    string str;
    getline(cin, str);
    string result = InfixToPrefix(str);
    cout << result << endl;
    return 0;
}
