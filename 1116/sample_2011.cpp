#include <iostream> //입출력 사용
#include <vector> //벡터 사용

using namespace std;
const int MOD = 1e6; //1000000 MOD 연산

int cntPassword(int n, string s) { //암호화 문자열 길이, 암호화 문자열
    vector<int> dp(n + 1, 0); //dp로 접근
    if (s[0] == '0') //암호를 해석할 수 없음
        return 0; //0 출력

    dp[0] = dp[1] = 1; //s[0]의 암호 해석 경우의 수 1로 초기화
    for (int i = 2; i <= n; i++) { //2~n까지 암호 해석 경우의 수 저장
        if (s[i - 1] == '0' && (s[i - 2] < '1' || s[i - 2] > '2')) //0 앞의 수가 1이나 2가 아닌 경우
            return 0; //해석 불가

        if (s[i - 1] != '0') //0이 아니라면
            dp[i] += dp[i - 1]; //현재 수 + 이전 수가 읽을 수 있는 단어의 수
        if (s[i - 2] == '1' || (s[i - 1] <= '6' && s[i - 2] == '2')) //현재 수가 2번째 수라면
            dp[i] += dp[i - 2]; //현재 수([i-1]-[i]) + 이전 수(i-2)가 읽을 수 있는 단어의 수
        dp[i] %= MOD; //%MOD로 정답 값 축소 (문제 요구사항)
    }
    return dp[n]; //해석할 수 있는 경우의 수 출력
}

/**
 * dp[i] = i인덱스까지 암호 해석할 수 있는 경우의 수 저장
 * => dp[i] = dp[i-1] + dp[i-2] (단, dp[i-1]과 dp[i-2]에서 이어서 암호 만들 수 있는 경우만)
 *
 * 1. '0' 혼자는 암호 해석 불가
 * 2. 처음 시작이 '0'인 경우 주의
 * 3. 현재 수가 '0'인데 앞의 수가 '1'이나 '2'가 아닌 경우 -> 암호 해석할 수 없음
 * 4. 두 개의 수를 하나의 알파벳으로 고려할 때, 26이하의 수인지 잘 확인해야 함
 *
 * 본 풀이는 dp 배열 인덱스를 편하게 관리하기 위해 1번 인덱스부터 시작
 */

int main() {
    string s; //암호화 문자열

    //입력
    cin >> s;

    //연산 & 출력
    cout << cntPassword(s.length(), s) << '\n';
    return 0;
}
