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

struct edge{
	int dest;
	int weight;
	edge(int b, int c):dest(b), weight(c){}
	edge():dest(0), weight(0){}
};

int N;
int root = 1;
int visit[100001] = {0,};
vector <struct edge> edges[100001];

/*
treeDP(pos)
pos를 root로 보고 수행한다.
ret.first : root로 오지 않는 트리의 가중치
ret.second : root를 기준으로 서브트리에서 root로 오는 트리의 가중치
N-1 차수이면 => O(N^2)이 된다.
for loop 두번 도는것을 한번에 돌면 된다!!!!
이전 방식
1->2, 1->3, 1->4, 2->3, 2->4, 3->4 6번만에 계산
변한 방식
1->2, (1->3, 2->3), (1->4, 2->4, 3->4) 3번만에 계산
*/
/*
pair <long long, long long> treeDP(int pos)
{
	visit[pos] = 1;
	pair<long long, long long> ret = make_pair(0, 0);
	if(edges[pos].size() == 1 && root != pos)
	{
		return ret;
	}

	int len = edges[pos].size();
	vector < pair<long long, long long> > childRet;
	vector <int> childIdx;
	for(int i = 0; i < len; i++)
	{
		if(visit[edges[pos][i].dest])
		{
			continue;
		}
		childRet.push_back(treeDP(edges[pos][i].dest));
		childIdx.push_back(i);
	}

	len = childRet.size();
	for(int i = 0; i < len; i++)
	{
		ret.first = (ret.first + childRet[i].second + childRet[i].first) % MOD;
		ret.second = (ret.second + (childRet[i].second + 1)* edges[pos][childIdx[i]].weight) % MOD;
		for(int j = i + 1; j < len; j++)
		{
			ret.first = (ret.first + ((edges[pos][childIdx[i]].weight * edges[pos][childIdx[j]].weight) % MOD ) * (((childRet[i].second + 1) * (childRet[j].second + 1))% MOD)) % MOD;
		}
	}
	return ret;
}
*/

pair <long long, long long> treeDP(int pos)
{
	visit[pos] = 1;
	pair<long long, long long> ret = make_pair(0, 0);
	if(edges[pos].size() == 1 && root != pos)
	{
		return ret;
	}

	int len = edges[pos].size();
	pair <long long, long long> childRet;
	long long tmpRet = 0;
	for(int i = 0; i < len; i++)
	{
		if(visit[edges[pos][i].dest])
		{
			continue;
		}
		childRet = treeDP(edges[pos][i].dest);
		ret.first = (ret.first + childRet.second + childRet.first + ((edges[pos][i].weight * tmpRet) % MOD) * (childRet.second + 1)) % MOD;
		ret.second = (ret.second + (childRet.second + 1)* edges[pos][i].weight) % MOD;
		tmpRet = (tmpRet + (childRet.second + 1) * edges[pos][i].weight) % MOD;
	}
	return ret;
}

int main ()
{
	freopen("sample.txt", "r", stdin);

	scanf("%d", &N);
	int A,B,W;
	for(int i = 0; i < N-1; i++)
	{
		scanf("%d %d %d", &A, &B, &W);
		edges[A].push_back(edge(B, W)); edges[B].push_back(edge(A, W));
	}
	pair <long long, long long> ret = treeDP(root);
	printf("%lld\n", (ret.first + ret.second) % MOD);
	return 0;
}