#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> bfs(vector<vector<int>> &people, vector<int> &init, int n) {
    vector<int> believer(n + 1, 0); //주변인들이 몇 명 믿는지
    vector<int> ans(n + 1, -1); //몇 분 후에 믿는지
    queue<int> q;

    //시작 정점 초기화
    for (int i = 0; i < init.size(); i++) { //i: i번째 유머 유포자
        ans[init[i]] = 0; //시간 초기화
        q.push(init[i]);//현재 시간 삽입
    }

    while (!q.empty()) { //하루가 지나기 전까지
        int v = q.front(); //현재 사람
        int t = ans[v]; //루머 믿은 시간
        q.pop(); //확인한 사람 제거

        for (int i = 0; i < people[v].size(); i++) { //i: i번째 사람
            int next = people[v][i]; //v번째 사람의 i번째 주변인 번호
            believer[next]++; //next의 주변에서 루머를 믿는 사람 증가
            if (ans[next] != -1) //이미 루머를 믿는 다면
                continue; //다음 사람 검사
            if ((people[next].size() + 1) / 2 <= believer[next]) { //주변인들 중 절반 이상이 루머를 믿으면
                ans[next] = t + 1; //시간 +1
                q.push(next); //루머 믿는 시간 삽입
            }
        }
    }
    return ans; //정답 반환
}

/**
 * 주변인들이 얼마나 믿는지를 배열을 통해 관리해야 함
 * 방문 체크를 탐색할 때 바로 하는 게 아니라, 루머를 믿게 될 경우 하는 게 중요 (루머를 몇 분 후에 믿는지를 저장하는 배열로 관리)
 */

int main() {
    int n, m, input; //n: 사람의 수, m: 최초 유포자 수

    //루머 퍼뜨리는 관계 입력
    cin >> n;
    vector<vector<int>> people(n + 1, vector<int>()); // i번째 사람의 주변인 번호 정보
    for (int i = 1; i <= n; i++) { //i: i번째 사람
        while (true) {
            cin >> input; //주변인 번호 입력
            if (!input) //주변인 번호가 0이면
                break; //i번째 사람 주변인 정보 입력 끝, 다음 사람으로 넘어가기
            people[i].push_back(input); //주변인 번호 정보 삽입
        }
    }

    //최초 유포자 입력
    cin >> m; //최초 유포자의 수
    vector<int> init(m, 0); //최초 유포자 번호 정보
    for (int i = 0; i < m; i++) //i번째 최초 유포자
        cin >> init[i]; //최초 유포자의 번호

    //연산
    vector<int> ans = bfs(people, init, n); //n명의 사람들이 각자 루머를 처음 믿기 시작하는 시간

    //출력
    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';

    return 0;
}
