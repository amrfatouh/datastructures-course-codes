#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;

vi merge(vi l, vi r) {
  vi v;
  int lp = 0, rp = 0;
  for (int i = 0; i < l.size() + r.size(); i++) {
    if (lp < l.size() && rp < r.size()) {
      if (l[lp] <= r[rp]) v.push_back(l[lp++]);
      else v.push_back(r[rp++]);
    }
    else {
      while (lp < l.size()) v.push_back(l[lp++]);
      while (rp < r.size()) v.push_back(r[rp++]);
    }
  }
  return v;
}

vi mergeSort(vi v) {
  if (v.size() == 1) return v;
  int mid = v.size() / 2;
  vi l = vi(v.begin(), v.begin() + mid);
  vi r = vi(v.begin() + mid, v.end());
  l = mergeSort(l);
  r = mergeSort(r);
  v = merge(l, r);
  return v;
}

void print(vi v) {
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << endl;
}

int main() {
  
  vi v{ 4,6,2,7,9,1,5,7,4 };
  v = mergeSort(v);
  print(v);

  return 0;
}