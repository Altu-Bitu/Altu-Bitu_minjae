#include <iostream> //입출력 사용
#include <vector> //벡터 사용
#include <queue>  //큐 사용
#include <algorithm> //정렬 사용

using namespace std;
const int INF = 401; //20*20이 최대
typedef pair<int, int> ci; //위치 좌표

pair<int, ci> nextPos(int n, int shark_size, ci &shark, vector<vector<int>> &board) { //칸 크기, 상어 크기, 상어 위치, 칸 정보
    int dr[4] = {-1, 1, 0, 0}; //상, 하, 좌, 우
    int dc[4] = {0, 0, -1, 1};

    int min_dist = INF; //초기화
    queue<ci> q; //상어가 갈 수 있는 곳
    vector<vector<int>> visited(n, vector<int>(n, 0)); //상어의 방문 여부
    vector<ci> list; //상어가 먹을 수 있는 물고기들의 위치

    visited[shark.first][shark.second] = 1; //현재 위치 상어 방문
    q.push(shark); //상어 위치 큐에 삽입
    while (!q.empty()) { //큐에 탐색할 장소가 있을 때까지
        int row = q.front().first; //행 위치
        int col = q.front().second; //열 위치
        int dist = visited[row][col]; // 거리 저장
        q.pop(); //탐색한 요소 제거

        if (dist >= min_dist) //최단거리 이상은 탐색할 필요 없음
            continue; //다음 차례 탐색
        for (int i = 0; i < 4; i++) { //i: 상하좌우 탐색
            int nr = row + dr[i]; //상하 위치 이동 반영
            int nc = col + dc[i]; //좌우 위치 이동 반영
            if (nr < 0 || nr >= n || nc < 0 || nc >= n || visited[nr][nc] || board[nr][nc] > shark_size) //범위 벗어나고 방문한적 있고, 물고기가 상어 크기보다 크다면
                continue; //다음 차례 탐색

            visited[nr][nc] = visited[row][col] + 1; //거리 갱신
            if (board[nr][nc] && board[nr][nc] < shark_size) { //먹을 수 있는 물고기 발견
                list.emplace_back(nr, nc); //list 벡터에 먹을 수 있는 위치 추가
                min_dist = visited[nr][nc]; //최단 거리(시간) 갱신
                continue; //다음 차례 탐색
            }
            q.push({nr, nc}); //먹을 수 있는 위치 삽입
        }
    }

    if (list.empty()) //상어가 갈 수 있는 곳이 없음
        return {min_dist, {-1, -1}}; //

    sort(list.begin(), list.end(), [](const ci &p1, const ci &p2) { //정렬
        if (p1.first != p2.first)  //오름차순 정렬
            return p1.first < p2.first;
        return p1.second < p2.second;
    });
    return {min_dist - 1, list[0]}; //구한 최단거리(시간)과 위치 좌표 반환
}

int simulation(int n, pair<int, int> &shark, vector<vector<int>> &board) { //칸 크기, 아기 상어 위치 정보, 칸 정보
    int ans = 0, size = 2, cnt = 0; //물고기 잡아먹을 수 있는 시간, 초기 아기 상어 크기, 물고기 개수
    while (true) { //반복문 돌면서 주변 탐색
        pair<int, ci> result = nextPos(n, size, shark, board); //먹을 수 있는 다음 위치
        if (result.first == INF) //더 이상 먹을 수 있는 물고기가 공간에 없음
            break; //탐색 중지, 반복문 탈출
        ans += result.first; //시간 갱신
        cnt++; //포식 횟수 +1
        if (cnt == size) { //상어 크기 증가
            cnt = 0; //초기화, 물고기 수 다시 세기 시작
            size++; //상어 크기는 +1
        }

        //상어 이동
        ci pos = result.second; //먹을 수 있는 위치
        board[shark.first][shark.second] = 0; //물고기 먹음
        shark = pos; //상어 위치 갱신
    }
    return ans; //포식 시간 반환
}

/**
 * 1. 상어로부터 가장 가까운 거리에 있는 모든 물고기 탐색 (BFS)
 * 2. 우선순위 조건에 맞추어 먹으러 갈 물고기 확정
 *    탐색하는 방향에 우선순위를 두는 걸로 해결되지 않음! (예제 입력 4) 정렬 필요
 * 3. 상어가 이동할 수 있는 곳이 없을 때까지 BFS 탐색 반복
 *
 * 입력 범위가 작기 때문에 매번 BFS 탐색을 반복해도 시간 초과 X
 * 가능한 물고기의 최대 마리 수 : 399마리
 * 최대 BFS 탐색 횟수 : 399회, 1회 탐색마다 while 문은 최대 400회 미만으로 순회
 * 총 연산 횟수 약 160000번으로 충분히 가능
 *
 * 해설 : https://myunji.tistory.com/378
 * *글 자체는 별로 도움이 안되고...그냥 리팩토링하면 코드가 이렇게 되는구나 정도만 봐주세요
 */
int main() {
    int n; //가로,세로 칸 크기
    pair<int, int> shark_pos; //상어 위치 정보

    //입력
    cin >> n;
    vector<vector<int>> board(n, vector<int>(n)); //칸 정보
    for (int i = 0; i < n; i++) { //i:행
        for (int j = 0; j < n; j++) { //j:열
            cin >> board[i][j]; //칸 정보 입력
            if (board[i][j] == 9) //상어의 초기 위치
                shark_pos = make_pair(i, j); //상어 위치 정보 입력
        }
    }

    //연산 & 출력
    cout << simulation(n, shark_pos, board);
}

