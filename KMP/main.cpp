#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> buildNext(const string &P) {
  vector<int> next(P.length(), 0);
  int i = 0, x = 1;
  int now = 0;
  while (x < P.length()) {
    if (P[now] == P[x]) {
      now += 1;
      x++;
      next[i++] = now;
    } else if (now)
      now = next[now - 1];
    else {
      next[i++] = 0;
      x++;
    }
  }
  return next;
}

int strStr(const string &haystack, const string &needle) {
  if (needle.empty() || haystack.empty() || haystack.length() < needle.length())
    return -1;
  vector<int> next = buildNext(needle);
  int i = 0, j = 0;
  while (i < haystack.length() && j < needle.length()) {
    if (haystack[i] == needle[j]) {
      i++;
      j++;
    } else if (j)
      j = next[j - 1];
    else
      i++;
  }
  return (j == needle.length()) ? i - needle.length() : -1;
}

void printVec(const vector<int> &vec) {
  for (auto num : vec)
    cout << num << " ";
  cout << endl;
}

int main() {
  // string P{"abcabdddabcabc"};
  // string P{"abcabc"};
  string S{"adcadcaddcadde"}, P{"adcadde"};
  vector<int> vec = buildNext(P);
  printVec(vec);
  cout << strStr(S, P) << endl;
  return 0;
}

