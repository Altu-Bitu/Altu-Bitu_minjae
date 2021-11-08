//
// Created by iw040 on 2021-10-12.
//

#include <iostream> //입출력 사용
#include <string> //문자열 사용
#include <vector> //벡터 사용
#include <map> //맵 사용 - key, value 쌍으로 저장 용도
#include <set> //셋 사용 - 중복 없이 저장하려는 용도

using namespace std;

//시간복잡도 O(n^2) -> 정확성 O, 효율성 X
vector<int> gemList(vector<string> &gems, int gem_size) {
    int size = gems.size();
    vector<int> ans = {1, size};

    for (int i = 0; i < size; i++) { //i로 시작하는 구간
        map<string, int> m; //구간에 있는 보석
        for (int j = i; j < size; j++) { //j에서 끝나는 구간
            m[gems[j]]++; //보석 추가
            if (m.size() == gem_size) { //모든 종류의 보석이 있음
                if (j - i < ans[1] - ans[0]) //최단 구간 갱신
                    ans = {i + 1, j + 1};
                break; //더이상 구간을 늘릴 필요 없음
            }
        }
    }
    return ans;
}

//시간복잡도 O(n) -> 정확성 O, 효율성 O
vector<int> gemListTwoPointer(vector<string> &gems, int gem_size) {//&gems: 보석 종류, gem_size: 보석 사이즈
    int left = 0, right = 0, size = gems.size(); //left&right: 투포인터, size: 보석 종류
    vector<int> ans = {1, size}; //1,size: 구간의 처음과 끝 인덱스를 의미
    map<string, int> m; //
    m[gems[left]]++; //초기 구간

    //left는 항상 right의 왼쪽 또는 같은 위치에 있어야 함
    while (left <= right && right < size) { //right가 left보다 왼쪽에 있게 되면 반복문 탈출 =
        if (m.size() == gem_size) { //모든 종류의 보석이 있음
            if (right - left < ans[1] - ans[0]) //최단 구간 갱신
                ans = {left + 1, right + 1}; //벡터 인덱스는 0부터 시작하므로 left, right 인덱스값 모두 +1씩
            left++; //구간을 짧게하기 위해 left 이동
            m[gems[left - 1]]--; //구간 줄여서 검사
            if (m[gems[left - 1]] == 0) //더이상 이 보석이 없다면 제거
                m.erase(gems[left - 1]); //제거
        } else if (m.size() < gem_size) { //모든 종류의 보석이 있는게 아니라면
            right++; //구간을 길게하기 위해 right 이동
            if (right == size) //런타임 에러 방지
                break; //right==size라면 인덱스 초과 방지 위해 반복문 탈출
            m[gems[right]]++; //구간 늘려서 검사
        }
    }
    return ans; //출력될 정답 (구간의 시작, 끝 인덱스) 반환
}

vector<int> solution(vector<string> gems) { //gems: 보석 이름 배열
    vector<int> answer; //모든 종류의 보석을 포함하는 구간

    set<string> unique_gem; //보석 이름
    for (int i = 0; i < gems.size(); i++)//i: i번째 보석
        unique_gem.insert(gems[i]); //보석 이름 삽입
    int gem_size = unique_gem.size(); //보석의 종류

    answer = gemListTwoPointer(gems, gem_size);
    return answer;
}

int main() {
    //입력
    vector<string> gems = {"DIA", "RUBY", "RUBY", "DIA", "DIA", "EMERALD", "SAPPHIRE", "DIA"};

    //연산
    vector<int> ans = solution(gems);

    //출력
    cout << ans[0] << ' ' << ans[1];
}