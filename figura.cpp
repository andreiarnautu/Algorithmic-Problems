#include <fstream>
using namespace std;
ifstream in("figura.in");
ofstream out("figura.out");
int n,d,x[400],y[400],m[400][400];
int vecini(int xx,int yy)
{
    int nr=0;
    if(m[xx-1][yy]==2)
        ++nr;
    if(m[xx+1][yy]==2)
        ++nr;
    if(m[xx][yy-1]==2)
        ++nr;
    if(m[xx][yy+1]==2)
        ++nr;
    return nr;
}

int main()
{
    int i,s=0,j=0;
    in>>d>>n;
    for(i=0;i<n;i++)
    {
        in>>x[i];
        x[i]--;
        in>>y[i];
        y[i]--;
        m[x[i]*2+1][y[i]*2+1]=1;
    }
    for(i=0;i<n;i++)
    {
        m[x[i]*2+1-1][y[i]*2+1]+=2;
        m[x[i]*2+1+1][y[i]*2+1]+=2;
        m[x[i]*2+1][y[i]*2+1-1]+=2;
        m[x[i]*2+1][y[i]*2+1+1]+=2;
    }
    for(i=0;i<n;i++)
        s+=vecini(x[i]*2+1,y[i]*2+1);
    out<<s;
    return 0;
}
