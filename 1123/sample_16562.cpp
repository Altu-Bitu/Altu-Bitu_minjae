//
// Created by iw040 on 2021-11-23.
//

#include <iostream> //입출력 사용
#include <vector> //벡터 사용

using namespace std;

vector<int> parent; //부모 노드 정보

//Find 연산
int findParent(int node) {
    if (parent[node] < 0) //값이 음수면 루트 정점
        return node; //부모 노드 반환
    return parent[node] = findParent(parent[node]); //그래프 압축하며 루트 정점 찾기
}

//Union 연산
void unionInput(int x, int y) { //x,y 원소 합집합 연산
    int xp = findParent(x); //원소 x의 부모 노드
    int yp = findParent(y); //원소 y의 부모 노드

    if (xp == yp) //같은 집합에 있다면 유니온 할 수 없음
        return; //함수 종료
    if (parent[xp] > parent[yp]) //새로운 루트 xp
        //친구비로 초기화 했으므로 정점 더할 필요 없음
        parent[yp] = xp; //부모 노드 업데이트
    else //새로운 루트 yp
        parent[xp] = yp; //부모 노드 업데이트
}

int friendshipCost(int n) { //친구비, 인자: 학생 번호
    int sum = 0; //친구비
    for (int i = 1; i <= n; i++) { //i: 학생마다
        if (parent[i] < 0) //루트 정점이라면
            sum += -parent[i]; // 친구비로 합산
    }
    return sum; //친구비 반환
}

int main() {
    int n, m, k, v, w, cost; //학생 수, 친구 관계 수, 가진 돈, 친구(간선) 정보, 친구비

    //입력
    cin >> n >> m >> k;
    parent.assign(n + 1, 0); //부모 노드 정보 초기화
    for (int i = 1; i <= n; i++) { //i: 학생마다
        cin >> cost; //요구하는 친구비
        parent[i] = -cost; //루트 정점에 필요한 친구비(음수)를 저장
    }

    //연산
    while (m--) { //m: 친구(간선) 정보 입력
        cin >> v >> w; //입력
        unionInput(v, w); //v와 w는 친구, 같은 집합으로 묶기
    }

    int ans = friendshipCost(n); //친구비

    //출력
    if (ans <= k) //친구비 <= 가진돈
        cout << ans; //친구비 출력
    else //가진돈 < 친구비
        cout << "Oh no"; //친구를 다 사귈 수 없음
}

