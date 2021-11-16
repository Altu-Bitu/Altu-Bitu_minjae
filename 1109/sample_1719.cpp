#include <iostream> //입출력 사용
#include <vector> //벡터 사용

using namespace std;
const int INF = 1e5 * 2; //최대 n-1개의 간선을 지나게 됨

void floydWarshall(int n, vector<vector<int>> &graph, vector<vector<int>> &table) { //집하장 개수, 그래프 정보, 테이블 정보
    for (int k = 1; k <= n; k++) { //중간 경로가 될 k
        for (int i = 1; i <= n; i++) { //i 집하장에서
            for (int j = 1; j <= n; j++) { //j 집하장까지
                int new_dist = graph[i][k] + graph[k][j]; //중간에 k를 거쳐서 i에서 j로 감
                if (new_dist < graph[i][j]) { //i->k->j가 i->j보다 빠른 경로라면
                    graph[i][j] = new_dist; //중간 k 거치는 경로로 거리 갱신
                    table[i][j] = table[i][k]; //i->k 경로에서 지나가는 집하장을 i->j도 지나게 됨
                }
            }
        }
    }
}

/**
 * graph : 플로이드-워셜 결과 행렬 그래프
 * table : 경로표. table[i][j] = i->j로 가기 위해 제일 먼저 거쳐야 하는 정점
 *
 * 1. i->j의 중간 경로를 i로 초기화
 * 2. i->k->j가 i->j보다 짧다면 i->j의 중간 경로를 i->k의 중간 경로(table[i][k])로 갱신
 *    k로 갱신하는게 아니라 table[i][k]로 갱신하는 이유는?
 *    만약 i->k의 경로가 i->t->k라면 최종 경로는 i->t->k->j
 *    바로 k로 갱신하면 t를 놓칠 수 있기 때문에 table[i][k]로 갱신
 *    line 16을 table[i][j] = k로 바꾸면 결과가 어떻게 되는지 확인해보세요
 */
int main() {
    int n, m, s, d, c; //n: 집하장 개수, m: 간선 개수, s&d: 두 집하장의 번호, c: 시간

    //입력
    cin >> n >> m;
    vector<vector<int>> graph(n+1, vector<int>(n+1, INF)); //집하장 간의 시간 정보 그래프
    vector<vector<int>> table(n+1, vector<int>(n+1, 0)); //최단 경로 테이블
    for (int i = 1; i <= n; i++) //초기화
        graph[i][i] = 0; //i to i는 고려 x, 0으로 초기화

    while (m--) { //무방향 그래프
        cin >> s >> d >> c;// 입력
        //간선 정보
        graph[s][d] = graph[d][s] = c; //두 집하장 사이 시간 입력

        //경로 정보
        table[s][d] = d; //s에서 d로 갈 때
        table[d][s] = s; //d에서 s로 갈 때
    }

    //연산
    floydWarshall(n, graph, table);

    //출력
    for (int i = 1; i <= n; i++) { //i 집하장에서
        for (int j = 1; j <= n; j++) {//j 집하장까지
            if (i == j) // 같은 집하장이면
                cout << "- "; // 생략
            else
                cout << table[i][j] << ' '; //시간 출력
        }
        cout << '\n'; //한 줄 띄우고 다음 단계로
    }
}