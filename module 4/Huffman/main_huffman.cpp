// made by Alexandr Ksan0 Vatulin

#include <iostream>
#include <fstream>
#include <vector>  // frequency table
#include <bitset>  // better, than vector or char[] to work with bits
#include <queue>  // for creating tree
#include <stack>  // go through the tree
using namespace std;


struct HNode {
    HNode()
        : left(NULL), right(NULL), ch(0), weight(0) {
    }
    HNode(HNode *l, HNode *r)
        : left(l), right(r), ch(0), weight(l->weight + r->weight) {
    }

    HNode *left;
    HNode *right;

    unsigned char ch;
    unsigned int weight;
};


struct HNode_comparator {
    bool operator()(const struct HNode *n1, const HNode *n2) {
        return n1->weight > n2->weight;
    }
};


class frequency_table {
public:
    frequency_table() : _table(256) {
        for (unsigned int i = 0; i < _table.size(); ++i) {
            _table[i] = new HNode;
            _table[i]->ch = i;
        }
    }
    ~frequency_table() {
        for (unsigned int i = 0; i < _table.size(); ++i)
            delete _table[i];
    }
    void create(ifstream &file) {
        while (1) {
            unsigned int uch = file.get();
            if (file.eof())
                break;
            ++_table[uch % _table.size()]->weight;
        }

        file.clear();
        file.seekg(ios::beg);
    }
    const HNode* to_tree() const {
        priority_queue<HNode*, vector<HNode*>, HNode_comparator> queue;

        for (unsigned int i = 0; i < _table.size(); ++i)
            if (_table[i]->weight != 0)
                queue.push(_table[i]);

        while (queue.size() > 1) {
            HNode *one = queue.top();
            queue.pop();
            HNode *two = queue.top();
            queue.pop();

            queue.push(new HNode(one, two));
        }

        return queue.top();
    }
    friend fstream& operator<<(fstream &file, const frequency_table &table) {
        for (unsigned int i = 0; i < table._table.size(); ++i)
            if (table._table[i]->weight != 0)
                file << table._table[i]->ch << table._table[i]->weight;
        return file;
    }
    friend fstream& operator>>(fstream &file, frequency_table &table) {
        unsigned int ch, weight;
        while (1) {
            ch = file.get();
            weight = file.get();
            if (file.eof())
                break;
            table._table[ch % table._table.size()]->weight = weight;
        }
        return file;
    }
private:
    vector<HNode*> _table;
};


// return count of filled bits
unsigned int code_char(unsigned char uch, const HNode *root, bitset<256> &bits) {
    const HNode *now = root;
    bool goDown = true;
    stack<const HNode*> parents;

    while (1) {
        if (goDown) {

            if (now->left == NULL && now->right == NULL) {
                if (uch == now->ch)
                    return parents.size();
                goDown = false;
                continue;
            }
            if (now->left != NULL) {
                bits.set(parents.size(), 0);
                parents.push(now);
                now = now->left;
                continue;
            }
            bits.set(parents.size(), 1);
            parents.push(now);
            now = now->right;

        } else {

            if (parents.empty())
                break;

            const HNode *from = now;
            now = parents.top();
            parents.pop();

            if (from == now->left) {
                if (now->right == NULL) {
                    continue;
                }
                bits.set(parents.size(), 1);
                parents.push(now);
                now = now->right;
                goDown = true;
                continue;
            }

        }
    }

    throw "Can not find char";
}


void code_file(ifstream &in_file, ofstream &out_file, const HNode *tree) {
    bitset<256> bits;

    while (1) {
        unsigned char uch = in_file.get();
        if (in_file.eof())
            break;

        unsigned int bits_n = code_char(uch, tree, bits);
        for (unsigned int i = 0; i < bits_n; ++i)
            out_file.put(bits[i] ? '1' : '0');
    }
}


void decode_file(ifstream &in_file, ofstream &out_file, const HNode *tree) {
    const HNode *now = tree;

    while (1) {
        if (now->left == NULL && now->right == NULL) {
            out_file.put(now->ch);
            now = tree;
        }

        unsigned char uch = in_file.get();
        if (in_file.eof())
            break;

        if (uch == '0')
            now = now->left;
        else
            now = now->right;
    }
}


int main() {
    // code or decode?
    char type, chbuff[256];
    cout << "[c]ode/[d]ecode: ";
    cin >> type;

    // open files: in, out, table
    cout << "in: ";
    cin >> chbuff;
    ifstream in_file(chbuff/*"in.txt"*/);
    if (!in_file) {
        cout << "Can't open " << chbuff << "\n";
        system("pause");
        return 1;
    }
    cout << "out: ";
    cin >> chbuff;
    ofstream out_file(chbuff/*"in.txt"*/);
    if (!out_file) {
        cout << "Can't open " << chbuff << "\n";
        system("pause");
        return 1;
    }
    cout << "table: ";
    cin >> chbuff;
    fstream table_file(chbuff/*"table.txt"*/, type == 'c' ? ios::out : ios::in);
    if (!table_file) {
        cout << "Can't open " << chbuff << "\n";
        system("pause");
        return 1;
    }

    // fill freq table and get tree
    frequency_table table;
    if (type == 'c') {
        table.create(in_file);
        table_file << table;
    } else {
        table_file >> table;
    }
    const HNode *tree = table.to_tree();

    if (type == 'c')
        code_file(in_file, out_file, tree);
    else
        decode_file(in_file, out_file, tree);

    in_file.close();
    out_file.close();
    table_file.close();

    cout << "\n\n";
    return 0;
}
