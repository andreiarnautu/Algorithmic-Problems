/**
  *  Worg
  */
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

const int ghilimele = 34;
const int apostrof = 39;

//std::ofstream fout ("main.out");

int main() {
  std::string s, t;
  s += "B="; s += apostrof; s += ghilimele; s += apostrof; s += ";";
  s += "C="; s += ghilimele; s += apostrof; s += ghilimele; s += ";";
  s += "A="; s += ghilimele; s += ";";

  t += "?"; t += apostrof; t += "B="; t += apostrof; t += "+C+B+C+"; t += apostrof; t += ";C="; t += apostrof; t += "+B+C+B+"; t += apostrof; t += ";A="; t += apostrof; t += "+B+A+B+A";

  s += t; s += ghilimele; s += ";"; s += t;

  std::cout << s;

  return 0;
}
