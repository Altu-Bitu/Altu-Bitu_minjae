#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>

using namespace std;
typedef pair<int, int> ci; //2차원 행렬

ci dir[4] = {{0,  1},  //우 남
             {-1, 0},  //상 서
             {0,  -1}, //좌 북
             {1,  0}}; //하 동

//게임을 진행하는 함수
int playGame(int n, vector<vector<int>> &board, map<int, char> &cmd) {//인자: 보드의 크기, 사과 위치 표시 행렬, 뱀 방향 변환 정보
    //뱀 초기화
    deque<ci> snake; //뱀 위치 정보
    snake.push_front(ci(0, 0)); //뱀 위치 초기화
    board[0][0] = 1; //(0,0)부터 시작

    int t = 0, head = 0; //시간, 뱀의 머리 방향
    while (true) { //종료 조건 만날 때까지 반복문 실행
        t++; //시간 1초 증가

        //뱀의 머리가 위치하게될 칸
        int nr = snake.front().first + dir[head].first;
        int nc = snake.front().second + dir[head].second; //꼬리 위치

        //게임 종료 조건 : 벽에 부딪히거나, 자기자신의 몸과 부딪힘
        if (nr < 0 || nr >= n || nc < 0 || nc >= n || board[nr][nc] == 1)
            break; //이동 종료 위해 반복문 탈출

        if (board[nr][nc] != 2) { //이동한 칸에 사과가 없다면 몸길이를 줄여서 꼬리가 위치한 칸을 비워준다
            board[snake.back().first][snake.back().second] = 0; //보드 칸 값 0
            snake.pop_back(); //꼬리 이동, 칸 비워짐
        }

        //뱀은 몸길이를 늘려 머리를 다음칸에 위치시킨다
        snake.push_front(ci(nr, nc));
        board[nr][nc] = 1; //보드 칸 값 1

        //이번에 방향을 변환하는지 확인
        if (cmd[t] == 'L') //왼쪽 회전
            head = (head + 1) % 4; //왼쪽 (0,1,2,3 사이의 값 하,우,상,좌 의미)
        if (cmd[t] == 'D') //오른쪽 회전
            head = (head + 3) % 4; //오른쪽
    }
    return t;//시간 반환
}

/**
 * 0 0 1
 * 0 2 1
 * 0 0 1
 *
 * 편의를 위해 문제와 달리 (0, 0)부터 시작
 *
 * 보드의 상태가 위와 같을 때
 * 뱀의 몸은 (0, 2)~(2, 2)에 걸쳐 있고, 사과는 (1, 1)에 위치하고 있음
 * -> 뱀의 꼬리와 머리 위치를 알기 위해 덱 사용
 * -> 덱의 front : 머리, 덱의 back : 꼬리
 *
 * 원활한 방향 변환을 위해 dir 배열 사용
 */
int main() {
    // n:보드의 크기, k: 사과의 개수, row: 행에서 사과 위치, col: 열에서 사과 위치, l: 뱀의 방향 변환 횟수, x: 초
    int n, k, row, col, l, x;
    char c; //방향 정보 저장

    //입력
    cin >> n >> k; //보드의 크기, 사과의 개수 입력
    vector<vector<int>> board(n, vector<int>(n)); //2차원 벡터 생성
    for (int i = 0; i < k; i++) {//k:사과 번호, 사과 개수만큼 반복문 돌면서
        cin >> row >> col; //사과의 행-열 위치 입력
        board[row - 1][col - 1] = 2; //사과 표시
    }
    cin >> l; //뱀의 방향 변환 횟수 입력
    map<int, char> cmd;//뱀의 방향 변환 정보는 정수(x초),문자(방향) 쌍
    for (int i = 0; i < l; i++) { //회전 정보
        cin >> x >> c; //초, 방향 정보 순서대로 입력
        cmd[x] = c; //정보 저장
    }

    //연산 & 출력
    cout << playGame(n, board, cmd);
}
