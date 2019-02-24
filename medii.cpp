#include <cstdio>
using namespace std;
FILE *fin=freopen("medii.in","r",stdin);
FILE *fout=freopen("medii.out","w",stdout);
float media,note;
int v[12],ok;
void afiseaza(int k)
{
    int i;
    if(v[1]==0)
        return;
    for(i=1;i<=k;i++)
        printf("%d ",v[i]);
    printf("\n");
    ok=1;
}
float media_calculata(int k)
{
    int i;
    float s=0,mn=0,mc=0;
    if(k>2)
    {
        s=0;
        for(i=1;i<=k;i++)
            s+=v[i];
        mn=s/k;
        mc=(note+3*mn)/4;
        return mc;
    }
    return 0;
}
void calculeaza(int k)
{
    int i;
    if(k<11)
        for(i=v[k-1];i<=10;i++)
        {
            v[k]=i;
           // printf("%.3f \n",media_calculata(k));
            if(media_calculata(k)==media)
                afiseaza(k);
            calculeaza(k+1);
            v[k]=0;
        }
}
int main()
{
    scanf("%f%f",&media,&note);
    calculeaza(1);
    if(!ok)
        printf("NU\n");
    return 0;
}
