#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> ci;

/**
 * [필요 강의실이 최소가 되도록 수업 배치]
 * 1. 먼저 시작시간을 기준으로 오름차순 정렬 (정렬)
 * 2. 종료 시간이 가장 빠른 수업과 현재 수업의 시작시간 비교해서 같은 강의실 배치 가능한지 검사 (우선순위 큐)
 */

//필요 강의실 배치하는 함수 -> 최소 필요 강의실 수 리턴
int arrayRoom(int n, vector<ci> lec) {
    priority_queue<int, vector<int>, greater<>> pq; //종료 시간을 저장하는 우선순위 큐

    //처음 수업에 무조건 강의실 1개 배치 -> 종료시간 우선순위큐에 넣기
    pq.push(lec[0].second);
    int ans = 1; //필요한 강의실 기본 1개

    //그 다음 수업부터 검사
    for (int i = 1; i < n; i++) { //총 수업 횟수 - 1 번만큼 반복문 돌면서 순차적으로 종료 시간 비교 후 강의실 배정
        if (lec[i].first >= pq.top()) // 종료시간이 가장 빠른 수업(pq의 top)보다 시작시간이 같거나 느리다면 -> 같은 강의실
            pq.pop(); //같은 강의실 사용
        else //종료시간이 가장 빠른 수업보다 시작시간이 빠르다면 -> 새로운 강의실
            ans++; //필요한 강의실 개수 증가
        pq.push(lec[i].second); //기존 강의실 정보 갱신 or 새로운 강의실 정보 저장
    }

    return ans;
}

int main() {
    int n;

    //입력
    cin >> n;
    vector<ci> lec(n, ci(0, 0)); //수업 시간 정보 저장할 벡터
    for (int i = 0; i < n; i++) { //수업별 시작시간, 종료시간 저장
        cin >> lec[i].first >> lec[i].second; //first: 시작시간, second: 종료시간
    }

    //연산
    sort(lec.begin(), lec.end()); //벡터 오름차순 정렬 (lec.begin():벡터의 시작 주소/lec.end():벡터의 마지막 주소)

    //출력
    cout << arrayRoom(n, lec) << '\n';

    return 0;
}

