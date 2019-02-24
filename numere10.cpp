#include <fstream>
#include <vector>
using namespace std;
ifstream in("numere10.in");
ofstream out("numere10.out");
vector<bool>ciur(1000000,true);
long long w[50000],p=1,x,nr,i,j,n;
int main()
{
    //scanf("%d",&n);
    w[0]=2;
    ciur[0]=false;
    ciur[1]=false;
    for(i=4;i<=500000;i+=2)
        ciur[i]=false;
    for(i=3;i<500000;i+=2)
        if(ciur[i]==true)
        {
            w[p]=i;
            ++p;
            for(j=i;i*j<500000;j+=2)
                ciur[i*j]=false;
        }
    in>>n;
    for(i=0;i<n;i++)
    {
        in>>x;
      //  if(ciur[x]==true)
         //   continue;
        for(j=0;j<p;j++)
        {
            if(x%w[j]==0 && (ciur[x/w[j]]==true) && w[j]*w[j]!=x)
            {
                ++nr;
               // out<<x<<" "<<w[j]<<" ";
                break;
            }
            if(w[j]*w[j]>x)
                break;
        }
    }
    out<<nr;
    return 0;
}
