//
// Created by iw040 on 2021-11-23.
//

#include <iostream> //입출력 사용
#include <vector> //벡터 사용

using namespace std;

vector<bool> cycle; //사이클 유무 정보
vector<int> parent; //원소별 부모 노드 정보

//Find 연산
int findParent(int node) { //부모 노드 찾는 함수
    if (parent[node] < 0) //값이 음수면 루트 정점
        return node; //루트 노드 반환
    return parent[node] = findParent(parent[node]); //그래프 압축하며 루트 정점 찾기
}

//Union 연산
void unionInput(int x, int y) { //x원소와 y원소 합집합 연산
    int xp = findParent(x); //부모 노드 찾기
    int yp = findParent(y); //부모 노드 찾기

    if (xp == yp) { //같은 집합에 있다면 유니온 할 수 없음 (사이클 O)
        cycle[xp] = true; //사이클이 있는 연결 요소
        return; //함수 종료
    }
    if (cycle[xp] || cycle[yp]) //둘 중 하나라도 사이클이 있으면 표시
        cycle[xp] = cycle[yp] = true; //사이클이 있는 연결 요소
    if (parent[xp] < parent[yp]) { //새로운 루트 xp
        parent[xp] += parent[yp]; //집합의 노드 개수 업데이트
        parent[yp] = xp; //yp의 부모노드 업데이트
    } else { //새로운 루트 yp
        parent[yp] += parent[xp]; //집합의 노드 개수 업데이트
        parent[xp] = yp; //xp의 부모 노드 업데이트
    }
}

int cntTree(int n) { //트리 개수
    int cnt = 0; //트리 개수
    for (int i = 1; i <= n; i++) { //i: 노드(원소) 번호
        if (parent[i] < 0 && !cycle[i]) //루트 정점인데 사이클도 없을 때
            cnt++; //트리 +1
    }
    return cnt; //트리 개수 반환
}

void printResult(int num, int cnt) { //결과 출력 함수, 인자: 테스트 케이스 번호, 트리 개수
    cout << "Case " << num;  //Case로 시작
    if (cnt == 0)  //트리가 없을 경우
        cout << ": No trees.\n"; //출력 문구
    else if (cnt == 1) //트리가 하나일 경우
        cout << ": There is one tree.\n"; //출력 문구
    else //트리가 여럿일 경우
        cout << ": A forest of " << cnt << " trees.\n"; //출력 문구
}

int main() {
    int n, m, a, b, test_case = 0; //정점의 개수, 간선의 개수, a&b: 간선 정보

    while (true) {
        test_case++; //n&m 입력 새로 시작되는 test case 여러 개, m번 동안 a,b 입력 끝나면 다른 test case 시작

        //입력
        cin >> n >> m;
        if (n == 0 && m == 0) //종료 조건
            break; //반복문 탈출, 종료
        parent.assign(n + 1, -1); //노드별 연결 상태 정보
        cycle.assign(n + 1, false); //사이클 유무 정보
        while (m--) { //무방향 그래프
            cin >> a >> b; //간선 정보
            unionInput(a, b); //같은 집합으로 묶기
        }

        //연산
        int tree_cnt = cntTree(n);

        //출력
        printResult(test_case, tree_cnt);
    }
}

