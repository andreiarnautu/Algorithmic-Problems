/**
  *  Worg
  */
#include <map>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("cadouri.in", "r", stdin);
ofstream fout("cadouri.out");

const int MAX_LEN = 1000;

map <string,int> mymap;
string s;
int n;

char line[MAX_LEN];
int pos;

vector < pair<string,int> > v;
int k;

bool digit(char c) {

    return ('0' <= c && c <= '9');
}

bool letter(char c) {

    return ('a' <= c && c <= 'z');
}

int getValue() {

    int ret = 0;
    while(digit(line[pos])) {

        ret = ret * 10 + line[pos] - '0';
        pos++;
    }
    return ret;
}

bool comp(pair<string, int> p1, pair<string, int> p2) {

    if(p1.second != p2.second) {
        return p1.second > p2.second;
    }
    else {
        int size1 = p1.first.size(), size2 = p2.first.size();

        for(int i = 0; i < min(size1, size2); i++)
            if(p1.first[0] != p2.first[0]) {
                return p1.first[0] < p2.first[0];
            }
        if(size1 < size2) {
            return 0;
        }
        return 1;
    }
}

int main() {

    scanf("%d ", &n);
    for(int i = 1; i <= n; ++i) {

        gets(line);
        int len = strlen(line);

        pos = 0;

        while(pos < len) {

            while(!digit(line[pos]))
                pos++;

            int val = getValue();
            while(!letter(line[pos])) {
                pos++;
            }

            s.clear();
            while(letter(line[pos])) {
                s += line[pos++];
            }

            mymap[s] += val;
            while(pos < len && !digit(line[pos]))
                pos++;
        }
    }


    for(map<string,int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
        v.push_back(make_pair(it->first, it->second));
    sort(v.begin(), v.end(), comp);

    fout << (int)v.size() << '\n';
    for(pair<string,int> p : v)
        fout << p.first << " " << p.second << '\n';
    return 0;
}
