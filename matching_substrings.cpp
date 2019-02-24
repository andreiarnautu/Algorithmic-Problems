/**
  *  Worg
  */
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>

//std::ifstream fin("main.in"); std::ofstream fout("main.out");

const int kMaxN = 1e5 + 5;
const long long modulo = 1e9 + 7;
const long long coef = 31;

/*-------- Data --------*/
int N, K;
std::string str[kMaxN];

int cursor;
std::map<long long, int > map;

std::string s[kMaxN * 2];
std::vector<std::pair<int, char > > graph[kMaxN * 2];
int in[kMaxN * 2], out[kMaxN * 2];

std::vector<int > ord;
std::vector<char > ch;
/*-------- --------*/

void Exit() {
  std::cout << -1; std::exit(0);
}

void DFS(int node) {
  for(int i = 0; i < (int)graph[node].size(); i++) {
    auto to = graph[node][i].first; auto c = graph[node][i].second;

    graph[node][i] = graph[node].back(); graph[node].pop_back();
    i--;

    DFS(to);
    ch.push_back(c);
  }
  ord.push_back(node);
}

int main() {
  std::cin >> N >> K;

  for(int i = 1; i <= N; i++) {
    std::cin >> str[i];

    long long h1 = 0, h2 = 0;
    for(int j = 0; j < K - 1; j++) {
      h1 = (h1 * coef + str[i][j] - 'a') % modulo;
    }
    for(int j = 1; j < K; j++) {
      h2 = (h2 * coef + str[i][j] - 'a') % modulo;
    }

    if(map[h1] == 0) {
      map[h1] = ++cursor; s[cursor] = str[i].substr(0, K - 1);
    }
    if(map[h2] == 0) {
      map[h2] = ++cursor; s[cursor] = str[i].substr(1, K - 1);
    }

    int u = map[h1], v = map[h2];
    graph[u].emplace_back(v, str[i].back());
    in[v]++; out[u]++;
  }

  int bad = 0, start = 1;
  for(int i = 1; i <= cursor; i++) {
    if(in[i] != out[i]) {
      if(in[i] > out[i] + 1 || out[i] > in[i] + 1) {
        Exit();
      }
      bad++;
      if(in[i] < out[i]) {
        start = i;
      }
    }
  }

  if(bad != 2 && bad != 0) {
    Exit();
  }

  //return 0;

  DFS(start);

  if((int)ord.size() != N + 1) Exit();

  std::reverse(ord.begin(), ord.end());
  std::reverse(ch.begin(), ch.end());

  std::cout << s[ord[0]];
  for(auto itr : ch) {
    std::cout << itr;
  }
	return 0;
}
