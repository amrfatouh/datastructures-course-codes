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
    TreeNode* p = root, * parent = root;
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
          TreeNode* q = p->left, * qParent = p;
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

  void postOrderTraverse(TreeNode* n) {
    if (n == NULL)
      return;
    postOrderTraverse(n->left);
    postOrderTraverse(n->right);
    cout << n->data;
  }
  void inOrderTraverse(TreeNode* n) {
    if (n == NULL)
      return;
    inOrderTraverse(n->left);
    cout << n->data;
    inOrderTraverse(n->right);
  }

  //determines number of nodes in a tree that starts from a given TreeNode
  int countSubNodes(TreeNode* n) {
    if (n == NULL)
      return 0;
    return countSubNodes(n->left) + countSubNodes(n->right) + 1;
  }
  //determines number of NULLs in a tree that starts from a given TreeNode
  int countSubNulls(TreeNode* n) {
    if (n == NULL)
      return 1;
    return countSubNulls(n->left) + countSubNulls(n->right);
  }

  // sums up the depth of each node in the tree and return the final summation
  int sumOfDepths(TreeNode* n, int parentDepth) {
    if (n == NULL)
      return 0;
    int myDepth = parentDepth + 1;
    return myDepth + sumOfDepths(n->left, myDepth) + sumOfDepths(n->right, myDepth);
  }
  // determines the average number of steps taken by the search method to find a node
  float foundAverageSearches() {
    return (float)sumOfDepths(root, 0) / countSubNodes(root);
  }

  // sums up the depth of each NULL in the tree and return the final summation
  int sumOfDepthsNotFound(TreeNode* n, int parentDepth) {
    int myDepth = parentDepth + 1;
    if (n == NULL)
      return myDepth;
    return sumOfDepthsNotFound(n->left, myDepth) + sumOfDepthsNotFound(n->right, myDepth);
  }
  //determines the average number of steps taken by search method when searching a non-existing node
  float notFoundAverageSearches() {
    return (float)sumOfDepthsNotFound(root, 0) / countSubNulls(root);
  }
};


// testing foundAverageSearches() and notFoundAverageSearches() methods
void testAverageSearches() {
  BinaryTree t;
  t.insert(10);
  t.insert(5);
  t.insert(3);
  t.insert(4);
  t.insert(6);
  t.insert(7);
  t.insert(8);
  t.insert(20);
  t.insert(15);
  t.insert(13);
  t.insert(18);
  t.insert(21);

  cout << "average searches needed (case found): " << t.foundAverageSearches() << endl;
  cout << "average searches needed (case not found): " << t.notFoundAverageSearches() << endl;
}

// testing remove() method
void testRemove() {
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
}

int main() {

  testRemove();

  return 0;
}

