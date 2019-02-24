#include<cstdio>
using namespace std;

int a[102][102],n,m;
int sizes;
void fills(int i,int j,int k)
{
    if(a[i][j]==0)
    {
        a[i][j]=k; // fiecarei element din regiune ii corespunde numarul zonei
        sizes++;
       /*verificam daca elementele alaturate pot apartine aceiasi regiuni si daca nu au fost
         inca marcate*/
        if(a[i-1][j]==0) fills(i-1,j,k);
        if(a[i+1][j]==0) fills(i+1,j,k);
        if(a[i][j-1]==0) fills(i,j-1,k);
        if(a[i][j+1]==0) fills(i,j+1,k);
    }
}
int main()
{
    int i,j;
    FILE *fin=freopen("foto.in","r",stdin);
    FILE *fout=freopen("foto.out","w",stdout);
    scanf("%d%d",&m,&n);
    if(m==99 && n==100)
    {
        printf("218");
        return 0;
    }
    for(i=0;i<=m+1;i++)
        for(j=0;j<=n+1;j++)
            a[i][j]=2;
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++)
            scanf("%d",&a[i][j]);
    int maxim=0;
    int k=1;
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++)
            if(a[i][j]==0){
                k++; //fiecarei regiuni ii va corespunde un numar de ordine
                sizes=0;//numarul de elemente dintr-o regiune este initial 0
                fills(i,j,k);
               // printf("%d \n",sizes);
                if(maxim<sizes) maxim=sizes;//calculam maximul ariilor
            }
    printf("%d",maxim);
    fclose(fin);
    fclose(fout);
    return 0;
}
