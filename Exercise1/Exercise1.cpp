#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k): key(k), left(nullptr), right(nullptr){}
};

Node* createPerfectBST(const vector<int>& sortedKeys, int start, int end) {
    if (start > end) return NULL;
    int n = end - start + 1;
    int mid = start + n / 2;

    Node* root = new Node(sortedKeys[mid]);
    root->left = createPerfectBST(sortedKeys, start, mid - 1);
    root->right = createPerfectBST(sortedKeys, mid + 1, end);
    return root;
}

Node* createPerfectBST(const vector<int>& sortedKeys) {
    return createPerfectBST(sortedKeys, 0, sortedKeys.size() - 1);
}

void preorderTraversal(Node* root) {
    if (root) {
        std::cout << root->key << " ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}
void inorderTraversal(Node* root) {
    if (root) {
        inorderTraversal(root->left);
        std::cout << root->key << " ";
        inorderTraversal(root->right);
    }
}
void postorderTraversal(Node* root) {
    if (root) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        std::cout << root->key << " ";
    }
}
void levelOrderTraversal(Node* root) {
    if (!root) return;
    queue<Node*>q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        bool hasRealNode = 0;
        for (int i = 0; i < size; i++) {
            Node* temp = q.front();
            q.pop();
            if (temp) {
                std::cout << temp->key << " ";
                q.push(temp->left);
                q.push(temp->right);
                if (temp->right || temp->left) {
                    hasRealNode = 1;
                }
            }
            else {
                std::cout << "NULL ";
                q.push(NULL);
                q.push(NULL);
            }
        }
        if (!hasRealNode) break;
        std::cout << endl;
    }
}
bool search(Node* root, int key, vector<int>& comparisions) {
    if (!root) return false;
    if (root->key > key) {
        comparisions.push_back(root->key);
        return search(root->left, key, comparisions);
    }
    else if (root->key < key) {
        comparisions.push_back(root->key);
        return search(root->right, key, comparisions);
    }
    else {
        comparisions.push_back(root->key);
        return true;
    }
}
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
bool binarySearch(const vector<int>& arr, int key, vector<int>& comparisions) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        comparisions.push_back(arr[mid]);
        if (key == arr[mid]) {
            return true;
        }
        else if (key > arr[mid]) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return false;
}
int main()
{
    vector<int>sortedKeys = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
    Node* root = createPerfectBST(sortedKeys);

    std::cout << "Inorder Traversal: ";
    inorderTraversal(root);
    std::cout << endl;

    std::cout << "PostOrder Traveral: ";
    postorderTraversal(root);
    std::cout << endl;

    std::cout << "Preorder Traversal: ";
    preorderTraversal(root);
    std::cout << endl;

    std::cout << "Level Order Traversal: " << endl;
    levelOrderTraversal(root);
    
    int testKey = 7;
    vector<int>bstComparisions;
    bool foundInBST = search(root, testKey, bstComparisions);
    vector<int>binarySearchComparisions;
    bool foundInArray = binarySearch(sortedKeys, testKey, binarySearchComparisions);

    std::cout << "\nSearch for key " << testKey << ":" << endl;
    std::cout << "BST search comparisions: ";
    for (int comp : bstComparisions) {
        std::cout << comp << " ";
    }
    std::cout << endl;

    std::cout << "Binary search comparisions: ";
    for (int comp : binarySearchComparisions) {
        std::cout << comp << " ";
    }
    std::cout << endl;

    deleteTree(root);
    return 0;
}