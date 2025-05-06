#include <iostream>
#include <stack>
#include <queue>
using namespace std;
struct MoveNode {
    int cell;
    char player;
    MoveNode* next;
    MoveNode(int c, char p) : cell(c), player(p), next(nullptr) {}
};
struct AVLNode {
    string name;
    int score;
    int height;
    AVLNode* left;
    AVLNode* right;
    AVLNode(string n, int s) : name(n), score(s), height(1), left(nullptr), right(nullptr) {}
};
int height(AVLNode* node) {
    return node ? node->height : 0;
}
int balanceFactor(AVLNode* node) {
    return height(node->left) - height(node->right);
}
void updateHeight(AVLNode* node) {
    node->height = 1 + max(height(node->left), height(node->right));
}
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}
AVLNode* insertAVL(AVLNode* root, string name, int score) {
    if (!root) return new AVLNode(name, score);
    if (score < root->score)
        root->left = insertAVL(root->left, name, score);
    else
        root->right = insertAVL(root->right, name, score);

    updateHeight(root);

    int bf = balanceFactor(root);
    if (bf > 1 && score < root->left->score)
        return rotateRight(root);
    if (bf < -1 && score > root->right->score)
        return rotateLeft(root);
    if (bf > 1 && score > root->left->score) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (bf < -1 && score < root->right->score) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void inOrder(AVLNode* root) {
    if (root) {
        inOrder(root->left);
        cout << root->name << " : " << root->score << endl;
        inOrder(root->right);
    }
}

char board[3][3];
stack<int> undoStack;
queue<char> turnQueue;
MoveNode* moveHead = nullptr;

void initializeBoard() {
    int k = 1;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = '0' + k++;
}

void printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---|---|---\n";
    }
    cout << "\n";
}

bool checkWin(char p) {
    for (int i = 0; i < 3; i++)
        if ((board[i][0] == p && board[i][1] == p && board[i][2] == p) ||
            (board[0][i] == p && board[1][i] == p && board[2][i] == p))
            return true;
    if ((board[0][0] == p && board[1][1] == p && board[2][2] == p) ||
        (board[0][2] == p && board[1][1] == p && board[2][0] == p))
        return true;
    return false;
}

bool isFull() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

bool makeMove(int cell, char player) {
    int row = (cell - 1) / 3;
    int col = (cell - 1) % 3;
    if (board[row][col] == 'X' || board[row][col] == 'O') return false;
    board[row][col] = player;
    undoStack.push(cell);
    MoveNode* newMove = new MoveNode(cell, player);
    newMove->next = moveHead;
    moveHead = newMove;

    return true;
}

void undoMove() {
    if (undoStack.empty()) {
        cout << "No move to undo!\n";
        return;
    }
    int cell = undoStack.top(); undoStack.pop();
    int row = (cell - 1) / 3;
    int col = (cell - 1) % 3;
    board[row][col] = '0' + cell;
    if (moveHead) {
        MoveNode* temp = moveHead;
        moveHead = moveHead->next;
        delete temp;
    }
}

int main() {
    AVLNode* leaderboard = nullptr;
    initializeBoard();

    turnQueue.push('X');
    turnQueue.push('O');

    printBoard();

    while (true) {
        char currentPlayer = turnQueue.front(); turnQueue.pop();
        int cell;
        cout << "Player " << currentPlayer << ", enter cell (1-9) or 0 to undo: ";
        cin >> cell;

        if (cell == 0) {
            undoMove();
            printBoard();
            turnQueue.push(currentPlayer);
            continue;
        }

        if (!makeMove(cell, currentPlayer)) {
            cout << "Invalid move! Try again.\n";
            turnQueue.push(currentPlayer);
            continue;
        }

        printBoard();

        if (checkWin(currentPlayer)) {
            cout << "Player " << currentPlayer << " wins!\n";
            string name;
            cout << "Enter name for leaderboard: ";
            cin >> name;
            leaderboard = insertAVL(leaderboard, name, 1);
            break;
        }

        if (isFull()) {
            cout << "It's a draw!\n";
            break;
        }

        turnQueue.push(currentPlayer);
    }

    cout << "\n?? Leaderboard:\n";
    inOrder(leaderboard);

    cout << "\n?? Move History:\n";
    MoveNode* temp = moveHead;
    while (temp) {
        cout << "Player " << temp->player << " -> Cell " << temp->cell << endl;
        temp = temp->next;
    }

    return 0;
}
