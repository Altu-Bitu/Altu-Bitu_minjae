import java.util.*;


public class Main {
	
		
	public static void main(String[] args) {
	
		Scanner sc = new Scanner(System.in); 
		
		HashMap<String,Integer> map = new HashMap<>();
		int CNT = 0; 
		List<String> arr = new ArrayList<String>(); 
		
		while(sc.hasNextLine()) {
			String input = sc.nextLine(); 
			
			if(map.get(input) == null) {
				map.put(input, 1);
				arr.add(input); 
			}
			else {
				map.put(input, map.get(input) + 1); 
			}
			
			CNT++; 
		}
		
		for(String s : map.keySet())
					arr.add(s);
					
		
		Collections.sort(arr); 
		
		for(int i = 0; i < arr.size(); i++) {
			String tree = arr.get(i); 
			int NUM = map.get(tree); 
			double PER = (double)(NUM/CNT * 100); 
			System.out.println(tree + " " + String.format("%.4f", PER)); 
				
			
		}
		
	
}
	
}




