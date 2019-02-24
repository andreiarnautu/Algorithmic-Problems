#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
#define maxn 200010
#define valmax 210

int N, sol;
int ST[maxn], DR[maxn], H[maxn];
int val[valmax];

/** functii calc_st() si calc_dr() se pot implementa eficient folosind o stiva **/
void calc_st() {
     memset(val, 0, sizeof(val));
     int i, j, p;

     for(i=1; i<=N; i++) {
          p = 0;
          for(j=H[i]; j<valmax; j++) {
               p = max(p, val[j]);
          }

          ST[i] = p;
          val[ H[i] ] = i;
     }
}

void calc_dr() {
     memset(val, 0, sizeof(val));
     int i, j, p;

     for(i=N; i>=1; i--) {
          p = N+1;
          for(j=H[i]; j<valmax; j++) {
               if(val[j]) p = min(p, val[j]);
          }

          DR[i] = p;
          val[ H[i] ] = i;
     }
}

int main() {
     FILE *f1=fopen("copaci2.in", "r"), *f2=fopen("copaci2.out", "w");
     int i, j, p, q;

     fscanf(f1, "%d\n", &N);
     for(i=1; i<=N; i++) {
          fscanf(f1, "%d", &H[i]);
     }

     calc_st();
     calc_dr();

     for(i=2; i<=N-1; i++) {
          //consideram copacul i ca fiind de inaltime minima din triunghiul (A, i, B)
          //poate exista cel mult un triunghi centrat in i
          p = ST[i], q = DR[i];
          if(p == 0 || q == N+1) continue;

          //trebuie sa verificam daca p vede pe i, daca q vede pe i
          //si daca p si q se vad reciproc
          if(ST[i] <= p && DR[i] >= q && DR[p] >= q && ST[q] <= p) {
               //cout<<p<<" "<<i<<" "<<q<<endl;
               sol ++;
          }
     }

     fprintf(f2, "%d\n", sol);

     fclose(f1); fclose(f2);
     return 0;
}
