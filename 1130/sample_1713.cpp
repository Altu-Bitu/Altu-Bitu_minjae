#include <iostream>
#include <vector>
#include <map>

using namespace std;
typedef pair<int, int> ci; //추천 횟수&게시 기간

map<int, ci>::iterator delCandidate(map<int, ci> &candidate) { //등록된 후보자 정보
    auto del = candidate.begin(); //처음 후보를 삭제한다 가정
    int cnt = candidate.begin()->second.first; //처음 후보의 추천 횟수
    int t = candidate.begin()->second.second; //처음 후보의 게시 시간
    for (auto iter = ++candidate.begin(); iter != candidate.end(); iter++) { //후보자마다 검사
        int cur_cnt = iter->second.first; //이번 차례 후보자의 추천횟수
        int cur_t = iter->second.second; //이번 차례 후보자의 게시 기간
        if (cur_cnt < cnt) { //추천 횟수가 가장 작은 후보 찾기
            cnt = cur_cnt; //가장 작은 추천 횟수 갱신
            t = cur_t; //게시 기간 갱신
            del = iter; //이번 차례 후보 삭제 가정
        } else if (cur_cnt == cnt && cur_t < t) { //추천 횟수가 가장 작은 후보가 여러명이라면, 게시 시간이 오래된 후보 찾기
            t = cur_t; //게시 기간 갱시
            del = iter; //이번 차례 후보 삭제 가정
        }
    }
    return del; //삭제될 후보 반환
}

/**
 * 1. 비어있는 사진틀이 없는 경우, 가장 추천수가 작은 학생 중 게시 시간이 오래된 학생을 삭제
 * 2. 후보 학생을 바로 찾기 위해 본 풀이는 map 컨테이너를 사용해 구현
 *
 * !주의! 게시 시간 정보 저장 시, 후보로 올라간 가장 첫 시간을 저장. 이미 후보에 있는데 게시 시간이 갱신되지 않도록 주의.
 */

int main() {
    int n, m, input; //비어있는 사진틀 개수, 추천 횟수, 후보자 번호

    //입력 & 연산
    cin >> n >> m;
    map<int, ci> candidate; //first: 후보 학생, second: {추천 횟수, 게시 시간}
    for (int i = 0; i < m; i++) { //i: 추천 횟수
        cin >> input; //후봐 번호 입력
        if (candidate.size() == n && candidate.find(input) == candidate.end()) //비어있는 사진틀이 없는 경우
            candidate.erase(delCandidate(candidate)); //적당한 후보자 사진틀에서 제거

        if (candidate.find(input) == candidate.end()) //첫 게시라면
            candidate[input].second = i; //후보자 등록
        candidate[input].first++; //추천 횟수 증가
    }

    //출력
    for (auto iter = candidate.begin(); iter != candidate.end(); iter++)
        cout << iter->first << ' '; //최종 후보 출력
}

