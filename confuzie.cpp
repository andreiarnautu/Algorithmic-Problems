/**
  *  Worg
  */
#include <set>
#include <cstdio>
#include <vector>
#include <utility>

using namespace std;
FILE *fin = freopen("confuzie.in", "r", stdin);
FILE *fout = freopen("confuzie.out", "w", stdout);

const int MAX_N = 200000;
const int bufferDim = 100000;

class inputReader {
private:
        char buffer[bufferDim];
        int pos = 0;

        bool digit(char c) {
            return('0' <= c && c <= '9');
        }

public:
        void getBuffer() {
            fread(buffer, 1, bufferDim, stdin);
            pos = 0;
        }

        void getInt(int &nr) {
            nr = 0;
            while(!digit(buffer[pos]))
                if(++pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == bufferDim)
                    getBuffer();
            }
        }
} cin;

struct Nod;
struct Lant;

set< pair<int,int> > SET;

struct Nod {
    bool culoare;
    int index;
    vector<Nod*> vecini;
    int adancime;
    int greutate;
    Lant* lant;
};

struct Lant {
    Nod* tata;
    vector<Nod*> noduri;
    set< pair<int, int> > adancimiNoduriNegre;
};

int N, M;
Nod noduri[1 + MAX_N];
int previous[1 + MAX_N];

void readData() {
    cin.getBuffer();
    cin.getInt(N); cin.getInt(M);
    int radacina = 1;
    noduri[radacina].index = radacina;
    for (int i = 1; i < N; i++) {
        int u, v; cin.getInt(u); cin.getInt(v);
        noduri[u].vecini.push_back(&noduri[v]);
        noduri[v].vecini.push_back(&noduri[u]);
    }

    for(int i = 0; i <= N; ++i) {
        noduri[i].index = i;
        noduri[i].culoare = 0;
        noduri[i].adancime = noduri[i].greutate = 0;
    }
}

void dfs(Nod* nod, int adancime = 1) {
    nod->adancime = adancime;
    nod->greutate = 1;
    Nod* fiu;
    int greutateFiu = 0;
    for (Nod* vecin : nod->vecini) {
        if(vecin->index != previous[nod->index]) {
            previous[vecin->index] = nod->index;
            dfs(vecin, adancime + 1);
            nod->greutate += vecin->greutate;
            if (greutateFiu < vecin->greutate) {
                greutateFiu = vecin->greutate;
                fiu = vecin;
            }
        }
    }

    if (greutateFiu == 0) {
        nod->lant = new Lant();
    } else {
        nod->lant = fiu->lant;
        for (Nod* vecin : nod->vecini) {
            if (vecin != fiu && previous[nod->index] != vecin->index) {
                vecin->lant->tata = nod;
            }
        }
    }
    nod->lant->noduri.push_back(nod);

}

int queryAnswer;

void Query(Nod *u, Nod *v) {
    if(u->lant == v->lant) {
        set < pair<int,int> >::iterator it = u->lant->adancimiNoduriNegre.upper_bound(make_pair(u->adancime - 1, 1000000));
        if(it != u->lant->adancimiNoduriNegre.end() && it->first <= v->adancime && it->first >= u->adancime) {
            queryAnswer = it->second;
        }
        return;
    } else {
        if(!v->lant->adancimiNoduriNegre.empty()) {
            set < pair<int,int> >::iterator it = v->lant->adancimiNoduriNegre.begin();
            if(it->first <= v->adancime) {
                queryAnswer = it->second;
            }
        }
        Query(u, v->lant->tata);
    }
}

void answerQuery() {
    int type;
    cin.getInt(type);

    if(type == 0) {
        int x; cin.getInt(x);
        Lant *lant = noduri[x].lant;
        if(noduri[x].culoare == 0) {
            noduri[x].culoare = 1;
            lant->adancimiNoduriNegre.insert(make_pair(noduri[x].adancime, x));
        }
        else {
            noduri[x].culoare = 0;
            lant->adancimiNoduriNegre.erase(lant->adancimiNoduriNegre.find(make_pair(noduri[x].adancime, x)));
        }
    } else {
        int x, y; cin.getInt(x); cin.getInt(y);
        queryAnswer = -1;
        Nod *u = &noduri[x];
        Nod *v = &noduri[y];
        Query(u, v);
        printf("%d\n", queryAnswer);
    }
}

int main() {
    readData();
    dfs(&noduri[1]);
    noduri[0].adancime = 0;
    noduri[1].lant->tata = &noduri[0];


    for(int i = 1; i <= M; ++i) {
        answerQuery();
    }
    return 0;
}
