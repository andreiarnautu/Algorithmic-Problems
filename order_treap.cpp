/**
  *  Worg
  */
#include <ctime>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <utility>

using namespace std;
FILE *fin = freopen("order.in", "r", stdin);
FILE *fout = freopen("order.out", "w", stdout);

/*-------- Data --------*/
int N;

struct Treap {
    Treap* left;
    Treap* right;
    long long priority;
    int value;
    int size;
};

Treap *empty_treap, *Root;
/*-------- --------*/

bool is_empty_treap(Treap *root) {
    return (root == empty_treap);
}

Treap* create_treap(int value) {
    return new Treap {
        empty_treap,
        empty_treap,
        ((1LL * rand() << 45) + (1LL * rand() << 30) + (1LL * rand() << 15) + (1LL * rand())) & 0x7fffffffffffffff,
        value,
        1
    };
}

void update_treap(Treap *root) {
    if(!is_empty_treap(root)) {
        root->size = root->left->size + root->right->size + 1;
    }
}

pair<Treap*, Treap*> split(Treap *root, int value) {
    pair<Treap*, Treap*> answer;
    if(is_empty_treap(root)) {
        answer.first = answer.second = empty_treap;
    } else if(value < root->value) {
        pair<Treap*, Treap*> t = split(root->left, value);
        answer.first = t.first;

        answer.second = root;
        answer.second->left = t.second;
        update_treap(answer.second);
    } else {
        pair<Treap*, Treap*> t = split(root->right, value);
        answer.first = root;
        answer.first->right = t.first;
        update_treap(answer.first);

        answer.second = t.second;
    }
    return answer;
}

Treap* join(Treap* first, Treap* second) {
    Treap* answer;
    if(is_empty_treap(first)) {
        answer = second;
    } else if(is_empty_treap(second)) {
        answer = first;
    } else if(first->priority > second->priority) {
        answer = first;
        answer->right = join(answer->right, second);
    } else {
        answer = second;
        answer->left = join(first, answer->left);
    }

    update_treap(answer);
    return answer;
}

Treap* insert(Treap* root, Treap* node) {
    Treap *answer;
    if(is_empty_treap(root) || node->priority > root->priority) {
        pair<Treap*, Treap*> t = split(root, node->value);
        answer = node;
        answer->left = t.first;
        answer->right = t.second;
        update_treap(answer);
    } else {
        if(node->value > root->value) {
            root->right = insert(root->right, node);
            update_treap(root);
        } else {
            root->left = insert(root->left, node);
            update_treap(root);
        }
        answer = root;
    }

    return answer;
}

Treap* insert(Treap* root, int value) {
    return insert(root, create_treap(value));
}

void print(Treap *root) {
    if(!is_empty_treap(root)) {
        print(root->left);
        printf("%d ", root->value);
        print(root->right);
    }
}

void initialize() {
    srand(time(NULL));
    Root = empty_treap = new Treap{NULL, NULL, -1, 0, 0};

    for(int i = 1; i <= N; i++) {
        Root = insert(Root, i);
    }
}

pair<Treap*, int> get_kth_element(Treap *root, int index) {
    pair<Treap*, int> answer;
    if(index < root->left->size) {
        pair<Treap*, int> t = get_kth_element(root->left, index);
        answer.first = root;
        answer.first->left = t.first;
        update_treap(answer.first);
        answer.second = t.second;
    } else if(index == root->left->size) {
        answer.first = join(root->left, root->right);
        update_treap(answer.first);
        answer.second = root->value;
        delete root;
    } else {
        pair<Treap*, int> t = get_kth_element(root->right, index - root->left->size - 1);
        answer.first = root;
        answer.first->right = t.first;
        update_treap(answer.first);
        answer.second = t.second;
    }
    return answer;
}

void simulate_changes() {
    int pos = 1;
    for(int i = 1; i <= N; i++) {
        pos = (pos + i - 1) % (N - i + 1);

        pair<Treap*, int> t = get_kth_element(Root, pos);
        Root = t.first;

        printf("%d ", t.second);
    }
}

int main() {
    scanf("%d", &N);
    initialize();
   // print(Root);
    simulate_changes();
    return 0;
}
