#include <iostream> //입출력
#include <vector> //벡터 사용
#include <algorithm> //sort 함수 사용

using namespace std;

vector<int> arr; //배열 역할 벡터

//lower bound : target이 위치하는 가장 낮은 위치 index
int lowerBound(int left, int right, int target) {//left,right : 이분탐색에 사용되는 포인터, target: 찾는 숫자
    while (left <= right) { //left 포인터가 right 포인터보다 뒤에 있으면 break
        int mid = (left + right) / 2; //중간값
        //중간값이 target보다 크다면 target은 왼쪽에 있음
        //중간값이 target과 같다면 왼쪽에 target과 같은 값이 더 있을 수 있음
        if (arr[mid] >= target)
            right = mid - 1;//왼쪽에 target이 더 있는지 찾기 위함
        if (arr[mid] < target) //중간값이 target보다 작다면 target은 오른쪽에 있음
            left = mid + 1;//target은 mid값 오른쪽에 위치해 있으므로 left 포인터를 mid 값 바로 다음으로 옮겨서 탐색 범위 줄이기
    }
    /**
     * right + 1을 리턴하는 이유
     * right가 움직일 때는 arr[mid]가 target 이상일 때
     * 값이 target 이상이면서, 인덱스가 가장 작은 mid값이 lower bound!
     * right는 mid - 1이므로 right + 1은 lower bound
     */
    return right + 1;
}

//upper bound : : target이 위치하는 가장 높은 위치 index
int upperBound(int left, int right, int target) { //left,right : 이분탐색에 사용되는 포인터, target: 찾는 숫자
    while (left <= right) { //left 포인터가 right 포인터보다 뒤에 있으면 break
        int mid = (left + right) / 2; //중간값
        if (arr[mid] > target) //중간값이 target보다 크다면 target은 왼쪽에 있음
            right = mid - 1; //target은 mid값 왼쪽에 위치해 있으므로 right 포인터를 mid 값 바로 전으로 옮겨서 탐색 범위 줄이기
        //중간값이 target보다 작다면 target은 오른쪽에 있음
        //중간값이 target과 같다면 오른쪽에 target과 같은 값이 더 있을 수 있음
        if (arr[mid] <= target)
            left = mid + 1; //오른쪽에 target이 더 있는지 찾기 위함
    }
    /**
     * right + 1을 리턴하는 이유
     * break 직전 left와 right는 같은 곳을 가리킴
     * 이 상태에서 right(mid)가 가리키는 값은 target 이하기 때문에 left 포인터가 이동하고 break
     * 이 때의 left값은 target을 처음으로 초과하는 upper bound이며 직전에 left와 right의 위치가 같았으므로 right + 1 == left
     */
    return right + 1;
}

int main() {
    ios::sync_with_stdio(false); //입력 속도 향상
    cin.tie(NULL);

    int n, m, input; //n: 카드 개수, m: 검사받을 숫자 개수, input: 검사받을 숫자

    //입력
    cin >> n; //소유한 카드 개수 입력
    arr.assign(n, 0); // 배열 역할 벡터 0으로 초기화
    for (int i = 0; i < n; i++) //i: 카드 번호
        cin >> arr[i]; //개별 카드에 해당하는 숫자 입력

    //연산
    sort(arr.begin(), arr.end()); //이분 탐색을 하기 위해선 반드시 정렬을 해야함

    //연산
    cin >> m; //검사받을 숫자 개수
    while (m--) {//(m-1~0까지) m번 검사
        cin >> input;//존재 유무 판정받을 숫자 입력

        //연산 & 출력
        cout << upperBound(0, n - 1, input) - lowerBound(0, n - 1, input) << ' ';
        //cout << upper_bound(arr.begin(), arr.end(), input) - lower_bound(arr.begin(), arr.end(), input) << ' ';
    }
}

