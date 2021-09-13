
import java.util.*;


public class Main {
	
		
	public static void main(String[] args) {
	
		Scanner sc = new Scanner(System.in); 
		
		long N = sc.nextInt(); 
		long M = sc.nextInt(); 
		String str; 
		
		ArrayList<String> arr1 = new ArrayList<String>(); 
		ArrayList<String> arr2 = new ArrayList<String>(); 
		
		sc.nextLine();
		
		for(int i=0; i<N; i++) {
			arr1.add(sc.nextLine());
		}
		
		Collections.sort(arr1);
		String[] str1 = new String[arr1.size()]; 
		str1 = arr1.toArray(str1); 
		
		for(int i=0; i<M; i++) {
			str = sc.nextLine(); 
			arr2.add(sc.nextLine());
			int IDX = Arrays.binarySearch(str1, str); 
			if(IDX >= 0) {
				arr2.add(str); 
			}
		}
		
		Collections.sort(arr2);
		System.out.println(arr2.size()); 
		for(String s : arr2) {
			System.out.println(s);
		}
	
}
	
}




