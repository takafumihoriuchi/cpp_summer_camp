#include <iostream>
// #include "clock.h"
int count = 0;

class keisan {
public:
	int counta;
	int suuzi[4];
	int n;
	std::string enzan;  //式表示用
	keisan(int n_, int a, int b, int c, int d) {
		n = n_;
		counta = 0;
		enzan = "+-*/";
		suuzi[0] = a;
		suuzi[1] = b;
		suuzi[2] = c;
		suuzi[3] = d;
	}
	void dousyutu(int i, int j, int k, int l) {
		double kai = 0;
		std::string siki = std::string("");  //式表示用
		try {
			if (i == 0) {
				siki += "(" ;
				siki += "(";
				siki += std::to_string(suuzi[0]);
				siki += enzan[j];
				siki += std::to_string(suuzi[1]);
				siki += ")";
				siki += enzan[k];
				siki += std::to_string(suuzi[2]);
				siki += ")";
				siki += enzan[l];
				siki += std::to_string(suuzi[3]);
				kai = sisoku(l, sisoku(k, sisoku(j, suuzi[0], suuzi[1]), suuzi[2]), suuzi[3]);
			} else if (i == 1) {
				siki += "(" ;
				siki += std::to_string(suuzi[0]);
				siki += enzan[j];
				siki += std::to_string(suuzi[1]);
				siki += ")";
				siki += enzan[k];
				siki += "(";
				siki += std::to_string(suuzi[2]);
				siki += enzan[l];
				siki += std::to_string(suuzi[3]);
				siki += ")";
				kai = sisoku(k, sisoku(j, suuzi[0], suuzi[1]), sisoku(l, suuzi[2], suuzi[3]));
			} else if (i == 2) {
				siki += "(" ;
				siki += std::to_string(suuzi[0]);
				siki += enzan[j];
				siki += "(";
				siki += std::to_string(suuzi[1]);
				siki += enzan[k];
				siki += std::to_string(suuzi[2]);
				siki += ")";
				siki += ")";
				siki += enzan[l];
				siki += std::to_string(suuzi[3]);
				kai = sisoku(l, sisoku(j, suuzi[0] , sisoku(k, suuzi[1], suuzi[2])), suuzi[3]);
			} else if (i == 3) {
				siki += std::to_string(suuzi[0]);
				siki += enzan[j];
				siki += "(" ;
				siki += "(";
				siki += std::to_string(suuzi[1]);
				siki += enzan[k];
				siki += std::to_string(suuzi[2]);
				siki += ")";
				siki += enzan[l];
				siki += std::to_string(suuzi[3]);
				siki += ")";
				kai = sisoku(j, suuzi[0], sisoku(l, sisoku(k, suuzi[1], suuzi[2]), suuzi[3]));
			} else if (i == 4) {
				siki += std::to_string(suuzi[0]);
				siki += enzan[j];
				siki += "(" ;
				siki += std::to_string(suuzi[1]);
				siki += enzan[k];
				siki += "(";
				siki += std::to_string(suuzi[2]);
				siki += enzan[l];
				siki += std::to_string(suuzi[3]);
				siki += ")";
				siki += ")";
				kai = sisoku(j, suuzi[0], sisoku(k, suuzi[1], sisoku(l, suuzi[2], suuzi[3])));
			}
		} catch (...) {
			//０で割るときの例外
			kai = 0;
		}
		
		if((kai < n + 0.001)&&(kai > n - 0.001)){
			counta++;
			// std::cout << siki << "=" << kai << std::endl;
		}
		// if((kai < n + 0.001)&&(kai > n - 0.001)&&(kai != (double)n)){
		//     //std::cout << siki << "=" << kai << std::endl;
		// }
	}

	double sisoku(int mode, double a, double b) { //四則演算の選択用のメソッド
		double c = 0;
		if (mode == 0) {
			c = a + b;
		} else if (mode == 1) {
			c = a - b;
		} else if (mode == 2) {
			c = a * b;
		} else if (mode == 3) {
			c = a / b;
		}
		return c;
	}

	void countsyori() {
		if (counta > 0) {
			count++;
		}
	}
};

int tenpuzzle(int n){

//　0000から9999までくりかえす
	for (int a = 0; a < 10; a++) {
		for (int b = 0; b < 10; b++) {
			for (int c = 0; c < 10; c++) {
				for (int d = 0; d < 10; d++) {
//　i:計算順序　j,k,l:四則演算選択
					keisan retu = keisan(n, a, b, c, d);
					for (int i = 0; i < 5; i++) {
						for (int j = 0; j < 4; j++) {
							for (int k = 0; k < 4; k++) {
								for (int l = 0; l < 4; l++) {
									retu.dousyutu(i, j, k, l);
								}
							}
						}
					}
					retu.countsyori();
				}
			}
		}
	}
	return count;
}