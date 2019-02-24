#include <fstream>
#include <cstring>
using namespace std;
ifstream in("nrcuv.in");
ofstream out("nrcuv.out");
char s[201],des[]=".,?!  -";
int main()
{
    int k=0,nrc=0;
    in.get(s,sizeof(s));
    while(k<strlen(s))
    {
        if(strchr(des,s[k])==NULL)
        {
            ++nrc;
            while(strchr(des,s[k])==NULL || (s[k]=='-' && strchr(des,s[k+1])==NULL))
            {
                ++k;
            }
        }
        ++k;
    }
    out<<nrc;
    return 0;
}
