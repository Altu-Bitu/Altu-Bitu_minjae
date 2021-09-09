import java.util.Arrays;
import java.util.Scanner; 


public class Main {
	
	
	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in); 
		int N = sc.nextInt(); 
		int[] stu_array = new int [N]; //배열[강의실수][수용인원]
		
		for(int i = 0; i < N ; i++) { //강의실별 학생수 배열 초기화
			stu_array[i] = sc.nextInt(); 
			}
		
		int B = sc.nextInt();
		int C = sc.nextInt(); 
		
		long CNT = 0; //모든 감독관 수
		
		for(int i = 0; i < N; i++) {
			if(stu_array[i]-B <= 0) { //총감독관 1명이 감시할 수 있는 경우
				CNT++;  
				continue; 
			}
			else { //총감독관 1명이 감시하지 못할 경우 
				CNT++; 
				int TEMP = stu_array[i] - B; 
				int DIV = TEMP / C; 
				CNT = CNT + DIV;
				if((TEMP % C)!=0) {//나머지가 있다면
					CNT++; //부감독관 1명 추가
				}
			}
			}
		
		System.out.println(CNT);
		
		}
	}


