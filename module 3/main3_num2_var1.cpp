#include <cstdio>
#include <iostream>
using namespace std;

struct CTreapNode {
    int Key;
	int Priority;
    CTreapNode* Left;
	CTreapNode* Right;

	CTreapNode(int key, int priority) : Key(key), Priority(priority), Left(0), Right(0) {}
};

CTreapNode* Merge(CTreapNode* left, CTreapNode* right)
{
	if( left == 0 || right == 0 ) {
		return left == 0 ? right : left;
	}
	if( left->Priority > right->Priority ) {
		left->Right = Merge(left->Right, right);
		return left;
    }
	right->Left = Merge(left, right->Left);
	return right;
}

void Split(CTreapNode* currentNode, int key, CTreapNode*& left, CTreapNode*& right)
{
	if( currentNode == 0 ) {
		left = 0;
		right = 0;
	} else if( currentNode->Key <= key ) {
		// Сокращенный вариант - Split(currentNode->Right, key, currentNode->Right, right);
		CTreapNode* tempLeft = 0;
		CTreapNode* tempRight = 0;
		Split(currentNode->Right, key, tempLeft, tempRight);
		right = tempRight;
		left = currentNode;
		left->Right = tempLeft;
    } else {
		// Сокращенный вариант - Split(currentNode->Left, key, left, currentNode->Left);
		CTreapNode* tempLeft = 0;
		CTreapNode* tempRight = 0;
		Split(currentNode->Left, key, tempLeft, tempRight);//a, t->l);
		left = tempLeft;
		right = currentNode;
		right->Left = tempRight;
    }
}

CTreapNode* Insert(CTreapNode* root, int key, int priority) {
	CTreapNode* node = new CTreapNode(key, priority);
	CTreapNode* splitLeft = 0;
	CTreapNode* splitRight = 0;
	Split(root, key, splitLeft, splitRight);
    return Merge(Merge(splitLeft, node), splitRight);
}

CTreapNode* Delete(CTreapNode* root, int key)
{
	CTreapNode* splitLeft = 0;
	CTreapNode* splitRight = 0;
	Split(root, key - 1, splitLeft, splitRight);
	CTreapNode* splitRightLeft = 0;
	CTreapNode* splitRightRight = 0;
    Split(splitRight, key, splitRightLeft, splitRightRight);
    delete splitRightLeft;
	return Merge(splitLeft, splitRightRight);
}

void InsertNaivu(CTreapNode *root, int key) {
    CTreapNode *now = root, **willIns;
    while (1) {
        willIns = (key < now->Key ? &(now->Left) : &(now->Right));
        if (*willIns == NULL) {
            *willIns = new CTreapNode(key, 0);
            break;
        }
        now = *willIns;
    }
}

int HowDeepIsThisTree(CTreapNode *root) {
    if(root == NULL)
        return 0;

    return max(HowDeepIsThisTree(root->Left), HowDeepIsThisTree(root->Right)) + 1;
}

int main()
{
    int n;
    cin >> n;
    int key, priority;
    cin >> key >> priority;
    CTreapNode *DecartRoot = new CTreapNode(key, priority);
    CTreapNode *NaivuRoot  = new CTreapNode(key, 0);

    for (int i = 1; i < n; ++i) {
        cin >> key >> priority;
        DecartRoot = Insert(DecartRoot, key, priority);
        InsertNaivu(NaivuRoot, key);
    }

    int decartDeep = HowDeepIsThisTree(DecartRoot);
    int naivuDeep  = HowDeepIsThisTree(NaivuRoot);
    int delta = decartDeep - naivuDeep;
    if (delta < 0)
        delta *= -1;

    cout << delta;

    //cout << "\n\n";
    //system("pause");
    return 0;
}
