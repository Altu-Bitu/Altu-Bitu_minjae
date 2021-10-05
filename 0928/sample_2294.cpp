#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1e9; //최댓값

int knapsackCoin(int n, int k, vector<int> &coin) {//인자: 동전의 개수, 목표하는 가치합, 동전 가치 정보
    vector<int> dp(k + 1, INF); //dp k+1크기, INF로 초기화

    dp[0] = 0; //0가치를 만드는 경우 초기화
    for (int i = 0; i < n; i++) { //i:동전 번호, 동전 개수 만큼 반복문 돌면서
        for (int j = coin[i]; j <= k; j++) { //j: 목표하는 가치합
            if (dp[j - coin[i]] != INF) //불가능한 값이 아니라면
                dp[j] = min(dp[j], dp[j - coin[i]] + 1); //dp[j]와 dp[j-coin[i]]+coin[j]한 값을 비교해서 더 적은 동전 사용한 경우 선택
        }
    }

    if (dp[k] == INF) //동전 개수가 최댓값(불가능한 값)과 같다면
        return -1; //-1 반환
    return dp[k]; //k 가치합을 만들기 위해 사용한 최소 동전 개수 반환
}

/**
 * 배낭 문제(12865)와 유사
 * 현재 가치를 만드는 동전 개수의 최솟값 저장
 * = max(기존 값, [현재 가치 - 현재 사용하려는 동전 가치]의 동전 개수 최솟값 + 1)
 *
 * !주의! 최솟값을 찾는 문제이므로 dp 배열 초기화 중요
 * !주의! 배낭 문제와 다르게, 꼭 현재 가치를 정확하게 만드는 경우만 검사해야함
 */

int main() {
    int n, k;//n:동전의 종류, k: 목표하는 가치의 합

    //입력
    cin >> n >> k;
    vector<int> coin(n, 0); //동전별 가치 정보
    for (int i = 0; i < n; i++)//i:동전 번호, 동전의 개수만큼 반복문 돌면서
        cin >> coin[i];//동전마다 갖는 가치 입력

    //연산 + 출력
    cout << knapsackCoin(n, k, coin) << '\n';

    return 0; //정수값 리턴
}