#include <iostream>
#include <cstring>
#include <stdio.h>
#include <cmath>
#include <vector>

using namespace std;

int length , k ,prime=0;    //k为路径深度
vector<int> numbers;
vector<int> arg;

bool isPrime(int num) {
	for (int i = 2; i <= sqrt(num); i++) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}

void DFS(int step , int start) {
	if (step == k + 1) {
		if (arg.size() == k) {
			int sum = 0;
			for (int i = 0; i < k; i++) {
				sum += arg[i];
			}
			if (isPrime(sum)) {
				prime++;
			}
		}
		return;
	}
	for (int i = start; i < length; i++) {
		arg.push_back(numbers[i]);
		DFS(step + 1 , i + 1);
		arg.pop_back();
	}
	return;
}

int main() {
	
	cin >> length >> k;
	for (int i = 0; i < length; i++) {
		int a;
		cin >> a;
		numbers.push_back(a);
	}
	DFS(1, 0);

	cout << prime;
	return 0;
}