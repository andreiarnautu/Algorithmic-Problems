/**
  *  Worg
  */
#include <tuple>
#include <cstdio>
#include <vector>

#define lsb(i) (i & (-i))
#define left_son (node << 1)
#define right_son ((node << 1) + 1)

using namespace std;
FILE *fin = freopen("neapuiu.in", "r", stdin);
FILE *fout = freopen("neapuiu.out", "w", stdout);

const int bufferDim = 100000;
const int MAX_N = (1 + 100000) << 1;
const int MAX_M = (1 + 100000);
const int MAX_INF = 0x3fffffff;
const int root = 1;

/*-------- Input reader --------*/
class inputReader {
private:
        char buffer[bufferDim];
        int pos = 0;

        bool digit(char c) {
            return('0' <= c && c <= '9');
        }
public:
        void getBuffer() {
            fread(buffer, 1, bufferDim, stdin);
            pos = 0;
        }

        void operator >>(int &nr) {
            nr = 0;
            while(!digit(buffer[pos]))
                if(++ pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++ pos == bufferDim)
                    getBuffer();
            }
        }
} cin;
/*-------- Input data --------*/
int vertex_count, query_count;
vector< int > graph[MAX_N];
tuple< int,int,int > queries[MAX_M];
/*-------- Eulerian DFS data--------*/
int eulerian_list[MAX_N << 1], crt_index;
int depth[MAX_N];
vector< int > apparitions[MAX_N];

int where[MAX_N], now;
int left[MAX_N], right[MAX_N];

int aib[MAX_N];
/*-------- Segment Tree data --------*/
struct Node {
    int min_depth, max_depth;
    int size;
    Node() {}
};
Node segment_tree[MAX_N << 3];
/*-------- --------*/

void read_input() {
    cin.getBuffer();
    cin >> vertex_count; cin >> query_count;

    for(int i = 1; i < vertex_count; i++) {
        int u, v; cin >> u; cin >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);

    }

    for(int i = 1; i <= query_count; i++) {
        int type, x, y = 0;
        cin >> type; cin >> x;
        if(type == 0) {
            cin >> y;
            graph[x].push_back(y);
        }
        queries[i] = make_tuple(type, x, y);
    }
}

void add_node(int node) {
    crt_index ++;
    eulerian_list[crt_index] = node;
    apparitions[node].push_back(crt_index);
}

void eulerian_dfs(int node, int crt_depth = 1, int father = -1) {
    depth[node] = crt_depth;

    add_node(node);
    now ++;
    where[node] = now;
    left[node] = now;

    for(int son : graph[node]) {
        if(son != father) {
            eulerian_dfs(son, crt_depth + 1, node);
            add_node(node);
        }
    }

    right[node] = now;
}

void construct_segment_tree(int node = 1, int left = 1, int right = crt_index) {
    if(left == right) {
        if(eulerian_list[left] <= vertex_count) {
            segment_tree[node].max_depth = depth[eulerian_list[left]];
            segment_tree[node].min_depth = depth[eulerian_list[left]];
            segment_tree[node].size = 1;
        } else {
            segment_tree[node].max_depth = 0;
            segment_tree[node].min_depth = MAX_INF;
            segment_tree[node].size = 0;
        }

    } else {
        int mid = (left + right) >> 1;
        construct_segment_tree(left_son, left, mid);
        construct_segment_tree(right_son, mid + 1, right);


        segment_tree[node].max_depth = max(segment_tree[left_son].max_depth, segment_tree[right_son].max_depth);
        segment_tree[node].min_depth = min(segment_tree[left_son].min_depth, segment_tree[right_son].min_depth);
        segment_tree[node].size = segment_tree[left_son].size + segment_tree[right_son].size;
    }
}

void add_new_apparition(int node, int left, int right, int pos) {
    if(left == right) {
        segment_tree[node].max_depth = depth[eulerian_list[left]];
        segment_tree[node].min_depth = depth[eulerian_list[left]];
        segment_tree[node].size = 1;
    } else {
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            add_new_apparition(left_son, left, mid, pos);
        } else {
            add_new_apparition(right_son, mid + 1, right, pos);
        }

        segment_tree[node].max_depth = max(segment_tree[left_son].max_depth, segment_tree[right_son].max_depth);
        segment_tree[node].min_depth = min(segment_tree[left_son].min_depth, segment_tree[right_son].min_depth);
        segment_tree[node].size = segment_tree[left_son].size + segment_tree[right_son].size;
    }
}

void delete_apparition(int node, int left, int right, int pos) {
    if(left == right) {
        segment_tree[node].max_depth = 0;
        segment_tree[node].min_depth = MAX_INF;
        segment_tree[node].size = 0;
    } else {
        int mid = (left + right) >> 1;

        if(pos <= mid) {
            delete_apparition(left_son, left, mid, pos);
        } else {
            delete_apparition(right_son, mid + 1, right, pos);
        }

        segment_tree[node].max_depth = max(segment_tree[left_son].max_depth, segment_tree[right_son].max_depth);
        segment_tree[node].min_depth = min(segment_tree[left_son].min_depth, segment_tree[right_son].min_depth);
        segment_tree[node].size = segment_tree[left_son].size + segment_tree[right_son].size;
    }
}

