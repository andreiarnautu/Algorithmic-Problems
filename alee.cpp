#include<fstream>
#include<iostream>
using namespace std;
short a[176][176]={{0}};
short col[30626],lin[30626];
ifstream in("alee.in");
ofstream out("alee.out");
int main()
{
    int i,j,k,i1,j1,i2,j2,p,u,n,m,x,y;
    in>>n>>m;// nr de obstacole;
    for (i=0;i<m;i++)
    {
         in>>x>>y; // coordontale obstacolelor,elem din labirint din coltul din stanga sus fiind de coordonate 1, 1
         a[x][y]=-1;
    }

    in>>i1>>j1; // coordonatele printului / de la care pornim
    a[i1][j1]=1;
    in>>i2>>j2; // coordonatele printesei / unde trebuie sa ajungem
    // utilizam 2 vectori lin si col, gestionati ca si o coada in care avem coordonatele locatiilor din matrice
    //in vederea explorarii vecinilor lor
    lin[1]=i1;
    col[1]=j1;
    p=1;u=1;
    m=n;
    while (p<=u)
    {


        i=lin[p];j=col[p]; // suntem la elem de coordonate i si j, ii verificam vecini
        if (i>1 && a[i-1][j]==0)
        {
            a[i-1][j]=a[i][j]+1;
            u++; // adaugam coordonatele acestei noi locatii in vederea
            lin[u]=i-1;
            col[u]=j;
        }
        if (i<n && a[i+1][j]==0)
        {
            a[i+1][j]=a[i][j]+1;
            u++; // adaugam coordonatele acestei noi locatii in vederea
            lin[u]=i+1;
            col[u]=j;
            if (lin[u]==i2 && col[u]==j2)
                break;
        }
        if (j>1 && a[i][j-1]==0)
        {
            a[i][j-1]=a[i][j]+1;
            u++; // adaugam coordonatele acestei noi locatii in vederea
            lin[u]=i;
            col[u]=j-1;
            if (lin[u]==i2 && col[u]==j2)
                break;
        }
        if (j<m && a[i][j+1]==0)
        {
            a[i][j+1]=a[i][j]+1;
            u++; // adaugam coordonatele acestei noi locatii in vederea
            lin[u]=i;
            col[u]=j+1;
            if (lin[u]==i2 && col[u]==j2)
                break;
        }
    p++; // merg la urmatorul elem
    }
  //  out<<i2<<" "<<j2;
    out<<a[i2][j2];
    return 0;
}
