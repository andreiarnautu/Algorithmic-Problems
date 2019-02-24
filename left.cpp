#include <cstdio>
#include <cstring>

#define DIM 1011
using namespace std;
int A[DIM], B[DIM], C[DIM], AA[DIM], BB[DIM], CC[DIM];
int V[DIM], W[DIM];
int N, M, i, j, mx, x;

inline int maxim(int a, int b){
	if (a>b)
		return a;
	return b;
}

int main(){
	FILE *f = fopen("left.in","r");
	FILE *g = fopen("left.out", "w");
	fscanf(f,"%d %d",&N, &M);
	for (j=1;j<=M;j++) {
		fscanf(f,"%d",&x);
		V[j] = V[j-1] + x;
	}
	for (j=1;j<=M;j++) {
		fscanf(f,"%d",&x);
		W[j] = W[j-1] + x;
		if (j==1) {
			B[j] = V[j] + W[j];
			C[j] = V[j+1] + W[j];
		} else
			if (j==M) {
				A[j] = V[j-1] + W[j];
				B[j] = V[j] + W[j];
			} else {
				A[j] = V[j-1] + W[j];
				B[j] = V[j] + W[j];
				C[j] = V[j+1] + W[j];
			}
	}

	for (i=3;i<=N;i++) {
		memcpy(AA, A, sizeof(A));
		memcpy(BB, B, sizeof(B));
		memcpy(CC, C, sizeof(C));
		for (j=1;j<=M;j++) {
			fscanf(f,"%d",&x);
			W[j] = W[j-1] + x;
			if (j==1) {
				B[j] = W[j] + CC[j];
				C[j] = W[j] + maxim(AA[j+1], BB[j+1]);
			} else
				if (j==M) {
					A[j] = W[j] + maxim(BB[j-1], CC[j-1]);
					B[j] = W[j] + AA[j];
				} else {
					A[j] = W[j] + maxim(BB[j-1], CC[j-1]);
					B[j] = W[j] + maxim(AA[j], CC[j]);
					C[j] = W[j] + maxim(AA[j+1], BB[j+1]);
				}
		}
	}

	fclose(f);

	mx = maxim(maxim(B[1], C[1]), maxim(A[M], B[M]));
	for (i=2;i<M;i++)
		if (mx < maxim(maxim(A[i], B[i]), C[i]))
			mx = maxim(maxim(A[i], B[i]), C[i]);


	fprintf(g,"%d",mx);
	fclose(g);
	return 0;
}
