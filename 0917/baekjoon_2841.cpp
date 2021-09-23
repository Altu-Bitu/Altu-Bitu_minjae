#include <iostream>
#include <stack>

using namespace std;

int main() {
    //입출력 속도 향상
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N;
    int P;

    cin >> N >> P;
    int CNT = 0;
    stack<int> stk[7];

    for(int i=0; i<N; i++)
    {
        int S; //줄
        int F; //프랫

        cin >> S >> F;

        if(stk[S].empty()) //줄을 누르고 있는 손가락이 없을 경우
        {
            CNT++;
            stk[S].push(F);
        }
        else{ //줄을 누르고 있는 손가락이 있을 경우

            if(F > stk[S].top()) { //입력 프랫이 이전 프랫보다 높을 경우
                stk[S].push(F);
                CNT++;
            }

            else if(F < stk[S].top()){//입력 프랫이 이전 프랫보다 낮을 경우
                while(F < stk[S].top() && !stk[S].empty())//더 낮은 프랫을 만날 때까지 손가락을 차례로 뗀다
                {
                    stk[S].pop();
                    CNT++;
                }
                if(!stk[S].empty() && F == stk[S].top())//같은 높이의 프랫일 경우
                    continue; //변화 없이 다음 입력으로

                stk[S].push(F);
                CNT++;
            }

            else if(F == stk[S].top())//같은 높이의 프랫일 경우
                continue; //변화 없이 다음 입력으로
        }
    }

    cout << CNT << "\n";
    return 0;
}
