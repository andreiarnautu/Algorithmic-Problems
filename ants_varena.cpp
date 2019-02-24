#include <stdio.h>
#include <assert.h>
#include <algorithm>


using std::min;
using std::max;


struct Node {
  int size;
  long long sum; // sum include si add
  long long add;
  Node *left;
  Node *right;
};


Node* emptyNode = new Node{0, 0, 0, NULL, NULL};


void recompute(Node* root) {
  root->sum = root->left->sum + root->right->sum
            + root->add * root->size;
}


// begin = pointer catre primul element
// end = pointer imediat dupa ultimul element
Node* build(int* begin, int* end) {
  Node* root = new Node();
  root->size = end - begin;
  if (root->size == 1) {
    root->add = *begin;
    root->left = emptyNode;
    root->right = emptyNode;
  } else {
    root->add = 0;
    root->left = build(begin, begin + root->size / 2);
    root->right = build(begin + root->size / 2, end);
  }
  recompute(root);
  return root;
}


//left inclus
//right exclus
Node* update(Node* root, int left, int right, long long value) {
  assert(0 <= left && left < right && right <= root->size);
  Node* newRoot = new Node(*root);

  if (root->size == right - left) {
    newRoot->add += value;
  } else {
    if (right <= root->left->size) {
      newRoot->left = update(root->left, left, right, value);
    } else if (root->left->size <= left) {
      newRoot->right = update(root->right, left - root->left->size,
                                           right - root->left->size, value);
    } else {
      newRoot->left = update(root->left, left, root->left->size, value);
      newRoot->right = update(root->right, 0, right - root->left->size, value);
    }
  }
  recompute(newRoot);
  return newRoot;
}


//left inclus
//right exclus
long long query(Node* root, int left, int right) {
  assert(0 <= left && left < right && right <= root->size);
  if (root->size == right - left)
    return root->sum;
  else {
    long long ans = (right - left) * root->add;
    if (right <= root->left->size) {
      ans += query(root->left, left, right);
    } else if (root->left->size <= left) {
      ans += query(root->right, left - root->left->size, right - root->left->size);
    } else {
      ans += query(root->left, left, root->left->size);
      ans += query(root->right, 0, right - root->left->size);
    }
    return ans;
  }
}


int main() {
  freopen("ants.in", "r", stdin);
  freopen("ants.out", "w", stdout);
  int N, M;
  scanf("%d%d", &N, &M);
  int* A = new int[M];
  for(int i = 0; i < M; i++) {
    scanf("%d", &A[i]);
  }
  Node** roots = new Node*[1 + N];
  roots[1] = build(A, A + M);
  long long S = 0;
  for (int k = 2; k <= N; k++) {
    int P, X, Y, V, Z, T;
    scanf("%d%d%d%d%d%d", &P, &X, &Y, &V, &Z, &T);
    int L = (X + S) % M;
    int R = (Y + S) % M;
    int i = (Z + S) % M;
    int j = (T + S) % M;
    roots[k] = update(roots[P], L, R + 1, V);
    S = query(roots[k], i, j + 1);
    printf("%lld\n", S);
  }
  return 0;
}
