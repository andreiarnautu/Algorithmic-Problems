#include <fstream>
using namespace std;
ifstream in("chibrituri.in");
ofstream out("chibrituri.out");

int m,n,mm,nn,v[10],o[10];
void ora(int i,int j)
{
    nn=0;mm=0;
    nn=v[i%10]; mm=o[i%10];
    i/=10;
    nn+=v[i%10]; mm+=o[i%10];
    nn+=v[j%10]; mm+=o[j%10];
    j/=10;
    nn+=v[j%10]; mm+=o[j%10];
}

int main()
{
    int ok=0,ii=0,jj=0,iii=0,jjj=0,pos=0;
    in>>n>>m;
    v[0]=4;o[0]=2;
    v[1]=2;o[1]=0;
    v[2]=2;o[2]=3;
    v[3]=2;o[3]=3;
    v[4]=3;o[4]=1;
    v[5]=2;o[5]=3;
    v[6]=3;o[6]=3;
    v[7]=2;o[7]=1;
    v[8]=4;o[8]=3;
    v[9]=3;o[9]=3;
    for(int i=0;i<24;i++)
        for(int j=0;j<60;j++)
        {
            ora(i,j);
            if(nn==n && mm==m)
            {
                if(ok==0)
                {
                    ii=i;
                    jj=j;
                    ++ok;
                }
                iii=i;
                jjj=j;
                ++pos;
            }
        }
    out<<pos<<endl;
    if(ii<10)
        out<<"0"<<ii<<":";
    else
        out<<ii<<":";
    if(jj<10)
        out<<"0"<<jj<<endl;
    else
        out<<jj<<endl;
    if(iii<10)
        out<<"0"<<iii<<":";
    else
        out<<iii<<":";
    if(jjj<10)
        out<<"0"<<jjj<<endl;
    else
        out<<jjj<<endl;
}
