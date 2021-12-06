#include <iostream> //입출력 사용
#include <vector> //벡터 사용
#include <map> //맵 사용

using namespace std;

vector<vector<int>> parent; //정점, 집합 정보

//Find 연산
int findParent(int m, int row, int col) { //열 크기, row&col: 위치
    if (parent[row][col] < 0) //루트 정점
        return row * m + col; //해당 정점 반환
    int pos = parent[row][col]; //현재 위치 초기화
    return parent[row][col] = findParent(m, pos / m, pos % m); //그래프 압축하며 루트 정점 찾기
}

//Union 연산
void unionInput(int m, int r1, int c1, int r2, int c2) {
    int xp = findParent(m, r1, c1); //현재 위치의 부모 노드
    int yp = findParent(m, r2, c2); //유니온 될 좌표의 부모 노드
    int xr = xp / m, xc = xp % m; //부모 노드 위치
    int yr = yp / m, yc = yp % m; //유니온 좌표의 부모노드 위치

    if (xp == yp) //같은 집합에 있다면 유니온 할 수 없음
        return; //함수 끝
    if (parent[xr][xc] < parent[yr][yc]) { //새로운 루트 xp
        parent[xr][xc] += parent[yr][yc]; //집합 갱신
        parent[yr][yc] = xp; //정점 갱신
    } else { //새로운 루트 yp
        parent[yr][yc] += parent[xr][xc]; //집합 갱신
        parent[xr][xc] = yp; //정점 갱신
    }
}

void unionPair(int n, int m, vector<vector<char>> &board) { //행렬 크기, 행렬 정보
    map<char, pair<int, int>> dir; //맵을 사용해 각 문자를 방향에 대입
    dir['U'] = {-1, 0}; //상
    dir['D'] = {1, 0}; //하
    dir['L'] = {0, -1}; //좌
    dir['R'] = {0, 1}; //우

    for (int i = 0; i < n; i++) {//i: 행
        for (int j = 0; j < m; j++) {//j: 열
            pair<int, int> d = dir[board[i][j]]; //유니온 될 좌표가 있는 방향
            unionInput(m, i, j, i + d.first, j + d.second); //합집합 연산
        }
    }
}

int cntZone(int n, int m) { //행렬 크기
    int cnt = 0; //집합의 개수 세기
    for (int i = 0; i < n; i++) { //i:행
        for (int j = 0; j < m; j++) { //j:열
            if (parent[i][j] < 0) //음수면
                cnt++; //집합 +1
        }
    }
    return cnt; //정답 반환
}

/**
 * 1. 화살표를 통해 접근할 수 있는 좌표 = 하나의 집합으로 연결된 좌표
 * 2. 같은 집합 안에 속해있는 좌표들은 모두 언젠가 방문 가능한 좌표
 * 3. 서로소인 각 집합에서 한 개씩의 좌표만 SAFE ZONE이어도 모든 회원들이 안전할 수 있음
 * 4. 2차원 좌표를 int 값 하나로 저장하기 위해 모든 행을 일렬로 나열하는 방법 사용 (각 좌표에 pair 변수를 저장해 부모를 표시할 수도 있음)
 */
int main() {
    int n, m; //행, 열
    string input; //입력 문자열

    //입력
    cin >> n >> m;
    vector<vector<char>> board(n, vector<char>(m)); //행렬 구현
    parent.assign(n, vector<int>(m, -1)); //노드 정보 초기화
    for (int i = 0; i < n; i++) { //i: 행
        cin >> input; //문자열 입력
        for (int j = 0; j < m; j++) //j:열
            board[i][j] = input[j]; //좌표에 문자열의 문자 하나씩 저장
    }

    //연산
    unionPair(n, m, board);

    //출력
    cout << cntZone(n, m);
}