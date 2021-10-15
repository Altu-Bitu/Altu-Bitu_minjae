#include <iostream> //입출력
#include <vector> //벡터 사용
#include <algorithm> //sort 사용

using namespace std;

vector<int> house; //집 좌표 정보 벡터

//가장 인접한 두 공유기 사이의 거리가 dist이도록 공유기를 설치했을 때, 설치된 공유기 숫자
int router(int dist) { //dist: 거리
    //첫번째 집에 무조건 공유기 설치
    int cnt = 1; //공유기 설치 횟수
    int pos = house[0]; //현재 위치

    for (int i = 1; i < house.size(); i++) { //i: 집 번호
        if (house[i] - pos < dist) //가장 가까운 집과의 거리가 dist 이상이어야 설치 가능
            continue; //house[i] 집과의 거리가 dist 보다 인접할 경우 패스, 다음 집 검사
        //i번째 집에 공유기 설치
        cnt++; //설치 횟수 카운트
        pos = house[i];//위치 갱신
    }
    return cnt; //설치된 공유기 수
}

//가능한 최대 거리 중 가장 큰 값(=upper bound)
int upperSearch(int left, int right, int target) { //left: 최단 거리, right: 최장거리, target: 공유기 개수
    int ans = 0; //최대 거리
    while (left <= right) { //left와 right의 위치가 뒤바뀌면 종료
        //가장 인접한 두 공유기 사이의 거리가 mid일 때, 공유기를 최대 몇 개 설치할 수 있는가?
        int mid = (left + right) / 2; //mid 포인터
        int installed = router(mid); //설치할 수 있는 공유기 수 받아오기

        if (installed < target) //mid의 거리로는 target만큼의 공유기를 설치할 수 없음 -> 거리를 줄여야
            right = mid - 1; //right 위치를 옮겨서 더 가까운 간격일 때를 검사
        else if (installed >= target) { //mid의 거리로는 target만큼의 공유기를 설치할 수 있음 -> 거리를 늘려보자
            ans = mid; //현재의 mid값 저장. 최종 갱신되는 값은 upper bound
            left = mid + 1; //left 위치를 옮겨서 더 먼 간격일 때를 검사
        }
    }
    return ans; //최대 거리 값 반환
}

int main() {
    int n, c;

    //입력
    cin >> n >> c; //n: 집의 개수, c: 공유기의 개수
    house.assign(n, 0); //집 관련 벡터 0으로 초기화
    for (int i = 0; i < n; i++)//i: 집 번호
        cin >> house[i];//집의 좌표 입력

    //연산
    sort(house.begin(), house.end()); //이분탐색 적용시 정렬 상태 세팅

    //연산 & 출력
    //공유기 사이의 최단 거리 (left) : 1
    //공유기 사이의 최장 거리 (right) : 가장 멀리 있는 두 집 사이의 거리
    cout << upperSearch(1, house[n - 1] - house[0], c);
}

