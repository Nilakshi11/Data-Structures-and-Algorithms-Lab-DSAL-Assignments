#include <iostream>
using namespace std;

class Node
{
    int data, lbit, rbit;
    Node *left, *right;
public:
    Node()
    {
        data = lbit = rbit = 0;
        left = right = NULL;
    }
    Node(int x)
    {
        data = x;
        lbit = rbit = 0;
        left = right = NULL;
    }
    friend class TBT;
};

class TBT
{
    Node *root, *head;
public:
    TBT()
    {
        head = new Node(0);
        head->lbit = head->rbit = 1;
        head->left = head;
        head->right = root;
        root = NULL;
    }
    void create()
    {
        int n;
        cout << "Keep entering values and 0 to stop: " << endl;
        while (1)
        {
            cin >> n;
            if (n == 0)
            {
                break;
            }
            insert(n);
        }
    }
    void insert(int x)
    {
        if (root == NULL)
        {
            root = new Node(x);
            root->left = root->right = head;
            root->lbit = root->rbit = 0;
            head->left = root;
            return;
        }
        int flag = 0;
        Node *T = root;
        Node *newnode = new Node(x);

        while (flag != 1)
        {
            if (x < T->data)
            {
                if (T->lbit == 0)
                {
                    newnode->right = T;
                    newnode->left = T->left;
                    newnode->lbit = newnode->rbit = 0;
                    T->left = newnode;
                    T->lbit = 1;
                    flag = 1;
                }
                else
                {
                    T = T->left;
                }
            }
            else if (x > T->data)
            {
                if (T->rbit == 0)
                {
                    newnode->left = T;
                    newnode->right = T->right;
                    newnode->lbit = newnode->rbit = 0;
                    T->right = newnode;
                    T->rbit = 1;
                    flag = 1;
                }
                else
                {
                    T = T->right;
                }
            }
            else
            {
                cout << "Duplicate entries..." << endl;
                return;
            }
        }
    }

    void inorder()
    {
        Node *T = root;
        if (T == NULL)
        {
            cout << "Tree is empty." << endl;
            return;
        }
        while (T->lbit == 1)
        {
            T = T->left;
        }
        while (T != head)
        {
            cout << T->data << " ";
            if (T->rbit == 0)
            {
                T = T->right;
            }
            else
            {
                T = T->right;
                while (T->lbit == 1)
                {
                    T = T->left;
                }
            }
        }
        cout << endl;
    }

    void preorder()
    {
        Node *T = root;
        if (T == NULL)
        {
            cout << "Tree is empty." << endl;
            return;
        }
        while (T != head)
        {
            cout << T->data << " ";
            if (T->lbit == 1)
            {
                T = T->left;
            }
            else if (T->rbit == 1)
            {
                T = T->right;
            }
            else
            {
                while (T != head && T->rbit == 0)
                {
                    T = T->right;
                }
                if (T != head)
                {
                    T = T->right;
                }
            }
        }
        cout << endl;
    }

    Node* inorderSuccessor(Node* p)
    {
        if (p->rbit == 0)
        {
            return p->right;
        }
        p = p->right;
        while (p->lbit == 1)
        {
            p = p->left;
        }
        return p;
    }

    void deleteNode(int x)
    {
        Node *p = root, *par = head;
        while (p != head)
        {
            if (x == p->data)
            {
                break;
            }
            par = p;
            if (x < p->data)
            {
                if (p->lbit == 0)
                {
                    break;
                }
                p = p->left;
            }
            else
            {
                if (p->rbit == 0)
                {
                    break;
                }
                p = p->right;
            }
        }
        if (p == head)
        {
            cout << "Node not found." << endl;
            return;
        }

        Node *target = p;
        if (p->lbit == 1 && p->rbit == 1)
        {
            Node *succ = inorderSuccessor(p);
            p->data = succ->data;
            par = p;
            p = succ;
        }
        if (p->lbit == 0 && p->rbit == 0)
        {
            if (par->left == p)
            {
                par->left = p->left;
                par->lbit = 0;
            }
            else
            {
                par->right = p->right;
                par->rbit = 0;
            }
        }
        else
        {
            Node *child = (p->lbit == 1) ? p->left : p->right;
            if (par->left == p)
            {
                par->left = child;
            }
            else
            {
                par->right = child;
            }
        }
        delete p;
    }

    void displayMenu()
    {
        int choice, value;
        do
        {
            cout << "\nMenu: \n";
            cout << "1. Create Threaded Binary Search Tree\n";
            cout << "2. Inorder Traversal (Non-Recursive)\n";
            cout << "3. Preorder Traversal (Non-Recursive)\n";
            cout << "4. Delete a Node\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    create();
                    break;
                case 2:
                    cout << "Inorder Traversal: ";
                    inorder();
                    break;
                case 3:
                    cout << "Preorder Traversal: ";
                    preorder();
                    break;
                case 4:
                    cout << "Enter value to delete: ";
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
    TBT t;
    t.displayMenu();
    return 0;
}
