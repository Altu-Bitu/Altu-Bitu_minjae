#include <iostream> //입출력 사용
#include <vector> //벡터 사용

using namespace std;

vector<int> parent;  //집합 노드 정보

//Find 연산
int findParent(int node) {
    if (parent[node] < 0) //루트 정점
        return node;
    return parent[node] = findParent(parent[node]); //그래프 압축하며 루트 정점 찾기
}

//Union 연산
bool unionInput(int x, int y) { //합집합 연산
    int xp = findParent(x); //x의 부모 노드
    int yp = findParent(y); //y의 부모 노드

    if (xp == yp) //같은 집합에 있다면 유니온 할 수 없음
        return false; //거짓 반환 (사이클 됨)
    if (parent[xp] < parent[yp]) { //새로운 루트 xp
        parent[xp] += parent[yp]; //정점 업데이트
        parent[yp] = xp; //부모 노드 업데이트
    } else { //새로운 루트 yp
        parent[yp] += parent[xp]; //정점 업데이트
        parent[xp] = yp //부모 노드 업데이트
    }
    return true; //참 반환 (사이클 x)
}

/**
 * 사이클이 발생한 순간 = 같은 집합에 있는 원소 두 개를 유니온하려 할 때
 * unionInput 함수의 반환형을 bool로 선언하여 cycle이 생성되는 순간 발견하기
 */
int main() {
    int n, m, x, y; //점의 개수, 게임 진행 횟수, 간선 정보

    //입력
    cin >> n >> m;
    parent.assign(n, -1); //정점 -1로 초기화
    for (int i = 0; i < m; i++) { //i: 게임 진행 횟수
        cin >> x >> y; //간선 입력

        //연산 & 출력
        if (!unionInput(x, y)) { //유니온 할 수 없음 = 사이클이 생성됨
            cout << i + 1; //차례 출력
            return 0; //종료
        }
    }
    cout << 0; //사이클 없음
}