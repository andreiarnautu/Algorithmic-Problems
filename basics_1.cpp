//Recursivitate
#include <iostream>
using namespace std;
int n,x,v[21];
int functie(int p)
{
    if(p==n)
        return 0;
    if(v[p]==x)
        return 1+functie(p+1);
    return functie(p+1);
}
int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>v[i];
    cin>>x;
    cout<<functie(0);
}
