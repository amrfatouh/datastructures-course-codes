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
  friend class LinkedList;
};

class LinkedList {
  //the "LinkedList" class has two properties
  //the "head" property points to the first node of the LinkedList
  //the "tail" property points to the last node of the linkedlist
  Node* head;
  Node* tail;
public:
  //in nothing is given to the constructor of the "LinkedList", head & tail are set to NULL
  LinkedList() {
    head = tail = NULL;
  }

  //if an integer is sent to the constructor, we set "head" and "tail" to a new Node with that value
  LinkedList(int d) {
    head = tail = new Node(d);
  }

  //returns the data in the head of the linked list
  int getHead() {
    return head->data;
  }

  //returns the data in the tail of the linked list
  int getTail() {
    return tail->data;
  }

  //add a node to the front of the LinkedList
  void push_front(int d) {
    //if the LinkedList is empty, set head and tail to a new Node
    if (head == NULL) {
      head = tail = new Node(d);
      return;
    }
    //if the LinkedList is not empty, set the head to a new Node and set the "next" of the Node that "head" is pointing to, set that "next" to the "previous first Node"
    Node* temp = head;
    head = new Node(d);
    head->next = temp;
  }

  //add a Node to the back of the LinkedList
  void push_back(int d) {
    //if the LinkedList is empty, make "head" and "tail" point to a new Node
    if (head == NULL) {
      head = tail = new Node(d);
      return;
    }
    //if the LinkedList is not empty, add a new node to the tail node
    //make the tail pointer points to the new node
    tail->next = new Node(d);
    tail = tail->next;
  }

  //remove head from the linked list
  void pop_front() {
    //the case where the linked list is empty
    if (isEmpty()) return;

    //the case where the linked list has only one element
    if (head == tail) {
      delete head;
      head = tail = NULL;
      return;
    }

    //the case where the linked list has more than one element
    Node* temp = head;
    head = head->next;
    delete temp;
  }

  //removes the tail of the linked list
  void pop_back() {
    //the case where the linked list is empty
    if (isEmpty()) return;

    //the case where the linked list has only one element
    if (head == tail) {
      delete head;
      head = tail = NULL;
      return;
    }

    Node* current = head->next;
    Node* prev = head;
    while (current != tail) {
      current = current->next;
      prev = prev->next;
    }
    
    tail = prev;
    tail->next = NULL;
    delete current;
  }

  //printing all elements of the LinkedList
  void print() {
    //move through the whole LinkedList & print the elements one by one
    Node* p = head;
    while (p != NULL) {
      cout << p->data << " ";
      p = p->next;
    }
    cout << endl;
  }

  //check whether the LinkedList is empty or not
  bool isEmpty() {
    return head == NULL;
  }

  //find a Node containing a specific value inside the LinkedList and return a pointer to that Node if found
  //if no Nodes are found holding the value, return NULL
  Node* find(int d) {
    //move through the whole LinkedList, if found the Node holding the value, return a pointer to its place
    Node* p = head;
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
    //if the LinkedList is empty, do nothing => nothing to remove
    if (isEmpty()) return;
    //remove the first Nodes if they contain the value
    while (head->data == d) {
      pop_front();
    }

    //remove the Node containing the value from the middle of the LinkedList
    Node* p = head->next; //pointer that go through the whole LinkedList
    Node* p2 = head; //pointer to point to the previous Node of the Node that the above pointer (p) points to (so that we could link the previous Node with the next Node)
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
      //if p doesn't equal NULL, continue moving through the LinkedList
      if (p != NULL) {
        p = p->next;
        p2 = p2->next;
      }
    }
    return;
  }

  //delete every Node in the LinkedList when destroying the LinkedList
  ~LinkedList() {
    while (!isEmpty()) pop_front();
  }
};

int main() {

  LinkedList l;
  l.push_back(5);
  l.push_back(6);
  l.print();
  l.pop_back();
  l.pop_back();
  l.push_back(7);
  l.print();
  

  return 0;
}