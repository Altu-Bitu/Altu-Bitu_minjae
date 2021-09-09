
import java.util.Arrays;
import java.util.Scanner; 


public class Main {
	
	public static int integer_sum(String a) {
		int SUM = 0; 
		for(int i=0; i<a.length(); i++) {
			if(a.charAt(i) <= '9' && a.charAt(i)>='0') 
				SUM +=  a.charAt(i)-'0'; 
		}
		return SUM; 
	}

	public static int compare(String a, String b){

		if(a.length() == b.length()) {//길이가 같을경우 
			
			int SUM1 = integer_sum(a); 
			int SUM2 = integer_sum(b); 
			
			if(SUM1 == SUM2) //숫자합 같을 경우
				return a.compareTo(b); 
			else //숫자합 다를 경우
				return SUM1 - SUM2; 
			}
		else {
			return a.length() - b.length(); 
		}
	
	}
	
	public static void main(String[] args) {
		
		//길이 짧은 것부터
		//길이 같으면 자리수 합 비교
		//사전순 비교
		
		Scanner sc = new Scanner(System.in); 
		int N = sc.nextInt(); 
		String[] snum = new String[N]; 
		for(int i=0; i<N; i++) {
			snum[i] = sc.next();
		}
		
		//버블정렬 사용
		for(int i=0; i<N; i++) {
			for(int j=0; j<N-i-1; j++) {
				if(compare(snum[j], snum[j+1])>0) { //snum[j]가 snum[j+1]보다 크다면
					String temp = snum[j+1];
					snum[j+1] = snum[j]; 
					snum[j] = temp;
				}
			}
		}
		 
		for(int i=0; i<N; i++) {
			System.out.println(snum[i]); 
		}
		
		
	}
}




