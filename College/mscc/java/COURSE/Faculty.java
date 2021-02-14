public class Faculty extends Employee {
	public Faculty(){}
	public String getHours(){
	return officeHours;
	}
	public String getRank(){
	return rank;
	}
	public void setHours(String temp){
	officeHours = temp;
	}
	public void setRank(String temp){
	rank = temp;
	}

	private String officeHours;
	private String rank;
	
}