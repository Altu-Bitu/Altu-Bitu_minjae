#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <cmath>

using namespace std;
typedef pair<double, double> ci; //좌표 정보
typedef tuple<double, int, int> tp; //간선 정보

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

double kruskal(int v, priority_queue<tp, vector<tp>, greater<>> &pq) { //정점 개수, 간선 정보
    int cnt = 0; //사용 간선
    double sum = 0; //가중치 합

    while (cnt < v - 1) { //사용한 간선의 수가 v-1보다 적을 동안
        double cost = get<0>(pq.top()); //가중치
        int x = get<1>(pq.top()); //시작 정점
        int y = get<2>(pq.top()); //끝 정점

        pq.pop(); //탐색한 정점 제거
        if (unionInput(x, y)) { //유니온 했다면
            cnt++; //사용된 간선 증가
            sum += cost; //간선의 가중치
        }
    }
    return sum; //최소 비용 반환
}

/**
 * 4386번 : 별자리 만들기의 응용 문제
 * 이미 연결된 정점들이 존재한다는 것을 제외하고는 4386번과 동일
 *
 * 1. 임의의 두 별에 대한 거리(간선) 모두 구하기
 * 2. 이미 존재하는 통로들 표시
 *    !주의! 통로의 개수가 m개라면 v-m-1개의 간선만 더 추가하면 될까?
 *          이미 연결된 통로들도 사이클을 이룰 수 있기 때문에 유니온 연산을 하며 사이클 없이 연결된 간선만 세기
 * 3. 이미 연결된 통로의 수를 k개라고 하면 v-k-1개의 간선을 추가로 선택
 */
int main() {
    int n, m, a, b, v = 0; //우주신들이 개수, 신들 사이 통로의 개수, 각 정점 좌표, 이미 연결된 통로
    priority_queue<tp, vector<tp>, greater<>> pq; //간선 정보

    //입력
    cin >> n >> m; //정점 개수, 간선 개수
    parent.assign(n + 1, -1); //정점 정보 초기화
    vector<ci> stars(n + 1); //별(정점) 좌표 정보
    for (int i = 1; i <= n; i++) //i: 별 번호
        cin >> stars[i].first >> stars[i].second; //위치 입력


    //연산
    //임의의 두 별에 대한 거리(간선) 모두 구하기
    for (int i = 1; i <= n - 1; i++) { //i: 시작별
        for (int j = i + 1; j <= n; j++) { //j: 끝별
            double xd = stars[i].first - stars[j].first; //x축 거리
            double yd = stars[i].second - stars[j].second; //y축 거리
            pq.push({sqrt(xd * xd + yd * yd), i, j}); //좌표 간의 거리 저장
        }
    }
    while (m--) { //이미 존재하는 간선마다
        cin >> a >> b; //정보 입력
        if (unionInput(a, b)) //이미 연결된 통로
            v++; //연결된 간선 +1
    }

    //연산 & 출력
    cout << fixed; //소수점 제한
    cout.precision(2); //소수점 2자리까지 표현
    cout << kruskal(n - v, pq); //최소 가중치 합 출력
}

