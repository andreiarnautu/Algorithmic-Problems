/**
  *  Short preview of the task :
  *
  *     ->  you are given an N * M binary matrix where "0" means water and "1" means land
  *     ->  you are asked to print the number of islands and peninsulas
  *     ->  each connected zone which consists of 1s can be either an island or a peninsula (a peninsula is connected to the frame and an island is not)
  */
#include <fstream>

using namespace std;
ifstream fin("lac.in");
ofstream fout("lac.out");

const int MAX_N = 1 + 1000;  //  Maximum dimension of the matrix
const int dx[] = {-1, 1, 0,  0};
const int dy[] = { 0, 0, 1, -1};

/*-------- Input data --------*/
int N, M;
bool matrix[MAX_N][MAX_N];
/*-------- Fill-related data --------*/
bool checked[MAX_N][MAX_N];  //  checked[i][j] is true if we have already evaluated the (i,j) cell
bool isPeninsula;

int islandCount, peninsulaCount;
/*-------- --------*/

void ReadInput() {
    fin >> N >> M;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            fin >> matrix[i][j];
        }
    }
}

bool InsideMatrix(int x, int y) {
    return(1 <= x && x <= N && 1 <= y && y <= M);
}

void Fill(int x, int y) {
    checked[x][y] = true;  //  mark the cell as checked

    //  We will look at the 4 neighbours of the (i, j) cell
    //  In order to be able to do that easily, we have dx[] and dy[]

    for(int i = 0; i < 4; i++) {
        //  Get the neighbour's coordinates
        int x1 = x + dx[i];
        int y1 = y + dy[i];

        if(InsideMatrix(x1, y1) && matrix[x1][y1] == 1 && checked[x1][y1] == false) {
            //  If the neighbour is unchecked and the position is valid, continue recursion there
            Fill(x1, y1);
        } else if(!InsideMatrix(x1, y1)) {
            //  Otherwise if the neighbour's position is not valid it means that the current zone is a peninsula, because it is connected to the frame
            isPeninsula = true;
        }
    }
}

void Solve() {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(matrix[i][j] == 1 && checked[i][j] == false) {
                //  If we reached an unchecked cell it means that we have a new zone. We will mark all of the zone's cells using recursion (the Fill() function)

                isPeninsula = false;  //  We start by presuming that the zone is an island
                Fill(i, j);

                if(isPeninsula) {
                    peninsulaCount ++;
                } else {
                    islandCount ++;
                }
            }
        }
    }
}

int main() {
    ReadInput();
    Solve();
    fout << islandCount << " " << peninsulaCount;
    return 0;
}
