#include <iostream> //입출력 사용
#include <vector> //벡터 사용
#include <algorithm> //sort 사용

using namespace std;

int childNum(vector<int> &snacks, int len) { //&snacks: 과자 길이 정보 벡터, len: 과자 길이
    int cnt = 0; //몇 명에게 나누어주는지
    for (int i = snacks.size() - 1; i >= 0; i--) { //가장 긴 과자부터 검사
        if (snacks[i] < len) //나누어주려는 길이보다 작아지면 더 이상 못 나눠줌
            break; //반복문 탈출
        cnt += (snacks[i] / len); //i번째 과자를 몇 명에게 나누어 줄 수 있는지
    }

    return cnt; //나누어 줄 수 있는 인원 반환
}

int upperSearch(vector<int> &snacks, int left, int right, int target) {//인자: 과자 길이 정보 벡터, 최소 길이, 최대 길이, 조카 수
    int ans = 0; //줄 수 있는 막대 과자의 최대 길이
    while (left <= right) { //left와 right의 위치가 뒤바뀌면 반복문 종료
        int mid = (left + right) / 2; //과자의 길이
        int cnt = childNum(snacks, mid); //과자 길이가 mid일 때 몇 명에게 나눠주는지

        if (cnt >= target) { //target보다 더 많은 아이들에게 나눠준다면 -> 과자 길이를 더 늘릴 수 있음
            left = mid + 1; //(다음 반복문에서)더 긴 과자 길이 탐색
            ans = mid; //현재 최대 길이
        } else { // target 보다 적은 아이들에게 나눠줄 수 있다면
            right = mid - 1; //(다음 반복문에서) 더 짧은 긴 과자 길이 탐색
        }
    }

    return ans; //정답 반환
}

/**
 * n개의 과자가 있을 때 m명의 조카에게 각각 같은 길이로 줄 수 있는 과자의 최대 길이를 구하는 문제
 * -> 특정 과자 길이에 대하여 m명의 조카에게 나누어 줄 수 있는가?
 *
 * left: 과자 길이의 최솟값 -> 1
 * right: 과자 길이의 최댓값
 *
 * 과자를 몇 명에게 나누어줄 수 있는지 차례로 검사하다 나누어줄 수 없으면 빠져나오기 위해 정렬을 먼저 해주면 좋음
 */

int main() {
    int m, n, left = 1, right = 0; //m: 조카의 수, n: 과자의 수, left: 과자 길이의 최솟값, right: 과자 길이의 최댓값

    //입력
    cin >> m >> n;
    vector<int> snacks(n, 0); //과자별 길이 정보 0으로 초기화
    for (int i = 0; i < n; i++) //i: 과자 번호
        cin >> snacks[i]; //과자 길이 입력

    //연산
    sort(snacks.begin(), snacks.end()); //정렬
    right = snacks[n - 1]; //가장 긴 과자의 길이

    //연산 & 출력
    cout << upperSearch(snacks, left, right, m);

    return 0; //정수값 반환
}
