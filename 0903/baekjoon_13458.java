import java.util.Arrays;
import java.util.Scanner; 


public class Main {
	
	
	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in); 
		int N = sc.nextInt(); 
		int[] stu_array = new int [N]; //�迭[���ǽǼ�][�����ο�]
		
		for(int i = 0; i < N ; i++) { //���ǽǺ� �л��� �迭 �ʱ�ȭ
			stu_array[i] = sc.nextInt(); 
			}
		
		int B = sc.nextInt();
		int C = sc.nextInt(); 
		
		long CNT = 0; //��� ������ ��
		
		for(int i = 0; i < N; i++) {
			if(stu_array[i]-B <= 0) { //�Ѱ����� 1���� ������ �� �ִ� ���
				CNT++;  
				continue; 
			}
			else { //�Ѱ����� 1���� �������� ���� ��� 
				CNT++; 
				int TEMP = stu_array[i] - B; 
				int DIV = TEMP / C; 
				CNT = CNT + DIV;
				if((TEMP % C)!=0) {//�������� �ִٸ�
					CNT++; //�ΰ����� 1�� �߰�
				}
			}
			}
		
		System.out.println(CNT);
		
		}
	}


