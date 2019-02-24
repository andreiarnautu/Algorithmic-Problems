#include <cstdio>
using namespace std;
FILE *fin=freopen("iepurasi.in","r",stdin);
FILE *fout=freopen("iepurasi.out","w",stdout);
int N, M, P[250002], T[250002], D, Val[13], Vmax[28000], F[13];
long long S;
void Read()
{
    int x;
    scanf("%d%d%d",&N,&M,&D);
    for(int i=1; i<= N*M ; ++i)
        scanf("%d",&P[i]);
    for(int i=1; i<= N*M ; ++i)
    {
        int x;
        scanf("%d",&x);
        F[x] = 1;
        for(int j=1 ; j<=12/x ; ++j)
            if( Val[ j * x ] < P[i] )
                Val[ j * x ] = P[i];
    }
  //  for(int i=1; i<=12 ;++i)
      //  printf("%d ",F[i]);
}

int Cmmdc(int a, int b)
{
    int r;
    while(b)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

void Solve()
{
    int Dim = 1;
    if( F[8] )
        Dim *= 8;
    else if( F[4] || F[12])
        Dim *= 4;
    else if( F[2] || F[6] || F[10])
        Dim *= 2;
    if( F[9] )
        Dim *= 9;
    else if( F[3] || F[6] || F[12])
        Dim *= 3;
    if( F[5] || F[10] )
        Dim *= 5;
    if( F[7] )
        Dim *= 7;
    if( F[11] )
        Dim *= 11;
  //  printf("%d",Dim);
    for(int i=1 ; i<= Dim ; ++i)
    {
        for(int j=1 ; j<=12 ; ++j)
            if( ( i % j ==0 ) && Val[j] > Vmax[i] )
                Vmax[i] = Val[j];
        S += Vmax[i];
    }
    S = S * ( D / Dim );
    for(int i=1 ; i<= D % Dim ; ++i)
        S += Vmax[i];
    printf("%lld",S);
}

int main()
{
    Read();
    Solve();
    return 0;
}
