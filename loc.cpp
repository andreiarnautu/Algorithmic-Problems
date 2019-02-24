#include <fstream>
using namespace std;
ifstream in("loc.in");
ofstream out("loc.out");

int elev[1001]={1},scaun[1001],n;

int main()
{
    int procedura=0,j,i,k;
    in>>n;
    for(i=1;i<n+1;i++)
        in>>scaun[i];
    for(i=1;i<n+1;i++)
    {
         if(scaun[i]!=i)
         {
            ++procedura;
            k=scaun[i];
            scaun[i]=-1;
            while(scaun[i]==-1)
            {
                j=scaun[k];
                scaun[k]=k;
                k=j;
                //out<<j<<" "<<k<<endl;
            }
         }
    }
    out<<procedura;
    return 0;
}
