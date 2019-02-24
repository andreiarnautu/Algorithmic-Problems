/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("boom.in", "r", stdin); FILE *fout = freopen("boom.out", "w", stdout);

const int kMaxInf = 1e9;

/*-------- Structures --------*/
struct Trio {
    int cost, state, prev, gasApplied;

    Trio(const int _cost, const int _state, const int _prev, const int _gasApplied) {
        cost = _cost; state = _state; prev = _prev; gasApplied = _gasApplied;
    }

    bool operator <(const Trio &other) const {
        return this->cost > other.cost;
    }
};
/*-------- Data --------*/
int N, M;
std::vector<std::pair<int, int > > gas;

std::vector<int > minCost;
std::vector<std::pair<int, int > > prev;
std::priority_queue<Trio > heap;
/*-------- --------*/

int NextState(int crtState) {
    int state = 0;
    for(int i = 0; i < N; i++) {
        if((i > 0 && (crtState & (1 << (i - 1)))) || (i + 1 < N && (crtState & (1 << (i + 1))))) {
            state ^= (1 << i);
        }
    }

    return state;
}

int main() {
    scanf("%d%d", &N, &M);

    for(int i = 0; i < M; i++) {
        int cost, q, mask = 0; scanf("%d%d", &cost, &q);
        for(int j = 0; j < q; j++) {
            int bit; scanf("%d", &bit); bit--;
            mask ^= (1 << bit);
        }

        gas.emplace_back(mask, cost);
    }

    //!  Run dijkstra on states
    minCost = std::vector<int >(1 << N, kMaxInf);
    prev = std::vector<std::pair<int, int > >(1 << N, {kMaxInf, kMaxInf});

    heap.emplace(0, (1 << N) - 1, kMaxInf, kMaxInf);

    while(!heap.empty()) {
        auto p = heap.top(); heap.pop();

        if(minCost[p.state] != kMaxInf) continue;
        minCost[p.state] = p.cost; prev[p.state] = {p.prev, p.gasApplied};

        if(p.state == 0) break;

        //!  Obtain next states
        for(int i = 0; i < M; i++) {
            int state = p.state ^ (p.state & gas[i].first);
            state = NextState(state);

            if(minCost[state] == kMaxInf) {
                heap.emplace(p.cost + gas[i].second, state, p.state, i + 1);
            }
        }
    }

    printf("%d\n", minCost[0]);

    std::vector<int > sol;
    int state = 0;
    while(state != kMaxInf) {
        sol.push_back(prev[state].second);
        state = prev[state].first;
    }
    sol.pop_back();

    std::reverse(sol.begin(), sol.end());
    printf("%d\n", (int)sol.size());

    for(auto& itr : sol) {
        printf("%d\n", itr);
    }

	return 0;
}
