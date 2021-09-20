#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main(void){

    ios_base::sync_with_stdio(0);
    cin.tie(0); // c의 stdio와 cpp의 iostream 동기화 비활성화

    bool checked[21];
    int I;
    int M;
    cin >> M;

    for(int i=0; i<M; i++){

        string str;
        cin >> str;

        if(str == "add")
        {
            cin >> I;
            checked[I] = true;
        }
        else if(str == "remove"){
            cin >> I;
            checked[I] = false;
        }
        else if(str == "check"){
            cin >> I;
            if(checked[I])
                cout << 1 << "\n"; //시간 초과 주의 : endl는 개행 문자 출력과 함께 출력 버퍼를 비워져서 딜레이 발생
            else
                cout << 0 << "\n";
        }
        else if(str == "toggle"){
            cin >> I;
            if(checked[I] == true)
                checked[I] = false;
            else
                checked[I] = true;
        }
        else if (str == "all"){
            memset(checked, true, 21);
        }
        else
           memset(checked, false, 21);
    }
    return 0;

}

