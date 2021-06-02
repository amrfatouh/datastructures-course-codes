#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
using namespace std;

typedef vector<int> vi;

class TreeNode {
protected:
  int data;
  TreeNode* left;
  TreeNode* right;
public:
  TreeNode(int d, TreeNode* l = NULL, TreeNode* r = NULL) {
    data = d;
    left = l;
    right = r;
  }
  void setData(int d) {
    data = d;
  }
  void setLeft(TreeNode* l) {
    left = l;
  }
  void setRight(TreeNode* r) {
    right = r;
  }
  int getData() {
    return data;
  }
  TreeNode* getLeft() {
    return left;
  }
  TreeNode* getRight() {
    return right;
  }
  void print() {
    cout << "data: " << data << endl;

    cout << "left: ";
    if (left != NULL)
      cout << left->data;
    else
      cout << "NULL";
    cout << endl;

    cout << "right: ";
    if (right != NULL)
      cout << right->data;
    else
      cout << "NULL";
    cout << endl;
  }
  friend class BinaryTree;
};

class BinaryTree {
  TreeNode* root;
public:
  BinaryTree(TreeNode* r = NULL) {
    root = r;
  }

  TreeNode* getRoot() {
    return root;
  }
  BinaryTree getLeftSubTree() {
    return BinaryTree(root->left);
  }
  BinaryTree getRightSubTree() {
    return BinaryTree(root->right);
  }
  bool empty() {
    return (root == NULL);
  }

  void print() {
    printSubTree(root);
  }

  void printSubTree(TreeNode* n) {
    if (root == NULL)
    {
      cout << "The tree is empty" << endl;
      return;
    }
    if (n->left == NULL && n->right == NULL) {
      cout << n->data << ": NULL, NULL" << endl;
      return;
    }
    cout << n->data << ": ";
    if (n->left != NULL)
      cout << n->left->data << ", ";
    else
      cout << "NULL, ";
    if (n->right != NULL)
      cout << n->right->data;
    else
      cout << "NULL";
    cout << endl;
    
    if (n->left != NULL)
      printSubTree(n->left);
    if (n->right != NULL)
      printSubTree(n->right);
  }

  TreeNode* search(int x) {
    if (root == NULL)
      return NULL;
    TreeNode* p = root;
    while (p != NULL) {
      if (p->data == x)
        return p;
      else if (x < p->data)
        p = p->left;
      else
        p = p->right;
    }
    return NULL;
  }

  bool insert(int x) {
    if (root == NULL) {
      root = new TreeNode(x);
      return true;
    }
    TreeNode* p = root;
    while (p != NULL) {
      if (p->data == x) {
        return false;
      }
      else if (x < p->data) {
        if (p->left == NULL) {
          p->left = new TreeNode(x);
          return true;
        }
        else {
          p = p->left;
        }
      }
      else {
        if (p->right == NULL) {
          p->right = new TreeNode(x);
          return true;
        }
        else {
          p = p->right;
        }
      }
    }
  }
  
  void remove(int x) {
    if (root == NULL)
      return;
    TreeNode* p = root, *parent = root;
    char dir;
    while (p != NULL) {
      if (p->data == x) {
        if (p->left == NULL && p->right == NULL) {
          if (p == root) {
            delete root;
            root = NULL;
            return;
          }
          delete p;
          if (dir == 'l') {
            parent->left = NULL;
          }
          else {
            parent->right = NULL;
          }
          return;
        }
        else if (p->left != NULL && p->right == NULL) {
          if (p == root) {
            root = root->left;
            delete p;
            return;
          }
          if (dir == 'l')
            parent->left = p->left;
          else
            parent->right = p->left;
          delete p;
          return;
        }
        else if (p->left == NULL && p->right != NULL) {
          if (p == root) {
            root = root->right;
            delete p;
            return;
          }
          if (dir == 'l')
            parent->left = p->right;
          else
            parent->right = p->right;
          delete p;
          return;
        }
        else {
          TreeNode* q = p->left, *qParent = p;
          char qDir = 'l';
          while (q->right != NULL)
          {
            qParent = q;
            q = q->right;
            qDir = 'r';
          }
          if (q->left == NULL)
          {
            if (qDir == 'l')
              qParent->left = NULL;
            else
              qParent->right = NULL;
            p->data = q->data;
            delete q;
            return;
          }
          else {
            if (qDir == 'l')
              qParent->left = q->left;
            else
              qParent->right = q->left;
            p->data = q->data;
            delete q;
            return;
          }
        }
      }
      else if (x < p->data) {
        parent = p;
        dir = 'l';
        p = p->left;
      }
      else {
        parent = p;
        dir = 'r';
        p = p->right;
      }
    }
    return;
  }

  ~BinaryTree() {
    deleteSubTree(root);
  }
  void deleteSubTree(TreeNode* n) {
    if (n != NULL) {
      if (n->left == NULL && n->right == NULL) {
        delete n;
        return;
      }
      if (n->left != NULL)
        deleteSubTree(n->left);
      if (n->right != NULL)
        deleteSubTree(n->right);
    }
    }
};

int main() {

  //testing remove()
  /*
  example tree structure
  example 1 - 4:
  5: 3, 6
  3: 2, 4
  2: NULL, NULL
  4: NULL, NULL
  6: NULL, 7
  7: NULL, NULL
  */

  //removing a leave 
  BinaryTree t1;
  t1.insert(5);
  t1.insert(3);
  t1.insert(2);
  t1.insert(4);
  t1.insert(6);
  t1.insert(7);

  t1.remove(7);
  t1.print();
  cout << endl;


  //removing a node having 1 direct child
  BinaryTree t2;
  t2.insert(5);
  t2.insert(3);
  t2.insert(2);
  t2.insert(4);
  t2.insert(6);
  t2.insert(7);

  t2.remove(6);
  t2.print();
  cout << endl;


  //removing a node having 2 direct children
  BinaryTree t3;
  t3.insert(5);
  t3.insert(3);
  t3.insert(2);
  t3.insert(4);
  t3.insert(6);
  t3.insert(7);

  t3.remove(3);
  t3.print();
  cout << endl;


  //removing a root node having 2  direct children
  BinaryTree t4;
  t4.insert(5);
  t4.insert(3);
  t4.insert(2);
  t4.insert(4);
  t4.insert(6);
  t4.insert(7);

  t4.remove(5);
  t4.print();
  cout << endl;


  //removing root node having no children
  BinaryTree t5;
  t5.insert(5);

  t5.remove(5);
  t5.print();
  cout << endl;


  //removing root node having 1 direct children
  BinaryTree t6;
  t6.insert(5);
  t6.insert(6);

  t6.remove(5);
  t6.print();
  cout << endl;

  ////testing search
  ////making tree
  //TreeNode n1(5);
  //TreeNode n2(3);
  //TreeNode n3(6);
  //n1.setLeft(&n2);
  //n1.setRight(&n3);

  //TreeNode n4(2);
  //TreeNode n5(4);
  //n2.setLeft(&n4);
  //n2.setRight(&n5);

  //BinaryTree t(&n1);
  //
  ////testing finding the root
  //TreeNode* p = t.search(5);
  //cout << p->getData() << endl;
  ////testing finding left child of root
  //p = t.search(3);
  //cout << p->getData() << endl;
  ////testing finding last child
  //p = t.search(4);
  //cout << p->getData() << endl;
  ////testing finding right child of root
  //p = t.search(6);
  //cout << p->getData() << endl;
  ////testing finding an element not in the tree
  //p = t.search(9);
  //cout << (p == NULL);

  return 0;
}