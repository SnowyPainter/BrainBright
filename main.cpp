#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
using namespace std;

const string savedPatterns = "patterns.txt";
const string output = "output.txt";

random_device rd;
mt19937 gen(rd());

string replaceUnknown(string pattern, int min, int max) {
	if (min > max) {
		auto temp = max;
		max = min;
		min = temp;
	}
	uniform_int_distribution<int> distr(min, max);

	for (int i = 0; i < pattern.length(); i++) {
		
		if (pattern[i] == '?') {
			auto n = to_string(distr(gen));
			pattern.replace(i, 1, n);
		}
	}
	return pattern;
}

vector<string> getPatterns() {
	ifstream  fs;
	fs.open(savedPatterns);
	string tempPat;
	vector<string> pats;
	if (fs.is_open()) {
		int i = 1;
		while (getline(fs, tempPat))
		{
			pats.push_back(tempPat);
		}
		fs.close();
		return pats;
	}

	return vector<string>();
}

int main() {
	cout << "Welcome to BrainBright" << endl;
	cout << "Continue on(Y/N)?" << endl;
	string yorn;
	cin >> yorn;
	if (yorn == "Y" || yorn == "y") {
		
		int selected = 0, max = 0;
		auto pats = getPatterns();
		vector<int> selecteds;
		cout << "Choose pattern what you want to do" << endl;
		for (int i = 0; i < pats.size(); i++) {
			auto pat = pats[i];
			cout << i + 1 << ". " << pat << endl;
		}
		cout << "0. Next" << endl;
		do {
			cout << endl << "= ";
			cin >> selected;
			if (selected != 0) {
				selecteds.push_back(selected);
				if (max < selected)
					max = selected;
			}
		} while (selected != 0);
		if (selecteds.size() > 0) {
		
			ofstream fs;
			fs.open(output, ios::trunc);
			
			uniform_int_distribution<int> distr(0, max - 1);
			int count = 0, minNumber, maxNumber;
			cout << "How many? : ";
			cin >> count;
			cout << "Min number : ";
			cin >> minNumber;
			cout << "Max number : ";
			cin >> maxNumber;
			for (int i = 0; i < count; i++) {
				const int n = distr(gen);
				auto replaced = replaceUnknown(pats[selecteds[n]], minNumber, maxNumber);
				cout << replaced << endl;
				fs << replaced << endl;
			}
			fs.close();
			cout << "Saved at output.txt" << endl;
		}

		cout << "Byebye" << endl;
		string a;
		cin >> a;
	}
	else {
		return 0;
	}


}