#include <iostream>
#include <vector>

using namespace std;
const int SIZE = 26; //알파벳 개수

//알파벳별 등장횟수 저장
vector<int> alphaMap(string str) { //str: 기준 단어
    vector<int> result(SIZE, 0); //0~25: A,B,C...,Z , value: 사용된 횟수
    for (int i = 0; i < str.size(); i++) //i: 문자 인덱스
        result[str[i] - 'A']++; //str[i]-'A' : 문자의 알파벳 순번
    return result; //결과 반환
}

/**
 * 단어가 같은 구성일 조건
 * 1. 두 개의 단어가 같은 종류의 문자로 이루어짐
 * 2. 같은 문자는 같은 개수만큼 있음
 *
 * 비슷한 단어의 조건
 * 1. 한 단어에서 한 문자를 더하거나, 빼면 같은 구성이 됨
 *    -> 두 단어에서 다른 문자의 개수가 총 1개
 * 2. 한 단어에서 한 문자를 바꾸면 같은 구성이 됨
 *    -> 두 단어에서 다른 문자의 개수가 총 2개
 *    -> !주의! 이때, 두 단어의 길이가 같아야 함 cf) doll | do
 */
int main() {
    int n, ans = 0; //n: 단어의 개수, ans: 첫번째 단어와 비슷한 단어의 개수
    string source, target; //source: 기준 단어, target: 비교 대상 단어

    //입력
    cin >> n >> source; //첫번째 단어 입력

    //연산
    vector<int> source_alpha = alphaMap(source);  //알파벳별 사용횟수 정보
    while (--n) { //n-1개 단어 비교
        cin >> target; //비교 대상 단어 입력

        int diff = 0; //차이
        vector<int> target_alpha = alphaMap(target); //알파벳별 사용횟수 정보
        for (int i = 0; i < SIZE; i++) //두 단어의 차이
            diff += abs(source_alpha[i] - target_alpha[i]); //알파벳별 사용횟수 차이 업데이트
        if (diff <= 1 || (diff == 2 && source.size() == target.size())) //문자를 더하거나, 빼거나, 바꾸거나
            ans++; //비슷한 단어 개수 +1
    }

    //출력
    cout << ans;
}

