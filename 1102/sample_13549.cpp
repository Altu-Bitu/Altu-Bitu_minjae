#include <iostream> //입출력 사용
#include <queue> //덱 사용

using namespace std;
const int SIZE = 100000; //좌표 범위

int zeroOneBfs(int n, int k) { //인자: 위치 정보
    vector<int> check(SIZE + 1, 0); //정점에 도착한 시간
    deque<int> dq; //덱 사용
    int ans = 0; //최소 시간

    //시작 위치 초기화
    check[n] = 1; //시간 1로 초기화
    dq.push_back(n); //덱에 삽입

    while (!dq.empty()) { //덱 비어 있지 않다면
        int x = dq.front(); //현재 탐색하려는 위치
        dq.pop_front(); //탐색한 위치 덱에서 제거

        if (x == k) { //동생 찾으면 탐색 종료. 시작 위치를 1로 초기화 했기 때문에 1을 빼줌
            ans = check[x] - 1; //탐색 시간 업데이트 되면서 처음 초기화한 1 값이 계속 유지된 상태이므로 -1
            break; //반복문 탈출
        }

        int next = x * 2; //순간이동
        if (next <= SIZE && !check[next]) { //범위 내에 있고 처음 방문하는 지점이라면
            check[next] = check[x]; //시간 +0
            dq.push_front(next); //덱에 삽입
        }

        next = x - 1; //뒤로 걷기
        if (next >= 0 && !check[next]) {//범위 내에 있고 처음 방문하는 지점이라면
            check[next] = check[x] + 1; //시간 +1
            dq.push_back(next); //덱에 삽입
        }

        next = x + 1; //앞으로 걷기
        if (next <= SIZE && !check[next]) { //범위 내에 있고 처음 방문하는 지점이라면
            check[next] = check[x] + 1; //시간 +1
            dq.push_back(next); //덱에 삽입
        }
    }
    return ans; //최소 시간
}

/**
 * x좌표 위에서 2*x, x-1, x+1의 위치로 계속 이동하며 탐색
 * 이동에 대한 가중치는 0, 1 두 가지이므로 다익스트라가 아니라 덱으로 풀 수 있음 (0-1 BFS)
 *
 * !주의!
 * 순간이동으로 이동하는 경우를 걸어서 이동하는 경우보다 먼저 고려해야 함
 * -> 어차피 순간이동은 push_front 되는데 왜?
 * -> 1에서 2로 이동할 땐 걷는 것도 가능하고 순간이동도 가능함
 *    걷는 방법을 먼저 고려하면 check 배열이 갱신되어 순간이동을 고려할 수 없음
 */
int main() {
    int n, k; //n: 수빈 위치, k: 동생 위치

    //입력
    cin >> n >> k;

    //연산 & 출력
    cout << zeroOneBfs(n, k) << '\n';
}

