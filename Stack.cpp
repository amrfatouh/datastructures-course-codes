#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;

class Node {
  //the Node class contains data and pointer to the next Node
  int data;
  Node* next;

public:
  Node(int d, Node* n = NULL) {
    data = d;
    next = n;
  }
  int getData() {
    return data;
  }
  Node* getNext() {
    return next;
  }
  void setData(int d) {
    data = d;
  }
  void setNext(Node* n) {
    next = n;
  }

  void print() {
    cout << "data: " << data << endl;
    cout << "next: " << next << endl;
  }
  friend class List;
};

class List {
  //the "List" class has only one property
  //the "chain" property points to the first node of the list
  Node* chain;
public:
  //if nothing is given to the constructor of the "List", chain is set to NULL
  List() {
    chain = NULL;
  }

  //if an integer is sent to the constructor, we set "chain" to a new Node with that value
  List(int d) {
    chain = new Node(d);
  }

  //add a node to the front of the List
  void addFront(int d) {
    //if the List is empty, set chain to a new Node
    if (chain == NULL) {
      chain = new Node(d);
      return;
    }
    //if the List is not empty, set the chain to a new Node and set the "next" of the Node that "chain" is pointing to, set that "next" to the "previous first Node"
    Node* temp = chain;
    chain = new Node(d);
    chain->next = temp;
  }

  //removes the first element in the list
  void removeFront() {
    if (chain == NULL) return;
    Node* temp = chain;
    chain = chain->next;
    delete temp;
  }

  //add a Node to the back of the List
  void push_back(int d) {
    //if the list is empty, make "chain" point to a new Node
    if (chain == NULL) {
      chain = new Node(d);
      return;
    }
    //if the List is not empty, move through the list till you reach the last Node
    //make the "next" of the last Node point to the new Node
    Node* p = chain;
    while (p->next != NULL) {
      p = p->next;
    }
    p->next = new Node(d);
  }

  //printing all elements of the List
  void print() {
    //move through the whole list & print the elements one by one
    Node* p = chain;
    while (p != NULL) {
      cout << p->data << " ";
      p = p->next;
    }
    cout << endl;
  }

  //check whether the List is empty or not
  bool isEmpty() {
    return chain == NULL;
  }

  //find a Node containing a specific value inside the List and return a pointer to that Npde if found
  //if no Nodes are found holding the value, return NULL
  Node* find(int d) {
    //move through the whole list, if found the Node holding the value, return a pointer to its place
    Node* p = chain;
    while (p != NULL) {
      if (p->data == d) {
        return p;
      }
      p = p->next;
    }
    //if no Nodes are found, return NULL
    return NULL;
  }

  //remove all Nodes containing a specific value
  void remove(int d) {
    //if the List is empty, do nothing => nothing to remove
    if (isEmpty()) return;
    //remove the first Nodes if they contain the value
    while (chain->data == d) {
      Node* temp = chain;
      chain = chain->next;
      delete temp;
    }

    //remove the Node containing the value from the middle of the List
    Node* p = chain->next; //pointer that go through the whole List
    Node* p2 = chain; //pointer to point to the previous Node of the Node that the above pointer (p) points to (so that we could link the previous Node with the next Node)
    //if a value is found in a Node, set the "next" of the previous node to point to the next Node of the current Node
    //delete the current Node
    while (p != NULL) {
      if (p->data == d) {
        Node* temp = p;
        p = p->next;
        p2->next = p;
        delete temp;
      }
      //check if "p" is equal to NULL, because it may be incremented from the previous if block
      //if p doesn't equal NULL, continue moving through the List
      if (p != NULL) {
        p = p->next;
        p2 = p2->next;
      }
    }
    return;
  }

  //returns the first element in the list
  int front() {
    if (isEmpty()) return 0;
    return chain->data;
  }

  //delete every Node in the List when destroying the List
  ~List() {
    Node* p = chain;
    while (p != NULL) {
      Node* temp = p->next;
      delete p;
      p = temp;
    }
  }
};

class Stack {
  List list;
public:
  void push(int x) {
    list.addFront(x);
  }
  int pop() {
    if (list.isEmpty()) return 0;
    int temp = list.front();
    list.removeFront();
    return temp;
  }
  int peak() {
    return list.front();
  }
};

int main() {

  Stack s;
  s.push(5);
  s.push(1);
  cout << s.peak() << endl;
  s.pop();
  cout << s.peak() << endl;

  return 0;
}