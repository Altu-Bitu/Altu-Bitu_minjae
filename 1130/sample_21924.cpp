#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;
typedef tuple<int, int, int> tp; //두 건물의 번호, 건물 간 도로 비용

vector<int> parent; //노드 정보

//Find 연산
int findParent(int node) {
    if (parent[node] < 0) //값이 음수면 루트 정점
        return node; //해당 집합에 속하는 node 반환
    return parent[node] = findParent(parent[node]); //그래프 압축하며 루트 정점 찾기
}

//Union 연산
bool unionInput(int x, int y) {
    int xp = findParent(x); //x가 속한 집합 (부모노드)
    int yp = findParent(y); //y가 속한 집합 (부모노드)

    if (xp == yp) //같은 집합에 있다면 유니온 할 수 없음
        return false; //유니온 불가
    if (parent[xp] < parent[yp]) { //새로운 루트 xp
        parent[xp] += parent[yp]; //xp의 집합 크기 증가
        parent[yp] = xp; //yp의 집합이 xp의 집합으로 유니온
    } else { //새로운 루트 yp
        parent[yp] += parent[xp]; //yp의 집합 크기 증가
        parent[xp] = yp; //xp의 집합이 yp의 집합으로 유니온
    }
    return true; //참 반환
}

long long kruskal(int v, long long tot, priority_queue<tp, vector<tp>, greater<>> &pq) { //건물 개수, 최대 비용, 간선 정보
    int cnt = 0; // 사용 간선
    long long sum = 0; //가중치 합, (범위 10^6*10^5)

    while (cnt < v - 1) { //사용한 간선의 수가 v-1보다 적을 동안
        if (pq.empty()) //사용한 간선이 v-1개가 안됐는데 더 이상 검사할 간선이 없다면
            return -1; //모든 건물이 연결되지 못하면 -1 반환

        int cost = get<0>(pq.top()); //가중치
        int x = get<1>(pq.top()); //시작건물
        int y = get<2>(pq.top()); //끝건물

        pq.pop(); //탐색한 간선 제거
        if (unionInput(x, y)) { //유니온 했다면
            cnt++; //사용 간선 +1
            sum += cost; //가중치 업데이트
        }
    }
    return tot - sum; //절약 비용 (최대 비용 - 최소 비용)
}

/**
 * 기본 MST 문제에서 트리를 만들 수 없는 경우(간선이 N-1개가 아닌 경우)를 고려한 문제
 *
 * 최대 비용의 범위가 약 10^6 x 10^5 이므로 long long 자료형을 써야 함
 */

int main() {
    int n, m, a, b, c; //건물의 개수, 도로의 개수, 두 건물의 번호 & 두 건물 사이 도로 제작 비용
    long long tot = 0; //최대 비용
    priority_queue<tp, vector<tp>, greater<>> pq; //간선 정보 큐

    //입력
    cin >> n >> m;
    parent.assign(n + 1, -1); //정점 정보 초기화
    while (m--) { //간선 별로
        cin >> a >> b >> c; //정보 저장
        pq.push({c, a, b}); //간선 정보 큐에 삽입
        tot += c; //도로를 다 설치할 때 드는 비용
    }

    //연산 & 출력
    cout << kruskal(n, tot, pq);
}
