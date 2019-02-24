/**
  *  Worg
  */
#include <set>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

#define x first
#define y second

FILE *fin = freopen("nuke.in", "r", stdin); FILE *fout = freopen("nuke.out", "w", stdout);

const int kBufferSize = 1e5;

class InputReader {
public:
    char buffer[kBufferSize];
    int cursor;

    void getBuffer() {
      cursor = 0; fread(buffer, 1, kBufferSize, stdin);
    }

    InputReader() {
      getBuffer();
    }

    bool digit(char c) {
      return '0' <= c && c <= '9';
    }

    InputReader& operator >>(int &number) {
      char sgn = '+';
      while(!digit(buffer[cursor])) {
        sgn = buffer[cursor];
        if(++cursor == kBufferSize) {
          getBuffer();
        }
      }

      number = 0;
      while(digit(buffer[cursor])) {
        number = number * 10 + buffer[cursor] - '0';
        if(++cursor == kBufferSize) {
          getBuffer();
        }
      }

      number = (sgn == '-') ? -number : number;

      return *this;
    }
} cin;

/*-------- Data --------*/
struct Bomb {
  int x, y, r, beg, end;
  Bomb() {}
  Bomb(int _x, int _y, int _r) {x = _x; y = _y; r =_r; beg = x - r; end = x + r;}
};

struct Trio {
  int where, type, idx;
  Trio() {}
  Trio(int _where, int _type, int _idx) {where = _where; type = _type; idx = _idx;}

  bool operator <(const Trio &other) const {
    if(where != other.where) {
      return where < other.where;
    } else if(type != other.type) {
      return type < other.type;
    } else {
      return idx < other.idx;
    }
  }
};

int n, m;
std::vector<std::pair<int, int > > soldiers;
std::vector<Bomb > bombs;

std::vector<Trio > events;
std::set<std::pair<int, int > > set;

std::vector<int > sol;
/*-------- --------*/

void ReadInput() {
  cin >> n >> m; sol.resize(m);
  for(int i = 0; i < n; i++) {
    int x, y; cin >> x >> y; soldiers.emplace_back(x, y);
  }
  for(int i = 0; i < m; i++) {
    int x, y, r; cin >> x >> y >> r; bombs.emplace_back(x, y, r);
  }
}

void AddEvents() {
  for(int i = 0; i < n; i++) {
    events.emplace_back(soldiers[i].x, 1, i);
  }
  for(int i = 0; i < m; i++) {
    events.emplace_back(bombs[i].beg, 0, i);
    events.emplace_back(bombs[i].end, 2, i);
  }

  std::sort(events.begin(), events.end());
}

int InRadius(int s, int b) {
  long long rad = 1LL * bombs[b].r * bombs[b].r;
  long long dist = 1LL * (soldiers[s].x - bombs[b].x) * (soldiers[s].x - bombs[b].x) + 1LL * (soldiers[s].y - bombs[b].y) * (soldiers[s].y - bombs[b].y);

  return dist <= rad;
}

void Sweep() {
  for(auto ev : events) {
    if(ev.type == 0) {  //  Add a new bomb
      set.emplace(bombs[ev.idx].y, ev.idx);
    } else if(ev.type == 2) {  //  Delete an existing bomb
      set.erase({bombs[ev.idx].y, ev.idx});
    } else {  //  Check if the current soldier is in the radius of an active bomb
      auto it = set.upper_bound({soldiers[ev.idx].y, 3});

      if(it != set.end()) {
        sol[it->second] += InRadius(ev.idx, it->second);
      }

      if(it == set.begin()) continue;

      it--;
      sol[it->second] += InRadius(ev.idx, it->second);
    }
  }
}

int main() {
  ReadInput();

  AddEvents();

  Sweep();

  for(auto& itr : sol) {
    printf("%d\n", itr);
  }
  return 0;
}
