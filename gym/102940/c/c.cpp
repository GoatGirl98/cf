#include <bits/stdc++.h>
#define watch(x) std::cout << (#x) << " is " << (x) << std::endl
using LL = long long;

int main() {
	//freopen("in", "r", stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	double s;
	std::cin >> s;
	std::cout.precision(14);
	std::cout << std::fixed << std::cbrt(s / 153) << std::endl;
	return 0;
}