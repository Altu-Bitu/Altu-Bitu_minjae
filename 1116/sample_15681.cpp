#include <iostream> //입출력 사용
#include <vector> //벡터 사용

using namespace std;

vector<int> subtree_cnt; //서브 트리

int treeDp(int cur, vector<vector<int>> &graph) { //루트 번호, 그래프 정보 인자로
    if (subtree_cnt[cur] != -1) //이미 탐색했던 상태
        return subtree_cnt[cur];// cur가 루트인 서브트리의 정점의 수 출력

    //서브트리에 속한 정점의 수를 세고, 저장
    subtree_cnt[cur] = 0;
    int node = 1; //정점의 수 1로 초기화(자기 자신 포함하므로)
    for (int i = 0; i < graph[cur].size(); i++) //i: 방문하는 노드
        node += treeDp(graph[cur][i], graph); //재귀로 자식까지 탐색
    return subtree_cnt[cur] = node; //얻은 정점 개수 반환
}

/**
 * PPT 트리의 정점의 수 구하기 응용
 *
 * 1. 루트에서부터 dfs 탐색
 * 2. 각 노드를 루트로 하는 서브트리의 정점 수를 재귀적으로 계산
 */
int main() {
    ios::sync_with_stdio(false); //입출력 속도 향상
    cin.tie(NULL);

    int n, r, q, u, v, input; //n: 정점의 수, r: 루트의 번호, q: 쿼리의 수

    //입력
    cin >> n >> r >> q;
    vector<vector<int>> graph(n + 1, vector<int>(0)); //트리 그래프 간선 정보
    subtree_cnt.assign(n + 1, -1); //서브 트리

    while (--n) { //무방향 그래프
        cin >> u >> v; //간선 입력
        graph[u].push_back(v); //u-v 간선 정보 저장
        graph[v].push_back(u); //v-u 간선 정보 저장
    }

    //연산
    treeDp(r, graph);

    //출력
    while (q--) { //쿼리 수만큼 반복
        cin >> input; //루트가 되는 U
        cout << subtree_cnt[input] << '\n'; //정점의 수 출력
    }
}
