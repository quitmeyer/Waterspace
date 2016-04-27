//This code was written to be easy to understand.
//Code efficiency was not considered.
//Modify this code as you see fit.
//This code will output data to the Arduino serial monitor.
//Type commands into the Arduino serial monitor to control the pH circuit.
//This code was written in the Arduino 1.6.5 IDE
//An Arduino Mega was used to test this code.


String inputstringPH = "";                              //a string to hold incoming data from the PC
String sensorstringPH= "";                             //a string to hold the data from the Atlas Scientific product
boolean input_string_completePH= false;                //have we received all the data from the PC
boolean sensor_string_completePH= false;               //have we received all the data from the Atlas Scientific product
float pH;                                             //used to hold a floating point number that is the pH


void setup() {                                        //set up the hardware
  Serial.begin(9600);                                 //set baud rate for the hardware serial port_0 to 9600
  Serial2.begin(9600);                                //set baud rate for software serial port_3 to 9600
  inputstringPH.reserve(10);                            //set aside some bytes for receiving data from the PC
  sensorstringPH.reserve(30);                           //set aside some bytes for receiving data from Atlas Scientific product
}

void serialEvent() {                                  //if the hardware serial port_0 receives a char
  inputstringPH = Serial.readStringUntil(13);           //read the string until we see a <CR>
  input_string_completePH= true;                       //set the flag used to tell if we have received a completed string from the PC
}


void serialEvent2() {                                 //if the hardware serial port_3 receives a char
  sensorstringPH= Serial2.readStringUntil(13);         //read the string until we see a <CR>
  sensor_string_completePH= true;                      //set the flag used to tell if we have received a completed string from the PC
}


void loop() {                                         //here we go...


  if (input_string_completePH== true) {                //if a string from the PC has been received in its entirety
    Serial2.print(inputstringPH);                       //send that string to the Atlas Scientific product
    Serial2.print('\r');                              //add a <CR> to the end of the string
    inputstringPH = "";                                 //clear the string
    input_string_completePH= false;                    //reset the flag used to tell if we have received a completed string from the PC
  }


  if (sensor_string_completePH== true) {               //if a string from the Atlas Scientific product has been received in its entirety
    Serial.println(sensorstringPH);                     //send that string to the PC's serial monitor
    if (isdigit(sensorstringPH[0])) {                   //if the first character in the string is a digit
      pH = sensorstringPH.toFloat();                    //convert the string to a floating point number so it can be evaluated by the Arduino
      if (pH >= 7.0) {                                //if the pH is greater than or equal to 7.0
        Serial.println("high");                       //print "high" this is demonstrating that the Arduino is evaluating the pH as a number and not as a string
      }
      if (pH <= 6.99) {                               //if the pH is less than or equal to 6.99
        Serial.println("low");                        //print "low" this is demonstrating that the Arduino is evaluating the pH as a number and not as a string
      }
    }
  }
  sensorstringPH= "";                                  //clear the string:
  sensor_string_completePH= false;                     //reset the flag used to tell if we have received a completed string from the Atlas Scientific product
}


