#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int INF = 1e6 + 1; //최댓값

vector<vector<int>> cost; //색깔별 비용

int paintDp(int n) {//인자: 집의 수
    vector<vector<int>> dp(n + 1, vector<int>(3, 0));//집집마다 RGB 각 컬러로 색칠하는데 드는 비용 정보 저장

    //i번째 집을 각각의 색으로 칠하는 최소 비용
    for (int i = 1; i <= n; i++) { //i:집 번호, 집의 수만큼 반복문 돌면서
        dp[i][0] = cost[i][0] + min(dp[i - 1][1], dp[i - 1][2]); //R 채택할 경우: 이전 집 G일 때, B일 때 중 최소 비용 + R 비용
        dp[i][1] = cost[i][1] + min(dp[i - 1][0], dp[i - 1][2]); //G 채택할 경우: 이전 집 R일 때, B일 때 중 최소 비용 + G 비용
        dp[i][2] = cost[i][2] + min(dp[i - 1][0], dp[i - 1][1]); //B 채택할 경우: 이전 집 R일 때, G일 때 중 최소 비용 + B 비용
    }

    int ans = INF; //ans: 비용
    for (int i = 0; i < 3; i++) //i:색깔(0-R,1-G,2-B), 반복문 돌면서 색깔별로
        ans = min(ans, dp[n][i]); //더 최소비용인 경우 ans에 저장

    return ans; //최소 비용 값 리턴
}

/**
 * 앞 뒤의 집의 색이 서로 달라야 한다.
 * 1번 집부터 시작해서 이전 집과 다른 색을 계속 골라주면 자동으로 앞 뒤 집의 색이 서로 달라진다
 * 따라서, 각 집에 대해 각각 3가지 색을 선택한 경우의 최솟값을 계속 저장하며 풀자
 *
 * dp[i][빨간색] = min(dp[i-1][초록색], dp[i-1][파란색]) + 비용[i][빨간색]
 * dp[i][초록색] = min(dp[i-1][빨간색], dp[i-1][파란색]) + 비용[i][초록색]
 * dp[i][파란색] = min(dp[i-1][빨간색], dp[i-1][초록색]) + 비용[i][파란색]
 */

int main() {
    int n;//집의 수

    //입력
    cin >> n;
    cost.assign(n + 1, vector<int>(3, 0)); //집마다 색칠 비용 정보
    for (int i = 1; i <= n; i++) { //i:집 번호, 집의 수만큼 반복문 돌면서
        for (int j = 0; j < 3; j++) {//집마다 빨강, 초록, 파랑칠 했을때
            cin >> cost[i][j];//비용 입력
        }
    }

    //연산 + 출력
    cout << paintDp(n) << '\n';

    return 0; //정수값 리턴
}