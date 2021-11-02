#include <iostream>
#include <vector>

using namespace std;
const int MAX = 100000; //수열은 100000이하의 양의 정수

int findLen(vector<int> &arr, int n, int k) {
    vector<int> cnt(MAX + 1, 0); //각 원소 등장 횟수

    int ans = 0, left = 0, right = 0;// 정답, 투포인터 초기화

    //left는 항상 right의 왼쪽 또는 같은 위치에 있어야 함
    while (left <= right && right < n) { // left와 right의 위치가 바뀌면 탈출
        if (cnt[arr[right]] + 1 <= k) { //현재 right가 가리키는 원소를 포함해도 등장 횟수가 k번 이하
            cnt[arr[right]]++; //해당 값의 등장 횟수 +1
            ans = max(ans, (right - left) + 1); //현재 구간의 길이
            right++; // right 증가
        } else { //현재 right가 가리키는 원소를 포함하면 등장 횟수가 k번을 초과
            cnt[arr[left]]--; //구간 업데이트 , 기존 구간의 두번째가 첫번째로
            left++; //left 이동
        }
    }
    return ans; //정답 반환
}

/**
 * 1. 최장 연속 부분 수열의 '길이'를 구해야 함 -> 구간 내의 모든 원소를 고려하기 때문에 한쪽에서 시작하는 투 포인터
 * 2. 각 원소의 최댓값이 100,000이기 때문에 배열로 등장 횟수 체크할 수 있음
 * 3. right를 옮기고 바로 원소를 추가했던 기존 방법과 달리, 일단 포인터만 옮겨놓고 원소를 추가해도 되는지 확인
 */
int main() {
    int n, k; //n: 수열의 길이, k: 연속구간에서 같은 원소가 k개 이하여야

    //입력
    cin >> n >> k;
    vector<int> arr(n, 0); //배열
    for (int i = 0; i < n; i++) //i: 배열 인덱스
        cin >> arr[i]; //값 차례로 입력

    //연산 & 출력
    cout << findLen(arr, n, k);
}