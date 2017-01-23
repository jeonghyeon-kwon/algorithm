#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <memory.h>
#include <stack>

using namespace std;

int main() {
    string str1; 		//입력 1
    string str2;		//입력 2
    string str3;		//최장 공통 수열 저장 스트링
    int end1, end2;		//string 길이를 각각 저장
    int dp[1001][1001];	//계산된 결과를 저장, 길이를 1씩 추가했으나 1000까지만 사용
    int initinput = 0;		//첫 [0][i]배열에 str1[0]문자와 str[i]가 같으면 initinput값을 1로
				//초기화 해줘서 같은 문자열이 나온 후 부터는 모두 1개의 최장 공통 수열의 개수를 
				//다 1로 초기화할때 사용
    stack<char> sta;		//dp[end1][end2]에서 부터 i, j둘 중 하나라도 0이 될때까지 최장 공통 수열
				//을 찾아서 저장하는 스택, 꺼꾸로 찾아가니 스택을이용
    int s1, s2;			

    cin >> str1;		//string객체에 입력을 받으려면 cin이나 getline이용
    cin >> str2;		
    memset(dp, 0, sizeof(dp));	//초기화
    end1 = str1.size()-1;	//0 ~ end1 - 1 의 범위를 
    end2 = str2.size()-1;
    s1 = end1, s2 = end2;	//최장 공통 수열 문자열을 찾을때 사용하는 변수

    for(int i = 0; i <= end2; i++)
    {
        if(str1[0] == str2[i])
            initinput = 1;
        dp[0][i] = initinput;
    } 
	//[0][0] ~ [0][end2]까지 초기화
 
    initinput = 0;

    for(int i = 0; i <= end1; i++)
    {
        if(str2[0] == str1[i])
            initinput = 1;
        dp[i][0] = initinput;
    }
	//[0][0] ~ [end1][0]까지 초기화

    for(int k = 1; k <= end1; k++) {
        for(int i = 1; i <= end2; i++){
            if(str1[k] == str2[i])
                dp[k][i] = dp[k-1][i-1]+ 1;
            else
                dp[k][i] = max(dp[k-1][i], dp[k][i-1]);
        }
    }
	//[1][1]부터 구하면서 계산 시작 
	//현재 [i][j]에 대해 일치하는 문자이면 [i][j] = [i-1][j-1] + 1 
	//다른 값이면 [i][j] = max([i-1][j], [i][j-1]) 

    while(s1 >= 0 && s2 >= 0)
    {
       if(s1 >= 1 && dp[s1][s2] == dp[s1-1][s2])
       {
           s1 = s1 - 1;
       }
       else if(s2 >= 1 && dp[s1][s2] == dp[s1][s2-1])
       {
           s2 = s2 - 1;
       }
       else if(dp[s1][s2] >= 1)
       {
           if(dp[s1][s2] == dp[s1-1][s2-1]) {
               s1 = s1 - 1;
               s2 = s2 - 1;
           }
           else {
               sta.push(str2[s2]);
               s1 = s1 - 1;
               s2 = s2 - 1;
           }
       }
       else{
           s1 = s1 - 1;
           s2 = s2 - 1;
       }
    }
	//그림 참고

    while(!sta.empty())
    {
        str3 += sta.top();
        sta.pop();
    }
	//스택한 저장한 문자를 순서대로 string에 저장

    printf("%d\n", dp[end1][end2]);
    printf("%s\n", str3.c_str());
    return 0;
}