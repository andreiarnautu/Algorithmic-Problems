//Emanuela Cerchez, 100 puncte
#include <cstdio>
#define JMax 50
#define NMax 501
using namespace std;
int P, nrJ;
int a[JMax+1][NMax];
int lista[NMax][2];

void read();
void sortare(int);


int main()
{
 int i, j, max1, pozmax1, k, max2, pozmax2;
 int inc[JMax+1];
 FILE * fout;
//out<<"!@!@!";
 read();
 for (i=1; i<=JMax; i++)
     if (a[i][0]) nrJ++;

 fout=fopen("concurs.out","w");
 fprintf(fout,"%d\n",nrJ);
 for (i=1; i<=JMax; i++)
     if (a[i][0]) fprintf(fout,"%d ",a[i][0]);
 fprintf(fout,"\n");

 for (i=1; i<=JMax; i++)
     if (a[i][0]) sortare(i);

 for (j=1; j<=JMax; j++) inc[j]=1;

 for (k=1; k<=P; i++)
     {
     //determina max1 si max2
     max1=max2=0; pozmax1=pozmax2=0;
     for (j=1; j<=JMax; j++)
         if (a[j][0]>max1) {max2=max1; pozmax2=pozmax1; max1=a[j][0]; pozmax1=j;}
            else
            if (a[j][0]>max2){max2=a[j][0]; pozmax2=j;}
     //distribuie primii 2 elevi in lista
     lista[k][0]=pozmax1;
     lista[k][1]=a[pozmax1][inc[pozmax1]];
     if (max2)
        {lista[k+1][0]=pozmax2;
         lista[k+1][1]=a[pozmax2][inc[pozmax2]];}
     k+=2;
     //elimina elevii repartizati
     a[pozmax1][0]--; a[pozmax2][0]--;
     inc[pozmax1]++;  inc[pozmax2]++;
     }

 for (i=1; i<=P; i++)
     fprintf(fout,"%d %d\n", lista[i][0], lista[i][1]);
 fclose(fout);
 return 0;
}


void read()
{
 int i, el, jud;
 FILE * fin = fopen("concurs.in", "rt");
 fscanf(fin, "%d", &P);
 for (i=1; i<=P; i++)
     {fscanf (fin,"%d %d",&jud, &el);
      a[jud][0]++;
      a[jud][a[jud][0]]=el;
     }
 fclose(fin);
}


void sortare (int i)
{
int ok, j, aux;
do
{  ok=1;
   for (j=1; j<a[i][0]; j++)
       if (a[i][j]>a[i][j+1])
          {aux=a[i][j];
           a[i][j]=a[i][j+1];
           a[i][j+1]=aux;
           ok=0;
          }

}
while (!ok);
}

