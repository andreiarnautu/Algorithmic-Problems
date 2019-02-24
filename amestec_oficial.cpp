#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;
ifstream f("amestec.in");
ofstream g("amestec.out");
char a[101][101],num[21];
int n,k;

void deplaseaza_N(char tip)
{
   int i,j;
   for(j=0;j<=n-1;j++)
       for(i=n-1;i>=1;i--)
          if(a[i][j]!=a[i-1][j] && a[i][j]==tip)
              {if(a[i][j]=='0') {a[i][j]='1';a[i-1][j]='0';}
               else {a[i][j]='0';a[i-1][j]='1';}
               i--;
              }
}

void deplaseaza_S(char tip)
{
   int i,j;
   for(j=0;j<=n-1;j++)
       for(i=n-2;i>=0;i--)
          if(a[i][j]!=a[i+1][j] && a[i][j]==tip)
              {if(a[i][j]=='0') {a[i][j]='1';a[i+1][j]='0';}
               else {a[i][j]='0';a[i+1][j]='1';}
               i--;
              }
}

void deplaseaza_E(char tip)
{
   int i,j;
   for(i=n-1;i>=0;i--)
       for(j=0;j<=n-2;j++)
          if(a[i][j]!=a[i][j+1] && a[i][j]==tip)
              {if(a[i][j]=='0') {a[i][j]='1';a[i][j+1]='0';}
               else {a[i][j]='0';a[i][j+1]='1';}
               j++;
              }
}

void deplaseaza_V(char tip)
{
   int i,j;
   for(i=n-1;i>=0;i--)
       for(j=1;j<=n-1;j++)
          if(a[i][j]!=a[i][j-1] && a[i][j]==tip)
              {if(a[i][j]=='0') {a[i][j]='1';a[i][j-1]='0';}
               else {a[i][j]='0';a[i][j-1]='1';}
               j++;
              }
}
void citire()
{
    int i,j,durata;char sens,tip;
    f.getline(num,21);
    n=atoi(strtok(num," "));k=atoi(strtok(NULL," "));
    for(i=0;i<n;i++)
       f.getline(a[i],101);
    for(i=1;i<=k;i++)
    {
        f.getline(num,21);j=0;durata=0;
        while(!strchr("NSEV",num[j])){durata=durata*10+(num[j]-'0');j++;}
        sens=num[j];
        tip=num[j+1];
        for(j=1;j<=durata && j<=n;j++)
             if(sens=='N')deplaseaza_N(tip);
             else if(sens=='S')deplaseaza_S(tip);
                  else if(sens=='E') deplaseaza_E(tip);
                       else deplaseaza_V(tip);
    }
    f.close();
}

void afisare()
{
    for(int i=0;i<=n-1;i++)g<<a[i]<<'\n';
}

int main()
{
    citire();
    afisare();
    return 0;
}
