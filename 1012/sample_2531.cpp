#include <iostream>
#include <vector>

using namespace std;

int chooseSushi(vector<int> &belt, int n, int d, int k, int c) {
    vector<int> sushi(d + 1, 0); //d: 초밥의 가짓수, value: 먹은 횟수

    //쿠폰으로 먹은 초밥
    int section_sushi = 1;
    sushi[c]++; //쿠폰에 적혀진 종류의 초밥 추가

    //윈도우 초기화
    for (int i = 0; i < k; i++) { //i: 연속해서 먹은 접시 i 개 , k: 연속해서 먹은 접시의 수
        sushi[belt[i]]++; //먹은 초밥 종류에 따라 횟수 +1
        if (sushi[belt[i]] == 1) //1번 먹은 초밥
            section_sushi++; //먹은 초밥 종류 +1
    }

    int ans = section_sushi; //연속해서 먹은 초밥 종류로 초기화
    int left = 0, right = k - 1; //투 포인터
    do { //원형태로 윈도우를 옮겨야 하기 때문에 종료조건은 left가 초기값(=0)이 됐을 때
        sushi[belt[left]]--;//맨 앞 초밥 제거
        if (!sushi[belt[left]]) //0이 되면
            section_sushi--;//삭제

        //윈도우의 양 끝 이동
        left = (left + 1) % n;
        right = (right + 1) % n;

        sushi[belt[right]]++; //오른쪽 초밥 추가
        if (sushi[belt[right]] == 1) //1번 먹었다면
            section_sushi++; //먹은 초밥 종류 +1

        ans = max(ans, section_sushi); //ans와 업데이트된 section_sushi 중 큰 값 할당
    } while (left);
    return ans; //정답 반환
}

/**
 * 1. 연속해서 먹어야 할 접시가 k로 고정됐기 때문에 슬라이딩 윈도우
 * 2. 직선이 아니라 원 형태의 배열! 모듈러 연산을 통해 윈도우의 양 끝 위치 조절하기
 * 3. 쿠폰으로 먹은 초밥을 먼저 고려해놓기
 * 4. 초밥의 종류가 최대 3000개로 많지 않음. 보석 쇼핑 문제처럼 각 종류별 먹은 초밥의 개수를 세어주기
 */
int main() {
    int n, d, k, c; //n:회전 초밥 벨트에 놓인 접시의 수, d:초밥의 가짓수, k:연속해서 먹는 접시의수, c:쿠폰 번호

    //입력
    cin >> n >> d >> k >> c;
    vector<int> belt(n, 0); //초밥의 종류 정보
    for (int i = 0; i < n; i++) //i번째 초밥
        cin >> belt[i]; //초밥의 종류 입력

    //연산 & 출력
    cout << chooseSushi(belt, n, d, k, c);
}

