/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("hash.in", "r", stdin);
FILE *fout = freopen("hash.out", "w", stdout);

const long long P1 = 1000000007; /* primul numar prim */
const long long P2 = 1000000009; /* al doilea numar prim */

const long long BASE = 29; /* baza in care calculam totul */

unsigned long long pow(unsigned long long base, unsigned long long exp, unsigned long long P) {
    /* functie de ridicare logaritmica la putere, pe care o vom folosi la diverse operatii */

    unsigned long long answer = 1, aux = base;
    for(unsigned long long i = 1; i <= exp; i *= 2) {
        if(i & exp) {
            answer = (answer * aux) % P;
        }
        aux = (aux * aux) % P;
    }
    return answer;
}

const long long INV_BASE_1 = pow(BASE, P1 - 2, P1);
const long long INV_BASE_2 = pow(BASE, P2 - 2, P2); /* inversi modulari pe care ii vom folosi pentru impartire */

struct Hash {
    /* structura propriu-zisa a hash-ului */
    long long r1, r2;
    int len;

    Hash() {
        this->r1 = this->r2 = this->len = 0;
    }

    bool operator ==(const Hash &other) const {
        return (this->r1 == other.r1 &&
                this->r2 == other.r2 &&
                this->len == other.len);
    }
};

Hash hashChar(char c) {
    /* hash-ul unui caracter */
    Hash answer;
    answer.r1 = c - 'a';
    answer.r2 = c - 'a';
    answer.len = 1;
    return answer;
}

Hash push_back(Hash h, char c) {
    /* adaugam un caracter la final */
    Hash answer;
    answer.r1 = (h.r1 * BASE + (c - 'a')) % P1;
    answer.r2 = (h.r2 * BASE + (c - 'a')) % P2;
    answer.len = h.len + 1;

    return answer;
}

Hash pop_back(Hash h, char c) {
    /* stergem un caracter de la final */
    Hash answer;
    answer.r1 = ((h.r1 - (c - 'a') + P1) * INV_BASE_1) % P1;
    answer.r2 = ((h.r2 - (c - 'a') + P2) * INV_BASE_2) % P2;
    answer.len = h.len - 1;

    return answer;
}

Hash push_front(Hash h, char c) {
    /* adaugam un caracter la inceput */
    Hash answer;
    answer.r1 = ((c - 'a') * pow(BASE, h.len, P1) + h.r1) % P1;
    answer.r2 = ((c - 'a') * pow(BASE, h.len, P2) + h.r2) % P2;
    answer.len = h.len + 1;

    return answer;
}

Hash pop_front(Hash h, char c) {
    /* se sterge un caracter de la inceput */
    Hash answer;
    answer.r1 = (h.r1 - (c - 'a') * pow(BASE, h.len - 1, P1) + BASE * P1) % P1;
    answer.r2 = (h.r2 - (c - 'a') * pow(BASE, h.len - 1, P2) + BASE * P2) % P2;
    answer.len = h.len - 1;

    return answer;
}

Hash concat(Hash h1, Hash h2) {
    /* concatenam doua siruri */
    Hash answer;
    answer.r1 = (h1.r1 * pow(BASE, h2.len, P1) + h2.r1) % P1;
    answer.r2 = (h1.r2 * pow(BASE, h2.len, P2) + h2.r2) % P2;
    answer.len = h1.len + h2.len;

    return answer;
}

Hash get_first(Hash h, Hash h2) {
    /* obtine prefixul unui sir, al carui sufix il stim */
    Hash answer;
    answer.r1 = ((h.r1 - h2.r1 + P1) * pow(BASE, P1 - 1 - h2.len, P1)) % P1;
    answer.r2 = ((h.r2 - h2.r2 + P2) * pow(BASE, P2 - 1 - h2.len, P2)) % P2;
    answer.len = h.len - h2.len;

    return answer;
}

Hash get_last(Hash h, Hash h1) {
    /* obtine sufixul unui sir, al carui prefix il stim */
    Hash answer;
    answer.r1 = (h.r1 - h1.r1 * pow(BASE, h.len - h1.len, P1) + P1 * P1) % P1;
    answer.r2 = (h.r2 - h1.r2 * pow(BASE, h.len - h1.len, P2) + P2 * P2) % P2;
    answer.len = h.len - h1.len;

    return answer;
}

Hash hash(char *s) {
    /* gasim hash-ul unui sir */
    Hash answer;
    while(*s != '\0') {
        answer = push_back(answer, *s);
        ++s;
    }

    return answer;
}

int main() {

    Hash h1, h2, h3;

    char s1[] = "imperial", s2[] = "college", s3[] = "imperialcollege";

    h1 = hash(s1);
    h2 = hash(s2);
    h3 = hash(s3);

    printf("Testam concatenarea:\n");
    Hash h4 = concat(h1, h2);
    printf("%lld %lld %d\n", h3.r1, h3.r2, h3.len);
    printf("%lld %lld %d\n", h4.r1, h4.r2, h4.len);
    printf("---------------------------\n");


    printf("Testam get_first:\n");
    h4 = get_first(h3, h2);
    printf("%lld %lld %d\n", h1.r1, h1.r2, h1.len);
    printf("%lld %lld %d\n", h4.r1, h4.r2, h4.len);
    printf("---------------------------\n");

    printf("Testam get_last:\n");
    h4 = get_last(h3, h1);
    printf("%lld %lld %d\n", h2.r1, h2.r2, h2.len);
    printf("%lld %lld %d\n", h4.r1, h4.r2, h4.len);
    printf("---------------------------\n");
    return 0;
}
