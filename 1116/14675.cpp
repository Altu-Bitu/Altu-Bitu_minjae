#include <iostream>

using namespace std;

//단절점: 리프노드 아닌 노드
//단절선: 모든 간선
int main() {
    ios_base :: sync_with_stdio(false); //없으면 시간 초과
    cin.tie(NULL);

    int n,a,b,q,t,k;
    cin >> n;

    int tree[100001] = {0, };
    for(int i=0; i<n-1; i++){ //n 아니고 n-1 주의
            cin >> a >> b;
            tree[a]++;
            tree[b]++;
    }

    cin >> q;
   while(q--){
        cin >> t >> k;

        if (t==1){
            if(tree[k] >= 2){
                cout << "yes" << '\n';
            }
            else
                cout << "no" << '\n';
        }
        else{
            cout << "yes" << '\n';
        }
    }

    return 0;
}
