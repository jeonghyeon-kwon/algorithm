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
MO's algorithm을 이용
	- 설명
		알고리즘은 별거 없다.
		많은 갯수의 query가 들어올때 정렬 잘해서 복잡도를 줄이는 방법이다.
		즉 정렬 방법이 중요하다는 뜻이다.
			정렬방법은 N을 sqrt N 단위로 쪼개서 그 part 별로 정렬하는 것이다.
		복잡도는 O(N sqrt(N))이다.
		sqrtN = sqrt(N) 의 값을 100이라 하면
		query가 (1, 100), (99, 100), (1, 200), (199, 200), (1, 300), (299, 300) .....
		으로 들어올때 복잡도는 100 + 100 + 200 + 200 + 300 ... =  200(1+2+3+4+5+.....100) 
		O(N sqrt(N))이 된다.
		query자체의 갯수는 크게 중요하지 않다.

	- 참고자료
		http://kesakiyo.tistory.com/25
		복잡도를 더 줄이고 싶으면 펜윅트리를 사용한다.
*/
struct range{
	int start;
	int end;
	int idx;
	range():start(0),end(0),idx(0){}
	range(int s, int e, int i):start(s),end(e),idx(i){}
};

int N, M;
int sqrtN;
int input[100001] = {0,};
int value[1000001] = {0,};
int differentCount = 0;

bool cmp(struct range fir, struct range sec)
{
	int firPos = fir.end / sqrtN;
	int secPos = sec.end / sqrtN;
	return firPos == secPos ? fir.start < sec.start : firPos < secPos;
}

int main () 
{
	freopen("sample.txt", "r", stdin);
	scanf("%d", &N);
	sqrtN = (int)sqrt(N);
	for(int i = 1; i <= N; i++)
	{
		scanf("%d", &input[i]);
	}
	
	scanf("%d", &M);
	vector <struct range> query(M);
	int s,e;
	for(int i = 0; i < M; i++)
	{
		scanf("%d%d", &s, &e);
		query[i] = range(s,e,i);
	}
	sort(query.begin(), query.end(), cmp);
	vector <int> ans(M);
	int prevStart = query[0].start, prevEnd = query[0].start - 1;
	int currStart, currEnd;
	for(int i = 0; i < M; i++)
	{
		currStart = query[i].start;
		currEnd = query[i].end;
		
		if(prevStart < currStart)
		{
			for(int j = prevStart; j < currStart; j++)
			{
				value[input[j]]--;
				if(value[input[j]] == 0)
				{
					differentCount--;
				}
			}
		}
		else
		{
			for(int j = currStart; j < prevStart; j++)
			{
				value[input[j]]++;
				if(value[input[j]] == 1)
				{
					differentCount++;
				}
			}
		}

		if(prevEnd < currEnd)
		{
			for(int j = prevEnd + 1; j <= currEnd; j++)
			{
				value[input[j]]++;
				if(value[input[j]] == 1)
				{
					differentCount++;
				}
			}
		}
		else
		{
			for(int j = currEnd + 1; j <= prevEnd; j++)
			{
				value[input[j]]--;
				if(value[input[j]] == 0)
				{
					differentCount--;
				}
			}
		}
		ans[query[i].idx] = differentCount;
		prevStart = currStart;
		prevEnd = currEnd;
	}

	for(int i = 0; i < M; i++)
	{
		printf("%d\n", ans[i]);
	}

	return 0;
}