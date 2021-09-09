
import java.util.Arrays;
import java.util.Scanner; 
import java.util.Comparator; 


public class Main {
	
		
	public static void main(String[] args) {
	
		Scanner sc = new Scanner(System.in); 
		int N = sc.nextInt(); 
		int[][] arr = new int[N][2];
		
		for(int i=0; i<N; i++) {
			arr[i][0] = sc.nextInt(); 
			arr[i][1] = sc.nextInt(); 
		}
		
		Arrays.sort(arr, new Comparator<int[]>(){//Comparator �̿��� 2���� �迭 ����
				@Override
				public int compare(int[] a1,int[] a2) {
					if(a1[1] == a2[1]) return a1[0] - a2[0]; //y��ǥ ���� ���, x��ǥ ��, �������� 
					else return a1[1] - a2[1]; //y��ǥ �ٸ� ���, y��ǥ ��, ��������
				}
		   }
	    );
		
		for(int i=0; i<N; i++) {
			System.out.println(arr[i][0] + " " + arr[i][1]); 
		
	}
}
	
}




