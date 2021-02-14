public class Employee extends Person{

	public String getOffice(){
	return office;
	}
	public String getSalary(){
	return salary;
	}
	public String getdateHired(){
	return dateHired;
	}
	public void setOffice(String temp){
	office = temp;
	}
	public void setSalary(String temp){
	salary = temp;
	}
	public void setdateHired(String temp){
	dateHired = temp;
	}
	

	private String office;
	private String salary;
	private String dateHired;
	}