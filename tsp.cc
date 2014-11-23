/*
解答
問1の解：{{1,3,2,4,1},1.307768723046356868593756860493e+01}
問2の解：{{1,4,6,7,5,2,3,8,1},3.701961621510202932194008854267e+16}
問3の解：{{1,3,4,8,9,7,2,6,10,5,1},7.731001749995506797619464268078e+16}
問4の解：{{1,7,5,3,9,10,4,8,2,6,11,12,1},8.773575157375087892939382099894e+17}

実行環境
プラットフォーム：Ubuntu 14.04 for Amd64
処理系：G++ 4.8.2
CPU：Core i7-4700MQ
メモリ：16GB
計算時間（秒）：6

環境構築方法
1. sudo apt-get update
2. sudo apt-get install g++

実行方法
1. ファイル名を「tsp.cc」とする。
2. g++ -O3 -march=native -std=c++11 tsp.cc -lquadmath
3. ./a.out
*/
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <quadmath.h>

using namespace std;

//typedef double REAL;
//typedef long double REAL;
typedef __float128 REAL;

__float128 sqrt(__float128 x) {
  return sqrtq(x);
}

template<typename T> void printVal(T x) {
  cout << scientific << setprecision(30) << x;
}

template<> void printVal<__float128>(__float128 x) {
  char tmp[1000];
  quadmath_snprintf(tmp, 1000, "%.30Qe", x);
  cout << tmp;
}

template<typename T> void report(const char* str, vector<int>* tour, T distance) {
  cout << str << '{';
  for (unsigned int i = 0; i < tour->size(); ++i) {
    cout << tour->at(i) + 1 << ',';
  }
  cout << "1},";
  printVal(distance);
  cout << "}" << endl;
}

void search(REAL cities[][2], int n) {
  REAL d[n][n]; //2点間の距離を計算しておく。
  for (int i = 0; i < n; ++i){
    for (int j = i + 1; j < n; ++j) {
      REAL dx = cities[i][0] - cities[j][0];
      REAL dy = cities[i][1] - cities[j][1];
      d[i][j] = d[j][i] = sqrt(dx*dx + dy*dy);
    }
  }

  REAL minDistance1 = INFINITY; //1番目に短い経路長
  REAL minDistance2 = INFINITY; //2番目に短い経路長
  vector<int> tour(n), minTour1, minTour2; //探索経路、1番目に短い経路、2番目に短い経路
  iota(tour.begin(), tour.end(), 0); //{0,1,2,...}を入れておく
  do {
    if (tour[1] < tour[n - 1]) { //結果の条件
      REAL distance = d[tour[n-1]][tour[0]];
      for (int i = 1; i < n; ++i) {
        distance += d[tour[i - 1]][tour[i]];
      }
      if (distance < minDistance2) {
        if (distance < minDistance1) {
          minDistance2 = minDistance1;
          minTour2 = minTour1;
          minDistance1 = distance;
          minTour1 = tour;
        } else {
          minDistance2 = distance;
          minTour2 = tour;
        }
      }
    }
  } while (next_permutation(tour.begin() + 1, tour.end())); //始点は0に固定
  
  report("1番目に短い経路: ", &minTour1, minDistance1);
  report("2番目に短い経路: ", &minTour2, minDistance2);
}

int main() {
  int n;
  cout << "example:" << endl;
  REAL example[][2] = {{4, 5}, {7, 2}, {9, 1}, {9, 4}, {7, 3}, {6, 8}};
  n = sizeof(example) / (2 * sizeof(REAL));
  search(example, n);

  cout << endl << "question 1:" << endl;
  REAL question1[][2] = {{6, 2}, {4, 6}, {3, 4}, {6, 7}};
  n = sizeof(question1) / (2 * sizeof(REAL));
  search(question1, n);

  cout << endl << "question 2:" << endl;
  REAL question2[][2] = {
    {9007199254742147, 18014398509481729},
    {12756043757992973, 9682416912451847},
    {7757599369284503, 13555003989651347},
    {6644379103590211, 16459957280325781},
    {7107267045169859, 11361149298161843},
    {17193260969299, 17215263416918057},
    {374711875842439, 13679925148827797},
    {9007199254742149, 18014398509481727}};
  n = sizeof(question2) / (2 * sizeof(REAL));
  search(question2, n);

  cout << endl << "question 3:" << endl;
  REAL question3[][2] = {
    {24450478250354407, 24162405956350007},
    {5022777106905113, 9351872806120363},
    {22646143480201399, 18046391278629037},
    {26904592918639433, 8822422244422001},
    {13510798882112671, 27021597764225159},
    {7416604674633347, 17884308649058737},
    {11322174193520947, 3885286011386431},
    {25871043906094921, 9505143934995377},
    {12509125559334347, 10427194051934741},
    {13510798882112669, 27021597764225161}};
  n = sizeof(question3) / (2 * sizeof(REAL));
  search(question3, n);

  cout << endl << "question 4:" << endl;
  REAL question4[][2] = {
    {143440002785145229, 125304038892333277},
    {264428432131034503, 120015772829769617},
    {128790875003948837, 270669230395068511},
    {159528435868345829, 204968426098505873},
    {19849988012900029, 184555790037852601},
    {275289191011264097, 71741794408943803},
    {10351044942542977, 120950333572309643},
    {256393278357970813, 144044348649819451},
    {144115188075856001, 288230376151712791},
    {144115188075856003, 288230376151712789},
    {219455401629103741, 10320154786742321},
    {227161482167126027, 70606670735479337}};
  n = sizeof(question4) / (2 * sizeof(REAL));
  search(question4, n);
}