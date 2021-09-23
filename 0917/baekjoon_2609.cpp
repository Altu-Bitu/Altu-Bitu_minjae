#include <iostream>
#include <vector>

using namespace std;

int gcdRecursion(int a, int b) {
    if (b == 0)
        return a;
    return gcdRecursion(b, a % b);
}

int main(){
    int T;
    cin >> T;

    for(int i=0; i<T; i++){

        long long SUM = 0;
        int N;
        cin >> N;

        vector<int> vt(N);
        for(int j=0; j<N; j++)
            cin >> vt[j];
        for(int j=0; j<N-1;j++){
            for(int k=j+1; k<N; k++)
                SUM += gcdRecursion(vt[j], vt[k]);
        }
        cout << SUM << "\n";
    }
    return 0;
}

