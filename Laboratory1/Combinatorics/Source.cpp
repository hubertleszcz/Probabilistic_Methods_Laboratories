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

void sortVector(vector <int> &vec) {
	for (int i = 0; i < vec.size(); i++) {
		for (int j = i + 1; j < vec.size(); j++) {
			if (vec[i] > vec[j]) swap(vec[i], vec[j]);
		}
	}
}


class Generator {
private:
	vector <int> data;
	vector<vector<int>> permutations;
	vector<vector<int>> combinations;
	int dataSize;
	Town* towns;
	int combinationSize;
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
		/*	for (int i = 0; i < currentNumbers.size(); i++) {
				cout << this->towns[currentNumbers[i]-1].name << " ";
			}
			cout << endl;*/
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

	void findShortestRoute() {
		int bestSolution = 0;
		double wynik = 1000000.00;
		for (int j = 0; j < this->permutations.size(); j++) {
			auto currentPermutation = this->permutations[j];
			double currentDist = 0;
			currentDist += towns[currentPermutation[0]-1].CalculateDistance(towns[currentPermutation[currentPermutation.size() - 1]-1]);
			for (int i = 0; i < currentPermutation.size()-1; i++) {
				currentDist += towns[currentPermutation[i]-1].CalculateDistance(towns[currentPermutation[i+1]-1]);

			}
			if (currentDist < wynik) {
				wynik = currentDist;
				bestSolution = j;
			}
		}
		for (int i = 0; i < permutations[bestSolution].size(); i++) {
			cout << towns[permutations[bestSolution][i] - 1].name << " ";
		}
		cout << wynik;
	}

	bool vectorsSame(vector <int> first, vector<int> second) {
		for (int i = 0; i < first.size(); i++) {
			if (first[i] != second[i]) return false;
		}

		return true;
	}

	bool comboExists(vector <int> toCheck, vector<vector<int>> combos) {
		for (int i = 0; i < combos.size(); i++) {
			auto currentCombo = combos[i];
			if (vectorsSame(toCheck, currentCombo)) return true;
		}
		return false;
	}

	void generateCombinations(int comboSize) {
		for (int i = 0; i < permutations.size(); i++) {
			auto current = permutations[i];
			vector<int> currentCombo;
			for (int i = 0; i < comboSize; i++) currentCombo.push_back(current[i]);
			sortVector(currentCombo);
			if (!comboExists(currentCombo, combinations)) combinations.push_back(currentCombo);
		}

	/*	for (int i = 0; i < combinations.size(); i++) {
			for (int j = 0; j < combinations[i].size(); j++) {
				cout << combinations[i][j] << " ";
			}
			cout << endl;
		}*/
	}

	void findClosestToHalf() {
		int neededValue = 0;
		int closest = 0x7FFFFFFF;
		int index = 0;
		int wynik = 0;
		for (int i = 0; i < this->dataSize; i++) {
			neededValue += this->towns[i].citizens;
		}
		neededValue /= 2;
		cout << neededValue << " ";

		for (int i = 0; i < combinations.size(); i++) {
			auto current = combinations[i];
			int sum = 0;
			for (int i = 0; i < current.size(); i++) {
				sum += towns[current[i] - 1].citizens;
			}
			if (abs(sum - neededValue) < closest) {
				closest = abs(sum - neededValue);
				index = i;
				wynik = sum;
			}
		}

		for (int i = 0; i < combinations[index].size(); i++) {
			cout << towns[combinations[index][i] - 1].name << " ";
		}
		cout << wynik;

	}

};

int main() {
	int N = 10;
	vector <int> tmpData;
	for (int i = 0; i < N; i++) {
		tmpData.push_back(i);
	}
	Generator task1(N, tmpData);
	vector<int> currentNumbers = vector<int>(N, N+1);
	task1.generatePermutations(N, currentNumbers);
	//task1.findShortestRoute();
	task1.generateCombinations(N / 2);
	task1.findClosestToHalf();
}