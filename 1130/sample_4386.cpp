//
// Created by iw040 on 2021/11/30.
//

#include <iostream> //입출력 사용
#include <vector> //벡터 사용
#include <tuple> //튜플 사용 (반환값 하나 이상일 때 유용)
#include <queue> //큐 사용
#include <cmath> //

using namespace std;
typedef pair<double, double> ci; //별자리 선 정보 타입 (double형 x, double형 y)
typedef tuple<double, int, int> tp; //간선 정보 타입 (거리, 시작별, 끝별)

vector<int> parent; //노드 정보

//Find 연산
int findParent(int node) {
    if (parent[node] < 0) //값이 음수면 루트 정점
        return node; //해당 집합에 속하는 node 반환
    return parent[node] = findParent(parent[node]); //그래프 압축하며 루트 정점 찾기
}

//Union 연산
bool unionInput(int x, int y) { //시작별, 끝별
    int xp = findParent(x); //x별이 포함된 집합 (=부모노드)
    int yp = findParent(y); //y별이 포함된 집합 (=부모노드)

    if (xp == yp) //같은 집합에 있다면 유니온 할 수 없음
        return false; //유니온 안함
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
double kruskal(int v, priority_queue<tp, vector<tp>, greater<>> &pq) {//별의 개수, 간선 정보
    int cnt = 0; //간선의 수
    double sum = 0; //가중치의 합

    while (cnt < v - 1) { //사용한 간선의 수가 v-1보다 적을 동안
        double weight = get<0>(pq.top()); //가중치 저장
        int x = get<1>(pq.top()); //시작별 저장
        int y = get<2>(pq.top()); //끝별 저장
        pq.pop(); //탐색한 간선 삭제

        if (unionInput(x, y)) { //유니온 했다면
            cnt++; //간선 +1
            sum += weight; //가중치 업데이트
        }
    }
    return sum; //최소 가중치의 합 반환
}

int main() {
    int n; //별의 개수
    priority_queue<tp, vector<tp>, greater<>> pq; //별들 간의 간선 정보와 가중치 저장

    //입력
    cin >> n;
    parent.assign(n, -1); //노드 초기화
    vector<ci> stars(n); //별자리 선 정보
    for (int i = 0; i < n; i++) //i: 별 번호
        cin >> stars[i].first >> stars[i].second; //시작점, 끝점 입력

    //연산
    //임의의 두 별에 대한 거리(간선) 모두 구하기
    for (int i = 0; i < n - 1; i++) { //i: 시작점이 되는 별 번호
        for (int j = i + 1; j < n; j++) { //j: 끝점이 되는 별 번호
            double xd = stars[i].first - stars[j].first; //x축 상의 거리
            double yd = stars[i].second - stars[j].second; //y축 상의 거리
            pq.push({sqrt(xd * xd + yd * yd), i, j}); //좌표의 떨어진 거리 계산
        }
    }

    //연산 & 출력
    cout << fixed; //소수자리 표현 제한
    cout.precision(2); //소수점 2자리까지 표현
    cout << kruskal(n, pq); //최소 가중치 출력
}