/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("luffpar.in", "r", stdin); FILE *fout = freopen("luffpar.out", "w", stdout);

const int maxN = 2e5 + 5;
const int kMagic = 450;

/*-------- Data --------*/
int n, m;
char s[maxN];

int a[maxN];
int blockSum[maxN], blockRev[maxN], blockMin[maxN], blockMax[maxN];

/*-------- --------*/

void ReadInput() {
  scanf("%d", &n);
  scanf("%s", s);
  for(int i = 0; i < n; i++) {
    a[i] = (s[i] == '(') ? +1 : -1;
  }
}

void RefreshBlock(int idx) {
  blockMin[idx] = maxN; blockMax[idx] = -maxN; blockSum[idx] = 0;

  for(int i = idx * kMagic; i < (idx + 1) * kMagic; i++) {
    if(blockRev[idx]) {
      a[i] *= -1;
    }
    
    blockSum[idx] += a[i];
    blockMin[idx] = std::min(blockMin[idx], blockSum[idx]);
    blockMax[idx] = std::max(blockMax[idx], blockSum[idx]);
  }

  blockRev[idx] = false;
}

void Update(int left, int right) {
  int id1 = left / kMagic, id2 = right / kMagic;

  if(id1 == id2) {
    for(int i = left; i <= right; i++) {
      a[i] *= -1;
    }
    RefreshBlock(id1);

    return;
  }

  //  Update leftmost
  for(int i = left; i < (id1 + 1) * kMagic; i++) {
    a[i] *= -1;
  }
  RefreshBlock(id1);

  //  Update rightmost
  for(int i = id2 * kMagic; i <= right; i++) {
    a[i] *= -1;
  }
  RefreshBlock(id2);

  //  Update in-between
  for(int i = id1 + 1; i < id2; i++) {
    blockRev[i] ^= true; blockSum[i] *= -1;
    int a = blockMin[i] * -1, b = blockMax[i] * -1;

    blockMin[i] = std::min(a, b); blockMax[i] = std::max(a, b);
  }
}

int Query(int left, int right) {
  //printf("---(%d %d)---\n", left, right);
  int id1 = left / kMagic, id2 = right / kMagic;

  if(id1 == id2) {
    RefreshBlock(id1);

    int sum = 0;
    for(int i = left; i <= right; i++) {
      sum += a[i];
      if(sum < 0) return false;
    }

    return (sum == 0);
  }

  //  Refresh the outter blocks
  RefreshBlock(id1); RefreshBlock(id2);

  //  Start from the leftmost one
  int sum = 0;
  for(int i = left; i < (id1 + 1) * kMagic; i++) {
    sum += a[i];
    if(sum < 0) return false;
  }

  for(int i = id1 + 1; i < id2; i++) {
    if(sum + blockMin[i] < 0) return false;
    sum += blockSum[i];
  }

  for(int i = id2 * kMagic; i <= right; i++) {
    sum += a[i];
    if(sum < 0) return false;
  }

  return (sum == 0);
}

void ProcessOperations() {
  scanf("%d", &m);
  for(int i = 0; i < m; i++) {
    int type, x, y; scanf("%d%d%d", &type, &x, &y);
    x--; y--;

    if(type == 1) {
      Update(x, y);
    } else {
      printf("%d\n", Query(x, y));
    }
  }
}

int main() {
  ReadInput();

  for(int i = 0; i * kMagic < n; i++) {
    RefreshBlock(i);
  }

  ProcessOperations();

  return 0;
}
