#include <iostream> //입출력
#include <vector> //벡터 사용

using namespace std;
typedef long long ll; //도시 사이 거리, 리터당 가격 범위 1,000,000,000까지이므로 정수 타입 long long 사용

ll greedyOil(vector<pair<ll, ll>> &city, int n) { //인자: 도시별 (다음 도시와의 거리, 기름값 정보), 도시 개수
    ll cur_cost = city[0].second, tot_cost = 0; //cur_cost: 저렴한 주유 가격 갱신, tot_cost: 총 비용

    for (int i = 0; i < n; i++) {//i:도시 번호
        if (city[i].second < cur_cost) //이 도시의 기름값이 더 저렴하면 교체
            cur_cost = city[i].second;//이 도시에서 기름값 지불
        tot_cost += (cur_cost * city[i].first); //이동 비용
    }
    return tot_cost; //총 비용 반환
}

/**
 * 1. 길이가 무제한인 호스가 있다고 가정
 * 2. 지금까지 지나온 도시 중 가격이 가장 저렴한 주유소와 호스를 연결한다
 * 3. 이번에 도착한 도시의 기름값이 지금 호스에 연결된 주유소의 기름값보다 저렴하다면 호스 교체
 *
 * 상세 풀이 : https://myunji.tistory.com/224
 */
int main() {
    int n; //도시 개수

    //입력
    cin >> n;
    vector<pair<ll, ll>> city(n, {0, 0}); //도시별 다음 도시와의 거리, 기름값 정보 저장
    for (int i = 0; i < n - 1; i++) //i: i:i~(i+1)번째 도시 간의 거리
        cin >> city[i].first; //다음 도시와의 거리
    for (int i = 0; i < n; i++) //i: 도시 번호
        cin >> city[i].second; //기름값 정보

    //연산 & 출력
    cout << greedyOil(city, n);
}

