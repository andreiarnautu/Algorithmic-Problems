/**
  *  Worg
  */
#include <cstdio>
#include <unordered_map>

using namespace std;
FILE *fin = freopen("brazi.in", "r", stdin);
FILE *fout = freopen("brazi.out", "w", stdout);

const int MAX_N = 1 + 10;
const int bufferDim = 100000;

class inputReader
{

private:
    char buffer[bufferDim];
    int pos = 0;

    bool digit(char c)
    {

        return('0' <= c && c <= '9');
    }
public:

    void getBuffer()
    {

        fread(buffer, 1, bufferDim, stdin);
        pos = 0;
    }

    void getInt(int &nr)
    {

        nr = 0;
        while(!digit(buffer[pos]))
            if(++pos == bufferDim)
                getBuffer();
        while(digit(buffer[pos]))
        {

            nr = nr * 10 + buffer[pos] - '0';
            if(++pos == bufferDim)
                getBuffer();
        }
    }
} cin;

int n;
int left[MAX_N], right[MAX_N];
bool hasFather[MAX_N];

unsigned long long id;
unordered_map <unsigned long long, int> umap;

void readData()
{

    cin.getInt(n);
    for(int i = 1; i < n; ++i)
    {
        int x, y, op;
        cin.getInt(x);
        cin.getInt(y);
        cin.getInt(op);

        hasFather[y] = true;
        if(op == 0)
        {
            left[x] = y;
        }
        else
        {
            right[x] = y;
        }
    }
}

int getRoot()
{
    for(int i = 1; i <= n; ++i)
        if(!hasFather[i])
        {
            return i;
        }
}

void dfs(int node)
{
    if(left[node])
    {
        id = id * 10 + 1;
        dfs(left[node]);
    }
    if(right[node])
    {
        id = id * 10 + 2;
        dfs(right[node]);
    }
    id *= 10;;
}

void cleanUp()
{
    for(int i = 1; i <= n; ++i)
    {
        left[i] = right[i] = 0;
        hasFather[i] = false;
    }
    id = 0;
}

int main()
{

    cin.getBuffer();
    int t;
    for(cin.getInt(t); t > 0; --t)
    {
        readData();
        int root = getRoot();
        dfs(root);
        printf("%d\n", umap[id]);
        umap[id]++;
        cleanUp();
    }
    return 0;
}
