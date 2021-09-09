
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

		if(a.length() == b.length()) {//���̰� ������� 
			
			int SUM1 = integer_sum(a); 
			int SUM2 = integer_sum(b); 
			
			if(SUM1 == SUM2) //������ ���� ���
				return a.compareTo(b); 
			else //������ �ٸ� ���
				return SUM1 - SUM2; 
			}
		else {
			return a.length() - b.length(); 
		}
	
	}
	
	public static void main(String[] args) {
		
		//���� ª�� �ͺ���
		//���� ������ �ڸ��� �� ��
		//������ ��
		
		Scanner sc = new Scanner(System.in); 
		int N = sc.nextInt(); 
		String[] snum = new String[N]; 
		for(int i=0; i<N; i++) {
			snum[i] = sc.next();
		}
		
		//�������� ���
		for(int i=0; i<N; i++) {
			for(int j=0; j<N-i-1; j++) {
				if(compare(snum[j], snum[j+1])>0) { //snum[j]�� snum[j+1]���� ũ�ٸ�
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




