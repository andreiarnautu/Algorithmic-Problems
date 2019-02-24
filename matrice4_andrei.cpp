#include <fstream>
#include <algorithm>

using namespace std;
ifstream cin("matrice4.in");
ofstream cout("matrice4.out");

int prim(int x)
{
    int div,nrDiv=0,p;
    for(p=x;p<=x+100;p++)
    {
        nrDiv=0;
         for(div=1;div*div<=p;div++)
          {

            if(p%div==0)
            {

            if(div==p/div)
              nrDiv++;
            if(div!=p/div)
              nrDiv+=2;
            }
          }
      if(nrDiv==2)
      {
            return p;
            break;
      }
    }

}




int a[55][55],b[55][55],c[1000];
int main()
{
   int m,n,i,j,r=0,maxim=0;
    cin>>n>>m;

    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            cin>>a[i][j];
        }
    }

    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            b[i][j]=prim(a[i][j])-a[i][j];
            if(b[i][j] > maxim) {
                maxim = b[i][j];
            }
        }
    }


    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
           if(b[i][j] == maxim)
           {
               r++;
               c[r]=a[i][j]+maxim;
           }
        }
    }

    sort(c+1,c+r+1);


    cout << maxim + 1 << " " << r << '\n'; //  maxim+1 fiindca se pune si runda initiala
    for(i=1;i<=r;i++)
    {
        cout<<c[i]<<" ";
    }

    return 0;
}
