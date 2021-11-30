#include <iostream> //입출력 사용
#include <vector> //벡터 사용

using namespace std;
const int INF = 1e9; //케이스에서 존재할 수 없는 최대 시간

int mineLand(int n, int m, int b, int height, vector<vector<int>> &land) {//세로 크기, 가로 크기, 인벤토리 블록 수, 높이, 땅 정보
    int tot_time = 0; //땅 높이 고르는 시간
    for (int i = 0; i < n; i++) { //i: 세로 칸
        for (int j = 0; j < m; j++) { //j: 가로 칸
            if (land[i][j] > height) { //블록 제거
                b += (land[i][j] - height); //제거한 블록 인벤토리에 저장
                tot_time += 2 * (land[i][j] - height); //블록 제거할 때 걸리는 시간
            } else if (land[i][j] < height) { //블록 쌓기
                b -= (height - land[i][j]); //인벤토리 블록 사용
                tot_time += (height - land[i][j]); //블록 쌓을 때 걸리는 시간
            }
        }
    }
    if (b < 0) //최종적으로 블럭이 음수면 불가능한 높이
        return INF + 1; //존재할 수 없는 최대 시간 반환
    return tot_time; //시간 반환
}

/**
 * 1. 가장 낮은 땅의 높이를 h라고 할 때, h-1의 높이를 만드는건 h보다 2*(N*M)의 시간이 더 소요됨
 * 2. 가장 높은 땅의 높이를 h라고 할 때, h+1의 높이를 만드는건 h보다 (N*M)의 시간이 더 소요됨
 * -> 따라서 땅의 높이가 될 수 있는 후보는 (가장 낮은 땅) ~ (가장 높은 땅)
 * -> 가능한 모든 높이에 대해 브루트포스 연산해도 시간 초과 X
 *
 * !주의! 당장 쌓을 블록이 없더라도 언젠가 다른 곳의 블록을 제거해서 쌓을 수 있음.
 */
int main() {
    //세로 크기, 가로 크기, 인벤토리 소장 블록 수, 최소 높이가 갱신될 변수, 최대 높이가 갱신될 변수
    int n, m, b, min_height = 256, max_height = 0;
    //입력
    cin >> n >> m >> b;
    vector<vector<int>> land(n, vector<int>(m, 0)); //땅 정보 초기화
    for (int i = 0; i < n; i++) { //i:세로 칸
        for (int j = 0; j < m; j++) { //j:가로 칸
            cin >> land[i][j]; //땅 높이
            min_height = min(min_height, land[i][j]); //제일 낮은 땅 높이
            max_height = max(max_height, land[i][j]); //제일 높은 땅 높이
        }
    }

    //연산
    int min_time = INF, height = 0;// 최소 시간이 갱신될 변수, 높이
    for (int i = min_height; i <= max_height; i++) { //i: 높이 별로 작업 시간 검사
        int t = mineLand(n, m, b, i, land); //작업 시간
        if (t <= min_time) { //가장 빨리 작업이 끝나는 높이
            min_time = t; //최소 시간 갱신
            height = i; //높이 저장
        }
    }

    //출력
    cout << min_time << ' ' << height;
}
