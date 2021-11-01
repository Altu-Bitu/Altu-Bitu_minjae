//
// Created by iw040 on 2021-10-12.
//

#include <iostream>
#include <vector>

using namespace std;

//에라토스테네스의 체로 n 이하인 모든 소수 구하기
vector<bool> isPrime(int n) {
    vector<bool> is_prime(n + 1, true); //소수 여부 저장

    is_prime[0] = is_prime[1] = false; //0,1은 소수가 아니므로
    for (int i = 2; i * i <= n; i++) { //i: 소수인지 검사받을 자연수
        if (is_prime[i]) { //i가 소수라면
            for (int j = i * i; j <= n; j += i) //j: 이전의 소수의 배수들은 모두 제거되었으므로 i*i 부터 시작
                is_prime[j] = false; //i의 배수 제거
        }
    }
    return is_prime; //소수 여부 저장 벡터 반환
}

//n 이하의 모든 소수
vector<int> primeList(vector<bool> &is_prime) {
    vector<int> prime_list; //n이하의 소수 저장 벡터

    for (int i = 2; i <= is_prime.size(); i++) {//i: 자연수
        if (is_prime[i]) //소수가 맞으면
            prime_list.push_back(i); //벡터 삽입(오름차순)
    }
    return prime_list; //n이하의 소수 값 벡터 반환
}

//같은 위치에서 시작하여 같은 방향으로 이동하는 투 포인터
int findSum(vector<int> &prime_list, int target) { //&prime_list:n이하의 소수 모음, target:
    int ans = 0; //연속된 소수의 합으로 나타낼 수 있는 경우의 수
    int size = prime_list.size(), left = 0, right = 0; //size: n이하의 소수 개수, left&right: 투포인터 선언
    int sum = prime_list[left]; //초기 구간

    //left는 항상 right의 왼쪽 또는 같은 위치에 있어야 함
    //right는 항상 size보다 작은 값이어야 함
    while (left <= right && right < size) {
//        if (sum == target) { //구간의 합이 target과 같을 때
//            ans++; left++; right++; //모든 포인터 이동
//            if (right == size)
//                break;
//            sum -= prime_list[left - 1]; //이번 구간에 제외되는 값
//            sum += prime_list[right]; //이번 구간에 추가되는 값
//        } else if (sum > target) { //구간의 합이 target보다 클 때
//            left++; //합을 작게하기 위해 left 이동
//            sum -= prime_list[left - 1];
//        } else if (sum < target) { //구간의 합이 target보다 작을 때
//            right++; //합을 크게하기 위해 right 이동
//            if (right == size)
//                break;
//            sum += prime_list[right];
//        }
        if (sum >= target) { //구간의 합이 target보다 크거나 같다면
            if (sum == target) //같다면
                ans++; //연속된 소수의 합으로 나타낸 경우 +1
            left++; //합을 작게하기 위해 left 이동
            sum -= prime_list[left - 1]; //이전 소수 값 합 연산 취소
        } else if (sum < target) { //구간의 합이 target보다 작을 때
            right++; //합을 크게하기 위해 right 이동
            if (right == size) //right가 소수 개수와 같다면 더이상의 검사는 이루어질 수 없으므로
                break; //반복문 탈출
            sum += prime_list[right]; //다음 소수 더하기
        }
    }
    return ans; //출력해야 할 정답 반환
}

int main() {
    int n; //n: 소수의 합으로 나타낼 자연수 n

    //입력
    cin >> n;

    //연산
    vector<bool> is_prime = isPrime(n); //n 이하인 모든 수 소수 여부에 대한 정보 벡터
    vector<int> prime_list = primeList(is_prime); //n이하의 소수 집합
    int ans = findSum(prime_list, n);//연속된 소수의 합으로 나타낼 수 있는 경우의 수

    //출력
    cout << ans;
}

