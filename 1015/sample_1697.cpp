#include <iostream>
#include <queue>

using namespace std;
const int SIZE = 100000;

int bfs(int n, int k) {
    vector<int> check(SIZE + 1, 0); //위치 방문 시간 정보
    queue<int> q; //큐에 좌표값 저장
    int ans = 0; //찾을 수 있는 최소 시간

    check[n] = 1; //시작 노드 방문체크 + 시간 초기화
    q.push(n); //시작 노드 초기화
    while (!q.empty()) { //큐가 비어 있지 않다면
        int x = q.front(); //현재 탐색하려는 위치
        q.pop(); //탐색한 위치 제거

        if (x == k) { //동생 찾으면 탐색 종료. 시작 위치를 1로 초기화 했기 때문에 1을 빼줌
            ans = check[x] - 1; //시간 업데이트
            break; //동생 찾았으므로 반복문 탈출
        }

        vector<int> child = {x - 1, x + 1, x * 2}; //자식 노드
        for (int i = 0; i < 3; i++) { //이동 케이스 3개
            if (child[i] >= 0 && child[i] <= SIZE && !check[child[i]]) { //범위 내에 있고, 첫 방문이라면
                check[child[i]] = check[x] + 1; //시간 증가
                q.push(child[i]); //큐에 삽입
            }
        }
    }
    return ans; //정답 반환
}

/**
 * x좌표 위에서 x-1, x+1, 2*x의 위치로 계속 이동하며 탐색
 * 가장 빠른 시간을 찾아야 하므로 주변 노드부터 탐색하는 풀이로 풀어서 k에 도달하면 바로 탐색 종료 (bfs)
 */

int main() {
    int n, k; //n: 수빈이 위치, k: 동생 위치

    //입력
    cin >> n >> k;

    //연산 & 출력
    cout << bfs(n, k) << '\n';

    return 0;
}

