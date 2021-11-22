#include <iostream> //입출력 사용
#include <vector> //벡터 사용

using namespace std;

int n, m, ans = 65; //n: 세로 크기, m: 가로 크기
vector<vector<int>> board; //사무실 구조

//cctv 범위 표시
void ray(int row, int col, int dir) { //행, 열, 방향
    int dr[4] = {-1, 0, 1, 0}; //cctv 방향
    int dc[4] = {0, 1, 0, -1}; //상, 우, 하, 좌

    while (row >= 0 && row < n && col >= 0 && col < m && board[row][col] != 6) { //dir 방향으로 뻗어나가며 cctv 표시
        if (board[row][col] == 0) //다른 cctv를 지우지 않기 위해 빈 공간일 때만 표시
            board[row][col] = 7; //감시 표시
        row += dr[dir]; //행 이동
        col += dc[dir]; //열 이동
    }
}

//cctv 방향 지정
void install(int cctv, int row, int col, int dir) { //현재 사무실 정보, 행 위치, 열 위치, 검사 순서(정해둔 방향 의미)
    if (cctv >= 1) //1, 2, 3, 4, 5번 cctv
        ray(row, col, dir); //cctv 감시 영역 표시 (dir : 0,1,2,3)
    if (cctv >= 2 && cctv != 3) //2, 4, 5번 cctv
        ray(row, col, (dir + 2) % 4); //(dir + 2) % 4 : 2,3,0,1
    if (cctv >= 3) //3, 4, 5번 cctv
        ray(row, col, (dir + 1) % 4); //(dir + 1) % 4 : 1,2,3,0
    if (cctv == 5) //5번 cctv
        ray(row, col, (dir + 3) % 4); //(dir + 1) % 4 : 3,0,1,2
}

//사각지대 계산
int blindSpot() {
    int cnt = 0; //사각지대 개수
    for (int i = 0; i < n; i++) {  //행
        for (int j = 0; j < m; j++) { //열
            if (!board[i][j]) //값이 0이라면
                cnt++; //개수 +1
        }
    }
    return cnt; //사각지대 개수 반환
}

void backtracking(int idx) { //백트래킹 함수
    if (idx == n * m) { //기저 조건 : 사무실의 모든 위치 확인
        ans = min(ans, blindSpot()); //사각지대 계산 후 최솟값 갱신
        return; //함수 끝
    }

    int row = idx / m; //사무실 y좌표
    int col = idx % m; //사무실 x좌표
    int cur = board[row][col]; //현재 사무실 정보
    if (cur == 0 || cur == 6 || cur == 7) //cctv가 없는 곳
        return backtracking(idx + 1); //백트래킹 호출

    vector<vector<int>> save = board; //unvisited 처리용 board 상태 저장
    for (int i = 0; i < 4; i++) { //4개의 방향에 대해 cctv 설치
        install(cur, row, col, i); //cctv 감시 방향 visited 처리
        backtracking(idx + 1); //백트래킹 호출
        board = save; //unvisited 처리

        //2번 cctv의 방향 종류는 2개, 5번 cctv의 방향 종류는 1개
        if ((cur == 2 && i == 1) || (cur == 5 && i == 0))
            break; //시간 단축
    }
}

/**
 * cctv가 설치될 수 있는 모든 경우를 고려하는 완전탐색 문제
 *
 * 1. 각 cctv에 대해 가능한 모든 방향을 고려하여 설치
 *    1, 3, 4번 cctv : 4방향
 *    2번 cctv : 2방향
 *    5번 cctv : 1방향
 * 2. install 함수에서 각 cctv의 빛이 뻗어나갈 방향을 잡음
 * 3. ray 함수에서 cctv의 감시 가능 범위 표시
 * 4. 모든 위치를 확인했으면 blindSpot 함수를 통해 사각지대 계산
 *
 * 풀이 : https://myunji.tistory.com/411
 * 해당 코드는 위 링크의 코드를 리팩토링한 코드입니다.
 * 말로는 풀이를 설명하기 어려우니 링크를 꼭 확인해주세요!
 */
int main() {
    //입력
    cin >> n >> m;
    board.assign(n, vector<int>(m)); //n*m인 사무실 구조 정보
    for (int i = 0; i < n; i++) { //i: 사무실 y좌표
        for (int j = 0; j < m; j++) //j: 사무실 x좌표
            cin >> board[i][j]; //사무실 정보 입력 (0, 1~5, 6)
    }

    //연산
    backtracking(0);

    //출력
    cout << ans;
}

