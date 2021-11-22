#include <iostream> //입출력 사용
#include <vector> //벡터 사용
#include <queue> //큐 사용

using namespace std;
typedef pair<int, int> ci; //시작점, 끝점 쌍 저장
const int INF = 1e5; //최대 n-1개의 간선을 지나게 됨

vector<int> dijkstra(int n, int start, vector<vector<ci>> &graph) { //n: 학생 수, start: 시작점, graph: 간선과 소요 시간 정보
    vector<int> dist(n + 1, INF); //정점까지의 최단 시간 저장 배열
    priority_queue<ci, vector<ci>, greater<>> pq; //first : 시작점으로부터 소요시간, second : 정점

    //시작 위치 초기화
    dist[start] = 0;
    pq.push({0, start}); //큐에 시작 지점 삽입

    while (!pq.empty()) { //큐가 비어있을 때까지
        int t = pq.top().first; //큐 안 요소에서 소요 시간 받아오기
        int node = pq.top().second; //정점 받아오기
        pq.pop(); //탐색한 요소 큐에서 제거

        if (t > dist[node]) //이미 더 짧은 경로가 존재한다면
            continue; //다음 탐색

        for (int i = 0; i < graph[node].size(); i++) { //현재 노드와 연결된 각 정점마다 검사
            int next_node = graph[node][i].first; //연결된 정점
            int next_t = t + graph[node][i].second; //시작점으로부터 연결된 정점까지의 소요시간
            if (dist[next_node] > next_t) { //더 짧은 경로로 갈 수 있다면
                dist[next_node] = next_t; // 더 짧은 소요시간으로 업데이트
                pq.push({next_t, next_node}); //큐에 삽입
            }
        }
    }
    return dist; // 최단 시간 정보 배열 반환
}

/**
 * 1. 각 학생들이 X를 가는 데 걸리는 최단 시간 (i -> x)
 * 2. X에서 다시 돌아오는 데 걸리는 최단 시간 (x -> i)
 *
 * 우선 단방향 그래프이므로 위의 2개 값은 다를 수 있어 따로 구해주어야 함
 * 2번은 시작점이 X인 다익스트라로 무난히 구현
 * 1번은 역뱡향 그래프에서 시작점이 X인 다익스트라로 구현 -> 역방향을 다시 원상태로 돌리면 결국 도착점이 X가 됨 (4ms)
 *
 * 해당 문제는 N이 크지 않아 1번도 시작점이 i인 다익스트라를 N번 또는 1번 2번을 통틀어 조금 더 효율적인 플로이드-워셜로 구현 가능 (220ms)
 */

int main() {
    int n, m, x, a, b, c, ans = 0; //n: 학생 수 m: 단방향 도로 수 x: 마을 번호

    //입력
    cin >> n >> m >> x;
    vector<vector<ci>> graph(n + 1, vector<ci>()); //도로별 시작-끝 위치, 소요 시간 정보 저장
    vector<vector<ci>> rev_graph(n + 1, vector<ci>()); //역방향 그래프
    while (m--) { //도로마다 시작점, 끝점, 소요 시간 입력
        cin >> a >> b >> c;
        graph[a].push_back({b, c}); //단방향
        rev_graph[b].push_back({a, c}); //역방향
    }

    //연산
    vector<int> dist_go = dijkstra(n, x, rev_graph); //역방향 그래프에서 시작점이 x인 모든 정점의 최단 시간
    vector<int> dist_back = dijkstra(n, x, graph); //시작점이 x인 모든 정점의 최단 시간
    for (int i = 1; i <= n; i++) //i: 학생 번호
        ans = max(dist_go[i] + dist_back[i], ans); //이전 학생의 소요 시간과 비교해서 최댓값 업데이트

    //출력
    cout << ans << '\n';
    return 0;
}

