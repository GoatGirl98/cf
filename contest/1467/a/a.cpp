#include <bits/stdc++.h>
#define watch(x) std::cout << (#x) << " is " << (x) << std::endl
using LL = long long;

int main() {
	//freopen("in", "r", stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int cas = 1;
	std::cin >> cas;
	while (cas--) {
		int n;
		std::cin >> n;
		for (int i = 0; i < n; ++i) {
			std::cout << (abs(i - 1) + 8) % 10;
		}
		std::cout << std::endl;
	}
	return 0;
}