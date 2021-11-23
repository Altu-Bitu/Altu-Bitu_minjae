//참고 링크
//https://gywlsp.github.io/boj/5639/
//https://ongveloper.tistory.com/295

//미해결

#include <iostream>
#include <vector>

using namespace std;

vector<int> tree;

//입력 결과 -> 루트/왼트리/오른트리
//왼트리 -> 루트/왼트리/오른트리 (재귀 반복)
//오른트리 -> 루트/왼트리/오른트리 (재귀 반복)
//루트 출력
void recur(int s, int e){
    int root = tree[s];
    int p;
    if (s > e)
        return;
    else{
        for(int i=s+1 ; i< e+1; i++){
            if(tree[s] < tree[i])
                p = i;
                break;
        }
    }

    recur(s+1, p-1);
    recur(p, e);
    cout << root << '\n';

}

int main(){
    int n;
    int i = 0;
    while(cin >> n){
            tree.push_back(n);
    }

    recur(0, i-1);
    return 0;
}


