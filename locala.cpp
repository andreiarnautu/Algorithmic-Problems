/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("locala.in", "r", stdin); FILE *fout = freopen("locala.out", "w", stdout);

int main() {
  int N, Na, Nb; scanf("%d%d%d", &N, &Na, &Nb);
  std::vector<int > mins(Na), maxs(Nb);

  for(auto& itr : mins) {
    scanf("%d", &itr);
  }
  for(auto& itr : maxs) {
    scanf("%d", &itr);
  }

  std::sort(mins.begin(), mins.end()); std::sort(maxs.begin(), maxs.end());

  if(N == 1 && Na == 1 && Nb == 1) {
    printf("1\n"); return 0;
  }
  if(Na == 0 || Nb == 0 || std::abs(Na - Nb) > 1 || mins[0] != 1 || maxs.back() != N || mins.back() == N || maxs[0] == 1) {
    printf("-1\n"); return 0;
  }

  std::vector<int > v;
  if(Na == Nb + 1) {
    for(int i = 0; i < Nb; i++) {
      v.push_back(mins[i]); v.push_back(maxs[i]);
    }
    v.push_back(mins.back());
  } else {
    for(int i = 0; i < Na; i++) {
      v.push_back(maxs[i]); v.push_back(mins[i]);
    }
    if(Nb == Na + 1) {
      v.push_back(maxs.back());
    }
  }

  std::vector<int > seen(N + 1, 0);
  for(auto& itr : v) {
    seen[itr]++;
    if(seen[itr] == 2) {
      printf("-1\n"); return 0;
    }
  }

  std::vector<int > ans;
  int cursor = 1, gap = 0;
  while(cursor <= N && gap + 1 < (int)v.size()) {
    int a = std::min(v[gap], v[gap + 1]), b = std::max(v[gap], v[gap + 1]);

    std::vector<int > insertHere;
    while(cursor <= b) {
      if(seen[cursor]) {cursor++; continue;}
      if(cursor < a) {printf("-1\n"); return 0;}

      insertHere.push_back(cursor); cursor++;
    }
    ans.push_back(v[gap]);
    if(v[gap] == b) {std::reverse(insertHere.begin(), insertHere.end());}
    for(auto& itr : insertHere) {
      ans.push_back(itr);
    }

    gap++;
  }
  for(int i = gap; i < (int)v.size(); i++) {
    ans.push_back(v[i]);
  }

  if(ans.size() != N) {printf("-1\n"); return 0;}


  std::vector<int > mins2, maxs2;
  for(int i = 0; i < N; i++) {
    if(i == 0) {
      if(ans[0] < ans[1]) {
        mins2.push_back(ans[0]);
      } else {
        maxs2.push_back(ans[0]);
      }
    } else if(i == N - 1) {
      if(ans[i] < ans[i - 1]) {
        mins2.push_back(ans[i]);
      } else {
        maxs2.push_back(ans[i]);
      }
    } else {
      if(ans[i] > ans[i - 1] && ans[i] > ans[i + 1]) {
        maxs2.push_back(ans[i]);
      } else if(ans[i] < ans[i - 1] && ans[i] < ans[i + 1]){
        mins2.push_back(ans[i]);
      }
    }
  }

  if(mins != mins2 || maxs != maxs2) {
    printf("-1\n"); return 0;
  }
  for(auto& itr : ans) {
    printf("%d ", itr);
  }
	return 0;
}
