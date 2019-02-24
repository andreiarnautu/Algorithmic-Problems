/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

#define lsb(i) ((i) & (-i))

using std::vector;
FILE *fin = freopen("arb.in", "r", stdin);
FILE *fout = freopen("arb.out", "w", stdout);

const int kMaxN = 1 + 250000;
const int kMaxM = 1 + 500000;
const int kMaxBufferDim = 1 + 100000;

/*-------- Input Reader --------*/
class InputReader {
private:
        char buffer[kMaxBufferDim];
        int pos;

        bool digit(char c) {
            return('0' <= c && c <= '9');
        }

public:
        void GetBuffer() {
            fread(buffer, 1, kMaxBufferDim, stdin);
            pos = 0;
        }

        void operator >>(int &nr) {
            nr = 0;
            char c = '+';
            while(!digit(buffer[pos])) {
                c = buffer[pos];
                if(++pos == kMaxBufferDim) {
                    GetBuffer();
                }
            }
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == kMaxBufferDim) {
                    GetBuffer();
                }
            }
            if(c == '-') {
                nr = -nr;
            }
        }
} cin;
/*-------- Output Writer --------*/
class OutputWriter {
public:
        char buffer[kMaxBufferDim];
        int digits[20];
        int pos;

        OutputWriter() {
            pos = 0;
        }

        void Write(char c) {
            buffer[pos++] = c;
            if(pos == kMaxBufferDim) {
                fwrite(buffer, 1, kMaxBufferDim, stdout);
                pos = 0;
            }
        }

        void PartialWrite() {
            fwrite(buffer, pos, 1, stdout);
        }

        void Insert(int number) {
            int cursor = 0;
            do {
                digits[cursor++] = number % 10; number /= 10;
            }while(number > 0);
            while(cursor > 0) {
                cursor --;
                Write(digits[cursor] + '0');
            }
            Write('\n');
        }
} cout;
/*-------- Structures --------*/
struct Event {
    int where, value, level;
    bool type;
    Event() {}
    Event(const int _where, const int _value, const int _level, const bool _type) {
        where = _where; value = _value; level = _level; type = _type;
    }
    bool operator <(const Event &other) const {
        if(this->level != other.level) {
            return this->level < other.level;
        } else {
            return this->type < other.type;
        }
    }
};
/*-------- Input data --------*/
int N, M;
int cost[kMaxN];
vector<int > graph[kMaxN];
/*-------- Algorithm data --------*/
int cursor;
int start[kMaxN], finish[kMaxN], depth[kMaxN];

Event events[kMaxN + kMaxM];
int crt_event;

int aib[kMaxN];
int query_answer[kMaxM];
/*-------- --------*/

void ReadInput() {
    cin.GetBuffer();
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> cost[i];
    }
    for(int i = 2; i <= N; i++) {
        int dad; cin >> dad;
        graph[dad].push_back(i);
    }
}

void DFS(int node = 1, int level = 1) {
    cursor ++;
    //printf("%d ", node);
    start[node] = cursor; depth[node] = level;
    for(int son : graph[node]) {
        DFS(son, level + 1);
    }
    finish[node] = cursor;
    crt_event ++;
    events[crt_event] = Event(start[node], cost[node], level, 0);
}

void Update(int pos, int value) {
    for(int i = pos; i <= cursor; i += lsb(i)) {
        aib[i] += value;
    }
}

int Query(int pos) {
    int answer = 0;
    for(int i = pos; i > 0; i -= lsb(i)) {
        answer += aib[i];
    }
    return answer;
}

void ProcessEvents() {
    cin >> M;
    for(int i = 1; i <= M; i++) {
        int node, dist; cin >> node; cin >> dist;
        crt_event ++;
        events[crt_event] = Event(node, i, depth[node] + dist, 1);
    }
    std::sort(events + 1, events + N + M + 1);
    for(int i = 1; i <= N + M; i++) {
        Event event = events[i];
        if(event.type == 0) {  //  Update
            Update(event.where, event.value);
        } else {
            query_answer[event.value] = Query(finish[event.where]) - Query(start[event.where] - 1);
        }
    }
}

void WriteOutput() {
    for(int i = 1; i <= M; i++) {
        cout.Insert(query_answer[i]);
    }
    if(cout.pos > 0) {
        cout.PartialWrite();
    }
}

int main() {
    ReadInput();
    DFS();
    ProcessEvents();
    WriteOutput();
    return 0;
}
