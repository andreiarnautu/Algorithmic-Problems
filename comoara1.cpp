#include <fstream>
#include <cstring>
using namespace std;
ifstream in("comoara1.in");
ofstream out("comoara1.out");
int n,m,k=0,x;
char s[1001];
int cauta(int a, int b)
{
    int i,maxim=0;
    for(i=a;i<=b;i++)
        if(s[i]>maxim)
            maxim=s[i];
    //out<<maxim;
   // return 0;
    for(i=a;i<=b;i++)
        if(s[i]==maxim)
            return i;
}
int main()
{
    int i,mm;
    in>>n>>m;
    mm=m;
    in.get();
    for(i=0;i<n;i++)
    {
       in>>s[i];
    }
    while(m)
    {
        x=cauta(k,k+m);
        strcpy(s+k,s+x);
        m+=k-x;
        //out<<m<<endl;
        ++k;
    }
    //out<<mm;
    for(i=0;i<n-mm;i++)
        out<<s[i];
    return 0;
}
