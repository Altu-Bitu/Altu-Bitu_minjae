#include <iostream> // 입출력 사용
#include <map> //맵 사용

using namespace std;

/**
 * 모든 캐릭터와 칭호를 매칭하는 브루트 포스를 사용하기엔 최대 연산 횟수 10^5 * 10^5 -> 100억!
 * 특정 전투력 '이하'까지 해당하는 칭호를 받을 수 있음
 * -> 이분 탐색
 *
 * 맵과 셋은 원소를 정렬된 상태로 저장하기 때문에 알고리즘 헤더 없이 자체적으로 이분 탐색 함수를 사용할 수 있음
 */
int main() {
    ios::sync_with_stdio(false); //입출력 속도 향상
    cin.tie(NULL);

    map<int, string> title; //칭호와 그 칭호의 전투력 상한값

    int n, m, power; //n: 칭호의 개수, m: 캐릭터의 개수, power: 전투력
    string name; //칭호

    //입력
    cin >> n >> m;
    while (n--) { //반복문 n번 동안
        cin >> name >> power; //칭호, 전투력 입력
        if (title[power].empty()) //전투력에 해당하는 칭호가 비어있다면
            title[power] = name; //칭호 입력
    }

    //출력
    while (m--) { //반복문 m번 동안
        cin >> power; //전투력 입력
        cout << title.lower_bound(power)->second << '\n'; //title에서 power보다 작은 첫번째 전투력의 칭호 출력
    }
}
