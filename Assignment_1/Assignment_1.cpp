#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class Node
{
    int data;
    Node *left, *right;
public:
    Node()
    {
        data = 0;
        left = right = NULL;
    }
    Node(int x)
    {
        data = x;
        left = right = NULL;
    }
    friend class Tree;
};

class Tree
{
    Node *root;
public:
    Tree() : root(NULL) {}

    Node* getRoot()
    {
        return root;
    }

    void create()
    {
        int n;
        cout << "Keep entering values and 0 to stop: " << endl;
        while (true)
        {
            cin >> n;
            if (n == 0)
            {
                break;
            }
            root = insert(root, n);
        }
    }

    Node* insert(Node *T, int x)
    {
        if (T == NULL)
        {
            T = new Node(x);
            return T;
        }
        if (x < T->data)
        {
            T->left = insert(T->left, x);
        }
        else if (x > T->data)
        {
            T->right = insert(T->right, x);
        }
        else
        {
            cout << "Duplicate entry..." << endl;
        }
        return T;
    }

    void preorder(Node *T)
    {
        if (T == NULL)
        {
            return;
        }
        cout << T->data << " ";
        preorder(T->left);
        preorder(T->right);
    }

    void inorder(Node *T)
    {
        if (T == NULL)
        {
            return;
        }
        inorder(T->left);
        cout << T->data << " ";
        inorder(T->right);
    }

    void postorder(Node *T)
    {
        if (T == NULL)
        {
            return;
        }
        postorder(T->left);
        postorder(T->right);
        cout << T->data << " ";
    }

    void inordernr(Node *T)
    {
        stack<Node*> s;
        while (T != NULL)
        {
            s.push(T);
            T = T->left;
        }
        while (!s.empty())
        {
            T = s.top();
            s.pop();
            cout << T->data << " ";
            T = T->right;
            while (T != NULL)
            {
                s.push(T);
                T = T->left;
            }
        }
    }

    void postordernr(Node *T)
    {
        stack<Node*> s;
        Node *temp = new Node(-1);
        while (1)
        {
            while (T != NULL)
            {
                s.push(T);
                if (T->right != NULL)
                {
                    s.push(T->right);
                    s.push(temp);
                }
                T = T->left;
            }
            if (s.empty())
            {
                return;
            }
            while (!s.empty())
            {
                Node *p = s.top();
                s.pop();
                if (p == temp)
                {
                    break;
                }
                cout << p->data << " ";
            }
            if (!s.empty())
            {
                T = s.top();
                s.pop();
            }
        }
    }

    void swapNodes(Node *T)
    {
        if (T == NULL)
        {
            return;
        }
        swap(T->left, T->right);
        swapNodes(T->left);
        swapNodes(T->right);
    }

    int height(Node *T)
    {
        if (T == NULL)
        {
            return 0;
        }
        return 1 + max(height(T->left), height(T->right));
    }

    void copyTree(Node* &copyRoot, Node* originalRoot)
    {
        if (originalRoot == NULL)
        {
            copyRoot = NULL;
            return;
        }
        copyRoot = new Node(originalRoot->data);
        copyTree(copyRoot->left, originalRoot->left);
        copyTree(copyRoot->right, originalRoot->right);
    }

    int countLeaves(Node *T)
    {
        if (T == NULL)
        {
            return 0;
        }
        if (T->left == NULL && T->right == NULL)
        {
            return 1;
        }
        return countLeaves(T->left) + countLeaves(T->right);
    }

    int countInternalNodes(Node *T)
    {
        if (T == NULL || (T->left == NULL && T->right == NULL))
        {
            return 0;
        }
        return 1 + countInternalNodes(T->left) + countInternalNodes(T->right);
    }

    void eraseTree(Node* &T)
    {
        if (T == NULL)
        {
            return;
        }
        eraseTree(T->left);
        eraseTree(T->right);
        delete T;
        T = NULL;
    }

    void deleteNode(int x)
    {
        Node *c = root;
        Node *p = NULL;
        while (1)
        {
            if (x < c->data)
            {
                if (c->left == NULL)
                {
                    cout << "Data not found..." << endl;
                    return;
                }
                p = c;
                c = c->left;
            }
            else if (x > c->data)
            {
                if (c->right == NULL)
                {
                    cout << "Data not found..." << endl;
                    return;
                }
                p = c;
                c = c->right;
            }
            else
            {
                break;
            }
        }

        if (c->left != NULL && c->right != NULL)
        {
            Node *t = c->right;
            p = c;
            while (t->left != NULL)
            {
                p = t;
                t = t->left;
            }
            swap(t->data, p->data);
            c = t;
        }
        if (c->right != NULL)
        {
            if (p->left == c)
            {
                p->left = c->right;
            }
            else if (p->right == c)
            {
                p->right = c->right;
            }
            delete c;
        }
        else if (c->left != NULL)
        {
            if (p->left == c)
            {
                p->left = c->left;
            }
            else if (p->right == c)
            {
                p->right = c->left;
            }
            delete c;
        }
        else
        {
            if (p->left == c)
            {
                p->left = NULL;
            }
            else
            {
                p->right = NULL;
            }
            delete c;
        }
    }

    void displayMenu()
    {
        int choice, value;
        Tree copyTree;
        do
        {
            cout << "\nMenu: \n";
            cout << "1. Create Tree\n";
            cout << "2. Preorder Traversal (Recursive)\n";
            cout << "3. Inorder Traversal (Recursive)\n";
            cout << "4. Postorder Traversal (Recursive)\n";
            cout << "5. Inorder Traversal (Non-Recursive)\n";
            cout << "6. Postorder Traversal (Non-Recursive)\n";
            cout << "7. Swap Nodes\n";
            cout << "8. Find Height\n";
            cout << "9. Copy Tree\n";
            cout << "10. Count Leaves\n";
            cout << "11. Count Internal Nodes\n";
            cout << "12. Erase Tree\n";
            cout << "13. Delete Node\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    create();
                    break;
                case 2:
                    cout << "Preorder Traversal: ";
                    preorder(root);
                    cout << endl;
                    break;
                case 3:
                    cout << "Inorder Traversal: ";
                    inorder(root);
                    cout << endl;
                    break;
                case 4:
                    cout << "Postorder Traversal: ";
                    postorder(root);
                    cout << endl;
                    break;
                case 5:
                    cout << "Inorder Traversal (Non-Recursive): ";
                    inordernr(root);
                    cout << endl;
                    break;
                case 6:
                    cout << "Postorder Traversal (Non-Recursive): ";
                    postordernr(root);
                    cout << endl;
                    break;
                case 7:
                    swapNodes(root);
                    cout << "Swapped left and right pointers at every node." << endl;
                    break;
                case 8:
                    cout << "Height of the Tree: " << height(root) << endl;
                    break;
                case 9:
                    copyTree.eraseTree(copyTree.root); // Clean any existing copy
                    copyTree.copyTree(copyTree.root, root);
                    cout << "Tree copied successfully." << endl;
                    break;
                case 10:
                    cout << "Number of Leaves: " << countLeaves(root) << endl;
                    break;
                case 11:
                    cout << "Number of Internal Nodes: " << countInternalNodes(root) << endl;
                    break;
                case 12:
                    eraseTree(root);
                    cout << "All nodes erased." << endl;
                    break;
                case 13:
                    cout << "Enter the value to delete: ";
                    cin >> value;
                    deleteNode(value);
                    cout << "Node deleted if it existed." << endl;
                    break;
                case 0:
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 0);
    }
};

int main()
{
    Tree t;
    t.displayMenu();
    return 0;
}
