#include <iostream>//입출력
#include <vector>//벡터 사용

using namespace std;

struct info { //물품 정보 저장 구조체
    int w, v;//w:물품의 무게, v:물품의 가치
};

//2차원 dp 활용 냅색
int knapsack_2(int n, int k, vector<info> &product) {//인자: 물품의 수, 버틸 수 있는 무게, 물품별 (무게, 가치) 정보
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));//2차원 벡터 생성

    for (int i = 1; i <= n; i++) { //각 물품에 대해, i: 물품 번호, j: 최대 배낭 무게
        for (int j = 1; j < product[i].w; j++) //우선 해당 물품을 배낭에 넣을 수 없는 경우
            dp[i][j] = dp[i - 1][j]; //그 전 물품에 대한 현재 무게의 최댓값 저장
        for (int j = product[i].w; j <= k; j++) //해당 물품을 배낭에 넣는게 가능한 경우
            dp[i][j] = max(dp[i - 1][j - product[i].w] + product[i].v, dp[i - 1][j]); //배낭에 넣는 경우와 안 넣는 경우 중 최댓값 저장
    }

    return dp[n][k];//dp[n][k]: n개의 가방이 있을 경우 k 무게 이하 범위에서 넣은 물건 가치합의 최댓값
}

//1차원 dp 활용 냅색
int knapsack_1(int n, int k, vector<info> &product) {//인자: 물품의 수, 버틸 수 있는 무게, 물품별 (무게, 가치) 정보
    vector<int> dp(k + 1, 0); //1차원 벡터 생성

    for (int i = 1; i <= n; i++) {//물품 개수만큼 반복문 돌면서(i: 물품 번호)
        for (int j = k; j >= product[i].w; j--) //j: 최대 배낭 무게, 1차원이니 무게 k부터 시작(거꾸로), 이전 값 사용하기 위해서
            dp[j] = max(dp[j - product[i].w] + product[i].v, dp[j]); //점화식: 물건 넣는 경우, 안 넣는 경우 중 최댓값 저장
    }

    return dp[k]; //dp[k]: k 무게 이하의 범위에서 넣은 물건 가치합의 최댓값
}

int main() {
    int n, k; //n: 물품의 수, k: 버틸 수 있는 무게

    //입력
    cin >> n >> k; // 물품의 수와 버틸 수 있는 무게 입력
    vector<info> product(n + 1, {0, 0});//물품의 수만큼 w(물품의 무게), v(물품의 가치) 쌍 저장하는 벡터
    for (int i = 1; i <= n; i++) //물품의 수만큼 반복문 돌면서
        cin >> product[i].w >> product[i].v; //물품의 무게, 물품의 가치 입력

    //연산 + 출력
    cout << knapsack_1(n, k, product) << '\n';


    return 0;//int형 반환
}
