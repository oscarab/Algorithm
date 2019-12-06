#include <iostream>
#include <cstring>
#include <stdio.h>
#include <cmath>
#include <vector>

using namespace std;

/*
   制造回文数，判断是否为质数，深度优先搜索
   洛谷P1217
*/
vector<int> numbers;

bool isPrime(int num) {
	for (int i = 3; i <= sqrt(num); i++) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}

//创造回文数
void buildPalindromes(int bit , int step , int down , int up) {
	if (step == (bit%2 != 0? bit/2 + 2:bit/2 +1)) {
		int sum = 0;
		//补充剩下的位数
		for (int i = bit / 2 - 1; i >= 0; i--) {
			numbers.push_back(numbers[i]);
		}
		//计算出回文数
		for (int i = 0; i < numbers.size(); i++) {
			sum += numbers[i] * int(round(pow(10,numbers.size() - i - 1)));
		}
		for (int i = bit / 2 - 1; i >= 0; i--) {
			numbers.pop_back();
		}
		if (sum < down) {
			return;
		}
		if (sum > up) {
			exit(0);
		}
		if (isPrime(sum)) {
			cout << sum <<endl;
		}
		return;
	}
	for (int i = 0; i <= 9; i ++) {
		if (step == 1) {
			i ++;
		}
		numbers.push_back(i);
		buildPalindromes(bit, step + 1 , down , up);
		numbers.pop_back();
	}
	return;
}

int getBits(int num) {
	int count = 0;
	for (;num != 0;num/=10,count++)
		;
	return count;
}
int main() {
	int a, b;
	cin >> a >> b;
	
	int bit1 = getBits(a) , bit2 = getBits(b);

	for (int i = bit1; i <= bit2; i++) {
		if (i > 2 && i % 2 == 0) {
			continue;
		}
		buildPalindromes(i, 1 ,a ,b);
	}

}