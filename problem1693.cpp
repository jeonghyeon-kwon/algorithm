#include <iostream> 
#include <iterator>
#include <algorithm> 
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;
#define MOD 1000000007
#define MAX_INT 2147483647
#define MAX_LLONG 9223372036854775807

/*
시도1.
	BFS로 트리를 탐색
	leaf 노드는 무조건 1을 칠한다.
	현재 pos를 root로 하는 최솟값 = 서브트리들의 최솟값의 합 + root가 가질 수 있는 색 중에 최솟값
	optimal 하지 않다.

해결
	- 참고사항
		트리는 평면 그래프이다.
		평면그래프에서의 그래프 색깔 칠하기는 4개로 칠할 수 있다고 증명 되었다.
		트리는 2가지 색으로 모두 칠할 수 있다.
	- 점화식
		dp[color][root] = (모든 child에 대해서)Sum( (색칠 가능한 모든 것에 대해서)min( dp[color'][subtree root] ) ) + root.color

		서브트리의에서 각각의 최솟값을 선택하는 이유는 root의 색깔이 정해져 주었기 때문에
		각각  서브트리의 최솟값을 선택해야지 전체가 최솟값이 된다.(시도1은 botom up, 해결은 top down)
*/

int N;
int root = 1;
int dp[5][100001] = {0,};
vector <int> edges[100001];

int treeDP(int parent, int pos, int color)
{
	int& ret = dp[color][pos];
	if(ret != 0)
	{
		return ret;
	}

	if(edges[pos].size() == 1 && root != pos)
	{
		return ret = color;
	}

	int len = edges[pos].size();
	for(int i = 0; i < len; i++)
	{
		int v = edges[pos][i];
		if(v == parent)
		{
			continue;
		}
		int tmp = 400000;
		for(int j = 1; j <= 4; j++)
		{
			if(j != color)
			{
				tmp = min(tmp, treeDP(pos, v, j));
			}
		}
		ret += tmp;
	}
	ret += color;
	return ret;
}
int main ()
{
	freopen("sample.txt", "r", stdin);

	scanf("%d", &N);
	int A,B;
	for(int i = 0; i < N-1; i++)
	{
		scanf("%d %d", &A, &B);
		edges[A].push_back(B); edges[B].push_back(A);
	}
	int ret = 400000;
	for(int i = 1; i <= 4; i++)
	{
		ret = min(ret, treeDP(0, root, i));
	}
	printf("%d\n", ret);
	return 0;
}