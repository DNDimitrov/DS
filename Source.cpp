#include<iostream>
#include "Header.h"
#include<stdlib.h>
using namespace std;

double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

int main() {
	double a[10];
	for (int i = 0; i < 10; i++) {
		cout << "vavedi ocenki";
		cin >> a[i];
	}
	double result = 0;
	for (int i = 0; i < 10; i++) {
		result += a[i];
	}
	result = result / 10;
	Vector<double> gosho;
	double random = 0;
	for (int i = 0; i < 10; i++) {
		random = fRand(result, 6);
		cout << "random" << random;
		gosho.push_back(random);
	}
	gosho.sort();
	for (int j = 0; j < gosho.size(); j++) {
		cout << gosho[j] << endl;
	}
	system("pause");
	return 0;
}