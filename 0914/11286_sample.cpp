#include <iostream>
#include <queue>

using namespace std;

/**
 * 우선순위 큐의 비교함수
 * sort 함수의 비교함수 형식과 비교해보기
 */
struct cmp  { //비교 함수
    bool operator()(int a, int b) {
        if (abs(a) == abs(b)) //절댓값이 같을 경우
            return a > b; //실제 값이 더 작은 음수 우선 정렬
        return abs(a) > abs(b); //절댓값 작은 순서대로 정렬
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    priority_queue<int, vector<int>, cmp> pq; //priority_queue <자료형, 구현체, 비교 연산자> 형태로 정의
    int n, x;

    cin >> n; //연산의 개수 입력
    for (int i = 0; i < n; i++) {
        cin >> x; //정수 입력
        if (x == 0) { // 0일 경우 배열에서 가장 작은 값 출력 & 제거
            if (pq.empty()) //런타임 에러 방지
                cout << 0 << '\n'; //배열 비어있을 경우 0 출력
            else {
                cout << pq.top() << '\n'; //가장 작은 수 출력
                pq.pop();//가장 작은 수 삭제
            }
        } else
            pq.push(x); //우선순위 큐에 삽입
    }
}

