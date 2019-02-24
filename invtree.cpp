/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("invtree.in", "r", stdin); FILE *fout = freopen("invtree.out", "w", stdout);

/*-------- Structures --------*/
struct Trio {
  int idx;
  long long height, bonus;

  Trio() {idx = height = bonus = 0;}

  bool operator <(const Trio &other) const {
    return this->height < other.height;
  }
};
struct Arbint {
  long long maxNeed, lazy;

  Arbint() {maxNeed = lazy = 0;}
};
/*-------- Data --------*/
int N;
long long H;
std::vector<std::vector<std::pair<int, int > > > graph;

std::vector<int > where, ans;
std::vector<Trio > params;
std::vector<long long > need;
std::vector<Arbint > arbint;
/*-------- --------*/

void ReadInput() {
  scanf("%d%lld", &N, &H); graph.resize(N);
  for(int i = 1; i < N ; i++) {
    int u, v, l; scanf("%d%d%d", &u, &v, &l);
    u--; v--;
    graph[u].emplace_back(v, l); graph[v].emplace_back(u, l);
  }

  params.resize(N); need.resize(N); where.resize(N); arbint.resize(4 * N); ans = std::vector<int >(N, 0);
}

void DFS(int node, int dad, long long dist) {
  params[node].height = dist; params[node].idx = node;

  for(auto& edge : graph[node]) {
    if(edge.first != dad) {
      DFS(edge.first, node, dist + edge.second);

      params[edge.first].bonus += edge.second;
      params[node].bonus += params[edge.first].bonus;
    }
  }
}

void BuildArbint(int node, int left, int right) {
  if(left == right) {
    arbint[node].lazy = 0; arbint[node].maxNeed = params[left].height;
  } else {
    int mid = (left + right) >> 1, leftSon = node << 1, rightSon = leftSon + 1;

    BuildArbint(leftSon, left, mid); BuildArbint(rightSon, mid + 1, right);

    arbint[node].lazy = 0; arbint[node].maxNeed = std::max(arbint[leftSon].maxNeed, arbint[rightSon].maxNeed);
  }
}

void Update(int node, int left, int right, int limit, long long value) {
  int mid = (left + right) >> 1, leftSon = node << 1, rightSon = leftSon + 1;
  if(limit > right) return;

  arbint[node].maxNeed += arbint[node].lazy;
  if(left != right) {
    arbint[leftSon].lazy += arbint[node].lazy; arbint[rightSon].lazy += arbint[node].lazy;
  }
  arbint[node].lazy = 0;

  if(limit <= left) {
    arbint[node].lazy += value; return;
  }

  if(limit <= mid) {
    Update(leftSon, left, mid, limit, value);
  }
  Update(rightSon, mid + 1, right, limit, value);

  arbint[node].maxNeed = std::max(arbint[leftSon].maxNeed + arbint[leftSon].lazy, arbint[rightSon].maxNeed + arbint[rightSon].lazy);
}

int queryAns;

void Query(int node, int left, int right) {
  int mid = (left + right) >> 1, leftSon = node << 1, rightSon = leftSon + 1;
  arbint[node].maxNeed += arbint[node].lazy;
  if(left != right) {
    arbint[leftSon].lazy += arbint[node].lazy; arbint[rightSon].lazy += arbint[node].lazy;
  }
  arbint[node].lazy = 0;

  if(H >= arbint[node].maxNeed) {
    queryAns = right; return;
  }
  if(left == right) return;

  if(H >= arbint[leftSon].maxNeed + arbint[leftSon].lazy) {
    queryAns = mid;
    Query(rightSon, mid + 1, right);
  } else {
    Query(leftSon, left, mid);
  }
}

void SolveDFS(int node, int dad) {
  //!  Introduce sons in arbint
  ans[node] = 1;
  for(auto& edge : graph[node]) {
    if(edge.first != dad) {
      int son = edge.first;
      Update(1, 0, N - 1, where[son] + 1, -params[where[son]].bonus);
    }
  }

  for(auto& edge : graph[node]) {
    if(edge.first != dad) {
      int son = edge.first;
      //!  Subtract it
      Update(1, 0, N - 1, where[son] + 1, +params[where[son]].bonus);
      queryAns = -1;
      Query(1, 0, N - 1);

      if(queryAns >= where[son]) {
        SolveDFS(son, node);
      }
      Update(1, 0, N - 1, where[son] + 1, -params[where[son]].bonus);
    }
  }
}

int main() {
  ReadInput();

  DFS(0, 0, 0);

  std::sort(params.begin(), params.end());
  for(int i = 0; i < N; i++) {
    where[params[i].idx] = i;
  }

  BuildArbint(1, 0, N - 1);

  SolveDFS(0, 0);

  for(auto& itr : ans) {
    printf("%d", itr);
  }
	return 0;
}
