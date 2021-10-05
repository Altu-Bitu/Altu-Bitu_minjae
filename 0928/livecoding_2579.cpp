#include <iostream> //입출력
#include <vector> //벡터 사용

using namespace std;

int maxScore(int n, vector<int> &score) { //인자: 계단 개수, 계단별 점수
    vector<int> dp(n + 1, 0); //각 계단까지의 최댓값 저장

    dp[1] = score[1]; //1번째 계단은 해당 칸 밟는게 최대
    dp[2] = score[1] + score[2]; //2번째 계단은 1번째와 2번째 밟는게 최대
    for (int i = 3; i <= n; i++) { //i번째 계단까지 경로 최댓값
        //2칸 전에서 온 경우(2칸 이동), 3칸 전 + 2칸 이동해서 1칸 전으로 온 경우(1칸 이동) 중 최댓값
        dp[i] = max(dp[i - 2], dp[i - 3] + score[i - 1]) + score[i];
    }

    return dp[n]; //dp[n]: n번째 계단까지 오르면서 얻을 수 있는 최대의 total score
}

int main() {
    int n;//계단의 개수

    //입력
    cin >> n;
    vector<int> score(n + 1, 0); //계단 점수
    for (int i = 1; i <= n; i++) //n개의 계단마다(i:계단 번호)
        cin >> score[i]; //점수 입력

    //연산 + 출력
    cout << maxScore(n, score) << '\n';

    return 0; //int형 반환
}