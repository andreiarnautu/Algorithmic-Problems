/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

const int kMaxInf = 2e9;

/*-------- Data --------*/
int n;
std::vector<std::pair<int, char > > v;

std::vector<int > pos;
/*-------- --------*/

int main() {
  scanf("%d ", &n); v.resize(n);

  for(int i = 0; i < n; i++) {
    scanf("%d %c", &v[i].first, &v[i].second);
    if(v[i].second == 'G') {
      pos.push_back(i);
    }
  }

  long long sol = 0;

  if(pos.empty()) {
    for(int i = 0, prevRed = -1, prevBlue = -1; i < n; i++) {
      if(v[i].second == 'R') {
        if(prevRed != -1) {
          sol += (v[i].first - prevRed);
        }
        prevRed = v[i].first;
      } else {
        if(prevBlue != -1) {
          sol += (v[i].first - prevBlue);
        }
        prevBlue = v[i].first;
      }
    }

    printf("%lld\n", sol); return 0;
  }

  //  Compute for preffix
  int prevRed = -1, prevBlue = -1;
  for(int i = 0; i < pos[0]; i++) {
    if(v[i].second == 'R') {
      if(prevRed != -1) {
        sol += (v[i].first - prevRed);
      }
      prevRed = v[i].first;
    } else {
      if(prevBlue != -1) {
        sol += (v[i].first - prevBlue);
      }
      prevBlue = v[i].first;
    }
  }

  sol += (prevRed == -1) ? 0 : v[pos[0]].first - prevRed;
  sol += (prevBlue == -1) ? 0 : v[pos[0]].first - prevBlue;

  //  Compute for suffix
  prevRed = -1, prevBlue = -1;
  for(int i = pos.back() + 1; i < n; i++) {
    if(v[i].second == 'R') {
      if(prevRed != -1) {
        sol += v[i].first - prevRed;
      } else {
        sol += v[i].first - v[pos.back()].first;
      }
      prevRed = v[i].first;
    } else {
      if(prevBlue != -1) {
        sol += v[i].first - prevBlue;
      } else {
        sol += v[i].first - v[pos.back()].first;
      }
      prevBlue = v[i].first;
    }
  }

  //  Compute for intervals
  for(int i = 0; i < (int)pos.size() - 1; i++) {
    int left = pos[i], right = pos[i + 1];

    long long opt1 = 2 * (v[right].first - v[left].first);

    prevRed = v[left].first; prevBlue = v[left].first;
    int maxRed = 0, maxBlue = 0;

    for(int j = left + 1; j < right; j++) {
      if(v[j].second == 'R') {
        maxRed = std::max(maxRed, v[j].first - prevRed);
        prevRed = v[j].first;
      } else {
        maxBlue = std::max(maxBlue, v[j].first - prevBlue);
        prevBlue = v[j].first;
      }
    }

    maxRed = std::max(maxRed, v[right].first - prevRed);
    maxBlue = std::max(maxBlue, v[right].first - prevBlue);

    long long opt2 = 3LL * (v[right].first - v[left].first) - maxRed - maxBlue;
    sol += std::min(opt1, opt2);
  }

  printf("%lld\n", sol);
	return 0;
}
