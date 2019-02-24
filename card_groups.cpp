/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

/*-------- Data --------*/
struct Str {
  long long sum, msk, cnt;

  Str() {sum = msk = cnt = 0;}

  Str(long long _sum, long long _msk, long long _cnt) {sum = _sum; msk = _msk; cnt = _cnt;}

  bool operator <(const Str &other) {
    if(this->sum != other.sum) {
      return this->sum < other.sum;
    }
    return this->cnt < other.cnt;
  }
};

int N;
std::vector<std::pair<long long, long long > > v;

std::vector<Str > arr[2];

/*-------- --------*/

std::vector<Str > Compute(std::vector<std::pair<long long, long long > > els, int type) {
  std::vector<Str > vec;

  int n = (int)els.size();
  for(int mask = 0; mask < (1 << n); mask++) {
    long long blue = 0, red = 0, cnt = 0;
    for(int i = 0; i < n; i++) {
      if(mask & (1 << i)) {
        blue += els[i].first; cnt++;
      } else {
        red += els[i].second;
      }
    }

    vec.emplace_back(type * (blue - red), mask, cnt);
  }

  std::sort(vec.begin(), vec.end());
  return vec;
}

int main() {
  scanf("%d", &N); v.resize(N);
  for(auto& itr : v) {
    scanf("%lld%lld", &itr.first, &itr.second);
  }

  arr[0] = Compute(std::vector<std::pair<long long, long long > >(v.begin(), v.begin() + N / 2), 1);
  arr[1] = Compute(std::vector<std::pair<long long, long long > >(v.begin() + N / 2, v.end()), -1);

  long long bst = N + 1, sol = 0;

  for(int i = 0, j = 0; i < (int)arr[0].size(); ) {
    while(j < (int)arr[1].size() && arr[1][j].sum < arr[0][i].sum) {
      j++;
    }

    if(j == (int)arr[1].size() || arr[1][j].sum > arr[0][i].sum) {
      i += 1; continue;
    }

    std::vector<long long > have(N, -1);

    while(j < (int)arr[1].size() && arr[1][j].sum == arr[0][i].sum) {
      have[arr[1][j].cnt] = arr[1][j].msk;
      j++;
    }

    int nxt = i;
    while(nxt < (int)arr[0].size() && arr[0][i].sum == arr[0][nxt].sum) {
      int cntLeft = arr[0][nxt].cnt;

      for(int cntRight = 0; cntRight < N; cntRight++) {
        if(have[cntRight] == -1) continue;

        if(std::abs(N - 2 * cntLeft - 2 * cntRight) < bst) {
          bst = std::abs(N - 2 * cntLeft - 2 * cntRight);
          sol = arr[0][nxt].msk ^ (have[cntRight] << (N / 2));
        }
      }

      nxt++;
    }

    i = nxt;
  }

  if(bst == N + 1) {
    printf("-1\n");
  } else {
    for(int i = 0; i < N; i++) {
      printf("%d", (sol & (1LL << i)) == 0 ? 1 : 0);
    }
  }
	return 0;
}
