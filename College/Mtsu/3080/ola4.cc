/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
 * 					     				*
 * Author:	Timothy Beckett              				*
 * Instructor:	C. Pettey		     				*
 * Class:	CSCI 3080		     				*
 * Program:	Open Lab 4		     				*
 * Date Due:	12-06-05 		     				*
 * Purpose:	This program simulates a top secrect recording device   *
 * 		with directional capabilities.  It uses the finite      *
 *		state machine that I designed from open lab three and 	*
 *		a graphics program designed by Dr. Chrisila Pettey	*
 *		to do the simulation.  The objective this assignment 	*
 *		is to test my abilities in decoding hamming, grey, and 	*
 *		excess-3 codes.						*
 * 		First the hamming code packet is read from the file.	*
 *		It is then checked for transmission error and corrects	*
 *		as the hamming code as needed.  Next the grey code	*
 *		message is exstracted from the hamming code and trans-	*
 *		lated into a excess-3 binary code which is in turn	*
 *		translated into a binary number.  The next step is to	*
 *		turn tranmitted message into a charactor that can be	*
 *		used by the sprite program.  This is done using my FSM	*
 *		from lab three.						*
 *									*
 * * * * * * * * * * * * * * * * * * * * * *  * * * * * * * * * * * * * */
 
#include <X11/Xlib.h> // Every Xlib program must include this
#include <assert.h>   // I include this to test return values the lazy way
#include <unistd.h>   // So we got the profile for 10 seconds
#include <fstream>

using namespace std;

#define NIL (0)       // A name for the void pointer

//Name:  handleWindow
//Author:  Chrisila Pettey
//Purpose:  This function creates a static window of size 400 X 400 in which
//			an equilateral triangle is drawn initially pointing up.  The 
//			triangle is redrawn each time the function is called by either
//			rotating it left or right or inverting it from its previous
//			position in the window.
//Parameters:  One value parameter called direction.  If direction has a value
//			of 0, then there is no change in the position of the triangle.
//			A value of 1 will rotate the triangle 90 degrees clockwise.
//			A value of 2 will rotate the triangle 180 degrees.
//			A value of 3 will rotate the triangle 90 degrees counter clockwise.

void handleWindow(int direction)
{
	  static int calltime = 1;
      // Open the display

      static Display *dpy = XOpenDisplay(NIL);
	  if(calltime)
      	assert(dpy);

      // Get some colors

      static int blackColor = BlackPixel(dpy, DefaultScreen(dpy));
      static int whiteColor = WhitePixel(dpy, DefaultScreen(dpy));

      // Create the window

      static Window w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 
				     400, 400, 0, blackColor, blackColor);
	  static GC gc;
	  static XPoint points[4];
	  int oldx, oldy;
	  if(calltime){
		  //set calltime to 0 so initializations are not done again
		  calltime = 0; 

		  //initialize triangle coordinates
	  	  points[0].x = 200;
	  	  points[0].y = 10;
	  	  points[1].x = 10;
	  	  points[1].y = 390;
	  	  points[2].x = 390;
	  	  points[2].y = 390;
	  	  points[3].x = 200;
	  	  points[3].y = 10;

      // We want to get MapNotify events
      	  XSelectInput(dpy, w, StructureNotifyMask);

      // "Map" the window (that is, make it appear on the screen)
      	  XMapWindow(dpy, w);

      // Create a "Graphics Context"
      	  gc = XCreateGC(dpy, w, 0, NIL);

      // Tell the GC we draw using the white color
      	  XSetForeground(dpy, gc, whiteColor);

      // Wait for the MapNotify event
      	  for(;;) {
	    	  XEvent e;
	    	  XNextEvent(dpy, &e);
	    	  if (e.type == MapNotify)
		  	 	   break;
      	  }
	  	  // Create initial triangle

	  	  XDrawLines(dpy, w, gc, points, 4, CoordModeOrigin);
	  	  XFlush(dpy);
	  }

	  if(direction == 0){
      	  // Do nothing

      	  sleep(2);
	  }
	  else if(direction == 1){
	 	   //Clear the window to prepare for new drawing
	  	  XClearWindow(dpy, w);
	  	  XFlush(dpy);

		  //rotate coordinates right 90 degrees
		  for(int i = 0; i < 4; i++){
				oldx = points[i].x;
				oldy = points[i].y;
	  	  	    points[i].x = 400 - oldy;
	  	  	    points[i].y = oldx;
		  }
          // Draw the triangle
	  	  XDrawLines(dpy, w, gc, points, 4, CoordModeOrigin);

          // Send the "DrawLine" request to the server
          XFlush(dpy);

          // Wait for 2 seconds

          sleep(2);
	  }
	  else if(direction == 2){
	 	   //Clear the window to prepare for new drawing
	  	  XClearWindow(dpy, w);
	  	  XFlush(dpy);

		  //rotate coordinates right 90 degrees
		  for(int i = 0; i < 4; i++){
				oldx = points[i].x;
				oldy = points[i].y;
	  	  	    points[i].x = 400 - oldx;
	  	  	    points[i].y = 400 - oldy;
		  }
      	  // Draw the triangle
	  	  XDrawLines(dpy, w, gc, points, 4, CoordModeOrigin);

      	  // Send the "DrawLine" request to the server
      	  XFlush(dpy);

      	  // Wait for 2 seconds

      	  sleep(2);
	  }
	  else if(direction == 3){
	  	  //Clear the window to prepare for new drawing
	  	  XClearWindow(dpy, w);
	  	  XFlush(dpy);

		  //rotate coordinates left 90 degrees
		  for(int i = 0; i < 4; i++){
				oldx = points[i].x;
				oldy = points[i].y;
	  	  	    points[i].x = oldy;
	  	  	    points[i].y = 400 - oldx;
			}
      	  // Draw the triangle
	  	  XDrawLines(dpy, w, gc, points, 4, CoordModeOrigin);

      	  // Send the "DrawLine" request to the server
      	  XFlush(dpy);

      	  // Wait for 2 seconds

      	  sleep(2);
	  }
	  else {
		  // There is an error in the input parameter
		  // At the moment I choose to ignore errors in input
		  // and do nothing
		  sleep(2);
	  }
}


