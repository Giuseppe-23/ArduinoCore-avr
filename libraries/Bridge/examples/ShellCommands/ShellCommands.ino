
/*
 Running shell coommands using Process class. 
 
 This sketch demonstrate how to run linux shell commands
 using an Arduino Yún. It runs the wifiCheck script on the linino side
 of the Yun, then uses grep to get just the signal strength line.
 Then it uses parseInt() to read the wifi signal strength as an integer,
 and finally uses that number to fade an LED using analogWrite().
 
 The circuit:
 * Arduino Yun with LED connected to pin 9
 
 created 12 Jun 2013
 by Cristian Maglie
 modified 25 June 2013
 by Tom Igoe
 
 This example code is in the public domain.
 
 */

#include <Process.h>

void setup() {
  // initialize the Bridge and Serial connections:
  Bridge.begin();
  Serial.begin(9600);
}

void loop() {
  Process p;
  // This command line runs the wifiCheck script, (lua /arduino/pretty...), then 
  // sends the result to the grep command to look for a line containing the word
  // "Signal:"  the result is passed to this sketch:
  p.runShellCommand("lua /arduino/pretty_wifi_info.lua | grep Signal");

  // do nothing until the process finishes, so you get the whole output:
  while(p.running());  

  // Read command output. runShellCommand() should have passed "Signal: xx&":
  while (p.available()) {
    int result = p.parseInt();                // look for an integer
    int signal = map(result, 0, 100, 0, 255); // map result from 0-100 range to 0-255
    analogWrite(9, signal);                   // set the brightness of LED on pin 9
    Serial.println(result);                   // print the number as well
  } 
  delay(5000);    // wait 5 seconds before you do it again
}



