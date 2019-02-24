// Popa Daniel - Colegiul National "Aurel Vlaicu" Orastie
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int lmax=402,cmax=402,//dimensiunile maxime ale terenului
          po[4][2]={{-1,0},{0,-1},{0,1},{1,0}};
char h[lmax][cmax],u[lmax*cmax];//cum sunt culturile
int a[lmax][cmax],//a[i][j]=x, unde x e numarul parcelei
    s[lmax*cmax][2],vs=0,//stiva
    t[lmax*cmax],// t[i]=x, i=nr parcelei, t[i]=aria parcelei i
    v,m,n,nr=0;

void citire_init()
{
    FILE *fin=fopen("ferma1.in","r");
 int i;
 fscanf(fin,"%d\n%d %d\n",&v,&m,&n );
 for(i=1;i<=m;i++)
        {fscanf(fin,"%s\n",h[i]+1);}
 fclose(fin);
 //bordez marginea cu -1
 for(i=0;i<=n+1;i++)a[0][i]=a[m+1][i]=-1;
 for(i=1;i<=m;i++)a[i][0]=a[i][n+1]=-1;
}
void afis()
{
    int i;
    for(i=1;i<=m;i++)cout<<h[i]+1<<endl;
}
void afis2()
{
    int i,j;
    for(i=1;i<=m;i++)
    {
        for(j=1;j<=n;j++){cout.width(3);cout<<a[i][j];}
        cout<<endl;
    }
}
//pun coord in stiva, cresc aria suprafetei nr, si marchez ca am fost pe acolo
void push(int l, int c,int nr)
{
    vs++;s[vs][0]=l;s[vs][1]=c;t[nr]++;a[l][c]=nr;
}
//extrag coord din stiva
void pop(int &l, int &c)
{
    l=s[vs][0];c=s[vs][1];vs--;
}
//incep de la coord li,co cu suprafata nr
int arie(int li,int co,int nr)
{
    int l,c;
    unsigned char cu=h[li][co];
    vs=0;//golesc stiva si incep sa pun in ea
    push(li,co,nr);
    while(vs>0)//cat timp mai am in stiva
    {
        pop(l,c);//extrag din stiva
        //merg in cele 4 directii
        if((h[l+1][c]==cu)&&(a[l+1][c]==0))push(l+1,c,nr);
        if((h[l][c+1]==cu)&&(a[l][c+1]==0))push(l,c+1,nr);
        if((h[l-1][c]==cu)&&(a[l-1][c]==0))push(l-1,c,nr);
        if((h[l][c-1]==cu)&&(a[l][c-1]==0))push(l,c-1,nr);
    }
    return t[nr];
}

void v1()
{
    FILE *fout=fopen("ferma1.out","w");
    int i,j,ma=0,x;
    nr=0;// sunt 0 suprafete gasite la inceput
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++)
         if(a[i][j]==0)
            {
                x=arie(i,j,++nr);
                if(x>ma)ma=x;
            }
    fprintf(fout,"%d\n",ma);
    fclose(fout);
}

int bun(int l, int c, int &cu)
{   int i,j,p=0,ma=0,z,k;
    char s;

    for(i=0;i<4;i++)
        {s=h[l+po[i][0]][c+po[i][1]];
        if(((s>='a')&&(s<='z'))&&(s!=h[l][c]))
           {   z=a[l+po[i][0]][c+po[i][1]];p=t[z];for(k=0;k<4;k++)u[a[l+po[k][0]][c+po[k][1]]]=0;
               u[z]=1;
               for(j=0;j<4;j++)
                if((s==h[l+po[j][0]][c+po[j][1]])&&(u[a[l+po[j][0]][c+po[j][1]]]==0))
                     {p+=t[a[l+po[j][0]][c+po[j][1]]];u[a[l+po[j][0]][c+po[j][1]]]=1;}
               if((p!=t[z])&&(p>ma)){ma=p+1;cu=s;}
           }
        }
    return ma;
}
void v2()
{
 FILE *fout=fopen("ferma1.out","w");
    int i,j,ma=0,x,l,c,l2,c2,ma2=0,bnr=0,ku;
    char cu;
    nr=0;// sunt 0 suprafete gasite la inceput
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++)
         if(a[i][j]==0)
            {x=arie(i,j,++nr);
             if(x>ma2){ma2=x;l2=i;c2=j;}
            }
    //caut sa lipesc 2,3,4 suprafete a.i. ara lor sa fie mai mare decat cea mai mare suprafata de cultura
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++)
            {
                x=bun(i,j,ku);
                if((x>ma)&&(x>ma2)){ma=x;l=i;c=j;cu=ku;}
            }
    if(ma==0)// nu am reusit sa unesc 2 zone cresc cea mai mare zona cu o casuta
    {
        cout<<"bau"<<ma2;
        cu=h[l2][c2];bnr=a[l2][c2];
        for(i=1;(i<=m)&&(ma==0);i++) // parcurg matricea
            for(j=1;(j<=n)&&(ma==0);j++)
                if(h[i][j]!=cu)//daca casuta curenta e de alta culoare decat cea ce trebuie marita
               if(a[i+1][j]==bnr){l=i;c=j;ma=1;}//verific daca casuta adiacenta face parte din parcela ce trebuie marita
                else if(a[i][j+1]==bnr){l=i;c=j;ma=1;}
                  else if(a[i][j-1]==bnr){l=i;c=j;ma=1;}
                      else if(a[i-1][j]==bnr){l=i;c=j;ma=1;}
    }
    fprintf(fout,"%d %d\n%c\n",l,c,cu);
    fclose(fout);
}

int main()
{
    citire_init();
    if(v==1)v1();
     else v2();

    return 0;
}

    getNeighbours(231, 43);
    pair<int,char> currentSurface = getSurface();
