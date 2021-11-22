#include <iostream> //입출력 사용
#include <queue> //큐 사용
#include <vector> //벡터 사용

using namespace std;
typedef pair<int, int> ci; //좌표 정보 저장
const int INF = 1e5 * 2; //최대 N*N 칸을 지나게 됨

int dijkstra(int n, vector<vector<int>> &board) { //n: 동굴의 크기 n*n , board: 동굴 칸별 도둑 루피 정보
    int dr[4] = {-1, 1, 0, 0}; //상,하,좌,우
    int dc[4] = {0, 0, -1, 1};

    int ans = 0; //잃게 되는 최소 금액
    vector<vector<int>> dist(n, vector<int>(n, INF)); //비용 저장 벡터
    priority_queue<pair<int, ci>, vector<pair<int, ci>>, greater<>> pq; //경로 저장 큐

    //시작 위치 초기화
    dist[0][0] = board[0][0];
    pq.push(make_pair(dist[0][0], make_pair(0, 0))); //방문한 시작 위치 기준으로 큐에 비용(루피 크기)와 좌표 저장

    while (!pq.empty()) { //큐가 비어있지 않다면
        int weight = pq.top().first; //가중치: 큐의 첫번째 요소 비용 저장
        int row = pq.top().second.first; //행: 큐의 두번째 요소 x 좌표 저장
        int col = pq.top().second.second; //열: 큐의 두번째 요소 y 좌표 저장
        pq.pop(); //큐에서 제거

        if (row == n - 1 && col == n - 1) { //제일 오른쪽 아래 칸 도착
            ans = weight; //답 지금까지 계산된 가중치로 초기화
            break; //끝까지 검사했으므로 반복문 탈출
        }
        if(weight > dist[row][col]) //이미 확인했던 좌표
            continue; //다음 요소 확인
        for (int i = 0; i < 4; i++) { //i: 상하좌우 각 비용 확인
            int nr = row + dr[i]; //현재 좌표에 +상/하/좌/우
            int nc = col + dc[i];
            if ((nr < 0) || (nr >= n) || (nc < 0) || (nc >= n)) //범위를 벗어난다면
                continue; //다음 방향 확인

            int next_weight = weight + board[nr][nc]; //시작점으로부터 연결된 좌표까지의 거리
            if (dist[nr][nc] > next_weight) { //더 짧은 경로로 갈 수 있다면
                dist[nr][nc] = next_weight; //가중치(축적 비용) 갱신
                pq.push({next_weight, {nr, nc}}); //큐에 현재 비용과 좌표 정보 입력
            }
        }
    }
    return ans;
}

/**
 * 상하좌우로 이동 가능 -> 연결됐다는 것
 * 시작 지점이 (0, 0)인 다익스트라
 */
int main() {
    int n, num = 1; //n: 동굴의 크기

    while (true) {
        //입력
        cin >> n;
        if (n == 0) //0 입력되면
            break; //전체 입력 종료

        vector<vector<int>> board(n, vector<int>(n, 0)); //동굴 칸 정보 저장 벡터
        for (int i = 0; i < n; i++) { //i: 행
            for (int j = 0; j < n; j++) //j:열
                cin >> board[i][j]; //도둑 루피의 크기 입력
        }

        //연산 & 출력
        cout << "Problem " << num++ << ": " << dijkstra(n, board) << '\n';
    }
}