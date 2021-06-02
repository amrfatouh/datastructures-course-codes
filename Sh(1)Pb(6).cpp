#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;

int recursiveMax(vi v) {
  if (v.size() == 1) return v[0];
  int mid = v.size() / 2;
  int max1 = recursiveMax(vi(v.begin(), v.begin() + mid));
  int max2 = recursiveMax(vi(v.begin() + mid, v.end()));
  return max1 >= max2 ? max1 : max2;
}

int main() {
  
  vi v{ 4,9,7,51,2,12,5,13,1,8 };
  cout << recursiveMax(v);

  return 0;
}