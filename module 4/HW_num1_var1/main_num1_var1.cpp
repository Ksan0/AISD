#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct Node_t;
unsigned int Insert(vector<Node_t> *&table, Node_t elem);
typedef string key_t;

struct Node_t {
    Node_t(const key_t &key = "") : state(nil) {
        this->key = key;
    }
    key_t key;
    
    typedef enum {
        nil = 0,
        deleted,
        used
    } state_t;
    state_t state;
};


size_t Hash_only(const key_t &key) {
    size_t c = 12343;
    size_t a = 31247;
    size_t b = 42589;

    size_t value = c;
    size_t multiplier = 1;
    for (size_t i = 0; i < key.size(); ++i) {
        value += key[i] * multiplier;
        value = value % b;

        multiplier = (multiplier * a) % b;
    }

    return value % b;
}


size_t Hash(const key_t &key, unsigned int i, unsigned int M) {
    return (Hash_only(key) % M + i % M + (i % M)*(i % M)) % M;
}


void Resize(vector<Node_t> *&table) {
    vector<Node_t> *newtable = new vector<Node_t>(table->size() * 2);
    for (unsigned int i = 0; i < table->size(); ++i) {
        if ((*table)[i].state == Node_t::used)
            Insert(newtable, (*table)[i]);
    }
    delete table;
    table = newtable;
}


unsigned int Insert(vector<Node_t> *&table, Node_t elem) {
    for (unsigned int i = 0; i < table->size(); ++i) {
        int j = Hash(elem.key, i, table->size());
        if ((*table)[j].state == Node_t::nil || (*table)[j].state == Node_t::deleted) {
            (*table)[j] = elem;
            (*table)[j].state = Node_t::used;
            return j;
        }
        if ((*table)[j].key == elem.key)
            return -1;
    }

    Resize(table);
    return Insert(table, elem);
}


unsigned int Find(vector<Node_t> *&table, const key_t &key) {
    for (unsigned int i = 0; i < table->size(); ++i) {
        int j = Hash(key, i, table->size());
        if ((*table)[j].state == Node_t::nil)
            return -1;
        if ((*table)[j].state == Node_t::used && (*table)[j].key == key)
            return j;
    }

    return -1;
}


bool Delete(vector<Node_t> *&table, const key_t &key) {
    unsigned int pos = Find(table, key);
    if(pos == -1)
        return false;
    (*table)[pos].state = Node_t::deleted;
    return true;
}


int main() {
    vector<Node_t> *table = new vector<Node_t>(2);

    while(1) {
        string type, key;
        cin >> type >> key;
        if(cin.eof())
            break;
        bool result = false;
        if (type == "+") {
            result = -1 != Insert(table, Node_t(key));
        } else if (type == "?") {
            result = -1 != Find(table, key);
        } else if (type == "-") {
            result = Delete(table, key);
        }

        cout << (result ? "OK\n" : "FAIL\n");
    } 

    return 0;
}