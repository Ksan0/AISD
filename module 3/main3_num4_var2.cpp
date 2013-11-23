#include <iostream>
#include <vector>
using namespace std;

struct CNode {
    CNode(int k) :
        key(k), height(1), count(1),
        left(NULL), right(NULL)
    { 
    }

    int key;
    int height;
    int count;

    CNode* left;
    CNode* right;
};

int Height(CNode* node)
{
    return node ? node->height : 0;
}


int Count(CNode* node) {
    return node ? node->count : 0;
}


int BalanceFactor(CNode* node)
{
    return Height(node->right) - Height(node->left);
}

void FixHeight(CNode* node)
{
    int hl = Height(node->left);
    int hr = Height(node->right);
    node->height = (hl > hr ? hl : hr) + 1;

    int cl = Count(node->left);
    int cr = Count(node->right);
    node->count = cl + cr + 1;
}

CNode* RotateRight(CNode* p) // правый поворот вокруг p
{
    if (p == NULL)
        return NULL;

    CNode *tmp = p->left;
    p->left = tmp->right;
    tmp->right = p;
    FixHeight(p);
    FixHeight(tmp);
    return tmp;
}

CNode* RotateLeft(CNode *p) // левый поворот вокруг p
{
    if (p == NULL)
        return NULL;

    CNode *tmp = p->right;
    p->right = tmp->left;
    tmp->left = p;
    FixHeight(p);
    FixHeight(tmp);
    return tmp;
}

CNode* Balance(CNode *p)
{
    if (p == NULL)
        return NULL;

    FixHeight(p);

    if( BalanceFactor(p) > 1 )
    {
        if( BalanceFactor(p->right) < 0 )
            p->right = RotateRight(p->right);
        return RotateLeft(p);
    }
    if( BalanceFactor(p) < -1 )
    {
        if( BalanceFactor(p->left) > 0  )
            p->left = RotateLeft(p->left);
        return RotateRight(p);
    }
    return p;
}

CNode* Insert(CNode* root, int key)
{
    if( root == NULL ) 
        return new CNode(key);

    if( key < root->key )
        root->left = Insert(root->left,key);
    else
        root->right = Insert(root->right,key);
    return Balance(root);
}

CNode* FindMin(CNode* p)
{
    return p->left ? FindMin(p->left) : p;
}

CNode* RemoveMin(CNode* p)
{
    if( p->left==0 )
        return p->right;
    p->left = RemoveMin(p->left);
    return Balance(p);
}

CNode* Remove(CNode* p, int k)
{
    if( !p ) return 0;
    if( k < p->key )
        p->left = Remove(p->left,k);
    else if( k > p->key )
        p->right = Remove(p->right,k);	
    else //  k == p->key 
    {
        CNode* q = p->left;
        CNode* r = p->right;
        delete p;
        if( !r ) return q;
        CNode* min = FindMin(r);
        min->right = RemoveMin(r);
        min->left = q;
        return Balance(min);
    }
    return Balance(p);
}

void DeleteTree(CNode* node)
{
    if (node == NULL) 
        return;
    DeleteTree(node->left);
    DeleteTree(node->right);
    delete node;
}


int GetElemAtK(CNode* root, int k) {
    if (k == Count(root->left))
        return root->key;

    if (k <= Count(root->left))
        return GetElemAtK(root->left, k);

    return GetElemAtK(root->right, k - Count(root->left) - 1);
}


int main()
{
    int n;
    cin >> n;

    CNode *root = NULL;
    int A, k;

    for (int i = 0; i < n; ++i) {
        cin >> A >> k;
        if( A >= 0 )
            root = Insert(root, A);
        else
            root = Remove(root, -A);

        cout << GetElemAtK(root, k) << endl;
    }

    DeleteTree(root);

    //system("pause");
    return 0;
}