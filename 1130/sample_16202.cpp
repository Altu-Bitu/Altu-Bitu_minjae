#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;
typedef tuple<int, int, int> tp;

vector<int> parent; //부모 노드

//Find 연산
int findParent(int node) {
    if (parent[node] < 0) //값이 음수면 루트 정점
        return node; //해당 집합에 속하는 node 반환
    return parent[node] = findParent(parent[node]); //그래프 압축하며 루트 정점 찾기
}

//Union 연산
bool unionInput(int x, int y) { //x&y 유니온 연산
    int xp = findParent(x); //x가 속한 집합 (부모노드)
    int yp = findParent(y);  //y가 속한 집합 (부모노드)

    if (xp == yp) //같은 집합에 있다면 유니온 할 수 없음
        return false; //유니온 불가
    if (parent[xp] < parent[yp]) { //새로운 루트 xp
        parent[xp] += parent[yp]; //xp의 집합 크기 증가
        parent[yp] = xp; //yp의 집합이 xp의 집합으로 유니온
    } else { //새로운 루트 yp
        parent[yp] += parent[xp]; //yp의 집합 크기 증가
        parent[xp] = yp; //xp의 집합이 yp의 집합으로 유니온
    }
    return true; //유니온 함
}

int kruskal(int n, int idx, vector<tp> &edges) { //정점 개수, 현재 턴, 정점 정보
    int cnt = 0, sum = 0; // 사용 간선, 가중치 합
    for (int i = idx; i < edges.size(); i++) { //i: 정점 번호
        if (cnt == n - 1) //n-1개의 간선을 모두 연결함
            break; //작업 끝
        int dist = get<0>(edges[i]); //현재 간선의 가중치
        int x = get<1>(edges[i]); //시작점
        int y = get<2>(edges[i]); //끝점

        if (unionInput(x, y)) { //유니온 연산
            cnt++; //간선의 수 +1
            sum += dist; //가중치 업데이트
        }
    }
    if (cnt < n - 1) //mst를 만들 수 없음
        return 0; //0 반환
    return sum; //최소 가중치 합 반환
}

/**
 * MST 알고리즘을 여러 번 실행해도 될까?
 * 1. 크루스칼 알고리즘의 시간 복잡도는 O(ElogE)
 *    이는 오직 간선을 정렬하는 연산의 시간 복잡도!
 *    즉, 모든 간선을 한 번 정렬해서 저장해두면 이후 몇 번의 알고리즘을 수행하여도 연산 시간에 큰 영향이 없음
 * 2. 간선 재사용을 위해 우선순위 큐가 아닌 벡터에 저장하고 크루스칼 알고리즘 k번 실행
 * 3. 매번 크루스칼을 수행할 때마다 제일 먼저 추가한 간선을 제외함
 *    -> 제외될 간선은 배열의 0번째 간선부터 1, 2, 3번째 간선으로 순차적 제외
 * 4. 만약 한 번 MST를 만들 수 없다는게 확인됐다면 이후에도 MST를 만들 수 없으므로 flag 변수로 불필요한 연산 절약
 */
int main() {
    int n, m, k, x, y; //정점 개수, 간선 개수, 턴의 수, 간선 정보

    cin >> n >> m >> k; //입력
    vector<tp> edges; //재사용할거라 우선순위 큐가 아닌 벡터에 저장
    for (int i = 1; i <= m; i++) { //i: 간선 번호
        cin >> x >> y; //정점 저장
        edges.emplace_back(i, x, y); //간선 정보 추가
    }

    bool flag = false; //MST 만들 수 있음
    for (int i = 0; i < k; i++) { //k: 턴 차례
        if (flag) { //더이상 mst를 만들 수 없음
            cout << 0 << ' '; //만들 수 없음
            continue; //다음 턴 검사
        }
        parent.assign(n + 1, -1); //초기화
        int ans = kruskal(n, i, edges); //MST 비용
        if (ans == 0) //0이면
            flag = true; //mst 만들 수 없음
        cout << ans << ' '; //이번 턴에서의 값 출력
    }
}
