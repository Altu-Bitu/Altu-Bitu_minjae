#include <iostream> //입출력
#include <vector> //벡터 사용
#include <algorithm> //sort 함수 사용

using namespace std;

vector<int> arr; //배열 역할 벡터

//이분 탐색
bool binarySearch(int left, int right, int target) {//left,right : 이분탐색에 사용되는 포인터, target: 찾는 숫자
    while (left <= right) { //left 포인터가 right 포인터보다 뒤에 있으면 break
        int mid = (left + right) / 2; //중간값
        if (arr[mid] == target) //target을 찾음
            return true; //true 반환, 함수 탈출
        if (arr[mid] > target) //중간값이 target보다 크다면 target은 왼쪽에//left,right : 이분탐색에 사용되는 포인터, target: 찾는 숫자 있음
            right = mid - 1; //target은 mid값 왼쪽에 위치해 있으므로 right 포인터를 mid 값 바로 전으로 옮겨서 탐색 범위 줄이기
        if (arr[mid] < target) //중간값이 target보다 작다면 target은 오른쪽에 있음
            left = mid + 1;//target은 mid값 오른쪽에 위치해 있으므로 left 포인터를 mid 값 바로 다음으로 옮겨서 탐색 범위 줄이기
    }
    return false; //target을 찾지 못함
}

int main() {
    ios::sync_with_stdio(false); //입력 속도 향상
    cin.tie(NULL);

    int n, m, input; //n: A 배열 크기, m: 존재 유무 검사받을 배열 크기

    //입력
    cin >> n;
    arr.assign(n, 0); //A 배열 0으로 초기화
    for (int i = 0; i < n; i++) //i: 배열 인덱스
        cin >> arr[i]; //A 배열의 값 입력

    //연산
    sort(arr.begin(), arr.end()); //이분 탐색을 하기 위해선 반드시 정렬을 해야함

    //입력
    cin >> m;
    while (m--) { //0~m-1까지, m:인덱스
        cin >> input; //배열의 값 입력

        //연산 & 출력
        cout << binarySearch(0, n - 1, input) << '\n'; //입력받은 값 A 배열에 있는지 확인
        //cout << binary_search(arr.begin(), arr.end(), input) << '\n';
    }
}