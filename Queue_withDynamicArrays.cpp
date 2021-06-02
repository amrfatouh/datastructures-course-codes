#include <iostream>
#include <cassert>
using namespace std;

class Queue {
  int* p = NULL;
  int capacity;
  int length;
  int head;
  int tail;

public:
  //specify the capacity of the queue
  Queue(int c = 50) {
    capacity = c;
    length = 0;
    head = 0;
    tail = 0;
    p = new int[capacity];
  }

  int size() {
    return length;
  }
  bool isEmpty() {
    return length == 0;
  }
  int getHead() {
    assert(length > 0);
    return p[head];
  }
  int getTail() {
    assert(length > 0);
    return p[tail];
  }

  void print() {
    for (int i = head; i != tail; i = (i + 1) % capacity) {
      cout << p[i] << " ";
    }
    cout << p[tail] << endl;
  }

  void enqueue(int d) {
    if (length == 0) {
      p[tail] = d;
      length++;
      return;
    }
    
    if (length < capacity) {
      length++;
      tail = (tail + 1) % capacity;
      p[tail] = d;
      return;
    }

    //copying the array into a new one with larger capacity
    int* p2 = new int[capacity * 2];
    for (int i = 0, j = head; i < capacity; i++) {
      p2[i] = p[j];
      j = (j + 1) % capacity;
    }
    delete[] p;
    p = p2;
    capacity *= 2;

    //adding the new item
    length++;
    head = 0;
    tail = length - 1;
    p[tail] = d;
  }

  int dequeue() {
    int x = getHead();
    head = (head + 1) % capacity;
    length--;
    return x;
  }

  ~Queue() {
    delete[] p;
  }
};

int main() {

  Queue q(3);
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  q.dequeue();
  q.enqueue(4);
  q.enqueue(5);
  q.print();
  cout << "Size: " << q.size() << endl;
  cout << "Head: " << q.getHead() << endl;
  cout << "Tail: " << q.getTail() << endl;

  return 0;
}