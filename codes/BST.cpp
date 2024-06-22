#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int key) {
        this->key = key;
        this->left = this->right = nullptr;
    }
};

class BST {
public:
    Node* root;

    BST() {
        root = nullptr;
    }

    // Function to insert a new key in the BST
    Node* insert(Node* node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        }

        return node;
    }

    // Function to search a given key in the BST
    Node* search(Node* node, int key) {
        if (node == nullptr || node->key == key) {
            return node;
        }

        if (key < node->key) {
            return search(node->left, key);
        } else {
            return search(node->right, key);
        }
    }

    // Function to perform inorder traversal of the BST
    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
    }

    // Function to insert a key
    void insert(int key) {
        root = insert(root, key);
    }

    // Function to search a key
    bool search(int key) {
        return search(root, key) != nullptr;
    }

    // Function to perform inorder traversal
    void inorder() {
        inorder(root);
        cout << endl;
    }
};

// Driver Code
int main() {
    BST tree;
    int choice, key;

    while (true) {
        cout << "1. Insert\n2. Search\n3. Inorder Traversal\n4. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                tree.insert(key);
                break;
            case 2:
                cout << "Enter key to search: ";
                cin >> key;
                if (tree.search(key)) {
                    cout << "Key found in the BST." << endl;
                } else {
                    cout << "Key not found in the BST." << endl;
                }
                break;
            case 3:
                cout << "Inorder Traversal: ";
                tree.inorder();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
