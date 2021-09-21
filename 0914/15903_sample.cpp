#include <iostream>
#include <queue>

using namespace std;
typedef long long ll;

//카드들의 점수 총합
ll sum(priority_queue<ll, vector<ll>, greater<>> &pq) {
    ll result = 0;
    while (!pq.empty()) { //최소 힙이 빌 때까지 반복
        result += pq.top(); //top 값 더하고
        pq.pop(); //제거
    }
    return result;
}

/**
 * 매번 숫자가 가장 작은 카드 2장을 뽑아야 최종 결과가 최솟값이 됨
 */
int main() {
    int n, m, input;
    priority_queue<ll, vector<ll>, greater<>> pq; //최소 힙

    //입력
    cin >> n >> m; //n: 카드 개수 m: 합체 횟수
    while (n--) {
        cin >> input; //카드 숫자 입력
        pq.push(input); //최소 힙에 삽입
    }

    //연산
    while (m--) {
        vector<ll> num(2);

        //카드의 총 수량은 변하지 않고, 카드의 개수 최솟값은 2이기 때문에 empty 체크를 하지 않아도 됨
        for (int i = 0; i < 2; i++) { //가장 숫자가 작은 카드 2장 뽑기
            num[i] = pq.top(); //최소 힙 : top에 최소값 위치
            pq.pop(); //뽑은 카드 제거
        }
        for (int i = 0; i < 2; i++) //계산 한 값을 덮어 쓰기
            pq.push(num[0] + num[1]);//제거된 2장 카드 대신 합체된 값 2번 삽입
    }

    //출력
    cout << sum(pq);
}
