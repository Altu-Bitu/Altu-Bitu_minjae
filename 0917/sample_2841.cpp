#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/**
 * 각 줄마다 외계인이 누르고 있는 프렛을 스택에 저장하기
 * 매 입력에 대해 이번에 누를 프렛이 해당 줄에서 가장 높은 프렛이어야 함
 *
 * 1. 이번에 눌러야 할 프렛보다 높은 프렛에서 손가락을 전부 떼기
 * 2. 만약 이번에 눌러야 할 프렛을 누르고 있지 않다면 누르기
 */
int main() {
    int n, p, guitar_string, fret, ans = 0;

    cin >> n >> p; //n:음의 수, p:프랫의 수
    vector<stack<int>> guitar(7); //1번 줄부터 6번줄 까지
    while (n--) {
        //입력
        cin >> guitar_string >> fret; //guitar_string:줄 번호, fret: 프랫 번호

        //연산
        //줄을 누르는 손가락이 있는 상태 && 입력 프렛이 이전 프렛(스택의 top)보다 낮은 경우
        while (!guitar[guitar_string].empty() && guitar[guitar_string].top() > fret) {
            ans++; //프렛에서 손가락 떼기
            guitar[guitar_string].pop(); //손가락 뗀 프렛 스택에서 삭제
        }

        //줄을 누르고 있지 않은 상태거나 같은 높이의 프랫이 아니라면(->위의 반복문 검사로 스택의 top은 낮은 프렛이 됨)
        if (guitar[guitar_string].empty() || guitar[guitar_string].top() != fret) {
            ans++; //프렛 누르기
            guitar[guitar_string].push(fret); //눌러야 하는 프렛 스택에 추가
        }
    }

    //출력
    cout << ans;
}

