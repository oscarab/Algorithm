#include <iostream>
#include <cstring>
#include <stdio.h>
#include <cmath>
#include <vector>

using namespace std;

/*
    使用了归并排序，贪心算法
	洛谷P1478
*/
vector<int> height;
vector<int> strength;

void merge(int start1 ,int end1, int start2 , int end2) {
	int size = start2 - start1;
	while (1) {
		if (start1 > end1 || start2 > end2) {
			break;
		}

		if (strength[start1] < strength[start2]) {
			start1++;
		}
		else{
			int temp = strength[start2];
			int arg = height[start2];
			bool flag = strength[start1] == strength[start2];

			for (int i = 0; i <= end1 - start1; i++) {
				strength[start2 - i] = strength[end1 - i];
				height[start2 - i] = height[end1 - i];
			}

			strength[start1] = temp;
			height[start1] = arg;

			start1++;
			if (flag) start1++;
			end1++;
			start2++;
		}

	}
}

void sort(int start , int end) {
	if (start + 1 == end) {
		merge(start, start, end, end);
		return;
	}
	else if (start == end) {
		return;
	}
	int mid = (end + start) / 2;
	sort(start , mid);
	sort(mid + 1, end);
	merge(start, mid, mid + 1, end);
}

int main() {
	int n, s ,a, b, count = 0;
	cin >> n >> s >> a >> b;

	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		height.push_back(a);
		strength.push_back(b);
	}

	if(n > 0) sort(0,strength.size() - 1);

	for (int i = 0; i < strength.size(); i++) {
		if (s >= strength[i] && a + b >= height[i]) {
			s -= strength[i];
			count++;
		}
	}
	cout << count;

}