#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin=freopen("biti.in","r",stdin);
FILE *fout=freopen("biti.out","w",stdout);
long int n;
void nr_biti_1()
{
    // Functia afiseaza numarul de biti de 1 din reprezentarea lui n in baza 2.
    int nr=0;
    if(n)
        do
            nr++;
        while(n&=n-1);
    printf("%d\n",nr);
}
int low1(long n)
{
    // Returneaza cel mai nesemnificativ bit din reprezentarea in baza 2 a lui n.
    return n ^ (n & (n - 1));
}
int indexHigh1(long int n)
{
    n = n | (n >> 1);
    n = n | (n >> 2);
    n = n | (n >> 4);
    n = n | (n >> 8);
    n = n | (n >> 16);
//    return count(n) - 1;
}
int main()
{
    int nr=0;
    scanf("%d",&n);
    while(n)
    {
        n>>=1;
        ++nr;
    }
    printf("%d\n",nr-1);
   // nr_biti_1();
    printf("%d\n",low1(n));
    printf("%d\n",indexHigh1(n));
    return 0;
}

