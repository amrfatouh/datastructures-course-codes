#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;

int sum(vi v) {
  if (v.size() == 1) {
    return v[0];
  }
  int totalSum = v.back() + sum(vi(v.begin(), v.end() - 1));
  return totalSum;
}

int main() {
  
  vi v(10, 5);
  cout << sum(v);

  return 0;
}