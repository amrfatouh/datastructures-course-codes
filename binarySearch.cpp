#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;

int binarySearch(int item, vi& v, int l, int r) {
  if (l == r) {
    if (v[l] == item) return l;
    else return -1;
  }
  int mid = (l + r) / 2;
  if (v[mid] == item) return mid;
  if (v[mid] > item) return binarySearch(item, v, l, mid - 1);
  return binarySearch(item, v, mid + 1, r);
}

int main() {

  vi v{ 1,4,5,6,7,9,23,65 };
  cout << binarySearch(66, v, 0, v.size() - 1) << endl;

  return 0;
}