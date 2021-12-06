#include <iostream> //입출력 사용
#include <vector> //벡터 사용
#include <tuple> //
#include <queue> //큐 사용

using namespace std;
typedef tuple<int, int, int> tp; //간선 정보 저장

vector<int> parent; //노드 정보 저장

//Find 연산
int findParent(int node) { //node의 부모 노드 찾기
    if (parent[node] < 0) //값이 음수면 루트 정점
        return node; //해당 집합에 속하는 node 반환
    return parent[node] = findParent(parent[node]); //그래프 압축하며 루트 정점 찾기
}

//Union 연산
bool unionInput(int x, int y) {
    int xp = findParent(x); //x의 부모노드 (x가 포함된 집합)
    int yp = findParent(y); //y의 부모노드

    if (xp == yp) //같은 집합에 있다면 유니온 할 수 없음
        return false; //유니온 연산 x
    if (parent[xp] < parent[yp]) { //새로운 루트 xp
        parent[xp] += parent[yp]; //xp의 집합 크기 증가
        parent[yp] = xp; //yp의 집합이 xp의 집합으로 유니온
    } else { //새로운 루트 yp
        parent[yp] += parent[xp]; //yp의 집합 크기 증가
        parent[xp] = yp; //xp의 집합이 yp의 집합으로 유니온
    }
    return true; //유니온 연산 o
}

//kruskal
int kruskal(int v, priority_queue<tp, vector<tp>, greater<>> &pq) { //정점 개수, 간선 정보
    int cnt = 0, sum = 0; //사용한 간선의 수, 가중치 합

    while (cnt < v - 1) { //사용한 간선의 수가 v-1보다 작을 동안
        int weight = get<0>(pq.top()); //가중치 저장
        int x = get<1>(pq.top()); //시작 정점 저장
        int y = get<2>(pq.top()); //끝 정점 저장
        pq.pop(); //큐에서 삭제

        if (unionInput(x, y)) { //유니온 했다면 (유니온 가능하다면)
            cnt++; //간선 +1
            sum += weight; //가중치 업데이트
        }
    }
    return sum; //최소 가중치의 합 반환
}

int main() {
    int v, e, a, b, c; //정점의 개수, 간선의 개수, a&b&c: 정점 사이 간선 가중치
    priority_queue<tp, vector<tp>, greater<>> pq; //간선 정보 큐, 가중치 기준 오름차순 정렬

    //입력
    cin >> v >> e;
    parent.assign(v + 1, -1); //노드 정보 초기화
    while (e--) { //간선마다
        cin >> a >> b >> c; //간선으로 연결된 정점과 가중치 정보
        pq.push({c, a, b});//큐에 간선 정보 저장
    }

    //연산 & 출력
    cout << kruskal(v, pq);
}
