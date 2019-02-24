// implementare - prof. Alin Burta
#include <fstream>
#include <cstring>
#include <cstdlib>
#define Fin "mxl.in"
#define Fou "mxl.out"
#define Max 255
#define NMax 41

using namespace std;

int N, K;
long long Tab[NMax][NMax];
char *S[NMax][NMax];

char *expand(char *Sir)
{
  char *left, *right;
  left = new char[Max];
  right = new char[Max];
  right = strchr(Sir,':')+1;
  strncpy(left, Sir, strchr(Sir,':')-Sir);
  left[strchr(Sir,':')-Sir]='\0';
  return S[atoi(left)][atoi(right)];
}


void lgtoa(long long x,char *s)
{
	int i=0;
	char ch;
	strcpy(s,"");
//	s = new char[24];
	while(x)
	{
		s[i++] = x % 10 + 48;
		x/=10;
	}
	s[i] = '\0';
	for(i=0;i<strlen(s)/2;i++)
	{
		 ch = s[strlen(s)-i-1];
		 s[strlen(s)-i-1] = s[i];
		 s[i] = ch;
    }
}

long long ValCelula(char *Sir)
{
     //determina valoarea din celula specificata
     char *left, *right;
     left = new char[Max];
     right = new char[Max];
     right = strchr(Sir,':')+1;
     strncpy(left, Sir, strchr(Sir,':')-Sir);
     left[strchr(Sir,':')-Sir]='\0';
     return Tab[atol(left)][atol(right)];
}

int rezolva()
{
    char *tmp = new char[Max];
    char *termen;
    char *Copy = new char[Max];
    int i,j, ok, OKT=0;
    long long sum;
    for(i=1;i<=N;i++)
      for(j=1;j<=N;j++)
      {
         if(strlen(S[i][j]) && strchr(S[i][j],'='))  //este formula
         {
            OKT = 1;
            sum = 0; ok = 1;  //pp ca se poate calcula
            strcpy(Copy, S[i][j]+1);
            termen = strtok(Copy, "+");
            while (termen)
            {
               if(strchr(termen,':'))
                  if(!strchr(expand(termen),'=')) sum+=ValCelula(termen);
                  else ok=0;
               else sum+=atoll(termen);
               termen = strtok(NULL,"+");
            }
            if(ok) {Tab[i][j]=sum; lgtoa(sum, tmp); S[i][j]=strdup(tmp); }
         }
      }
    return OKT;
}

int main()
{
    ifstream f(Fin);
    ofstream g(Fou);
    int i, j, Lin, Col;
    char Val[Max];
    //citesc datele de intrare
    f>>N>>K; f.get();
    for(i=1;i<=N;i++)
       for(j=1;j<=N;j++) { Tab[i][j]=0; S[i][j]=strdup(""); }
    for(i=1;i<=K;i++)
    {
       f>>Lin; f.get();
       f>>Col; f.get();
       f.get(Val, Max); f.get();
       if(!strchr(Val,'='))
        {
            Tab[Lin][Col]=atoll(Val);
            S[Lin][Col]  =strdup(Val);
        }
       else
        {
            S[Lin][Col]=strdup(Val);
        }
    }

    while (rezolva());


    for(i=1;i<=N;i++)
      {
        for(j=1;j<N;j++) g<<Tab[i][j]<<' ';
        g<<Tab[i][N]<<'\n';
      }

    f.close();
    g.close();
    return 0;
}
