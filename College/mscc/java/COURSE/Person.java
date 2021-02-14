public class Person {
	
	public Person(){}
	public String getName(){
	return name;
	}
	public String getAddress(){
	return address;
	}
	public String getCity(){
	return city;
	}
	public String getZip(){
	return zip;
	}
	public String getPhone(){
	return phone;
	}
	public String getEmail(){
	return email;
	}
	public void setName(String temp){
	name = temp;
	}
	public void setAddress(String temp){
	address = temp;
	}
	public void setCity(String temp){
	city = temp;
	}
	public void setZip(String temp){
	zip = temp;
	}
	public void setPhone(String temp){
	phone = temp;
	}
	public void setEmail(String temp){
	email = temp;
	}
	
	private String name;
	private String address;
	private String city;
	private String zip;
	private String phone;
	private String email;
}