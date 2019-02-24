/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using std::vector;

const int MAX_N = 100000;
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

struct Nod {
    int index;
    vector<Nod*> vecini;
    int adancime;
    int greutate;
    Lant* lant;
};

struct Lant {
    Nod* tata;
    vector<Nod*> noduri;
  //set<int> adancimiNoduriNegre;
};

int N;
Nod noduri[1 + MAX_N];

int M;

Nod* queryLCA(Nod* u, Nod* v) {
    if (u->lant ==v->lant) {
        if (u->adancime < v->adancime) {
        return u;
        } else {
            return v;
        }
    } else {
        int hu = u->lant->tata->adancime;
        int hv = v->lant->tata->adancime;
        if (hu < hv) {
            return queryLCA(u, v->lant->tata);
        } else {
            return queryLCA(u->lant->tata, v);
        }
    }
}

int queryLCA(int idU, int idV) {
    Nod* u = &noduri[idU];
    Nod* v = &noduri[idV];
    return queryLCA(u, v)->index;
}

void dfs(Nod* nod, int adancime = 1) {
    nod->adancime = adancime;
    nod->greutate = 1;
    Nod* fiu;
    int greutateFiu = 0;
    for (Nod* vecin : nod->vecini) {
        dfs(vecin, adancime + 1);
        nod->greutate += vecin->greutate;
        if (greutateFiu < vecin->greutate) {
            greutateFiu = vecin->greutate;
            fiu = vecin;
        }
    }

    if (greutateFiu == 0) {
        nod->lant = new Lant();
    } else {
        nod->lant = fiu->lant;
        for (Nod* vecin : nod->vecini) {
            if (vecin != fiu) {
                vecin->lant->tata = nod;
            }
        }
    }
    nod->lant->noduri.push_back(nod);
}

int main() {
    freopen("lca.in", "r", stdin);
    freopen("lca.out", "w", stdout);
    cin.getBuffer();
    cin.getInt(N); cin.getInt(M);
    int radacina = 1;
    noduri[radacina].index = radacina;
    for (int i = 2; i <= N; i++) {
        int t;
        cin.getInt(t);
        noduri[i].index = i;
        noduri[t].vecini.push_back(&noduri[i]);
    }
    dfs(&noduri[radacina]);
    noduri[0].adancime = 0;
    noduri[radacina].lant->tata = &noduri[0];


    return 0;
}
