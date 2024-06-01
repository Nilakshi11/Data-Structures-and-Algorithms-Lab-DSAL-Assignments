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
    Tree()
    {
        root = NULL;
    }
    Node* getroot()
    {
        return root;
    }
    void create()
    {
        root = insert();
    }
    Node* insert()
    {
        Node *temp = new Node();
        int ch;
        cout << "Enter the data: ";
        cin >> temp->data;
        cout << "Do you want to insert data in left of " << temp->data << "(0/1): ";
        cin >> ch;
        if (ch)
        {
            temp->left = insert();
        }
        cout << "Do you want to insert data in right of " << temp->data << " (0/1): ";
        cin >> ch;
        if (ch)
        {
            temp->right = insert();
        }
        return temp;
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
    void inordernr()
    {
        Node *T = root;
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
    void preodernr()
    {
        Node *T = root;
        stack<Node*> s;
        while (T != NULL)
        {
            cout << T->data << " ";
            s.push(T);
            T = T->left;
        }
        while (!s.empty())
        {
            T = s.top();
            s.pop();
            T = T->right;
            while (T != NULL)
            {
                cout << T->data << " ";
                s.push(T);
                T = T->left;
            }
        }
    }
    int height(Node *T)
    {
        if (T == NULL)
        {
            return -1;
        }
        return max(height(T->left), height(T->right)) + 1;
    }
    void mirrorimage(Node *T)
    {
        if (T == NULL)
        {
            return;
        }
        mirrorimage(T->left);
        mirrorimage(T->right);
        Node *temp = T->left;
        T->left = T->right;
        T->right = temp;
    }
    void levelwise(Node *T)
    {
        if (T == NULL)
        {
            return;
        }
        queue<Node*> q;
        q.push(T);

        while (!q.empty())
        {
            Node *current = q.front();
            q.pop();
            cout << current->data << " ";

            if (current->left)
            {
                q.push(current->left);
            }
            if (current->right)
            {
                q.push(current->right);
            }
        }
    }
    Node* insertNode(Node *T, int x)
    {
        if (T == NULL)
        {
            T = new Node(x);
            return T;
        }
        if (x < T->data)
        {
            T->left = insertNode(T->left, x);
        }
        else if (x > T->data)
        {
            T->right = insertNode(T->right, x);
        }
        else
        {
            cout << "Duplicate entry..." << endl;
        }
        return T;
    }
    int findMax(Node *T)
    {
        while (T->right != NULL)
        {
            T = T->right;
        }
        return T->data;
    }
    int findMin(Node *T)
    {
        while (T->left != NULL)
        {
            T = T->left;
        }
        return T->data;
    }
    bool search(Node *T, int x)
    {
        while (T != NULL)
        {
            if (x < T->data)
            {
                T = T->left;
            }
            else if (x > T->data)
            {
                T = T->right;
            }
            else
            {
                return true;
            }
        }
        return false;
    }
    void displayMenu()
    {
        int choice, value;
        do
        {
            cout << "\n---- Menu ---- \n";
            cout << "1. Insert a new node\n";
            cout << "2. Find numbers of nodes in longest path\n";
            cout << "3. Minimum and maximum data value found in tree\n";
            cout << "4. Swap Tree\n";
            cout << "5. Search an element\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    cout << "Enter value to insert: ";
                    cin >> value;
                    root = insertNode(root, value);
                    break;
                case 2:
                    cout << "Number of nodes in longest path (height): " << height(root) + 1 << endl;
                    break;
                case 3:
                    if (root != NULL)
                    {
                        cout << "Minimum value: " << findMin(root) << endl;
                        cout << "Maximum value: " << findMax(root) << endl;
                    }
                    else
                    {
                        cout << "Tree is empty." << endl;
                    }
                    break;
                case 4:
                    mirrorimage(root);
                    cout << "Swapped left and right pointers at every node." << endl;
                    break;
                case 5:
                    cout << "Enter value to search: ";
                    cin >> value;
                    if (search(root, value))
                    {
                        cout << "Element found in tree." << endl;
                    }
                    else
                    {
                        cout << "Element not found in tree." << endl;
                    }
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
