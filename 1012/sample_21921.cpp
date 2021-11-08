//
// Created by iw040 on 2021-10-12.
//

#include <iostream> //입출력 사용
#include <vector> //벡터 사용

using namespace std;

//슬라이딩 윈도우로 최대 방문자 수를 구하고, 그 기간의 수를 리턴
pair<int, int> maxVisitor(int n, int x, vector<int> &visitor) { //n: 운영 기간, x: 기간, &visitor: 일별 방문자 수 정보
    //윈도우 초기화
    int section_visitor = 0;
    for (int i = 0; i < x; i++) //첫날부터 x일 동안의 방문자 수
        section_visitor += visitor[i]; //누적합

    int ans = section_visitor; //최대 방문자 수
    int cnt = 1; //최대 방문자 수인 기간의 수

    //슬라이딩
    for (int i = x; i < n; i++) {
        section_visitor -= visitor[i - x]; //이번 윈도우에 제외되는 값
        section_visitor += visitor[i]; //이번 윈도우에 추가되는 값
        if (section_visitor > ans) { //최대 방문자 수가 갱신된다면
            cnt = 1; //최대 방문자 수 다시 1
            ans = section_visitor; //최대 방문자 수 업데이트
        } else if (section_visitor == ans) //최대 방문자 수와 같다면
            cnt++; // 최대 방문자 수인 기간 +1
    }
    return make_pair(ans, cnt); //최대 방문자 수와 기간 개수 리턴
}

int main() {
    int n, x; //n: 블로그 시작하고 지난 일수, x: 기간

    //입력
    cin >> n >> x;
    vector<int> visitor(n, 0); //일별 방문자 수
    for (int i = 0; i < n; i++) //i: i일째
        cin >> visitor[i]; //입력

    //연산
    pair<int, int> ans = maxVisitor(n, x, visitor);

    //출력
    if (ans.first == 0) { //최대 방문자 수가 0명이라면
        cout << "SAD\n"; //SAD 출력
        return 0; //프로그램 종료
    }
    cout << ans.first << '\n' << ans.second; //최대 방문자수 (줄바꿈) 기간 횟수 출력
}