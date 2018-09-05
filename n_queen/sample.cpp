// #include <iostream>
#include <cstring>
// #include "clock.h"

#define N 20

int n;
int count=0;

/* (i,j)の位置から縦横斜めの方向にある board のすべての要素の値に dを加える */
void changeBoard(int board[N][N], int i, int j, int d)
{
  for (int k = 0; k < n; k++) {
    board[i][k] += d;             /* 横方向 */
    board[k][j] += d;             /* 縦方向 */
  }
  if (i > j) {
    for (int k = 0; k < n - (i - j); k++) {
      board[k + (i - j)][k] += d; /* 右下がり斜め方向 (i > jのとき） */
    }
  } else {
    for (int k = 0; k < n - (j - i); k++) {
      board[k][k + (j - i)] += d; /* 右下がり斜め方向 (i <= jのとき） */
    }
  }
  if (i + j < n) {
    for (int k = 0; k <= i + j; k++) {
      board[i + j - k][k] += d; /* 左下がり斜め方向（i +j < nのとき） */
    }
  } else {
    for (int k = i + j - n + 1; k < n; k++) {
      board[i + j - k][k] += d; /* 左下がり斜め方向（i+j >= nのとき） */
    }
  }
}

/* i 行目のクイーンの位置を設定して， setQueen(queen, board, i+1) を呼び出す
　ただし， i == n のときは，一つの解が queen に入っているのでそれを表示するだけである */
void setQueen(int queen[N], int board[N][N], int i)
{
  int j;

  if (i == n) {                              /* 解が見つかった */
    count++;
    return;
  }

  for (j = 0; j < n; j++) {
    if (board[i][j] == 0) {                /* (i,j) の位置に置けるならば */
      queen[i] = j;                      /* (i,j) の位置にクイーンを置く */
      changeBoard(board, i, j, +1);      /* (i,j) から縦横斜めの方向のboard値を+1する */
      setQueen(queen, board, i + 1);     /* i+1 行目のクイーンの位置を決める */
      changeBoard(board, i, j, -1);      /* (i,j) から縦横斜めの方向のboard値を元に戻す */
    }
  }
}

int findSolution(int n_)
{
  n=n_;
  int queen[N];
  int board[N][N];

  std::memset(board, 0, sizeof(board));
  setQueen(queen, board, 0);
  return count;
}
