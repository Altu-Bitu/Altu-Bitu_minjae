//
// Created by BaeSuA on 2021-10-15.
//

#include <iostream> //입출력 사용
#include <vector> //벡터 사용
#include <stack> //스택 사용
#include <queue> //큐 사용
#include <algorithm> //정렬 사용

using namespace std;

vector<vector<bool>> adj_matrix; //인접행렬
vector<vector<int>> adj_list; //인접리스트

vector<bool> visited_recur; //방문 여부

//DFS (재귀함수)
//노드가 작은 순으로 탐색해야 하는 문제이므로 재귀함수가 더 효율적
void dfsRecur(int v) { //v:탐색 시작한 정점
    if (visited_recur[v]) //이미 방문한 노드라면
        return; //종료

    visited_recur[v] = true; //방문 체크
    cout << v << ' '; //방문 노드 출력

    for (int i = 0; i < adj_list[v].size(); i++) //i: v번 노드의 인접리스트
        dfsRecur(adj_list[v][i]); //방문
}

//DFS : 깊이 우선 탐색
vector<int> dfs(int n, int v) { //n: 정점 개수 , v: 탐색 시작 정점
    stack<int> st; //스택 사용
    vector<bool> visited(n + 1, false); //방문 노드 체크
    vector<int> result; //탐색순으로 노드 저장

    st.push(v); //처음 탐색 노드 삽입
    visited[v] = true; //방문 체크
    result.push_back(v); //방문한 노드 저장

    //탐색 시작
    while (!st.empty()) {
        int node = st.top(); //현재 탐색하려는 노드
        bool check = false; //연결 노드 존재 여부
        //인접행렬로 검사
        for (int i = 1; i <= n; i++) { //모든 노드에 대해
            if (adj_matrix[node][i] && !visited[i]) { //연결이 되어 있고, 처음 방문이라면
                check = true; //연결 노드 있음
                visited[i] = true; //방문 체크
                st.push(i); //앞으로 탐색해야 할 노드이므로 스택에 삽입
                result.push_back(i); //탐색 노드 바로 삽입
                break; //이 문제에선 작은 노드부터 방문해야 하므로 바로 break
            }
        }
        /*
        //인접리스트로 검사
        for (int i = 0; i < adj_list[node].size(); i++) { //연결된 노드만
            if (!visited[adj_list[node][i]]) { //이미 연결된 노드 정보만 있으므로, 방문 체크만!
                check = true;
                visited[adj_list[node][i]] = true;
                st.push(adj_list[node][i]);
                result.push_back(adj_list[node][i]); //탐색 노드 바로 삽입
                break;
            }
        }
        */
        if (!check) //더 이상 연결 노드가 없다면, 원래 DFS라면 앞에서 꺼내온 순간 바로 pop()해야함
            st.pop(); //스택에서 노드 삭제
    }

    return result;
}

//BFS : 너비 우선 탐색
vector<int> bfs(int n, int v) { //n: 정점 개수, v: 탐색 시작 정점
    queue<int> q; //큐 사용
    vector<bool> visited(n + 1, false); //방문 노드 체크
    vector<int> result; //탐색 순으로 정점 저장

    q.push(v); //처음 탐색 노드 삽입
    visited[v] = true; //방문 체크

    //탐색 시작
    while (!q.empty()) { //큐에 탐색할 노드가 있다면
        int node = q.front(); //현재 탐색하려는 노드
        q.pop(); // 탐색 노드 pop
        result.push_back(node); //결과에 탐색 노드 저장
        //인접행렬로 검사
        for (int i = 1; i <= n; i++) { //모든 노드에 대해
            if (adj_matrix[node][i] && !visited[i]) { //연결이 되어 있고, 처음 방문이라면
                visited[i] = true; //방문 체크
                q.push(i); //앞으로 탐색해야할 노드이므로 큐에 삽입
            }
        }
        /*
        //인접리스트로 검사
        for (int i = 0; i < adj_list[node].size(); i++) { //연결된 노드만
            if (!visited[adj_list[node][i]]) { //이미 연결된 노드 정보만 있으므로, 방문 체크만!
                visited[adj_list[node][i]] = true;
                q.push(adj_list[node][i]);
            }
        }
        */
    }

    return result; //결과 반환

}

int main() {
    int n, m, v, a, b; //정점(node) 개수, 간선(edge) 개수, 시작 정점, 간선 정보(a, b)
    vector<vector<int>> result(2, vector<int>()); //결과 저장 배열

    //입력
    cin >> n >> m >> v;
    adj_matrix.assign(n + 1, vector<bool>(n + 1, false)); // 간선 연결 정보 저장
    adj_list.assign(n + 1, vector<int>()); //인접리스트에 연결되는 두 정점의 번호 저장
    while (m--) { //m: 간선마다
        cin >> a >> b; // 간선 정보 (a,b) 입력
        //인접행렬
        adj_matrix[a][b] = adj_matrix[b][a] = true;
        //인접리스트
        adj_list[a].push_back(b); //a - b 간선 정보 저장
        adj_list[b].push_back(a); // b - a 간선 정보 저장
    }

    //인접리스트 구현 시, 노드 번호가 작은 것부터 방문하기 위해 정렬해야 함
    for (int i = 1; i <= n; i++) //i: 노드 번호
        sort(adj_list[i].begin(), adj_list[i].end()); //정렬

    //DFS - stack
    //result[0] = dfs(n, v);
    //DFS - 재귀함수
    visited_recur.assign(n + 1, false); //노드 방문 정보 벡터 초기화
    dfsRecur(v); //노드 방문 여부
    //BFS - queue
    result[1] = bfs(n, v); //너비 우선 탐색 결과

    //출력
    for (int i = 0; i < 2; i++) { //i=0 : DFS , i=1: BFS 출력
        for (int j = 0; j < result[i].size(); j++) { //j번째 탐색
            cout << result[i][j] << ' '; //방문한 노드 번호 출력
        }
        cout << '\n';
    }

    return 0;
}