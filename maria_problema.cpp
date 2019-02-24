/**
  *  Worg
  */
#include <fstream>

std::ifstream f("partitiinumar.in"); std::ofstream g("partitiinumar.out");

int v[50];

void Back (int n, int val, int k){
    if (n == 0){
      for (int i = 1; i < k; i++)
        g << v[i] << " ";
      g << '\n';
    }
    else {
        if (val > n) return;

        int maxI = n / val;  //  Maxim cate valori de val pot sa pun ca sa nu imi depaseasca n

        for (int i = maxI; i >= 0; i--) {
          for (int j = 0; j < i; j++) {
            v[k + j] = val;
          }
          Back (n - i * val, val + 1, k + i);
        }
    }
}

int main() {
  int n; f >> n;
  Back(n, 1, 1);
  return 0;
}
