public class Student extends Person {
	public Student(){}
	public String getClassStat(){
	return classStatus;
	}
	public void setClassStat(String temp){
	classStatus = temp;
	}
	
	private String classStatus;/* classifactions
					freshman
					sophomore
					junior
					senior
				   */
}