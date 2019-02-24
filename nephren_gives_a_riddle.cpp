/**
  *  Worg
  */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

const int kMaxN = 1e5 + 5;
const long long kMaxK = 1e18 + 10;

std::string s0 = "What are you doing at the end of the world? Are you busy? Will you save us?";
std::string s1 = "What are you doing while sending ";

long long len[kMaxN];

int main() {
  s1 += 34; s1 += 34; s1 += "? Are you busy? Will you send "; s1 += 34; s1 += 34; s1 += "?";

  int add = (int)s1.size();

  len[0] = (int)s0.size();
  for(int i = 1; i < kMaxN; i++) {
    if(kMaxK - len[i - 1] < len[i - 1] + add) {
      len[i] = kMaxK;
    } else {
      len[i] = 2 * len[i - 1] + add;
    }
  }

  int l1 = 34, l2 = 32, l3 = 2;

  int q; std::cin >> q;
  for(int i = 0; i < q; i++) {
    long long n, k; std::cin >> n >> k;

    if(k > len[n]) {
      std::cout << "."; continue;
    }

    for(int j = n; j >= 0; j--) {
      if(j == 0) {
        std::cout << s0[k - 1]; break;
      }

      if(k <= l1) {
        std::cout << s1[k - 1]; break;
      } else if(k <= l1 + len[j - 1]) {
        k -= l1;
      } else if(k <= l1 + len[j - 1] + l2) {
        std::cout << s1[k - len[j - 1] - 1]; break;
      } else if(k <= l1 + len[j - 1] + l2 + len[j - 1]) {
        k -= (l1 + len[j - 1] + l2);
      } else {
        std::cout << s1[k - len[j - 1] - len[j - 1] - 1]; break;
      }
    }
  }
	return 0;
}
