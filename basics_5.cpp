// Divide et Impera -> Turnurile din Hanoi
#include <iostream>
using namespace std;
void muta(int x, int i, int j)
{
    if(x>1)
    {
        muta(x-1,i,6-i-j);
        cout<<i<<" -> "<<j<<'\n';
        muta(x-1,6-i-j,j);
    }
    else
        cout<<i<<" -> "<<j<<'\n';
}
int main()
{
    int n;
    cin>>n;
    muta(n,1,2);
    return 0;
}
