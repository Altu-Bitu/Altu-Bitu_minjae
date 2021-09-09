import java.util.Arrays;
import java.util.Scanner; 


public class Main {
	
	public static boolean check() { 
		//알파벳 문자 배열 false로 초기화 
		boolean[] alpha = new boolean[26];
		Arrays.fill(alpha, false);
		
		//입력받은 문자열 문자 배열로 초기화 
		String str = sc.next(); 
		char[] array_word = new char[str.length()]; 
		for (int a = 0; a < str.length(); a++) {
			array_word[a] = (char)str.charAt(a); 
	
		}
	
		for(int i = 1; i < str.length() ; i++ ) {
			
			//앞뒤 문자가 다른 경우
			if(array_word[i] != array_word[i-1]) {
				if(alpha[array_word[i]-97] == true)
					return false;
				else if(alpha[array_word[i]-97]== false) {
					alpha[array_word[i]-97] = true; 
					alpha[array_word[i-1]-97] = true;
			}
			
		}
		}
			
		return true;
	}

	
	static Scanner sc = new Scanner(System.in);

	public static void main(String[] args) {
		
		int N = sc.nextInt(); //입력단어개수
		int CNT=0; //그룹단어개수
			
		 while(N>0) {
				if(check()) {
					N--; CNT++; 
				}
				else
					N--; 
			}
			System.out.println(CNT);
	}

}
