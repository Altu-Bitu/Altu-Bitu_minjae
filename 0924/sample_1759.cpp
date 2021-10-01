#include <iostream> //입출력 사용
#include <vector> //벡터 사용
#include <algorithm> //prev_permutation 함수 사용

using namespace std;

bool is_vowel[26]; //알파벳 사용 여부 체크 배열

//가능성 있는 암호인지 체크하는 함수
bool promising(int l, vector<char> &alpha, vector<bool> &comb) { //인자: 암호길이, 사용 알파벳 집합, 알파벳별 사용 유무
    int vowel_cnt = 0, size = comb.size(); //vowel_cnt: 모음 사용 횟수, size: 사용할 수 있는 알파벳의 수
    for (int i = 0; i < size; i++) { //알파벳마다 조건 체크
        if (!comb[i]) //연산에 포함되지 않는 문자
            continue; //다음 문자 체크
        if (is_vowel[alpha[i]-'a']) //모음이라면
            vowel_cnt++; //모음 사용 횟수 증가
    }
    return (vowel_cnt >= 1) && ((l - vowel_cnt) >= 2); //암호조건: 모음이 최소 1개 이상 && 자음이 최소 2개 이상 -> 충족 시 true 반환
}

//문자 배열을 문자열로 만드는 함수
string charToString(vector<char> &alpha, vector<bool> &comb) {//인자: 사용 알파벳 집합, 알파벳별 사용 유무
    string result;//암호 문자열
    for (int i = 0; i < comb.size(); i++) { //알파벳마다 사용여부 체크하는 반복문
        if (comb[i]) //연산에 포함된 문자라면 result에 더하기
            result += alpha[i]; //result에 추가
    }
    return result;//암호 문자열로 반환
}

/**
 * permutation 이용한 조합 풀이 (2529_2.cpp, 15661_2.cpp 주석을 먼저 봐주세요)
 *
 * 크기가 n인 배열에서 k개의 원소를 뽑는 방법
 *
 * 1. 비트마스킹 -> 00...00~11...11까지 확인 but 비트마다 k개가 뽑힌게 맞는지 추가 연산 필요.
 *    (ex) n=4, k=2일 때. 조건에 맞는건 {0011, 0101, 1001, 1010, 1100, 0110}이지만 {1111, 1110}등도 반복문에 들어옴
 *         비트마스킹은 (n^2)개의 경우의 수를 고려하지만, 여기선 (nCk)개의 경우만 필요하기 때문에 시간낭비
 *
 * 2. permutation -> n 크기의 배열을 준비하고 그 중 k개의 원소를 true로 셋팅
 *    (ex) n=4, k=2일 때. arr = {1, 1, 0, 0}에 대한 prev_permutation 결과
 *         {1, 1, 0, 0} -> {1, 0, 1, 0} -> {1, 0, 0, 1} -> {0, 1, 1, 0} -> {0, 1, 0, 1} -> {0, 0, 1, 1}
 *         비트마스킹 풀이와 마찬가지로 1로 표시된 인덱스의 값만 연산에 포함하면 됨
 */
int main() {
    int l, c; //l:암호길이 , c:입력될 수 있는 알파벳 종류 개수
    vector<char> alpha;//암호로 쓰일 알파벳 집합
    vector<bool> comb;//암호로 사용된 유무 나타내기 위한 용도

    //모음 저장
    is_vowel['a' - 'a'] = is_vowel['e' - 'a'] = is_vowel['i' - 'a'] = is_vowel['o' - 'a'] = is_vowel['u' - 'a'] = true;//모음 자리 true 삽입

    //입력
    cin >> l >> c; //l:암호길이, c:입력될 수 있는 알파벳 종류 개수
    alpha.assign(c, ' ');//사용될 알파벳 종류 개수만큼 벡터에 추가
    comb.assign(c, false);//알파벳별로 false(미사용) 값 대입
    for (int i = 0; i < c; i++) //사용될 알파벳 c번 입력받음
        cin >> alpha[i]; //alpha 벡터에 값 저장

    //연산 & 출력

    //인덱스 0부터 l개의 원소를 true로 셋팅
    for (int i = 0; i < l; i++) //암호 길이만큼 반복문 돌면서 true 표시를 통해 암호 생성
        comb[i] = true; //처음 입력된 알파벳 순서대로 암호 1세트 생성
    sort(alpha.begin(), alpha.end()); //알파벳 사전순 정렬
    do { //앞서 암호 1세트를 생성한 상태이므로 가능성 있는 암호인지 검사 시도
        if (promising(l, alpha, comb)) //가능성 있는 암호라면 출력
            cout << charToString(alpha, comb) << '\n'; //문자열 형태의 암호 출력
    } while (prev_permutation(comb.begin(), comb.end())); //prev_permutation을 통해 암호의 모든 조합을 체크하며 반복문 돌기, 다음 순열이 없다면 false 반환하여 반복문 탈출
}