void get_max_depth(int node, int left, int right, int first, int last, int &answer) {
    if(first <= left && right <= last) {
        answer = max(answer, segment_tree[node].max_depth);
    } else {
        int mid = (left + right) >> 1;
        if(first <= mid) {
            get_max_depth(left_son, left, mid, first, last, answer);
        }
        if(mid < last) {
            get_max_depth(right_son, mid + 1, right, first, last, answer);
        }
    }
}

void get_left_most(int node, int left, int right, int first, int last, int wanted, int &answer, bool &found) {
    if(found == true) {
        return;
    }
    int mid = (left + right) >> 1;

    if(first <= left && right <= last) {
        if(segment_tree[node].max_depth != wanted) {
            return;
        }
        if(left == right) {
            answer = left; found = true;
        } else {
            if(segment_tree[left_son].max_depth == wanted) {
                get_left_most(left_son, left, mid, first, last, wanted, answer, found);
            } else {
                get_left_most(right_son, mid + 1, right, first, last, wanted, answer, found);
            }
        }
    } else {
        if(first <= mid) {
            get_left_most(left_son, left, mid, first, last, wanted, answer, found);
        }
        if(mid < last) {
            get_left_most(right_son, mid + 1, right, first, last, wanted, answer, found);
        }
    }
}

void get_right_most(int node, int left, int right, int first, int last, int wanted, int &answer, bool &found) {
    if(found == true) {
        return;
    }

    int mid = (left + right) >> 1;

    if(first <= left && right <= last) {
        if(segment_tree[node].max_depth != wanted) {
            return;
        }
        if(left == right) {
            answer = right; found = true;
        } else {
            if(segment_tree[right_son].max_depth == wanted) {
                get_right_most(right_son, mid + 1, right, first, last, wanted, answer, found);
            } else {
                get_right_most(left_son, left, mid, first, last, wanted, answer, found);
            }
        }
    } else {
        if(mid < last) {
            get_right_most(right_son, mid + 1, right, first, last, wanted, answer, found);
        }
        if(first <= mid) {
            get_right_most(left_son, left, mid, first, last, wanted, answer, found);
        }
    }
}

void get_min_depth(int node, int left, int right, int first, int last, int &min_depth) {
    if(first <= left && right <= last) {
        min_depth = min(min_depth, segment_tree[node].min_depth);
    } else {
        int mid = (left + right) >> 1;
        if(first <= mid) {
            get_min_depth(left_son, left, mid, first, last, min_depth);
        }
        if(mid < last) {
            get_min_depth(right_son, mid + 1, right, first, last, min_depth);
        }
    }
}


void add_aib(int pos, int value) {
    for(int i = pos; i <= now; i += lsb(i)) {
        aib[i] += value;
    }
}


void construct_aib() {
    for(int i = 1; i <= vertex_count; i++) {
        add_aib(where[i], +1);
    }
}

int aib_query(int pos) {
    int answer = 0;
    for(int i = pos; i > 0; i -= lsb(i)) {
        answer += aib[i];
    }
    return answer;
}

void process_operations() {
    for(int i = 1; i <= query_count; i++) {
        if(get< 0 > (queries[i]) == 0) {
            int node = get< 2 > (queries[i]);
            for(int where : apparitions[node]) {
                add_new_apparition(1, 1, crt_index, where);
            }
            add_aib(where[node], +1);
        } else if(get< 0 > (queries[i]) == 1) {
            int node = get< 1 > (queries[i]);
            for(int where : apparitions[node]) {
                delete_apparition(1, 1, crt_index, where);
            }
            add_aib(where[node], -1);
        } else {
            int node = get< 1 > (queries[i]);
            int max_depth = 0;
            get_max_depth(1, 1, crt_index, apparitions[node][0], apparitions[node].back(), max_depth);

            int left_most = MAX_INF, right_most = 0;
            bool found = false;
            get_left_most(1, 1, crt_index, apparitions[node][0], apparitions[node].back(), max_depth, left_most, found);

            found = false;
            get_right_most(1, 1, crt_index, apparitions[node][0], apparitions[node].back(), max_depth, right_most, found);


            int min_depth = MAX_INF, subtree_size = 0;
            get_min_depth(1, 1, crt_index, left_most, right_most, min_depth);
            subtree_size = aib_query(right[node]) - aib_query(left[node] - 1);

            printf("%d\n", (subtree_size - 1) - (min_depth - depth[node]));
        }
    }
}

int main() {
    read_input();
    eulerian_dfs(root);
    construct_segment_tree();
    construct_aib();
    process_operations();
    return 0;
}
