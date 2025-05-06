#include <iostream>
using namespace std;
struct BSTNode 
{
    int data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int val) {
        data = val;
        left = right = nullptr;
    }
};

class BST
 {
public:
    BSTNode* insert(BSTNode* root, int val) {
        if (!root) return new BSTNode(val);
        if (val < root->data)
            root->left = insert(root->left, val);
        else
            root->right = insert(root->right, val);
        return root;
    }

    void inorder(BSTNode* root) {
        if (!root) return;
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
};

struct AVLNode
 {
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int val) {
        data = val;
        left = right = nullptr;
        height = 1;
    }
};

class AVL 
{
public:
    int height(AVLNode* n) {
        return n ? n->height : 0;
    }

    int getBalance(AVLNode* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    AVLNode* rightRotate(AVLNode* y) 
	{
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));
        return x;
    }

    AVLNode* leftRotate(AVLNode* x) 
	{
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));
        return y;
    }

    AVLNode* insert(AVLNode* root, int val) 
	{
    	
        if (!root) return new AVLNode(val);
        if (val < root->data)
            root->left = insert(root->left, val);
        else if (val > root->data)
            root->right = insert(root->right, val);
        else
            return root;

        root->height = 1 + max(height(root->left), height(root->right));
        int balance = getBalance(root);

        if (balance > 1 && val < root->left->data)
            return rightRotate(root);
        if (balance < -1 && val > root->right->data)
            return leftRotate(root);
        if (balance > 1 && val > root->left->data) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && val < root->right->data) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }

    void inorder(AVLNode* root) {
        if (!root) return;
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
};

int main() 
{
    BST bst;
    BSTNode* bstRoot = nullptr;
    bstRoot = bst.insert(bstRoot, 30);
    bst.insert(bstRoot, 20);
    bst.insert(bstRoot, 40);
    bst.insert(bstRoot, 10);
    cout << "BST In-order: ";
    bst.inorder(bstRoot);
    cout << "\n";

    AVL avl;
    AVLNode* avlRoot = nullptr;
    avlRoot = avl.insert(avlRoot, 30);
    avlRoot = avl.insert(avlRoot, 20);
    avlRoot = avl.insert(avlRoot, 40);
    avlRoot = avl.insert(avlRoot, 10);
    cout << "AVL In-order: ";
    avl.inorder(avlRoot);
    cout << "\n";

    return 0;
}
