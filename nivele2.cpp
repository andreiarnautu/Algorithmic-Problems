#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
ifstream in("nivele2.in");
ofstream out("nivele2.out");

vector <int> V[100003], Level[100003];
vector <int>::iterator it;
int A[100003];
int n;

void Read()
{
    int a, b;
    in >> n;
    for(int i = 1; i < n ; ++i)
    {
        in >> a >> b;
        V[a].push_back(b);
        V[b].push_back(a);
    }
}

void Check(int nod)
{
    if( V[nod].size() == 0 )
        return;
    for(vector <int>::iterator it1 = V[nod].begin(); it1 < V[nod].end(); ++it1)
        if( !A[*it1] )
        {
            A[*it1] = A[nod] + 1;
            Level[A[*it1]].push_back(*it1);
            Check(*it1);
        }
}

int main()
{
    Read();
    Level[1].push_back(1);
    A[1] = 1;
    Check(1);
    for(int i = 1; ; ++i)
    {
        if(Level[i].size() == 0)
            break;
        out << "nivelul " << i << ": ";
        sort(Level[i].begin(), Level[i].end());
        for(it = Level[i].begin(); it < Level[i].end(); ++it)
        {
            out << *it;
                out << " ";
        }
        out << '\n';
    }
    return 0;
}
