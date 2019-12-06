#include <iostream>
#include <cstring>
#include <stdio.h>
#include <cmath>
#include <vector>

using namespace std;

/*
   三连击升级版洛谷P1618
   深度优先搜索
*/

int a, b, c;
bool box[9] = { 0 };
bool checking[9] = { 0 };
int number[3] = { 0 };
int point = 0;
bool hasAnswer = false;

void clear() {
	for (int i = 0; i < 9; i++) {
		checking[i] = false;
	}
}
bool check(int num) {
	while (num != 0) {
		if (box[(num % 10) - 1] || checking[(num % 10) - 1] || (num % 10) == 0) {
			return false;
		}
		checking[(num % 10) - 1] = true;
		num /= 10;
	}
	return true;
}
void DFS(int step) {
	if (step == 4) {
		int num1 = number[0] * 100 + number[1] * 10 + number[2];
		int num2 = num1 * b / a;
		int num3 = num1 * c / a;
		bool f1 = check(num2);
		bool f2 = check(num3);

		if (num3 >= 1000) {
			if (!hasAnswer) {
				cout << "No!!!";
			}
			exit(0);
		}
		if ((num1 * b) % a == 0 && (num1 * c) % a == 0 && f1 && f2) {
			cout << num1 << " " << num2 << " " << num3 << endl;
			hasAnswer = true;
		}
		clear();
		return;
	}

	for (int i = 1; i <= 9; i++) {
		if (!box[i - 1]) {
			number[point ++] = i;
			box[i - 1] = true;
			DFS(step + 1);
			box[i - 1] = false;
			point--;
		}
	}
	return;
}

int main() {

	cin >> a >> b >> c;
	DFS(1);
	return 0;
}