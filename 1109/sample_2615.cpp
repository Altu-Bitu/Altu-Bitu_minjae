#include <iostream> //입출력 사용
#include <vector> //벡터 사용

using namespace std;
const int SIZE = 19; //바둑판 사이즈 19*19

//범위와 돌의 종류가 유효한지 확인
bool promising(int r, int c, int stone, vector<vector<int>> &board) { //행, 열, 보드 위치, 보드 정보
    return r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c] == stone; //행&열 숫자가 범위 내에 있고, 해당 보드 위치의 정보와 검사받는 보드 위치의 정보가 일치한다면 참 반환
}

bool validDir(int r, int c, int d, int stone, vector<vector<int>> &board) {//행, 열, 보드 위치, 보드 정보
    //가로, 세로, 우하향 대각선, 우상향 대각선
    int dr[4] = {0, 1, 1, -1};
    int dc[4] = {1, 0, 1, 1};

    //(r, c) 이전에 위치한 이어지는 돌이 있나?
    bool is_six = promising(r - dr[d], c - dc[d], stone, board);

    int cnt = 0; //연속되는 바둑알 개수
    while (cnt < 6 && promising(r, c, stone, board)) { //(r, c)를 가장 왼쪽으로 하는 이어지는 바둑알의 개수
        cnt++; //이어지는 바둑알 +1
        r += dr[d]; //이동
        c += dc[d]; //이동
    }
    return cnt == 5 && !is_six; //연속되는 바둑알 개수가 5개이고 (r,c)에서 처음 시작하는 나열이 맞다면 true 반환
}

bool isEnd(int r, int c, vector<vector<int>> &board) { //행, 열, 보드 상태
    for (int i = 0; i < 4; i++) { //가로, 세로, 우하향 대각선, 우상향 대각선
        if (validDir(r, c, i, board[r][c], board)) //오목 상태가 맞다면
            return true; //참 반환
    }
    return false; //반복문 빠져나왔다면 거짓 반환 (오목 상태 없음)
}

/**
 * 1. 특정 좌표(r, c)를 가장 왼쪽으로 하는 가능한 모든 오목 배치에 대해 오목 여부 확인
 *    가능한 모든 배치 :  오른쪽, 아래, 우하향, 우상향
 * 2. 육목이상이 되는 경우 : (r, c) 왼쪽에 같은 돌이 있는 경우
 */
int main() {
    vector<vector<int>> board(SIZE, vector<int>(SIZE, 0)); //보드판 상황

    //입력
    for (int i = 0; i < SIZE; i++) { //행
        for (int j = 0; j < SIZE; j++) //열
            cin >> board[i][j]; //칸 정보
    }

    //연산 & 출력
    for (int i = 0; i < SIZE; i++) { //행
        for (int j = 0; j < SIZE; j++) { //열
            if (!board[i][j]) //돌이 없음
                continue; //다음 칸 확인
            if (isEnd(i, j, board)) { //누군가 이겼나?
                cout << board[i][j] << '\n' << i + 1 << ' ' << j + 1; //이긴 돌 정보 출력, 행&열 출력 (1부터 시작하므로 +1)
                return 0; //끝
            }
        }
    }
    cout << 0; //반복문 무사히 나올 경우 승부 미정 상태 출력
}

