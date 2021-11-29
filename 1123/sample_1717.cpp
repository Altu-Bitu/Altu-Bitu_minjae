//
// Created by iw040 on 2021-11-23.
//

#include <iostream> //입출력 사용
#include <vector> //벡터 사용

using namespace std;

vector<int> parent; //원소별 집합 상태 저장용

//Find 연산
int findParent(int node) {
    if (parent[node] < 0) //값이 음수면 루트 정점
        return node; //정점 노드 반환
    return parent[node] = findParent(parent[node]); //그래프 압축하며 루트 정점 찾기
}

//Union 연산
void unionInput(int x, int y) { //x원소와 y원소 합집합 연산
    int xp = findParent(x); //x원소의 부모 노드
    int yp = findParent(y); //y원소의 부모 노드

    if (xp == yp) //같은 집합에 있다면 유니온 할 수 없음
        return; //합집합 연산 할 필요없음
    if (parent[xp] < parent[yp]) { //새로운 루트 xp
        parent[xp] += parent[yp]; //집합에 노드 개수 더하기
        parent[yp] = xp; //새로운 부모 노드로 업데이트
    } else { //새로운 루트 yp
        parent[yp] += parent[xp]; //집합에 노드 개수 더하기
        parent[xp] = yp; //xp의 부모 노드 업데이트
    }
}

int main() {
    ios::sync_with_stdio(false); //입력 속도 향상
    cin.tie(NULL);

    int n, m, cmd, a, b; //집합의 수, 연산 횟수, 연산 명령(유니온/파인드), 연산대상(a,b)

    //입력
    cin >> n >> m;
    parent.assign(n + 1, -1); //집합 정보 초기화
    while (m--) { //m번의 연산 입력받으면서
        cin >> cmd >> a >> b;

        //연산
        if (cmd == 0) { //유니온
            unionInput(a, b); //a,b 합집합 연산
        }
        if (cmd == 1) { //파인드
            if (findParent(a) == findParent(b)) //부모 노드가 같다면
                cout << "YES\n"; //같은 집합
            else //아니라면
                cout << "NO\n"; //다른 집합
        }
    }
}

