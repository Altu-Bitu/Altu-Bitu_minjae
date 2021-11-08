#include <iostream> //입출력 사용
#include <algorithm> //정렬 사용
#include <vector> //벡터 사용

using namespace std;

//좋은 수인지 검사하는 함수(투 포인터)
bool isGood(vector<int> &num, int left, int right, int idx) {//숫자 정보 저장 , left(0부터 시작)&right(마지막부터 시작) 포인터, isGood 검사 대상 숫자 인덱스
    while (left < right) { //레프트 라이트 위치 뒤바뀌면 탈출
        if (left == idx) { //left가 현재 수 위치와 같은 경우
            left++; //포인터 옮기기 (점점 오른쪽으로 감)
            continue; // 다음 단계에서 검사 실행
        }
        if (right == idx) { //right가 현재 수 위치와 같은 경우
            right--; //포인터 옮기기 (점점 왼쪽으로 감)
            continue; //다음 단계에서 검사 실행
        }

        if (num[left] + num[right] == num[idx]) //두수의 합으로 나타낼 수 있음
            return true;  //참 반환

        if (num[left] + num[right] > num[idx]) //만드려는 수보다 크다면
            right--; //right 왼쪽으로 옮기기
        else //만드려는 수보다 작다면
            left++; //left 오른쪽으로 옮기기
    }
    return false;
}

/**
 * 1. 각 수마다 양 쪽 끝에서 포인터를 시작해서 좁혀오면서 어떤 '다른 두 수'가 현재 수를 만들 수 있는지 검사
 * 2. 포인터를 차례로 옮기며 검사하기 위해 미리 수를 오름차순 정렬함
 * 3. 현재 만드려는 수의 위치와 left, right 포인터 위치가 겹칠 경우 처리 주의
 */

int main() {
    int n, ans = 0; //n:수의 개수, ans: 다른 두 수의 합으로 나타낼 수 있는 수의 개수

    //입력
    cin >> n;
    vector<int> num(n, 0); //숫자 정보 저장
    for (int i = 0; i < n; i++) //i번째 입력 숫자
        cin >> num[i]; //숫자 입력

    //연산
    sort(num.begin(), num.end()); //입력 숫자 정렬
    for (int i = 0; i < n; i++) { //i: 입력 숫자 순차 접근
        if (isGood(num, 0, n - 1, i))  // GOOD인지 판단
            ans++; //다른 두수의 합으로 나타낼 수 있으면 +1
    }

    //출력
    cout << ans << '\n';

    return 0;
}
