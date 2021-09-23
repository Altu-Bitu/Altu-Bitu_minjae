#include <iostream>
#include <string>

using namespace std;

//자바 to c++ 함수
//c++ to 자바 함수
//언어 판단 함수

int java_or_cpp(string s){
    //'_'로 시작하거나 끝, 대문자 시작, 가운데 __ 연속일 경우 에러
    if(s[0] == '_' || s[s.length()-1]=='_' || s[0]<'a'){
        cout<<"Error!"<<"\n";
        return -1;
    }
}

int main() {
        string str;
        cin>>str;
        java_or_c(str);
}

