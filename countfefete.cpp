/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("countfefete.in", "r", stdin); FILE *fout = freopen("countfefete.out", "w", stdout);

const int mod = 1e9 + 7;
const int maxN = 2e5 + 1;
const int maxLog = 31;

/*-------- Input data --------*/
int n;
int v[maxN];
std::vector<int > graph[maxN];
/*-------- Solving data --------*/
int odd[maxN], even[maxN], all[maxN];

int active[maxN], father[maxN], bitsZero[maxN][maxLog], bitsOne[maxN][maxLog];

long long sol = 0;
/*-------- --------*/

int Mod(int value) {
  if(value >= mod) {
    return value - mod;
  } else if(value < 0) {
    return value + mod;
  }
  return value;
}

void Precompute() {
  odd[0] = 0; even[0] = 1; all[0] = 1;

  for(int i = 1; i < maxN; i++) {
    odd[i] = Mod(odd[i - 1]  + even[i - 1]);
    even[i] = Mod(even[i - 1] + odd[i - 1]);
    all[i] = Mod(even[i] + odd[i]);
  }
}

void ReadInput() {
  scanf("%d", &n);

  for(int i = 1; i <= n; i++) {
    scanf("%d", &v[i]);
  }

  for(int i = 1; i < n; i++) {
    int u, v; scanf("%d%d", &u, &v);
    graph[u].push_back(v); graph[v].push_back(u);
  }
}

int Group(int node) {
  if(node != father[node]) {
    father[node] = Group(father[node]);
  }
  return father[node];
}

void Unite(int u, int v, int value) {
  u = Group(u); v = Group(v);

  for(int bit = 0; bit < maxLog; bit++) {
    int a1 = bitsOne[u][bit], b1 = bitsZero[u][bit];
    int a2 = bitsOne[v][bit], b2 = bitsZero[v][bit];

    int x0 = 1LL * even[a1] * all[b1] % mod - 1;
    int x1 = 1LL *  odd[a1] * all[b1] % mod;

    int y0 = 1LL * even[a2] * all[b2] % mod - 1;
    int y1 = 1LL *  odd[a2] * all[b2] % mod;

    int vBit = (value & (1 << bit));
    int revBit = vBit ^ (1 << bit);

    long long addHere = 0;

    if(vBit) {
      //  (x0, y0)
      if(x0 && y0) addHere = Mod(addHere + 1LL * x0 * y0 % mod * vBit % mod);
      //  (x1, y1)
      if(x1 && y1) addHere = Mod(addHere + 1LL * x1 * y1 % mod * vBit % mod);
    } else {
      //  (x0, y1)
      if(x0 && y1) addHere = Mod(addHere + 1LL * x0 * y1 % mod * revBit % mod);
      //  (x1, y0)
      if(x1 && y0) addHere = Mod(addHere + 1LL * x1 * y0 % mod * revBit % mod);
    }

    sol = Mod(sol + addHere);
    //  Unite data
    bitsOne[u][bit] += bitsOne[v][bit];
    bitsZero[u][bit] += bitsZero[v][bit];
  }

  father[v] = u;
}

void Initialize() {
  for(int i = 1; i <= n; i++) {
    father[i] = i;
    active[i] = false;

    for(int bit = 0; bit < maxLog; bit++) {
      if(v[i] & (1 << bit)) {
        bitsOne[i][bit] = 1;
      } else {
        bitsZero[i][bit] = 1;
      }
    }
  }
}

void Solve() {
  Initialize();

  std::vector<std::pair<int, int > > vals;
  for(int i = 1; i <= n; i++) {
    vals.emplace_back(v[i], i);
  }

  std::sort(vals.begin(), vals.end()); std::reverse(vals.begin(), vals.end());


  for(auto& elem : vals) {
    int value = elem.first, node = elem.second;

    for(auto& itr : graph[node]) {
      if(!active[itr]) continue;
      Unite(node, itr, value);
    }

    active[node] = true;
  }
}

int main() {
  Precompute();

  ReadInput();

  Solve();

  printf("%lld", sol);

  return 0;
}
