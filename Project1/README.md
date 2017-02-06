# OSys
Jacob Hamblen & Matt Baron
 
 Implemented function calls
 Reading strings
 Printing strings
 Reading ints
 Printing ints
  
  This can be verified booting up our program in bochs
   
	In the readString function we have backspace functionality which moves the cursor back and also removes the last character.  In main we have test functions for read/print string.  Read/print int.  We also changed the color.  
	We also implemented handleInterrupt21 which does exactly as the name says.  It gets passed multiple ints which indicate the registers and the type of interrupt that is being used.  From that the needed function is called from the list above.
