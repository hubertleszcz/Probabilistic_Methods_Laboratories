#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

//15 miast
//id, nazwa, mieszkancy, wspolrzedne


struct Town {
	int id;
	string name;
	int citizens;
	double coordinateX;
	double coordinateY;

	double CalculateDistance(Town secondTown) {
		return sqrt(pow((this->coordinateX - secondTown.coordinateX), 2) + pow((this->coordinateY - secondTown.coordinateY), 2));
	}
};

bool isInVector(int a, vector <int> vector) {
	for (int i = 0; i < vector.size(); i++) {
		if (a == vector[i]) return true;
	}
	return false;
}


class Generator {
private:
	vector <int> data;
	vector<vector<int>> permutations;
	int dataSize;
	Town* towns;
public:
	Generator(int dataSize, vector <int> data) {
		this->dataSize = dataSize;
		for (int i = 0; i < data.size(); i++) {
			this->data.push_back(data[i]);
		}
		this->towns = new Town[dataSize];
		ifstream plik("france.txt");
		for (int i = 0; i < dataSize; i++) {
			plik >> towns[i].id >> towns[i].name >> towns[i].citizens >> towns[i].coordinateX >> towns[i].coordinateY;
		}
	}
	void generatePermutations(int count, vector<int> currentNumbers) {
		if (count == 0) {
			for (int i = 0; i < currentNumbers.size(); i++) {
				cout << this->towns[currentNumbers[i]-1].name << " ";
			}
			cout << endl;
			this->permutations.push_back(currentNumbers);
		}
		else {
			for (int i = 1; i <= this->dataSize; i++) {
				if (isInVector(i, currentNumbers)) continue;
				else{
					currentNumbers[this->dataSize - count] = i;
					generatePermutations(count -1, currentNumbers);
				}
			}
		}
	}
};

int main() {
	int N = 5;
	vector <int> tmpData;
	for (int i = 0; i < N; i++) {
		tmpData.push_back(i);
	}
	Generator task1(N, tmpData);
	vector<int> currentNumbers = vector<int>(N, N+1);
	task1.generatePermutations(N, currentNumbers);
}