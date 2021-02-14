/*
Class Name:	TestFan.class
Programmer:	Tim Beckett
function:	This class creates an object of the class Fan and it let's change private
		variables inside that object using object methods
other
classes
used:		Stnd.class
		Fan.class
inputs:		na
outputs:	popup box of the object's specs.
*/

public class TestFan {
	
	public static void main(String args[]) {
	Fan myFan = new Fan();
	myFan.setSpeed(myFan.HI);
	myFan.setColor("yellow");
	myFan.setOn(true);
	myFan.setRadius(10);
	Stnd.out("My Fan Specs: \n Speed = "+myFan.getSpeed()+"\n status = "+myFan.isOn()+"\n Color = "+myFan.getColor()+"\n Radius = "+myFan.getRadius());
	System.exit(0);
	}
}