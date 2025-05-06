#include <iostream>
#include <queue>
#include <list>
#include <unordered_map>
#include <unordered_set>

using namespace std;
class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val)
	{
		data = val;
		left = right = nullptr;
		
	}
};

void dfsTree(Node* root) 
{
    if (root == nullptr)
    {
    	 return;
	}
    cout << root->data << " ";
    dfsTree(root->left);
    dfsTree(root->right);
}

void bfsTree(Node* root) 
{
    if (root == nullptr)
    {
    	return;
	}
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) 
	{
        Node* temp = q.front();
        q.pop();
        cout << temp->data << " ";
        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);
    }
}

class Graph {
public:
    unordered_map<int, list<int>> adj;

    void addEdge(int u, int v) 
	{
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfsGraph(int start, unordered_set<int>& visited) 
	{
        visited.insert(start);
        cout << start << " ";
        for (int neighbor : adj[start]) 
		{
            if (visited.find(neighbor) == visited.end()) 
			{
                dfsGraph(neighbor, visited);
            }
        }
    }

    void bfsGraph(int start) 
	{
        queue<int> q;
        unordered_set<int> visited;

        q.push(start);
        visited.insert(start);

        while (!q.empty()) 
		{
            int curr = q.front();
            q.pop();
            cout << curr << " ";

            for (int neighbor : adj[curr]) 
			{
                if (visited.find(neighbor) == visited.end()) 
				{
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
    }
};

int main() {
    // Tree
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    cout << "DFS Tree: ";
    dfsTree(root);
    cout << "\n";

    cout << "BFS Tree: ";
    bfsTree(root);
    cout << "\n";

    // Graph
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);

    unordered_set<int> visitedNodes;
    cout << "DFS Graph: ";
    g.dfsGraph(1, visitedNodes);
    cout << "\n";

    cout << "BFS Graph: ";
    g.bfsGraph(1);
    cout << "\n";

    // Clean up tree memory (important to avoid memory leaks in real applications)
    delete root->left->right;
    delete root->left->left;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}
