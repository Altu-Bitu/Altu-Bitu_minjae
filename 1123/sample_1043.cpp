#include <iostream>
#include <vector>

using namespace std;

vector<bool> truth; //진실을 아는지 여부
vector<int> parent; //노드, 집합 정보 저장

//Find 연산
int findParent(int node) { //정점 찾기
    if (parent[node] < 0) //루트 정점
        return node; //정점 반환
    return parent[node] = findParent(parent[node]); //그래프 압축하며 루트 정점 찾기
}

//Union 연산
void unionInput(int x, int y) { //파티 참여한 첫번째 사람, 그 다음 사람들 중 1명
    int xp = findParent(x); //x의 부모 노드
    int yp = findParent(y); //y의 부모 노드

    if (xp == yp) //같은 집합에 있다면 유니온 할 수 없음
        return; //함수 끝
    if (truth[xp] || truth[yp]) //둘 중 하나라도 진실을 믿는 사람이 있다면 표시
        truth[xp] = truth[yp] = true; //둘 다 진실을 알게 됨
    if (parent[xp] < parent[yp]) { //새로운 루트 xp
        parent[xp] += parent[yp]; //집합 갱신
        parent[yp] = xp; //부모 노드 갱신
    } else { //새로운 루트 yp
        parent[yp] += parent[xp]; //집합 갱신
        parent[xp] = yp; //부모 노드 갱신
    }
}

int liarParty(vector<int> &parties) { //파티 정보 (파티 참여 첫번째 사람)
    int cnt = 0; //거짓말할 수 있는 파티 개수
    for (int i = 0; i < parties.size(); i++) { //i: 파티별로
        int root = findParent(parties[i]); //파티 집합의 루트 정점
        if (!truth[root]) //truth[root]==false 라면, 동일 집합의 정점 노드에 있는 사람이 진실 모르면
            cnt++; //거짓말 가능 파티 개수 +1
    }
    return cnt; //정답 반환
}

/**
 * 1. 각 사람들은 다양한 파티를 통해 연결됐다고 할 수 있음
 * 2. 연결된 사람들은 같은 집합에 속함
 * 3. 각 집합에 속한 사람들 중 한 명이라도 진실을 안다면 그 집합의 사람들이 속한 파티에는 거짓말을 할 수 없음
 * -> 유니온 파인드로 사람들을 집합으로 묶은 뒤, 파티마다 거짓말을 할 수 있는지 확인하기
 *
 * !주의! 파티 정보를 입력받으며 바로 거짓말 가능 여부를 판단할 수 없음 (예제 입력 4)
 *       각 파티에서 한 사람만 저장해둔 뒤, 마지막에 거짓말 가능 여부 한 번에 판단
 */
int main() {
    int n, m; //사람의 수, 파티의 수

    //입력
    cin >> n >> m;
    truth.assign(n + 1, false); //사람별로 진실을 아는지 모르는지 저장
    parent.assign(n + 1, -1); //정점

    int init, p; //진실을 아는 사람의 수, 그 사람들의 번호
    cin >> init; //입력
    while (init--) { //진실을 아는 사람들
        cin >> p; //번호 입력
        truth[p] = true; //진실 알고있음
    }

    int cnt, first_person, people; //파티 참여 인원, 첫번째 사람 번호, 사람 번호
    vector<int> parties;
    while (m--) { //파티별로 해당 파티에 대한 정보 저장
        cin >> cnt >> first_person; //입력

        //연산
        parties.push_back(first_person); //파티 정보로 각 파티의 첫번째 사람만 저장
        while (--cnt) { //(cnt-1)명의 나머지 사람 번호 입력
            cin >> people;
            unionInput(first_person, people); //진실 판별 유무 저장
        }
    }

    int ans = liarParty(parties); //거짓말할 수 있는 파티 개수

    //출력
    cout << ans;
}
