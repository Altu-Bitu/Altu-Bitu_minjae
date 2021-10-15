#include <iostream> //입출력 사용
#include <vector> //벡터 사용
#include <algorithm> //min, max 사용

using namespace std;

vector<int> arr; //배열 역할 벡터

//구간의 점수의 최댓값이 score일 때 나뉘는 구간의 개수
int cntSection(int score) { //score: 구간 점수의 최댓값
    //첫번째 구간의 시작
    int cnt = 1;
    int min_value = arr[0], max_value = arr[0]; //최소, 최대 초기화

    for (int i = 1; i < arr.size(); i++) { //i: 배열 인덱스
        min_value = min(min_value, arr[i]); //더 작은 값 만나면 최솟값 갱신
        max_value = max(max_value, arr[i]); //더 큰 값 만나면 최댓값 갱신
        if (max_value - min_value > score) { //구간의 점수가 score를 초과한다면 새로운 구간 만들기
            cnt++; //구간 추가
            min_value = arr[i]; //i: 새로운 구간 시작한 인덱스 , 최소로 초기화
            max_value = arr[i]; //최대로 초기화
        }
    }
    return cnt; //만들어지는 구간 개수 반환
}

int lowerSearch(int left, int right, int target) { //left: 구간 점수의 최댓값 중 최솟값(0), right: 구간 점수의 최댓값 중 최댓값(max-min), 구간 수
    int ans = 0; //구간 점수의 최댓값이 최소일때 최솟값
    while (left <= right) { //left가 right보다 커지면 점수별로 검사 다 한 것이므로 반복문 종료
        //구간의 점수의 최댓값이 mid일 때, 몇 개의 구간이 만들어지는가?
        int mid = (left + right) / 2; //mid 초기화, 구간 점수의 최댓값
        int section = cntSection(mid);//만들어지는 구간의 수

        if (section <= target) { //만들어지는 구간의 수가 target(=m) 이하면
            ans = mid; //현재 mid값이 (구간 점수의 최댓값이 최소인 경우의) 최솟값
            right = mid - 1; //더 작은 값 탐색 (현재 mid 이하)
        } else if (section > target) //구간의 수가 target 이상이면
            left = mid + 1; //더 큰 값 탐색 (현재 mid 이상)
    }
    return ans; //찾은 최솟값 반환
}

/**
 * 배열을 M개 이하의 구간으로 나눈다. 나눈 구간의 점수의 최댓값을 최소로 만든 결과는?
 * -> 구간의 점수의 최댓값이 k라고 할 때, 몇 개의 구간이 필요한가?
 *
 * left (구간 점수의 최댓값의 최솟값) : 배열의 모든 원소가 같다면 구간의 점수는 항상 0이다. 그러므로 구간의 점수의 최댓값도 0이 된다.
 * right (구간 점수의 최댓값의 최댓값) : 구간이 1개라면 그 점수는 가장 큰 값과 가장 작은 값의 차이와 같다.
 */
int main() {
    int n, m; //n: A배열, m:구간 개수가 m개 이하
    int min_value = 10001, max_value = 0; //최소값, 최대값 저장 변수

    //입력
    cin >> n >> m;
    arr.assign(n, 0); //n크기 배열 0으로 초기화
    for (int i = 0; i < n; i++) {//i: 배열 인덱스
        cin >> arr[i]; //입력
        min_value = min(min_value, arr[i]); //더 작은 값 입력받으면 최솟값 갱신
        max_value = max(max_value, arr[i]); //더 큰 값 입력받으면 최댓값 갱신
    }

    //연산 & 출력
    cout << lowerSearch(0, max_value - min_value, m);
}

