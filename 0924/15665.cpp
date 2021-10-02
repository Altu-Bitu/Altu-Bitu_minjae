#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int SIZE = 8;

int n, m, num;
vector<int> v;
int arr[SIZE];
bool check[SIZE+1];

void bt(int cnt) {
    if (cnt == m) {
        for (int i = 0; i < m; i++)
            cout << arr[i] << " ";
        cout << "\n";
        return;
    }
    for(int i=0; i<v.size(); i++)
    {
        arr[cnt] = v[i];
        bt(cnt+1);
    }
}
    int main(){
        cin >> n >> m;
        for(int i=0; i<n; i++) {
            cin >> num;
            if(!check[num]) {
                v.push_back(num);
                check[num] = true;
            }
        }
        sort(v.begin(), v.end());
        bt(0);
    }




