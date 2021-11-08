#include <iostream>
#include <vector>

using namespace std;

int ans, n, m; //순서대로 정답 , 종이의 세로칸, 종이의 가로칸
vector<vector<int>> board; //종이 숫자 정보 저장
int dr[4] = {-1, 1, 0, 0}; //dr,dc로 상하좌우 표현
int dc[4] = {0, 0, -1, 1};

//board[row][col]을 가운데로 하는 +모양 만들기
int horn(int row, int col) {
    int cnt = 0, min_block = 1001, sum = board[row][col]; //cnt: 가장자리 수, min_block: 최대값 1000, row&col: 행, 열

    for (int i = 0; i < 4; i++) {
        int nr = row + dr[i]; //상or하 움직임
        int nc = col + dc[i]; //좌or우 움직임

        if (nr < 0 || nr >= n || nc < 0 || nc >= m) //범위를 벗어나면 무시
            continue; //다음 사각형
        min_block = min(min_block, board[nr][nc]); //가장자리 블럭 중 값이 가장 작은 블럭
        sum += board[nr][nc]; //합 누적
        cnt++; //처음 board[row][col] 기준으로 추가된 사각형
    }

    if (cnt < 3) //가능한 가장자리가 최소 3개 이상이어야 함
        return 0; //테트로미노 생성 실패
    if (cnt == 3)
        return sum; //구한 최대합 반환

    //+
    return sum - min_block; //가장 값 작은 블록 제거
}

//한붓 그리기가 가능한 블럭들 백트래킹 탐색
void backtracking(int row, int col, int cnt, int sum) {
    if (cnt == 4) { //기저조건 : 4개의 블럭을 탐색함
        ans = max(ans, sum); //백트래킹 불가능한 테트로미노 최대합과 비교
        return; //끝
    }

    for (int i = 0; i < 4; i++) { //정사각형 4개
        int nr = row + dr[i]; //상or하 움직임
        int nc = col + dc[i]; //좌or우 움직임

        if (nr < 0 || nr >= n || nc < 0 || nc >= m || !board[nr][nc]) //범위를 벗어나거나, 이미 방문했다면
            continue; //다음 사각형
        int save = board[nr][nc]; //종이 칸의 값 저장
        board[nr][nc] = 0; //0으로 초기화
        backtracking(nr, nc, cnt + 1, sum + save); //현재 값 더해서 다음 지점으로 이동
        board[nr][nc] = save; //값 업데이트
    }
}

/**
 * 1. 각 블럭을 백트래킹이 가능한 블럭과 불가능한 블럭으로 나누기
 *    -> 블럭을 한붓 그리기로 그릴 수 있으면 백트래킹이 가능 아니라면 불가능
 *    -> 보라색 블럭을 제외하면 모두 백트래킹 가능
 * 2. 보라색 블럭은 + 모양에서 가장자리를 하나 제거한 것과 같음
 *    -> 가운데 블럭을 중심으로 가장자리 블럭을 붙여보고 가능한 최댓값 구하기
 * 3. 각 블럭에 대해 깊이가 4인 백트래킹 함수를 수행하며 최댓값 갱신
 *
 * 해설 : https://myunji.tistory.com/297
 * *코드가 살짝 달라요(블로그 코드는 최적화 하기 전)
 */
int main() {
    //입력
    cin >> n >> m; // n:세로크기, m:가로크기
    board.assign(n, vector<int>(m, 0)); //종이 숫자 정보
    for (int i = 0; i < n; i++) { //n: n번째 세로줄
        for (int j = 0; j < m; j++) //m: m번째 가로줄
            cin >> board[i][j]; //종이 숫자
    }

    //연산
    for (int i = 0; i < n; i++) { //i:세로칸
        for (int j = 0; j < m; j++) {//j:가로칸
            ans = max(ans, horn(i, j)); //보라색 블럭 처리
            int save = board[i][j]; //현재 칸 숫자 저장

            board[i][j] = 0;
            backtracking(i, j, 1, save); //나머지 모양 처리
            board[i][j] = save;
        }
    }

    //출력
    cout << ans;
}