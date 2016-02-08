#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

int n;
vector<int> v;

long long getMinCost() {
	priority_queue<int, std::vector<int>, std::greater<int>> queue;
	for (int i = 0; i < v.size(); ++i) {
		queue.push(v[i]);
	}
	long long cost = 0;
	while (queue.size() != 1) {
		int a = queue.top();
		queue.pop();
		int b = queue.top();
		queue.pop();
		//printf("a = %d, b = %d\n", a, b);
		cost += a + b;
		queue.push(a + b);
	}
	return cost;
}

int main() {
	freopen("FenceRepair.in", "r", stdin);
	scanf("%d", &n);
	v.resize(n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &v[i]);
	}
	long long result = getMinCost();
	printf("%lld\n", result);
	return 0;
}
