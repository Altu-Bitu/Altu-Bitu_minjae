#include <iostream>
#include <vector>
#include <deque>

using namespace std;

//그라운드에 있는 카드를 덱으로 옮기는 함수
void moveCard(deque<int> &deck, deque<int> &ground) { //인자: 덱 정보, 그라운드 정보
    while (!ground.empty()) {//그라운드가 비어 있지 않다면
        deck.push_back(ground.back());//덱 아래에 합치기
        ground.pop_back();//그라운드에서 옮겨진 카드 정보 제거
    }
}

//게임을 진행하는 함수
pair<int, int> playGame(int m, vector<deque<int>> &deck, vector<deque<int>> &ground) { //인자: 게임 진행 횟수, 덱 정보, 그라운드 정보
    bool turn = false; //도도부터 시작 : 0

    while (m--) { //카드 진행 횟수만큼 반복문 돌면서
        //이번 턴의 사람이 카드 뒤집어서 그라운드에 올려놓기
        int card = deck[turn].front(); //0이면 도도, 1이면 수연
        ground[turn].push_front(card);//그라운드에 놓은 카드 그라운드에 추가
        deck[turn].pop_front();//그라운드에 놓은 카드 덱에서 제거

        //게임 진행 도중 둘 중 한 명의 덱에 있는 카드의 수가 0개가 되는 즉시 게임 종료
        if (deck[turn].empty())
            break; //게임 종료하기 위해 반복문 탈출

        //이번에 종을 칠 사람
        int bell = -1;
        if (card == 5) //카드 숫자가 5라면
            bell = 0;//도도가 종치기
            // 도도와 수연의 그라운드에 카드가 존재하고, 카드 더미 위의 숫자 합이 5라면
        else if (!ground[0].empty() && !ground[1].empty() && (card + ground[!turn].front() == 5))
            bell = 1; //수연이 종치기

        if (bell != -1) { //누군가가 종을 쳤다면
            moveCard(deck[bell], ground[!bell]); //도도 승리일 경우 (deck[0],ground[1]) 인자 전달, 수연 승리일 경우 (deck[1],ground[0]) 인자 전달
            moveCard(deck[bell], ground[bell]); //도도 승리일 경우 (deck[0],ground[0]) 인자 전달, 수연 승리일 경우 (deck[1],ground[1]) 인자 전달
        }
        turn = !turn; //차례 바꾸기
    }
    return make_pair(deck[0].size(), deck[1].size()); //도도의 덱 카드 개수, 수연의 덱 카드 개수 쌍 반환
}

/**
 * 1. 카드 덱과 그라운드의 카드를 관리하기 위해 덱 사용
 * 2. 게임을 진행하던 도중 언제든지 누군가의 카드 덱이 비게되면 게임을 종료
 */
int main() {
    int n, m, num1, num2; //n: 카드의 개수, m: 게임 진행 횟수, num1: 도도의 카드 번호, num2:수연의 카드 번호
    vector<deque<int>> deck(2), ground(2); //도도와 수연의 덱,그라운드 정보 저장

    cin >> n >> m; //카드의 개수, 게임 진행 횟수 입력
    while (n--) { //카드의 개수만큼 반복문 돌면서
        cin >> num1 >> num2; //도도의 카드 번호, 수연의 카드 번호 입력
        deck[0].push_front(num1);//도도의 덱에 존재하는 카드 번호 삽입
        deck[1].push_front(num2);//수연의 덱에 존재하는 카드 번호 삽입
    }

    pair<int, int> result = playGame(m, deck, ground); //각각 덱에 남은 카드 개수 결과 받아오기

    if (result.first == result.second) //같다면
        cout << "dosu\n"; //무승부
    else if (result.first > result.second)//도도 쪽이 더 많다면
        cout << "do\n"; //도도 승리
    else if (result.first < result.second)//수연 쪽이 더 많다면
        cout << "su\n"; //수연 승리
}

