/**
  *  Worg
  */
#include <map>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("bvarcolaci.in", "r", stdin); FILE *fout = freopen("bvarcolaci.out", "w", stdout);

/*-------- Data --------*/
int N;
std::vector<int > a;

long long sol;
/*-------- --------*/

void ReadInput() {
  scanf("%d", &N); a.resize(N + 1);
  for(int i = 1; i <= N; i++) {
    scanf("%d", &a[i]);
  }
}

void Divide(int left, int right) {
  if(left == right) {sol++; return;}

  int mid = (left + right) >> 1;

  Divide(left, mid); Divide(mid + 1, right);

  std::map<int, int > freq, ok;
  for(int i = mid; i >= left; i--) {
    freq[a[i]]++;
    if(freq[a[i]] >= (mid - i + 1) / 2 + 1) {
      ok[a[i]] = 1;
    }
  }

  freq.clear();

  for(int i = mid + 1; i <= right; i++) {
    freq[a[i]]++;
    if(freq[a[i]] >= (i - mid) / 2 + 1) {
      ok[a[i]] = 1;
    }
  }

  int offset = right - left + 1;
  std::vector<long long > cnt(offset * 2 + 10, 0);

  for(auto& p : ok) {
    int el = p.first;
    cnt[0 + offset] = 1;

    int act = 0;
    for(int i = left; i <= mid; i++) {
      act += (a[i] == el) ? 1 : -1;

      if(i != mid) {
        cnt[act + offset]++;
      }
    }

    for(int i = 1; i < (int)cnt.size(); i++) {
      cnt[i] += cnt[i - 1];
    }

    for(int i = mid + 1; i <= right; i++) {
      act += (a[i] == el) ? 1 : -1;

      sol += cnt[act - 1 + offset];
    }

    for(int i = 0; i < (int)cnt.size(); i++) {
      cnt[i] = 0;
    }
  }
}

int main() {
  ReadInput();
  Divide(1, N);

  printf("%lld\n", sol);
  return 0;
}
