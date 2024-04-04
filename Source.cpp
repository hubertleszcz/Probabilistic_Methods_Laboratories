#include <iostream>
#include <vector>
using namespace std;

#define n 100000
#define M (unsigned int)(1 << 31)
#define a 69069
#define c 1
// wzor 2,2 M = 2^31 unsigned inty a = 69069, c=1, X0 = 15, n=100 000, 10 przedziałów - DONE
//2. wzor 2.6, p=7, q = 3, 1001101 - poczatkowe, liczby co 31 bitów, 100k liczb, przesuwasz kolejne 7 bitow na poczatek wektora po koncu generacji

void createRandom(int amount, vector <unsigned int>& task1, vector<vector<unsigned int>> &intervals) {
	vector <unsigned int> tmp = { 0,M / 10, M / 5, M / 10 * 3,M / 5 * 2, M / 2, M / 5 * 3, M / 10 * 7, M / 5 * 4, M / 10 * 9 };
	for (int i = 1; i < amount; i++) {
		task1.push_back((a * task1[i - 1] + c) % M);
		for (int j = 9; j >= 0; j--) {
			if (task1[i] >= tmp[j]) {
				intervals[j].push_back(task1[i]);
				break;
			}
		}
	}
}
unsigned int conversion(vector <bool> bits) {
	unsigned int wynik = 0;
	for (int i = 31; i >= 0; i--) {
		wynik *= 2;
		if (bits[i]) wynik++;
	}
	return wynik;
}
void randomRegister(int amount, vector <unsigned int>& task2, vector <vector<unsigned int>>& intervals, vector <bool>& bits) {
	vector <unsigned int> tmp = { 0,M / 10, M / 5, M / 10 * 3,M / 5 * 2, M / 2, M / 5 * 3, M / 10 * 7, M / 5 * 4, M / 10 * 9 };
	for (int j = 0; j < amount; j++) {
		for (int i = 7; i < 31; i++) {
			bits[i] = (bits[i - 7]^bits[i - 3]);
		}
		task2.push_back(conversion(bits));
		for (int i = 9; i >= 0; i--) {
			if (task2[j] >= tmp[i]) {
				intervals[i].push_back(task2[j]);
				break;
			}
		}
		for (int i = 0; i < 7; i++) {
			int index1 = i - 7 >= 0 ? i - 7 : i - 7 + 31;
			int index2 = i - 3 >= 0 ? i - 3 : i - 3 + 31;
			bits[i] = bits[index1] ^ bits[index2];
		}
	}
	for (int i = 0; i < 10; i++) {
		cout << task2[i] << endl;
	}
}


int main() {
	vector <unsigned int> task1 = { 15 };
	vector <vector <unsigned int>> intervals(10);
	createRandom(n, task1, intervals);
	/*for (int i = 0; i < task1.size(); i++) {
		cout << task1[i] << endl;
	}*/
	for (int i = 0; i < intervals.size(); i++) {
		cout << intervals[i].size() << " ";
		intervals[i].clear();
	}
	vector <bool> bits(31);
	bits.push_back(1);
	bits.push_back(0);
	bits.push_back(0);
	bits.push_back(1);
	bits.push_back(1);
	bits.push_back(0);
	bits.push_back(1);
	cout << endl;
	vector <unsigned int> task2;
	randomRegister(n, task2, intervals, bits);
	for (int i = 0; i < intervals.size(); i++) {
		cout << intervals[i].size() << " ";
		intervals[i].clear();
	}
}