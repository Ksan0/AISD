#include <iostream>
#include <stack>
using namespace std;


struct Node
{
    Node() 
        : left(NULL), right(NULL) 
    {
    }
    Node(int __val)
        : left(NULL), right(NULL)
    {
        val = __val;
    }

    int val;
    Node *left, *right;
};


Node* BuildNaiveTreeFromConsole() {
    int n;
    cin >> n;

    if (n <= 0)
        return NULL;

    int val;
    cin >> val;
    Node *root = new Node(val);
    
    for (int i = 1; i < n; ++i) {

        cin >> val;
        Node *now = root, **willIns;
        while (1) {
            willIns = (val < now->val ? &(now->left) : &(now->right));
            if (*willIns == NULL) {
                *willIns = new Node(val);
                break;
            }
            now = *willIns;
        }

    }

    return root;
}


// post
void PassThroughTree(Node *root, void (*func)(int)) {
    Node *now = root;
    bool goDown = true;
    stack<Node*> parents;

    while (1) {
        if (goDown) {

            if (now->left == NULL && now->right == NULL) {
                func(now->val);
                goDown = false;
                continue;
            }
            if (now->left != NULL) {
                parents.push(now);
                now = now->left;
                continue;
            }
            parents.push(now);
            now = now->right;

        } else {

            if (parents.empty())
                break;
            Node *from = now;
            now = parents.top();
            parents.pop();

            if (from == now->left) {
                if (now->right == NULL) {
                    func(now->val);
                    continue;
                }
                parents.push(now);
                now = now->right;
                goDown = true;
                continue;
            }
            func(now->val);
        }
    }
}


void Print(int val) {
    cout << val << " ";
}


int main()
{
    Node *root = BuildNaiveTreeFromConsole();
    PassThroughTree(root, Print);
    // cout << "\n\n";
    // system("pause");
    return 0;
}