import java.util.Arrays;
import java.util.Scanner; 


public class Main {
	
	public static boolean check() { 
		//���ĺ� ���� �迭 false�� �ʱ�ȭ 
		boolean[] alpha = new boolean[26];
		Arrays.fill(alpha, false);
		
		//�Է¹��� ���ڿ� ���� �迭�� �ʱ�ȭ 
		String str = sc.next(); 
		char[] array_word = new char[str.length()]; 
		for (int a = 0; a < str.length(); a++) {
			array_word[a] = (char)str.charAt(a); 
	
		}
	
		for(int i = 1; i < str.length() ; i++ ) {
			
			//�յ� ���ڰ� �ٸ� ���
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
		
		int N = sc.nextInt(); //�Է´ܾ��
		int CNT=0; //�׷�ܾ��
			
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
