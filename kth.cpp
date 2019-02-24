/**
  *  Worg
  */
#include <set>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("kth.in", "r", stdin); FILE *fout = freopen("kth.out", "w", stdout);

/*-------- Structures --------*/
struct Range {
  int left, right, value;

  Range(const int _left, const int _right, const int _value) {left = _left; right = _right; value = _value;}

  bool operator <(const Range &other) const {
    if(this->left != other.left) {
      return this->left < other.left;
    }
    return this->right < other.right;
  }
};
/*-------- Data --------*/
int N, M;
std::set<Range > set;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &N, &M);
  for(int i = 1; i <= N; i++) {
    int x; scanf("%d", &x);
    set.insert({i, i, x});
  }
}

void ProcessOperations() {
  for(int i = 0; i < M; i++) {
    int type, a, b, k; scanf("%d%d%d%d", &type, &a, &b, &k);

    auto begin = set.lower_bound({a, 0, 0}), end = set.upper_bound({b + 1, 0, 0});
    if(begin == set.end() || begin->left > a) {
      begin--;
    }

    std::vector<Range > v;
    for(auto it = begin; it != end; it++) {
      v.push_back(*it);
    }
    if(type == 0) {
      std::sort(v.begin(), v.end(), [&](Range p, Range q) {
        return p.value < q.value;
      });
      int updateValue = 0;
      for(auto& itr : v) {
        int countHere = std::min(itr.right, b) - std::max(a, itr.left) + 1;

        if(countHere >= k) {
          updateValue = itr.value; break;
        }
        k -= countHere;
      }

      set.erase(begin, end);

      std::sort(v.begin(), v.end());
      if(!v.empty() && v[0].left < a) {
        set.insert({v[0].left, a - 1, v[0].value});
      }
      if(!v.empty() && v.back().right > b) {
        set.insert({b + 1, v.back().right, v.back().value});
      }
      set.insert({a, b, updateValue});
    } else {
      set.erase(begin, end);

      if(!v.empty() && v[0].left < a) {
        set.insert({v[0].left, a - 1, v[0].value});
      }
      if(!v.empty() && v.back().right > b) {
        set.insert({b + 1, v.back().right, v.back().value});
      }

      set.insert({a, b, k});
    }
  }
}

void WriteOutput() {
  for(auto& itr : set) {
    for(int i = itr.left; i <= itr.right; i++) {
      printf("%d ", itr.value);
    }
  }
}

int main() {
  ReadInput();

  ProcessOperations();

  WriteOutput();

  return 0;
}
