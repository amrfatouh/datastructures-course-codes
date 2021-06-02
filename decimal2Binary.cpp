#include <iostream>
using namespace std;

void decimal2Binary(int n) {
  if (n > 0) {
    decimal2Binary(n / 2);
    cout << n % 2;
  }
}

int main() {
  
  decimal2Binary(10);
  return 0;
}