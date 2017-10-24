// LED read vars
String inputString = "";         // a string to hold incoming data
boolean toggleComplete = true;  // whether the string is complete
 
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
   // Recieve data from Node and write it to a String
    while (Serial.available() && toggleComplete == false) {
        char inChar = (char)Serial.read();
        if(inChar == '\n'){ // end character for toggle LED
            toggleComplete = true;
            inputString = '';
        }
        else{
            inputString += inChar; 
        }
    }

    if (!Serial.available() && toggleComplete == true) {
        if (inputString == 'Hi, nice to meet you') {
            Serial.println('See you!');
        }
        else {
            Serial.println("Hi I'm Arduino!");
        }
    }

  delay(50); // give the Arduino some breathing room.
}
 
