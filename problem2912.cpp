#include <iostream> 
#include <iterator>
#include <algorithm> 
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;
#define MOD 1000000007

/*
	- 참고사항 
		문제에 대해 답이 맞긴 하였지만 복잡도는 O(MN)이다.
		왜냐하면 (1,N), (2,2), (3, N).... 이런식으로 들어오면 O(MN)인데 테스트 데이터는 그러지 않은 듯 하다.
	
	다른 사람들의 풀이를 보는데 O(MClog(N))으로 풀었음.....
	무슨 문제인지 잘모르겟다는 의문이 든다.

*/
struct range{
	int A;
	int B;
	int idx;
	range():A(0),B(0),idx(0){}
	range(int a, int b, int i):A(a),B(b),idx(i){}
};

bool cmp(struct range fir, struct range sec)
{
	return fir.A < sec.A || (fir.A == sec.A && fir.B < sec.B);
}

int input[300001] = {0,};
int cnt[10001] = {0,};

int main () 
{
	freopen("sample.txt", "r", stdin);

	int N, C, M;
	scanf("%d %d",&N, &C);
	for(int i = 1; i <= N; i++)
	{
		scanf("%d", &input[i]);
	}
	
	scanf("%d", &M);
	vector <struct range> query(M+1);
	for(int i = 1; i <= M; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		query[i] = range(a,b,i);
	}
	sort(query.begin() + 1, query.end(), cmp);

	query[0] = range(query[1].A, query[1].A - 1, 0);
	vector <int> ans(M+1);
	for(int i = 1; i <= M; i++)
	{
		for(int j = query[i-1].A; j < query[i].A; j++)
		{
			cnt[input[j]]--;
		}
		if(query[i-1].B < query[i].B)
		{
			for(int j = query[i-1].B + 1; j <= query[i].B; j++)
			{
				cnt[input[j]]++;
			}
		}
		else
		{
			for(int j = query[i].B + 1; j <= query[i-1].B; j++)
			{
				cnt[input[j]]--;
			}
		}
		int sum = 0;
		int half = (query[i].B - query[i].A + 1) / 2;
		for(int j = 1; j <= C; j++)
		{
			if(cnt[j] > half)
			{
				ans[query[i].idx] = j;
				break;
			}
			sum += cnt[j];
			if(sum > half)
			{
				ans[query[i].idx] = 0;
				break;
			}
		}
	}
	for(int i = 1; i <= M; i++)
	{
		if(ans[i] == 0)
		{
			printf("no\n");
		}
		else
		{
			printf("yes %d\n", ans[i]);
		}
	}
	return 0;
}