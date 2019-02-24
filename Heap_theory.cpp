#include <iostream>
#define Dim 1001
#include <algorithm>
using namespace std;
int N, H[Dim];


void Read()
{
    cin >> N;
    for(int i = 1 ; i <= N ; ++i )
        cin >> H[i];
}

void CombHeap( int i , int n )
{
    int v , Father, Son;
    v = H[i];
    Father = i;
    Son = 2 * i;
    while( Son <= n )
    {
        if( Son < n && H[Son] > H[Son + 1] )
            ++Son;
        if( v > H[Son] )
        {
            H[Father] = H[Son];
            Father = Son;
            Son *= 2;
        }
        else
            Son = n + 1;
    }
    H[Father] = v;
}

void Make_Heap()
{
    for(int i = N / 2 ; i > 0 ; --i )
        CombHeap( i , N );
    // Crearea unui Heap standard
}

int Extract_Max()
{
    int v;
    v = H[1];
    H[1] = H[N--];
    CombHeap( 1 , N );
    return v;
}

void Heapsort() // Complexitate O( N log N )
{
    int i;
    for( i = N ; i > 1 ; --i )
    {
        swap( H[1] , H[i] );
        CombHeap( 1 , i - 1 );
    }
    for(int i = 1 ; i <= N ; ++i )
        cout << H[i] << " ";
}

void PushHeap()
{
    int k, v, pos;
    cin >> k;
    ++N;
    H[N] = k;
    v = H[N] , pos = N;
    while( pos > 1 && v > H[pos / 2] )
    {
        H[pos] = H[pos / 2];
        pos /= 2;
    }
    H[pos] = v;
    for(int i = 1 ; i <= N ; ++i )
        cout << H[i] << " ";
}

int main()
{
    Read();
    Make_Heap();
  //  cout << Extract_Max() << " ";
    Heapsort();
    PushHeap(); // Nu sorteaza!!!

    return 0;
}
