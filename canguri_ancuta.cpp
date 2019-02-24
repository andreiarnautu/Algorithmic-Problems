# include<cstdio>
# include<cmath>
FILE *f=fopen("canguri.in","r"); //
FILE *g=fopen("canguri.out","w"); // Am marit putin dimensiunile vectorilor. Cu 2-3 elemente, ca sa fim sigur ca nu se depaseste limita vectorului nici pe cazurile mari.
long long pr[102],n,a[502],r=1; // Cand declari vectorii global nu e nevoie sa ii initializezi cu 0, pentru ca sunt deja initializati cu 0
long long cmmmc() // Daca ai declarata o variabila globala( in cazul tau n) , nu e nevoie sa o mai pui ca si parametru la functie
                // Adica poti lasa int cmmmc()
{
    long long d=0,i,m,x; // Iti dadea kill by signal pentru ca tu declarasei int si valorile depaseau int. Plus ca tu in a pusesei 100 de elemente, si maximul e de 500. Aici dadea kill by signal. :)
    for(i=0;i<=n-1;i++)
    {
        x=a[i];
        for(d=2;x>1;d++)
        {
            m=0;
            while(x%d==0)
            {
                m++;
                x/=d;
            }
            if(m!=0 && pr[d]<=m) pr[d]=m;
        }
    }
    for(i=2;i<100;i++)
    {
        if(pr[i]>0)
            r*=pow((double)i,(double)pr[i]); // In general functiile pow si sqrt au nevoie de acel (double), pentru a nu da erori.
    }
    return r;
}
int main()
{
    long long rez=1,i, maxim=0;
    fscanf(f,"%d",&n);
    for(i=0;i<=n-1;i++)
    {
        fscanf(f,"%d",&a[i]);
        if( a[i] > maxim )
            maxim = a[i]; // Am adaugat variabila maxim in care stocam cea mai mare valoare din vectorul a.
    }
    fclose(f);
    rez=cmmmc();
    // Aici ai rez=cmmmc(). Ideea e ca nu tb tot timpul sa inmultesti cu 3, ci numai daca rez < 3 * maxim, adica doar sa te asiguri ca pana si cangurul care sare cel mai mult face minim 3 sarituri.
    if( maxim * 3 > rez ) //verifici
    { // Acum tb sa vedem cu cat sa inmultim valoare rez.
        if( rez * 2 >= maxim * 3 )
            rez *= 2;
        else
            rez *=3;
    }
    fprintf(g,"%d",rez);
    fclose(g);
    return 0;

}
