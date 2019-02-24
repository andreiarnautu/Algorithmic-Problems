/**
  *  Worg
  *  Mar 24, 2018
  *  10:59:00 AM
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("partitionare.in", "r", stdin); FILE *fout = freopen("partitionare.out", "w", stdout);

const double eps = 1e-8;
const int limit = 90;

std::vector<int > ans[limit + 1];

int main() {
  ans[1].push_back(1);


  ans[4].push_back(2); ans[4].push_back(2);




  ans[9].push_back(3); ans[9].push_back(3); ans[9].push_back(3);
  ans[10].push_back(2); ans[10].push_back(4); ans[10].push_back(4);
  ans[11].push_back(2); ans[11].push_back(3); ans[11].push_back(6);




  ans[16].push_back(4); ans[16].push_back(4); ans[16].push_back(4); ans[16].push_back(4);
  ans[17].push_back(3); ans[17].push_back(4); ans[17].push_back(4); ans[17].push_back(6);
  ans[18].push_back(3); ans[18].push_back(3); ans[18].push_back(6); ans[18].push_back(6);

  ans[20].push_back(2); ans[20].push_back(6); ans[20].push_back(6); ans[20].push_back(6);

  ans[22].push_back(2); ans[22].push_back(4); ans[22].push_back(8); ans[22].push_back(8);

  ans[24].push_back(2); ans[24].push_back(4); ans[24].push_back(6); ans[24].push_back(12);
  ans[25].push_back(5); ans[25].push_back(5); ans[25].push_back(5); ans[25].push_back(5); ans[25].push_back(5);
  ans[26].push_back(4); ans[26].push_back(4); ans[26].push_back(6); ans[26].push_back(6); ans[26].push_back(6);
  ans[27].push_back(3); ans[27].push_back(6); ans[27].push_back(6); ans[27].push_back(6); ans[27].push_back(6);
  ans[28].push_back(4); ans[28].push_back(4); ans[28].push_back(4); ans[28].push_back(8); ans[28].push_back(8);
  ans[29].push_back(2); ans[29].push_back(3); ans[29].push_back(12); ans[29].push_back(12);
  ans[30].push_back(2); ans[30].push_back(3); ans[30].push_back(10); ans[30].push_back(15);
  ans[31].push_back(2); ans[31].push_back(4); ans[31].push_back(5); ans[31].push_back(20);
  ans[32].push_back(2); ans[32].push_back(3); ans[32].push_back(9); ans[32].push_back(18);
  ans[33].push_back(3); ans[33].push_back(3); ans[33].push_back(9); ans[33].push_back(9); ans[33].push_back(9);
  ans[34].push_back(2); ans[34].push_back(8); ans[34].push_back(8); ans[34].push_back(8); ans[34].push_back(8);
  ans[35].push_back(2); ans[35].push_back(6); ans[35].push_back(9); ans[35].push_back(9); ans[35].push_back(9);
  ans[36].push_back(2); ans[36].push_back(6); ans[36].push_back(8); ans[36].push_back(8); ans[36].push_back(12);
  ans[37].push_back(2); ans[37].push_back(3); ans[37].push_back(8); ans[37].push_back(24);
  ans[38].push_back(2); ans[38].push_back(6); ans[38].push_back(6); ans[38].push_back(12); ans[38].push_back(12);
  ans[39].push_back(2); ans[39].push_back(6); ans[39].push_back(6); ans[39].push_back(10); ans[39].push_back(15);
  ans[40].push_back(4); ans[40].push_back(4); ans[40].push_back(8); ans[40].push_back(8); ans[40].push_back(8); ans[40].push_back(8);
  ans[41].push_back(2); ans[41].push_back(6); ans[41].push_back(6); ans[41].push_back(9); ans[41].push_back(18);
  ans[42].push_back(2); ans[42].push_back(4); ans[42].push_back(12); ans[42].push_back(12); ans[42].push_back(12);
  ans[43].push_back(2); ans[43].push_back(4); ans[43].push_back(10); ans[43].push_back(12); ans[43].push_back(15);
  ans[44].push_back(3); ans[44].push_back(3); ans[44].push_back(6); ans[44].push_back(8); ans[44].push_back(24);
  ans[45].push_back(2); ans[45].push_back(4); ans[45].push_back(9); ans[45].push_back(12); ans[45].push_back(18);
  ans[46].push_back(2); ans[46].push_back(4); ans[46].push_back(8); ans[46].push_back(16); ans[46].push_back(16);
  ans[47].push_back(3); ans[47].push_back(4); ans[47].push_back(8); ans[47].push_back(8); ans[47].push_back(12); ans[47].push_back(12);
  ans[48].push_back(3); ans[48].push_back(4); ans[48].push_back(8); ans[48].push_back(8); ans[48].push_back(10); ans[48].push_back(15);
  ans[49].push_back(3); ans[49].push_back(4); ans[49].push_back(6); ans[49].push_back(12); ans[49].push_back(12); ans[49].push_back(12);
  ans[50].push_back(2); ans[50].push_back(4); ans[50].push_back(8); ans[50].push_back(12); ans[50].push_back(24);
  ans[51].push_back(3); ans[51].push_back(3); ans[51].push_back(5); ans[51].push_back(10); ans[51].push_back(30);
  ans[52].push_back(2); ans[52].push_back(5); ans[52].push_back(5); ans[52].push_back(20); ans[52].push_back(20);
  ans[53].push_back(2); ans[53].push_back(5); ans[53].push_back(6); ans[53].push_back(10); ans[53].push_back(30);
  ans[54].push_back(2); ans[54].push_back(3); ans[54].push_back(7); ans[54].push_back(42);
  ans[55].push_back(2); ans[55].push_back(4); ans[55].push_back(7); ans[55].push_back(14); ans[55].push_back(28);
  ans[56].push_back(2); ans[56].push_back(6); ans[56].push_back(12); ans[56].push_back(12); ans[56].push_back(12); ans[56].push_back(12);
  ans[57].push_back(2); ans[57].push_back(5); ans[57].push_back(5); ans[57].push_back(15); ans[57].push_back(30);
  ans[58].push_back(2); ans[58].push_back(6); ans[58].push_back(10); ans[58].push_back(10); ans[58].push_back(15); ans[58].push_back(15);
  ans[59].push_back(2); ans[59].push_back(3); ans[59].push_back(18); ans[59].push_back(18); ans[59].push_back(18);
  ans[60].push_back(2); ans[60].push_back(3); ans[60].push_back(15); ans[60].push_back(20); ans[60].push_back(20);
  ans[61].push_back(2); ans[61].push_back(3); ans[61].push_back(14); ans[61].push_back(21); ans[61].push_back(21);
  ans[62].push_back(2); ans[62].push_back(4); ans[62].push_back(6); ans[62].push_back(20); ans[62].push_back(30);
  ans[63].push_back(2); ans[63].push_back(5); ans[63].push_back(12); ans[63].push_back(12); ans[63].push_back(12); ans[63].push_back(20);
  ans[64].push_back(2); ans[64].push_back(4); ans[64].push_back(8); ans[64].push_back(10); ans[64].push_back(40);
  ans[65].push_back(2); ans[65].push_back(3); ans[65].push_back(12); ans[65].push_back(24); ans[65].push_back(24);
  ans[66].push_back(2); ans[66].push_back(3); ans[66].push_back(12); ans[66].push_back(21); ans[66].push_back(28);
  ans[67].push_back(2); ans[67].push_back(3); ans[67].push_back(12); ans[67].push_back(20); ans[67].push_back(30);
  ans[68].push_back(2); ans[68].push_back(6); ans[68].push_back(6); ans[68].push_back(18); ans[68].push_back(18); ans[68].push_back(18);
  ans[69].push_back(2); ans[69].push_back(3); ans[69].push_back(14); ans[69].push_back(15); ans[69].push_back(35);
  ans[70].push_back(2); ans[70].push_back(4); ans[70].push_back(16); ans[70].push_back(16); ans[70].push_back(16); ans[70].push_back(16);
  ans[71].push_back(2); ans[71].push_back(3); ans[71].push_back(11); ans[71].push_back(22); ans[71].push_back(33);
  ans[72].push_back(2); ans[72].push_back(4); ans[72].push_back(12); ans[72].push_back(18); ans[72].push_back(18); ans[72].push_back(18);
  ans[73].push_back(2); ans[73].push_back(4); ans[73].push_back(12); ans[73].push_back(15); ans[73].push_back(20); ans[73].push_back(20);
  ans[74].push_back(2); ans[74].push_back(4); ans[74].push_back(12); ans[74].push_back(14); ans[74].push_back(21); ans[74].push_back(21);
  ans[75].push_back(2); ans[75].push_back(3); ans[75].push_back(10); ans[75].push_back(30); ans[75].push_back(30);
  ans[76].push_back(2); ans[76].push_back(4); ans[76].push_back(6); ans[76].push_back(16); ans[76].push_back(48);
  ans[77].push_back(2); ans[77].push_back(10); ans[77].push_back(10); ans[77].push_back(10); ans[77].push_back(15); ans[77].push_back(15); ans[77].push_back(15);
  ans[78].push_back(2); ans[78].push_back(4); ans[78].push_back(12); ans[78].push_back(12); ans[78].push_back(24); ans[78].push_back(24);
  ans[79].push_back(2); ans[79].push_back(3); ans[79].push_back(10); ans[79].push_back(24); ans[79].push_back(40);
  ans[80].push_back(2); ans[80].push_back(4); ans[80].push_back(10); ans[80].push_back(15); ans[80].push_back(21); ans[80].push_back(28);
  ans[81].push_back(2); ans[81].push_back(3); ans[81].push_back(12); ans[81].push_back(16); ans[81].push_back(48);
  ans[82].push_back(2); ans[82].push_back(4); ans[82].push_back(12); ans[82].push_back(14); ans[82].push_back(15); ans[82].push_back(35);
  ans[83].push_back(2); ans[83].push_back(5); ans[83].push_back(6); ans[83].push_back(20); ans[83].push_back(20); ans[83].push_back(30);
  ans[84].push_back(2); ans[84].push_back(4); ans[84].push_back(11); ans[84].push_back(12); ans[84].push_back(22); ans[84].push_back(33);
  ans[85].push_back(2); ans[85].push_back(4); ans[85].push_back(10); ans[85].push_back(14); ans[85].push_back(20); ans[85].push_back(35);
  ans[86].push_back(2); ans[86].push_back(3); ans[86].push_back(9); ans[86].push_back(36); ans[86].push_back(36);
  ans[87].push_back(2); ans[87].push_back(4); ans[87].push_back(6); ans[87].push_back(15); ans[87].push_back(60);
  ans[88].push_back(2); ans[88].push_back(4); ans[88].push_back(8); ans[88].push_back(20); ans[88].push_back(24); ans[88].push_back(30);
  ans[89].push_back(2); ans[89].push_back(3); ans[89].push_back(9); ans[89].push_back(30); ans[89].push_back(45);
  ans[90].push_back(2); ans[90].push_back(6); ans[90].push_back(6); ans[90].push_back(12); ans[90].push_back(16); ans[90].push_back(48);

  int n; scanf("%d", &n);

  std::vector<int > sol;

  int coef = 1;
  while(n > limit) {
    if(n % 2 == 1) {
      sol.push_back(coef * 3); sol.push_back(coef * 6);

      n -= 9; n /= 2;
    } else {
      sol.push_back(coef * 4); sol.push_back(coef * 4);

      n -= 8; n /= 2;
    }
    coef *= 2;
  }

  for(auto& itr : ans[n]) {
    sol.push_back(coef * itr);
  }
  for(auto& itr : sol) {
    printf("%d ", itr);
  }
  return 0;
}
