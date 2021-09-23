#include <iostream>

using namespace std;

int factorial(int N){

    if(N == 0 || N == 1){
        return 1;
    }
    else
        return factorial(N-1)*N;
}

int main(void){

    int N,K;
    cin >> N >> K;
    cout << factorial(N)/(factorial(K)*factorial(N-K));
    return 0;
}

