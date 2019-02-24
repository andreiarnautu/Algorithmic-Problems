#include <fstream>
#include <cstring>
using namespace std;
ifstream in("alfabetar.in");
ofstream out("alfabetar.out");

int main()
{
    char s[100][200];
    int n,maxim=0,i,j;
    in>>n;
    in.get();
    for(i=0;i<n;i++)
    {
        in.get(s[i],sizeof(s[i]));
        in.get();
        if(strlen(s[i])>maxim)
            maxim=strlen(s[i]);
    }
    for(i=maxim-1;i>=0;i--)
    {
        for(j=0;j<n;j++)
            {
                if(i<strlen(s[j]))
                    out<<s[j][i];
                else
                    out<<" ";
            }
        out<<endl;
    }
    return 0;
}
