//참고 링크: https://www.secmem.org/blog/2020/10/24/dp/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define SIZE 1000001

int num[SIZE];
int dp[SIZE];

int main(){
    int n;
    cin >> n;

    //첫번째 초기화
    dp[1] = 0;
    num[1] = -1;

    for(int i=2; i<=n; i++){

        //-1
        dp[i] = dp[i-1] + 1;
        num[i] = i-1;

        //2
        if(i % 2 == 0 && dp[i/2]+1 < dp[i] ){
            dp[i] = dp[i/2]+1;
            num[i] = i/2;
        }

        //3
        if(i % 3 == 0 && dp[i/3]+1 < dp[i] ){
            dp[i] = dp[i/3]+1;
            num[i] = i/3;
        }
    }

    cout << dp[n] << '\n';

    while(n>0){
        cout << n << ' ';
        n = num[n];
    }

    return 0;
}