int main()
{
	char message[7], code;
	int error, oddBit, erchk;

	ifstream fin;
	char curr = ' ';
	int MACHINE[5][5] = {
	/*
	finite state machine definition
	{add, strip unwanted bits, confined to domain, state select modifier, output select value}
	*/
	{  0,   1, 1, 0, 0}, /*S0 -> no recognized input -- display triangle*/
	{107, 210, 4, 1, 0}, /*s1 -> k recognized -- do not move trianle*/
	{  0,   1, 1, 0, 1}, /*s2 -> l recognized -- rotate triangle 90 degrees clockwise*/
	{  0,   1, 1, 0, 2}, /*s3 -> i recognized -- invert triangle*/
	{  0,   1, 1, 0, 3}  /*s4 -> j recognized -- rotate triangle 90 degrees counter clockwise*/
	},
	state = 0;
	
	fin.open("test.dat");
	
	fin>>message[0];
	
	message[0] &=1;
	
	while(fin)
	{
		//retreaving coded word
		for(int i = 1; i < 7; ++i)
		{
			fin>>message[i];
			
		//stripping ascii bits
			message[i] &= 1;
		}

		//error checking
		error = 0;
		erchk = (message[3]+message[4]+message[5]+message[6])%2;
		error |= erchk;
		error <<= 1;
		
		erchk = (message[1]+message[2]+message[5]+message[6])%2;
		error |= erchk;
		error <<= 1;
		
		erchk = (message[0]+message[2]+message[4]+message[6])%2;
		error |= erchk; 
		
		//correcting erroneous bit if needed
		if(error)
			message[error-1] ^= 1;
			
		
		//translating grey code to binary

		oddBit = 0;
		code = 0;
		
		//gathering code bits
		code |= message[2]; 
		code <<= 1;
		code |= message[4];
		code <<= 1;
		code |= message[5];
		code <<= 1;
		code |= message[6];
		
		if(message[2] == 1) oddBit++;		
		if(oddBit%2) code ^= 4;	
		if(message[4] == 1) oddBit++;
		if(oddBit%2) code ^= 2;  
		if(message[5] == 1) oddBit++;
		if(oddBit%2) code ^= 1; 

		//end translation
		
		//word is now in excess-3
		
		code -= 3;
		
		//word is now in binary
		
		/*creating character
		
		char ascii transmitted value 
		'i'  69    9     
		'j'  6a    a (10)
		'k'  6b    b (11)
		'l'  6c    c (12)
		
		 therefore the char = code | 60 hex (96 base 10)
		*/
		curr = code | 96; 		
		
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
		 * determining next state											      *
		 * if current input equal to k then go to state 1 otherwise go to desired state					      *
		 * if in state one calculate the next state as follows:								      *
		 * state = {[(curr + 'k') mod 210] mod 4} + 1									      *
		 * 'i' = 105 base 10												      *
		 * 'j' = 106 base 10												      *
	 	 * 'k' = 107 base 10												      *
		 * 'l' = 108 base 10												      *
		 * in state 1 (which means that a k has all ready been encountered)						      *
		 * input i : [(i+k) mod 210] mod 4] = 2	note that these are the proper values to make the triangle rotate accordingly *
		 * input j : [(j+k) mod 210] mod 4] = 3	adding 1 to it tells us the state to switch to inorder to make this action    *
		 * input l : [(l+k) mod 210] mod 4] = 1	occur									      *
		 * input k : stay in state 1               									      *
		 * otherwise go to state 0 											      *
		 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
		((int)curr == 107) ? state = 1 : state = ((((int)curr + MACHINE[state][0]) % MACHINE[state][1]) % MACHINE[state][2]) + MACHINE[state][3];
		
		/* * * * * * * * * * * * * * * * * * * * * * * * *  *  
		 * handleWindow(int)				    *
		 * 0 -> display triangle			    *
		 * 1 -> rotate triangle 90 degrees clockwise	    *
		 * 2 -> invert triangle rotate triangle 180 degrees *
		 * 3 -> rotate triangle 90 degrees clockwise	    *
		 * invalid input is handled by the function	    *
		 * * * * * * * * * * * * * * * * * * * * * * * * *  */
		handleWindow(MACHINE[state][4]);
			
		fin>>message[0];
		
		message[0] &= 1;
	
	}
	
	fin.close();
	sleep(2);

	return 0;
}
