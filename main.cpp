#include <iostream>
#include <vector>
#include <string>

//https://contest.yandex.ru/contest/37787/run-report/68494752/

std::vector<int> EvenOddPalindrom(const std::string &s, bool flag) {
  std::vector<int> res(s.size());
  int l = 0, r = -1;
  for (int i = 0; i < s.size(); ++i) {
    if (i <= r) res[i] = std::min(r - i + 1, res[l + r - i + flag]);
    while (i + res[i] + flag < s.size() && i - res[i] - 1 >= 0 && s[i + res[i] + flag] == s[i - res[i] - 1])
      ++res[i];
    if (i + res[i] - 1 > r) {
      l = i - res[i] + 1 - flag;
      r = i + res[i] - 1;
    }
  }
  return res;
}

unsigned long long Manaker(const std::string &s) {
  std::vector<int> d1 = EvenOddPalindrom(s, false);
  std::vector<int> d2 = EvenOddPalindrom(s, true);
  unsigned long long count = 0;
  for (int i = 0; i < s.size(); ++i) {
    count += d1[i] + d2[i];
  }
  return count;
}

int main() {
  std::string s;
  std::cin >> s;
  std::cout << Manaker(s);
  return 0;
}
