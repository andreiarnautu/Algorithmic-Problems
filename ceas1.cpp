#include <fstream>
#include <cstdio>
#include <cstring>
using namespace std;
ifstream in("ceas1.in");
ofstream out("ceas1.out");
int c[9][5],i=0,c2[8][5],n[4],l,j,ok,t=0;
char s[16];
int main()
{
    c[0][1]=111;c[0][2]=101;c[0][3]=101;c[0][4]=101;c[0][5]=111;
    c[1][1]=10;c[1][2]=10;c[1][3]=10;c[1][4]=10;c[1][5]=10;
    c[2][1]=111;c[2][2]=1;c[2][3]=111;c[2][4]=1;c[2][5]=111;
    c[3][1]=111;c[3][2]=1;c[3][3]=111;c[3][4]=1;c[3][5]=111;
    c[4][1]=101;c[4][2]=101;c[4][3]=111;c[4][4]=1;c[4][5]=1;
    c[5][1]=111;c[5][2]=101;c[5][3]=101;c[5][4]=101;c[5][5]=111;
    c[6][1]=111;c[6][2]=100;c[6][3]=111;c[6][4]=101;c[6][5]=111;
    c[7][1]=111;c[7][2]=1;c[7][3]=1;c[7][4]=1;c[7][5]=1;
    c[8][1]=111;c[8][2]=101;c[8][3]=111;c[8][4]=101;c[8][5]=111;
    c[9][1]=111;c[9][2]=101;c[9][3]=111;c[9][4]=1;c[9][5]=111;
    i=0;
    while(i<6)
    {
        in.get(s,16);
        out<<s<<endl;
        if(s[1]=='.' || s[1]=='#')
            ++i;
        if(s[0]=='#')
            c2[1][i]+=100;
        if(s[1]=='#')
            c2[1][i]+=10;
        if(s[2]=='#')
            c2[1][i]++;

        if(s[4]=='#')
            c2[2][i]+=100;
        if(s[5]=='#')
            c2[2][i]+=10;
        if(s[6]=='#')
            c2[2][i]++;

        if(s[8]=='#')
            c2[3][i]+=100;
        if(s[9]=='#')
            c2[3][i]+=10;
        if(s[10]=='#')
            c2[3][i]++;

        if(s[11]=='#')
            c2[4][i]+=100;
        if(s[12]=='#')
            c2[4][i]+=10;
        if(s[13]=='#')
            c2[4][i]++;
        in.get();
    }
    out<<c2[1][1]<<" "<<c2[1][2]<<" "<<c2[1][3]<<" "<<c2[1][4]<<" "<<c2[1][5];
    //for(i=1;i<=4;i++)
  //  {
        for(j=0;j<10;j++)
        {
            ok=1;
            for(l=1;l<=5;l++)
            {
                if(c[j][l]%10<c2[i][l]%10)
                    ok=0;
                c[j][l]/=10;c[i][l]/=10;
                if(c[j][l]%10<c2[i][l]%10)
                    ok=0;
                c[j][l]/=10;c[i][l]/=10;
                if(c[j][l]%10<c2[i][l]%10)
                    ok=0;
            }
            if(ok==1)
            {
                n[i]=j;
                break;
            }
        }
  //  }
    out<<n[1]<<n[2]<<":"<<n[3]<<n[4];
    return 0;
}