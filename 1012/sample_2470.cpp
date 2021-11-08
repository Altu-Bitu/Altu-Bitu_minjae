//
// Created by iw040 on 2021-10-12.
//

#include <iostream> //출력 사용
#include <vector> //벡터 사용
#include <algorithm> //정렬 사용

using namespace std;

//다른 위치에서 시작하여 서로를 향해 가까워지는 투 포인터
pair<int, int> liquid(vector<int> &arr, int left, int right) {
    pair<int, int> ans; //혼합시 특성값이 0에 가장 가까운 두 용액의 특성값
    int min_diff = 2 * 1e9 + 1; //0에 가까운 값, 처음 단계를 위해 무한대 수로 초기화

    //left는 항상 right의 왼쪽에 있어야 함
    while (left < right) { //left와 right의 상대적 위치가 뒤바뀌면 반복문 탈출
        int mix = arr[left] + arr[right]; //두 용액을 혼합
        if (mix == 0) //그 값이 0이라면 이보다 더 0에 가까워질 수 없기 때문에 바로 리턴
            return make_pair(arr[left], arr[right]);
        if (abs(mix) < min_diff) { //0에 가까운 값을 갱신할 수 있는지 확인
            min_diff = abs(mix);//더 작은 값으로 갱신
            ans = make_pair(arr[left], arr[right]); //정답도 해당 두 용액의 특성값으로 갱신
        }
        if (mix > 0) //0보다 크면 더 작은 값을 만들어야 함
            right--; //더 작은 값이 있는 범위 탐색 (오름차순 되어 있는 상태)
        else if (mix < 0) //0보다 작으면 더 큰 값을 만들어야 함
            left++; //더 큰 값이 있는 범위 탐색
    }
    return ans; //특성값이 0에 가장 가까운 두 용액의 특성값 반환
}

int main() {
    int n; //n: 전체 용액의 수

    //입력
    cin >> n;
    vector<int> arr(n, 0); //용액의 특성값 정보
    for (int i = 0; i < n; i++) //i번째 용액
        cin >> arr[i]; //특성값 정수 입력

    //연산
    sort(arr.begin(), arr.end()); //오름차순 정렬
    pair<int, int> ans = liquid(arr, 0, n - 1); //출력해야 하는 두 용액의 특성값 대입

    //출력
    cout << ans.first << ' ' << ans.second; //첫번째 특성값, 두번째 특성값
}
