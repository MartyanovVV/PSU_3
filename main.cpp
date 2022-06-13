#include <iostream>
#include <string>
#include <vector>

//https://contest.yandex.ru/contest/37787/run-report/68799465/

std::vector<int> SuffixArray(const std::string &s) {
  int n = s.length() + 1;
  std::vector<int> c(std::max(256, n));
  for (int i = 0; i < n; ++i) ++c[static_cast<uint8_t>(s[i])];
  for (int i = 1; i < c.size(); ++i) c[i] += c[i - 1];
  std::vector<int> smass(n);
  for (int i = n - 1; i >= 0; --i) {
    smass[--c[static_cast<uint8_t>(s[i])]] = i;
  }

  std::vector<int> pockets(n);
  c.assign(n, 0);
  int current_group = 0;
  for (int i = 0; i < n; ++i) {
    if (i != 0 && s[smass[i]] != s[smass[i - 1]]) ++current_group;
    pockets[smass[i]] = current_group;
    c[current_group] = i + 1;
  }

  std::vector<int> smass_new(n);
  std::vector<int> new_pockets(n);
  for (int k = 1; k < n; k <<= 1) {
    for (int i = n - 1; i >= 0; --i) {
      int shifted_suffix = (smass[i] - k + n) % n;
      int pocket = pockets[shifted_suffix];
      smass_new[--c[pocket]] = shifted_suffix;
    }
    std::swap(smass, smass_new);

    current_group = 0;
    c.assign(n, 0);
    for (int i = 0; i < n; ++i) {
      if (i != 0 && (pockets[smass[i]] != pockets[smass[i - 1]] ||
                     pockets[(smass[i] + k) % n] != pockets[(smass[i - 1] + k) % n])) {
        ++current_group;
      }
      new_pockets[smass[i]] = current_group;
      c[current_group] = i + 1;
    }
    std::swap(pockets, new_pockets);
  }
  return smass;
}

size_t SubstringCount(const std::vector<int> &smass, const std::string &s) {
  //Kasai
  std::vector<int> o(smass.size());
  for (int i = 0; i < smass.size(); ++i) o[smass[i]] = i;

  std::vector<int> lcp(smass.size());
  int cur_lcp = 0;
  for (int i = 0; i < s.size(); ++i) {
    if (o[i] == smass.size() - 1) continue;
    int inext = smass[o[i] + 1];
    for (; s[i + cur_lcp] == s[inext + cur_lcp]; ++cur_lcp);
    lcp[o[i]] = cur_lcp;
    cur_lcp = std::max(0, cur_lcp - 1);
  }
  //Подсчет
  size_t sum1 = 0, sum2 = 0;
  for (int i = 0; i < s.length() + 1; ++i) {
    sum1 += s.length() - o[i];
  }
  for (int i = 0; i < s.length() + 1; ++i) {
    sum2 += lcp[i];
  }
  return sum1 - sum2;
}

int main() {
  std::string s;
  std::cin >> s;
  std::vector<int> smass = SuffixArray(s);
  std::cout << SubstringCount(smass, s);
  return 0;
}
