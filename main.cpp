#include <iostream>
#include <vector>
#include <string>

//https://contest.yandex.ru/contest/37787/run-report/68248100/

std::vector<int> ZFunction(const int &pattern, const std::string &pattern_text) {
  std::vector<int> z(pattern_text.size());
  z[0] = pattern_text.size();
  int l = 0, r = 0;
  for (int i = 1; i < pattern_text.size(); ++i) {
    if (i < r) {
      z[i] = std::min(r - i, z[i - l]);
    }
    while (i + z[i] < pattern_text.size() && pattern_text[z[i]] == pattern_text[i + z[i]]) ++z[i];
    if (i + z[i] > r) {
      l = i;
      r = i + z[i];
    }
  }
  std::vector<int> res;
  for (int i = pattern;i<z.size();++i) {
    if (z[i] == pattern) {
      res.push_back(i-pattern-1);
    }
  }
  return res;
}

int main() {
  std::string pattern;
  std::string text;
  std::cin >> pattern >> text;
  std::string pattern_text = pattern + "$" + text;
  std::vector<int> res = ZFunction(pattern.size(), pattern_text);
  for (auto elem: res) {
    std::cout << elem << " ";
  }
  return 0;
}
