public class Course {
	public static void main(String args[]){
	Faculty instructor = new Faculty();
	Staff member = new Staff();
	Student studentInfo = new Student();

	instructor.setName(Stnd.getStr("Enter instructor name"));
	instructor.setAddress(Stnd.getStr("Enter street address"));
	instructor.setCity(Stnd.getStr("enter city to address"));
	instructor.setZip(Stnd.getStr("enter zip code to city"));
	instructor.setPhone(Stnd.getStr("enter phone number"));
	instructor.setEmail(Stnd.getStr("enter email address"));
	instructor.setOffice(Stnd.getStr("enter department"));
	instructor.setSalary(Stnd.getStr("enter salary"));
	instructor.setdateHired(Stnd.getStr("enter date hired"));
	instructor.setHours(Stnd.getStr("enter office hours"));
	instructor.setRank(Stnd.getStr("enter rank"));

	member.setName(Stnd.getStr("enter staff member's name"));
	member.setAddress(Stnd.getStr("Enter street address"));
	member.setCity(Stnd.getStr("enter city to address"));
	member.setZip(Stnd.getStr("enter zip code to city"));
	member.setPhone(Stnd.getStr("enter phone number"));
	member.setEmail(Stnd.getStr("enter email address"));
	member.setOffice(Stnd.getStr("enter department"));
	member.setSalary(Stnd.getStr("enter salary"));
	member.setdateHired(Stnd.getStr("enter date hired"));	
	member.setTitle(Stnd.getStr("enter staff members title"));

	studentInfo.setName(Stnd.getStr("Enter student name"));
	studentInfo.setAddress(Stnd.getStr("Enter street address"));
	studentInfo.setCity(Stnd.getStr("enter city to address"));
	studentInfo.setZip(Stnd.getStr("enter zip code to city"));
	studentInfo.setPhone(Stnd.getStr("enter phone number"));
	studentInfo.setEmail(Stnd.getStr("enter email address"));
	studentInfo.setClassStat(Stnd.getStr("enter student class"));

	Stnd.out("instructor:\n" + instructor.getName() + "\n" + instructor.getAddress() + "\n" + instructor.getCity() + "\n" + instructor.getZip()+"\n" + instructor.getPhone() + "\n" + instructor.getEmail() + "\n" + instructor.getOffice() + "\n" + instructor.getSalary() + "\n" + instructor.getdateHired() + "\n" + instructor.getHours() + "\n" + instructor.getRank());
	Stnd.out("Staff member:\n"+member.getName()+"\n"+member.getAddress()+"\n"+member.getCity()+"\n"+member.getZip()+"\n"+member.getPhone()+"\n"+member.getEmail()+"\n"+member.getOffice()+"\n"+member.getSalary()+"\n"+member.getdateHired()+"\n"+member.getTitle());
	Stnd.out("Student Information\n"+studentInfo.getName()+"\n"+studentInfo.getAddress()+"\n"+studentInfo.getCity()+"\n"+studentInfo.getZip()+"\n"+studentInfo.getPhone()+"\n"+studentInfo.getEmail()+"\n"+studentInfo.getClassStat());
	
	Sytem.exit(0);
	}
}