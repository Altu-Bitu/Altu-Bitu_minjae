#include <iostream> //입출력 사용
#include <vector> //벡터 사용

using namespace std;

int cntCleanRobot(int r, int c, int d, vector<vector<int>> &board) {//청소기의 현재 위치와 방향, 칸의 정보
    //상, 우, 하, 좌
    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, 1, 0, -1};

    int step = 0, ans = 0; //step: 네 방향 탐색 플래그, ans: 청소 횟수
    while (true) {
        if (board[r][c] == 0) { //칸이 비었다면
            board[r][c] = 2; //청소
            ans++; //청소횟수+1
        }

        if (step == 4) { //인접 칸을 모두 탐색했는데
            if (board[r - dr[d]][c - dc[d]] == 1) //뒤쪽이 벽이라면
                return ans; //작동 멈춤
            r -= dr[d]; //한 칸 후진
            c -= dc[d]; //한 칸 후진
            step = 0; //네 방향 탐색에 따른 이동 마쳤으므로 step 초기화
        } else { //인접 칸 방향별로 탐색 중
            d = (d + 3) % 4; //방향
            if (board[r + dr[d]][c + dc[d]]) { //청소할 공간이 없다면
                step++; //회전
                continue; //다음 방향 탐색
            }
            //청소할 공간 있으면
            r += dr[d]; //한 칸 전진
            c += dc[d]; //한 칸 전진
            step = 0; //step 초기화 후 다시 청소 프로세스 시작점으로 진입
        }
    }
}

/**
 * board 정보 -> 0: 빈 칸, 1: 벽, 2: 청소한 공간
 * step: 회전 카운트. 4가 되면 한 바퀴 돌아 다시 제자리로 돌아왔음을 의미
 *
 * 항상 첫 행, 마지막 행, 첫 열, 마지막 열은 벽이라고 문제에서 주어졌으므로 범위 검사를 할 필요가 없음
 */

int main() {
    int n, m, r, c, d; //n: 세로 크기, m: 가로 크기 r&c: 로봇청소기 칸의 좌표, d: 로봇청소기 방향

    //입력
    cin >> n >> m >> r >> c >> d;
    vector<vector<int>> board(n, vector<int>(m, 0)); //칸의 상태 정보
    for (int i = 0; i < n; i++) { //i: 행
        for (int j = 0; j < m; j++) { //j: 열
            cin >> board[i][j]; //입력
        }
    }

    //연산 & 출력
    cout << cntCleanRobot(r, c, d, board);
    return 0;
}
