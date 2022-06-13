#include <iostream>
#include <string>
#include <vector>

//https://contest.yandex.ru/contest/37787/run-report/68526748/

std::string Str(const std::vector<int> &pref) {
  std::string res = "a";
  for (int i = 1; i < pref.size(); ++i) {
    if (pref[i] == 0) {
      std::vector<bool> char_used(26);
      int char_last = pref[i - 1];
      while (char_last > 0) {
        char_used[res[char_last] - 'a'] = true;
        char_last = pref[char_last - 1];
      }
      int i = 1;
      while (true) {
        if (!char_used[i]) {
          res += 'a' + i;
          break;
        }
        ++i;
      }
    } else {
      res += res[pref[i] - 1];
    }
  }
  return res;
}

int main() {
  std::vector<int> pi;
  int a;
  while (std::cin >> a) {
    pi.push_back(a);
  }
  std::cout << Str(pi);

  return 0;
}
