/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("main.in", "r", stdin);
FILE *fout = freopen("main.out", "w", stdout);

const int total_lines = 5;
const int suit_count = 4;

vector< int > cards[suit_count];
vector< pair< int, int > > all_cards;

pair< char, char > scan_card() {
    pair< char, char > answer;
    scanf("%c%c", &answer.first, &answer.second);
    return answer;
}

pair< int, int > get_card_values(pair< char, char > card) {
    int card_number;
    if('1' <= card.first && card.first <= '9') {
        card_number = card.first - '0';
    } else {
        if(card.first == 'A') {
            card_number = 1;
        } else if(card.first == 'T') {
            card_number = 10;
        } else if(card.first == 'J') {
            card_number = 11;
        } else if(card.first == 'Q') {
            card_number = 12;
        } else {
            card_number = 13;
        }
    }

    int card_suit;

    if(card.second == 'C') {
        card_suit = 0;
    } else if(card.second == 'D') {
        card_suit = 1;
    } else if(card.second == 'H') {
        card_suit = 2;
    } else {
        card_suit = 3;
    }

    return make_pair(card_number, card_suit);
}

void insert_values(pair< char, char > card) {
    pair< int, int > values = get_card_values(card);
    int card_number = values.first;
    int card_suit = values.second;

    cards[card_suit].push_back(card_number);
    all_cards.push_back(make_pair(card_number, card_suit));
}

pair< char, char > get_card(pair< int, int > values) {
    pair< char, char > answer;
    if(values.first == 1) {
        answer.first = 'A';
    } else if(2 <= values.first && values.first <= 9) {
        answer.first = '1' + values.first - 1;
    } else if(values.first == 10) {
        answer.first = 'T';
    } else if(values.first == 11) {
        answer.first = 'J';
    } else if(values.first == 12) {
        answer.first = 'Q';
    } else {
        answer.first = 'K';
    }

    if(values.second == 0) {
        answer.second = 'C';
    } else if(values.second == 1) {
        answer.second = 'D';
    } else if(values.second == 2) {
        answer.second = 'H';
    } else {
        answer.second = 'S';
    }

    return answer;
}

int main() {
    for(int crt_line = 1; crt_line <= total_lines; crt_line ++) {
        pair< char, char > card = scan_card();                //printf("%c%c\n", card.first, card.second);
        pair< int, int > values = get_card_values(card);
        scanf(", "); card = scan_card(); insert_values(card); //printf("%c%c\n", card.first, card.second);
        scanf(", "); card = scan_card(); insert_values(card); //printf("%c%c\n", card.first, card.second);
        scanf(", "); card = scan_card(); insert_values(card); //printf("%c%c\n", card.first, card.second);
        scanf(", "); card = scan_card(); insert_values(card); //printf("%c%c\n", card.first, card.second);
        scanf(", "); card = scan_card(); insert_values(card); //printf("%c%c\n", card.first, card.second);
        scanf(" ");
        sort(all_cards.begin(), all_cards.end());
        sort(cards[0].begin(), cards[0].end());
        sort(cards[1].begin(), cards[1].end());
        sort(cards[2].begin(), cards[2].end());
        sort(cards[3].begin(), cards[3].end());
        /* Now let's see what we have to output */

        pair< char, char > solution;
        if(!cards[values.second].empty()) {
            /* We can choose a card with the same suit */
            if(cards[values.second].back() > values.first) {
                /* We can choose a better card */
                int crt_value = cards[values.second].back(); cards[values.second].pop_back();
                while(!cards[values.second].empty() && cards[values.second].back() > values.first) {
                    crt_value = cards[values.second].back(); cards[values.second].pop_back();
                }
                solution = get_card(make_pair(crt_value, values.second));
            } else {
                /* We choose the lowest one */
                solution = get_card(make_pair(cards[values.second][0], values.second));
            }
        } else {
            solution = get_card(all_cards[0]);
        }
        printf("%c%c\n", solution.first, solution.second);

        all_cards.clear();
        cards[0].clear();
        cards[1].clear();
        cards[2].clear();
        cards[3].clear();
    }

    return 0;
}
