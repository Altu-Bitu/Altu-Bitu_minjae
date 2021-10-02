#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int INF = 1e9; //최댓값

vector<vector<int>> matrix; //n*n 비용 행렬
int ans = INF; //ans: 최소비용

//특정 경로에 대해 유효한 경로인지 확인하고, 순회 비용을 계산하는 함수
int calcCost(int n, vector<int> visited) {//인자: 도시 개수, 도시 번호 벡터
    int sum = 0; //총 순회 비용
    visited.push_back(visited[0]); //시작 도시로 되돌아오기 위해 삽입

    for (int i = 1; i <= n; i++) { //도시마다 체크
        int before_city = visited[i - 1], cur_city = visited[i]; //도시 방문의 비용 행렬 인덱스 값
        if (!matrix[before_city][cur_city]) //길이 없다면 이 경로는 불가능
            return INF; //갈 수 없는 경우이므로 최대 비용 반환
        sum += matrix[before_city][cur_city]; //순회 비용 추가
    }
    return sum; //순회 비용 반환
}

/**
 * permutation 풀이 (300ms) (2529_2.cpp 주석을 먼저 봐주세요)
 *
 * 모든 도시를 한 번씩 방문 하는 모든 경우의 수를 탐색
 * 만약 탐색 가능한 경로라면 최소 비용 갱신
 *
 * 도시가 3개일 때 방문하는 모든 경우의 수
 * (0->1->2->0), (0->2->1->0), (1->0->2->1), (1->2->0->1), (2->0->1->2), (2->1->0->2)
 */
int main() {
    int n; //도시의 수
    vector<int> visited;//도시 번호

    //입력
    cin >> n;
    visited.assign(n, 0); //n개의 도시 번호 0으로 초기화
    matrix.assign(n, vector<int>(n, 0));//n*n 행렬 0으로 초기화
    for (int i = 0; i < n; i++) { //도시마다 번호 입력
        for (int j = 0; j < n; j++) //행렬 칸마다
            cin >> matrix[i][j]; //비용 입력
        visited[i] = i; //도시 번호 입력
    }

    //연산
    do { //순열 처음부터 시작
        ans = min(ans, calcCost(n, visited)); //최소값 갱신 (현재값, calcCost 함수를 통해 얻은 다음 도시 순회 비용 비교)
    } while (next_permutation(visited.begin(), visited.end())); //permutation 함수가 반환하는 순열대로 순차적 방문

    //출력
    cout << ans;
}
