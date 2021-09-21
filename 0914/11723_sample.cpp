#include <iostream>
#include <vector>
#include <string>

using namespace std;
const int SIZE = 21; //배열 사이즈, 1~20의 숫자가 입력되므로 인덱스가 20까지 있는 배열 필요

/**
 * 배열 사용 풀이
 * 1. 집합에는 1~20의 숫자만 입력 or 제거됨 (=true or false)
 * 2. 크기 21의 bool 배열을 선언
 * 3. 입력은 true 처리, 제거는 false 처리
 */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); //시간초과방지 ,c의 stdio와 cpp의 iostream 동기화 비활성화

    int m, num; //m: 입력받을 연산의 수
    string cmd; //연산의 종류 입력받을 변수 : add, remove, check, toggle, all, empty
    vector<bool> s(SIZE, false); //집합에서 1~20의 숫자의 유무 정보 입력될 boolean 배열

    cin >> m; //총 연산의 수 입력
    while (m--) {
        cin >> cmd; //연산의 종료 입력
        if (cmd == "all") { //1~20까지 true가 되도록 재할당
            s.assign(SIZE, true); //인덱스0부터 인덱스20까지 true 입력 : 집합 S ={1, 2, ~, 19, 20}
            continue; //반복문 탈출
        }
        if (cmd == "empty") { //1~20까지 false가 되도록 재할당
            s.assign(SIZE, false); //인덱스0부터 인덱스20까지 false 입력 : 집합 S는 공집합
            continue; //반복문 탈출
        }

        cin >> num; //피연산자 숫자 입력
        if (cmd == "add") { //num을 true 처리
            s[num] = true; //입력받은 숫자 인덱스 값에 true 입력 : 집합에 추가
            continue; //반복문 탈출
        }
        if (cmd == "remove") { //num을 false 처리
            s[num] = false; //입력받은 숫자 인덱스 값에 false 입력 : 집합에서 제거
            continue; //반복문 탈출
        }
        if (cmd == "check") { //num의 상태 확인
            cout << s[num] << '\n'; //입력받은 숫자 인덱스 값이 true(존재)면 1, false(없음)이면 0 출력
            continue; //반복문 탈출
        }
        if (cmd == "toggle") { //true->false, false->true
            s[num] = !s[num]; //있으면 제거(true->false), 없으면 추가(false->true)
            continue; //반복문 탈출
        }
    }
}

