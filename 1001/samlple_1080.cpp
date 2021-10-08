#include <iostream> //입출력
#include <vector> //벡터

using namespace std;

//부분 행렬 원소 뒤집는 함수
void reverseMtx(int row, int col, vector<string> &matrix_a) { //인자: 행, 열, 행렬a을 이루는 원소 값
    for (int i = row; i < row + 3; i++) { //i: 행, row+3:3*3 부분 행렬만 바꿔주면 됨
        for (int j = col; j < col + 3; j++) { //j: 열
            if (matrix_a[i][j] == '1') //원소값이 1이면
                matrix_a[i][j] = '0';//0
            else //0이면
                matrix_a[i][j] = '1';//1로
        }
    }
}

//마지막으로 A == B인지 확인하는 함수
int isPossible(int n, int m, vector<string> &matrix_a, vector<string> &matrix_b) { //인자: 행, 열, 행렬a, 행렬b
    for (int i = 0; i < n; i++) { //i:행
        for (int j = 0; j < m; j++) {//j:열
            if (matrix_a[i][j] != matrix_b[i][j])//값이 다른 부분이 있다면
                return false;//false 반환
        }
    }

    return true;//A==B라면 true 반환
}

/**
 * (0, 0) 인덱스부터 부분행렬을 만들 수 있는 마지막 인덱스까지 검사하며 그리디하게 푸는 문제
 * A, B 행렬의 현재 인덱스 값이 서로 다르다면 A 행렬에서 현재 인덱스로 '시작'하는 3x3 크기만큼의 부분 행렬 원소 뒤집기
 * 검사가 모두 끝난 후, A와 B가 서로 다르다면 바꿀 수 없는 경우임
 * !주의! 입력이 공백없이 주어지므로 string으로 받음
 */

int main() {
    int n, m; //n: 행, m: 열

    //입력
    cin >> n >> m;
    vector<string> matrix_a(n); //a행렬
    vector<string> matrix_b(n); //b행렬
    for (int i = 0; i < n; i++)//i:행 번호
        cin >> matrix_a[i];//입력

    for (int i = 0; i < n; i++)//i:행 번호
        cin >> matrix_b[i];//입력

    //연산
    int ans = 0;//행렬a->행렬b로 바꾸는데 필요한 연산의 횟수
    for (int i = 0; i <= n - 3; i++) {//i:행 번호
        for (int j = 0; j <= m - 3; j++) {//j: 열 번호
            if (matrix_a[i][j] != matrix_b[i][j]) { //(i, j)원소가 서로 다르다면
                reverseMtx(i, j, matrix_a); //행렬 변환 연산
                ans++;//연산 횟수 증가
            }
        }
    }

    //출력
    if (!isPossible(n, m, matrix_a, matrix_b)) //연산이 끝난 후에도 행렬이 서로 다르다면(반환값이 0이라면)
        ans = -1; //-1: 행렬a->행렬b로 바꾸는데 실패함
    cout << ans; //연산횟수 출력

    return 0;//정수값 반환
}
