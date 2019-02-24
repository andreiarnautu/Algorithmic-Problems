/**
  *  Worg
  *  Mar 10, 2018
  *  6:18:34 PM
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("luffxor.in", "r", stdin); FILE *fout = freopen("luffxor.out", "w", stdout);

const int maxM = 2e5 + 5;

/*-------- Structures --------*/
struct Node {
  int count;
  Node *son[2];

  Node() {
    count = 0; son[0] = son[1] = NULL;
  }
};
/*-------- Data --------*/
int m;
int ins[maxM];

Node *root = new Node();
/*-------- --------*/

int Val(int number, int bit) {
  if(number & (1 << bit)) {
    return 1;
  }
  return 0;
}

void Insert(Node* node, int number, int bit) {
  node->count++;
  if(bit == -1) return;

  int where = Val(number, bit);

  if(node->son[where] == NULL) {
    node->son[where] = new Node();
  }
  Insert(node->son[where], number, bit - 1);
}

void Erase(Node *node, int number, int bit) {
  node->count--;
  if(bit == -1) return;

  int where = Val(number, bit);

  Erase(node->son[where], number, bit - 1);
}

int Query(Node *node, int x, int k, int bit) {
  if(bit == -1) return node->count;

  int bitK = Val(k, bit);
  int zero, unu;

  if(Val(x, bit) == 0) {
    zero = 0; unu = 1;
  } else {
    zero = 1; unu = 0;
  }

  if(bitK == 1) {
    int ans = 0;
    if(node->son[zero] != NULL) {
      ans = node->son[zero]->count;
    }
    if(node->son[unu] != NULL) {
      ans += Query(node->son[unu], x, k, bit - 1);
    }

    return ans;
  } else {
    if(node->son[zero] != NULL) {
      return Query(node->son[zero], x, k, bit - 1);
    } else {
      return 0;
    }
  }

}

int main() {
  scanf("%d", &m);
  for(int i = 0, inserted = 0; i < m; i++) {
    int type; scanf("%d", &type);

    if(type == 0) {
      int x; scanf("%d", &x);
      Insert(root, x, 31);

      ins[++inserted] = x;
    } else if(type == 1) {
      int x; scanf("%d", &x);
      Erase(root, ins[x], 31);
    } else {
      int x, k; scanf("%d%d", &x, &k);
      printf("%d\n", Query(root, x, k, 31));
    }
  }

  return 0;
}
