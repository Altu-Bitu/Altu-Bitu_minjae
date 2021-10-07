#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 1000000000
long long dist[MAX]; //dist[0]: 1-2번째 도시 간의 거리
long long cost[MAX]; //cost[0]: 1번째 도시에서의 주유 가격

int main(){
    long long n;
    long long SUM=0; //총 비용
    long long temp; //저렴한 주유 가격 갱신

    cin >> n;

    for(int i=1; i<n; i++){ //i:i-(i+1)번째 도시 간의 거리
        cin >> dist[i];
    }
    for(int i=0; i<n; i++){
        cin >> cost[i];
    }

    temp = cost[0];

    for(int i=0; i<n-1; i++) {

        if (temp > cost[i]) {
            SUM += temp * dist[i];
        } else {
            temp = cost[i];
            SUM += temp * dist[i];
        }

    }

    cout << SUM;
    return 0;
}
