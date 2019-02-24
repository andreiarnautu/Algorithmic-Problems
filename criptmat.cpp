#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;
ifstream in("criptmat.in");
ofstream out("criptmat.out");

char s2[200][200];



int main()
{
    int n,i,j,k;
    char s[2000];
    in>>n;
    in.get();
    in.get(s,sizeof(s));
    for(i=0;i<strlen(s);i=i+n)
    {
        if((i/n)%2==0)
            for(j=0;j<n;j++)
                {
                    s2[i][j]=s[i+j];
                }
        if((i/n)%2==1)
            for(j=0;j<n;j++)
                {
                    s2[i][j]=s[i+n-j-1];
                }
    }
    k=strlen(s)/n;
    for(i=0;i<n;i++)
        for(j=0;j<strlen(s);j+=n)
            out<<s2[j][i];
    return 0;
}
