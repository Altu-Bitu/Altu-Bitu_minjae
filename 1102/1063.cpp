#include <iostream>
#include <string>

using namespace std;

int main(){
    int n;
    string king, stone;
    int k[2];
    int s[2];
    cin >> king >> stone >> n;

    //체스판 열 정수 변환
    k[0] = king[0] - 'A';
    k[1] = king[1] - '1';
    s[0] = stone[0] - 'A';
    s[1] = stone[1] - '1';

    string a;
    //n번 이동 시 주의: 체스판 밖 이동 or 돌과 같은 위치
    //1. 체스판 밖 범위인지 확인
    //2. 돌과 같은 위치인지 확인
        //2-1.같은 위치라면 돌은 킹과 같은 방향으로 이동
            //2-2.이동할 경우 체스판 밖 범위인지 확인
    while(n--){
        cin >> a;
        if(a.size()==1 && a[0]=='R'){//한 칸 오른쪽: 행 +1 열 그대로
            if( (k[0]+1)>7 or (k[0]+1)<0) //이동했을 경우(이동 실행 x) 킹의 위치가 체스판 밖이라면
                continue; //그 다음으로 이동
            if(++k[0] == s[0] && k[1] == s[1]) { //이동 실행시 킹과 돌이 같은 위치라면
                ++s[0];  //돌은 킹과 같은 방향으로 이동
                if(s[0]>7 or s[0]<0) { //이동한 돌이 체스판 밖 범위라면 이동 무르기
                    --k[0];
                    --s[0];
                    continue;
                }
            }
            continue; //시간 단축
        }

        else if(a.size()==1 && a[0]=='L'){
            if( (k[0]-1)>7 or (k[0]-1)<0) //이동했을 경우(이동 실행 x) 킹의 위치가 체스판 밖이라면
                continue; //그 다음으로 이동
            if(--k[0] == s[0] && k[1] == s[1]) { //이동 실행시 킹과 돌이 같은 위치라면
                --s[0];  //돌은 킹과 같은 방향으로 이동
                if(s[0]>7 or s[0]<0) { //이동한 돌이 체스판 밖 범위라면 이동 무르기
                    ++k[0];
                    ++s[0];
                    continue;
                }
            }
            continue; //시간 단축
        }
        else if(a.size()==1 && a[0]=='B'){
            if( (k[1]-1)>7 or (k[1]-1)<0) //이동했을 경우(이동 실행 x) 킹의 위치가 체스판 밖이라면
                continue; //그 다음으로 이동
            if(--k[1] == s[1] && k[0] == s[0]) { //이동 실행시 킹과 돌이 같은 위치라면
                --s[1];  //돌은 킹과 같은 방향으로 이동
                if(s[1]>7 or s[1]<0) { //이동한 돌이 체스판 밖 범위라면 이동 무르기
                    ++k[1];
                    ++s[1];
                    continue;
                }
            }
            continue; //시간 단축
        }

        else if(a.size()==1 && a[0]=='T'){
            if( (k[1]+1)>7 or (k[1]+1)<0) //이동했을 경우(이동 실행 x) 킹의 위치가 체스판 밖이라면
                continue; //그 다음으로 이동
            if(++k[1] == s[1] && k[0] == s[0]) { //이동 실행시 킹과 돌이 같은 위치라면
                ++s[1];  //돌은 킹과 같은 방향으로 이동
                if(s[1]>7 or s[1]<0) { //이동한 돌이 체스판 밖 범위라면 이동 무르기
                    --k[1];
                    --s[1];
                    continue;
                }
            }
            continue; //시간 단축
        }

        else if(a.size()==2 && a[0] == 'R' && a[1] =='T'){
            if( (k[1]+1)>7 or (k[1]+1)<0 or (k[0]+1)>7 or (k[0]+1)<0 ) //이동했을 경우(이동 실행 x) 킹의 위치가 체스판 밖이라면
                continue; //그 다음으로 이동
            if(++k[1] == s[1] && ++k[0] == s[0]) { //이동 실행시 킹과 돌이 같은 위치라면
                ++s[1];  //돌은 킹과 같은 방향으로 이동
                ++s[0];
                if(s[1]>7 or s[1]<0 or s[0]>7 or s[0]<0) { //이동한 돌이 체스판 밖 범위라면 이동 무르기
                    --k[1];
                    --k[0];
                    --s[1];
                    --s[0];
                    continue;
                }
            }
            continue; //시간 단축

        }
        else if(a.size()==2 && a[0] == 'L' && a[1] =='T'){ //열[0]은 -1, 행[1]은 +1
            if( (k[0]-1)>7 or (k[0]-1)<0 or (k[1]+1)>7 or (k[1]+1)<0 ) //이동했을 경우(이동 실행 x) 킹의 위치가 체스판 밖이라면
                continue; //그 다음으로 이동
            if(--k[0] == s[0] && ++k[1] == s[1]) { //이동 실행시 킹과 돌이 같은 위치라면
                --s[0];  //돌은 킹과 같은 방향으로 이동
                ++s[1];
                if(s[0]>7 or s[0]<0 or s[1]>7 or s[1]<0) { //이동한 돌이 체스판 밖 범위라면 이동 무르기
                    ++k[0];
                    --k[1];
                    ++s[0];
                    --s[1];
                    continue;
                }
            }
            continue; //시간 단축
        }

        else if(a.size()==2 && a[0] == 'R' && a[1] =='B'){ //열[0]은 +1, 행[1]은 -1
            if( (k[0]+1)>7 or (k[0]+1)<0 or (k[1]-1)>7 or (k[1]-1)<0 ) //이동했을 경우(이동 실행 x) 킹의 위치가 체스판 밖이라면
                continue; //그 다음으로 이동
            if(++k[0] == s[0] && --k[1] == s[1]) { //이동 실행시 킹과 돌이 같은 위치라면
                ++s[0];  //돌은 킹과 같은 방향으로 이동
                --s[1];
                if(s[0]>7 or s[0]<0 or s[1]>7 or s[1]<0) { //이동한 돌이 체스판 밖 범위라면 이동 무르기
                    --k[0];
                    ++k[1];
                    --s[0];
                    ++s[1];
                    continue;
                }
            }
            continue; //시간 단축
        }

        else if(a.size()==2 && a[0] == 'L' && a[1] =='B'){ //행[0]은 -1, 열[1]은 -1
            if( (k[1]-1)>7 or (k[1]-1)<0 or (k[0]-1)>7 or (k[0]-1)<0 ) //이동했을 경우(이동 실행 x) 킹의 위치가 체스판 밖이라면
                continue; //그 다음으로 이동
            if(--k[1] == s[1] && --k[0] == s[0]) { //이동 실행시 킹과 돌이 같은 위치라면
                --s[1];  //돌은 킹과 같은 방향으로 이동
                --s[0];
                if(s[1]>7 or s[1]<0 or s[0]>7 or s[0]<0) { //이동한 돌이 체스판 밖 범위라면 이동 무르기
                    ++k[1];
                    ++k[0];
                    ++s[1];
                    ++s[0];
                    continue;
                }
            }
            continue; //시간 단축
        }

    }

    king[0] = k[0] + 'A';
    king[1] = k[1] + '1';
    stone[0] = s[0] + 'A';
    stone[1] = s[1] + '1';

    //다시 문자열 변환
    cout << king[0] << king[1] << '\n';
    cout << stone[0] << stone[1] << '\n';

    return 0;
}