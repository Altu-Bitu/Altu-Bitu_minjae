//
// Created by iw040 on 2021-10-12.
//

#include <iostream> //입출력 사용
#include <vector> //벡터 사용

using namespace std;

int main() {
    ios::sync_with_stdio(false); //입출력 속도 향상
    cin.tie(NULL);

    int n, m, num; //n: 수의 개수, m: 합을 구해야 하는 횟수, num: n개의 숫자

    //입력
    cin >> n >> m;
    vector<int> sum(n + 1, 0);
    for (int i = 1; i <= n; i++) { //인덱스를 1부터 시작하면 i=0인 경우를 따로 처리할 필요 없음
        cin >> num;
        sum[i] = sum[i - 1] + num; //첫번째 수부터 i번째 수까지의 누적합
    }

    while (m--) {// m: 구간 개수
        int s, e; //s: 구간 시작, e:구간 끝
        cin >> s >> e; //입력

        //출력
        cout << sum[e] - sum[s - 1] << '\n'; // 누적합이므로 e번째 sum - (s-1)번째 sum
    }
}