#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,abm,mmx,avx,avx2,popcnt,tune=native")

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<std::pair<LL, int>, null_type, std::less<>, rb_tree_tag, tree_order_statistics_node_update>

#include <bits/stdc++.h>
#define watch(x) std::cout << (#x) << " is " << (x) << std::endl
using LL = long long;
#include "include/izlyforever.hpp"

template<typename T>
void debug(std::vector<T> a){
	for (auto &i : a) std::cout << i << ' ';
	std::cout << std::endl; 
}

int main() {
	// freopen("C:\\Users\\dna049\\cf\\in", "r", stdin);
	std::cin.tie(nullptr)->sync_with_stdio(false);
	auto start = std::clock();
	
	std::cout << "Time used: " << (std::clock() - start) << "ms" << std::endl;
	return 0;
}