#include <iostream>

using namespace std;

//n번째 종말의 숫자 리턴
int endNumber(int n) {
    int cnt = 0; //종말의 숫자 카운트

    //666(1번째 종말의 숫자)부터 차례로 모두 검사해보기
    for (int i = 666;; i++) {
        string s = to_string(i); //숫자 -> 문자열로 치환
        if (s.find("666") != s.npos) //"666"이 존재한다면
            cnt++; //종말의 숫자 카운트 +1
        if (cnt == n) //n번째 종말의 숫자 리턴
            return i;
    }
}

int main() {
    int n;

    //입력 (n번째 영화에 들어갈 수)
    cin >> n;

    //연산+출력
    cout << endNumber(n) << '\n';

    return 0;
}

