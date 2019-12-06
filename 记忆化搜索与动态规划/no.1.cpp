#include <iostream>
#include <cstring>
#include <stdio.h>
#include <cmath>
#include <vector>

using namespace std;

/*
   记忆化搜索
   洛谷P1464
*/
int memory[25][25][25] = { 0 };
int w(int a, int b, int c) {

	if (a <= 0 || b <= 0 || c <= 0) {
		return 1;
	}
	else if (a > 20 || b > 20 || c > 20) {
		return w(20, 20, 20);
	}
	else if (memory[a][b][c]) {
		return memory[a][b][c];
	}
	else if(a < b && b < c){
		memory[a][b][c] = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
		return memory[a][b][c];
	}
	else {
		memory[a][b][c] = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1);
		return memory[a][b][c];
	}
}
int main() {

	int a, b, c;
	while (cin >> a >> b >> c) {
		if (a == -1 && b == -1 && c == -1) {
			break;
		}
		cout << "w(" << a << ", " << b << ", " << c << ") = " << w(a, b, c) << endl;
	}
	return 0;
}