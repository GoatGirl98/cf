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
		std::vector<int> a(n + 1);
		for (int i = 0, x; i < n; ++i) {
			std::cin >> x;
			++a[x];
		}
		std::cout << *std::max_element(a.begin(), a.end()) << "\n";
	}
	return 0;
}