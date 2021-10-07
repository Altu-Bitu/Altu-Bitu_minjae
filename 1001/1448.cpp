#include <iostream>
#include <algorithm>

using namespace std;

int line[1000000];

int main(){

    cin.tie(0);
    cin.sync_with_stdio(false);

    int n;
    cin >> n;
    for(int i=0; i<n; i++)
        cin >> line[i];

    sort(line,line+n);

    for(int i=n-1; i>1; i--){
        int a = line[i-2];
        int b= line[i-1];
        int c = line[i];
        if(c < a+b){
            cout << a+b+c;
            return 0;
        }
    }
    cout<< -1;
    return 0;
}

