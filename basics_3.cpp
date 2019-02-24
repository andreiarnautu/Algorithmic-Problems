#include <iostream>
#include <cmath>
using namespace std;
int n, nrsol,c[30];
void afisare()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            if(j==c[i])
                cout<<"*";
            else
                cout<<"o";
        cout<<endl;
    }
    cout<<endl;
}
void plaseaza(int k)
{
    int i,j,ok;
    if(k==n)
        afisare();
    else
        for(i=0;i<n;i++)
        {
            for(ok=1,j=0;j<k;j++)
                if(c[j]==i || abs(c[j]-i)==k-j)
                    ok=0;
            if(ok)
            {
                c[k]=i;
                plaseaza(k+1);
            }
        }
}
int main()
{
    cin>>n;
    plaseaza(0);
    return 0;
}
