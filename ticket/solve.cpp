#include <iostream>
#include <thread>

class keisan {
	int counta;
	int suuzi[4];
	int n; // target-number
	std::string enzan;  //式表示用
	double sisoku(int mode, double a, double b);
public:
	static int count;
	keisan(int n_, int a, int b, int c, int d);
	void dousyutu(int i, int j, int k, int l);
	void countsyori() { if (counta > 0) this->count++;}
};

keisan::keisan(int n_, int a, int b, int c, int d)
{
	this->n = n_;
	this->counta = 0;
	this->enzan = "+-*/";
	this->suuzi[0] = a;
	this->suuzi[1] = b;
	this->suuzi[2] = c;
	this->suuzi[3] = d;
}

// i: 計算順序
// j,k,l: 四則演算選択
void keisan::dousyutu(int i, int j, int k, int l)
{
	double kai = 0;
	std::string siki = std::string("");  //式表示用
	try {
		if (i == 0)
			kai = sisoku(l, sisoku(k, sisoku(j, suuzi[0], suuzi[1]), suuzi[2]), suuzi[3]);
		else if (i == 1)
			kai = sisoku(k, sisoku(j, suuzi[0], suuzi[1]), sisoku(l, suuzi[2], suuzi[3]));
		else if (i == 2)
			kai = sisoku(l, sisoku(j, suuzi[0] , sisoku(k, suuzi[1], suuzi[2])), suuzi[3]);
		else if (i == 3)
			kai = sisoku(j, suuzi[0], sisoku(l, sisoku(k, suuzi[1], suuzi[2]), suuzi[3]));
		else if (i == 4)
			kai = sisoku(j, suuzi[0], sisoku(k, suuzi[1], sisoku(l, suuzi[2], suuzi[3])));
	} catch (...) {
		kai = 0; // 0で割るときの例外
	}
	if ((kai < n+0.001) && (kai > n-0.001)) counta++;
}

//四則演算の選択用のメソッド
double keisan::sisoku(int mode, double a, double b)
{
	double c = 0;
	if (mode == 0) c = a + b;
	else if (mode == 1) c = a - b;
	else if (mode == 2) c = a * b;
	else if (mode == 3) c = a / b;
	return c;
}

int keisan::count;

int tenpuzzle(int n)
{
	keisan::count = 0;
	// loop "abcd" as "[0-9][0-9][0-9][0-9]"
	for (int a=0; a<10; a++) {
		for (int b=0; b<10; b++) {
			for (int c=0; c<10; c++) {
				for (int d=0; d<10; d++) {
					// i:計算順序 j,k,l:四則演算選択
					keisan retu = keisan(n, a, b, c, d);
					for (int i=0; i<5; i++) {
						for (int j=0; j<4; j++) {
							for (int k=0; k<4; k++) {
								for (int l=0; l<4; l++) {
									retu.dousyutu(i, j, k, l);
								}
							}
						}
					}
					retu.countsyori(); // this number-sequence is valid
				}
			}
		}
	}
	return keisan::count;
}