

int ledout = 0;
int speaker = 1;
int ledpin = 2;
int sensor = A3;
double value = 0;
int calibrationavg=0;

//Audio
// Notes
const int Note_C  = 239;
const int Note_CS = 225;
const int Note_D  = 213;
const int Note_DS = 201;
const int Note_E  = 190;
const int Note_F  = 179;
const int Note_FS = 169;
const int Note_G  = 159;
const int Note_GS = 150;
const int Note_A  = 142;
const int Note_AS = 134;
const int Note_B  = 127;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(sensor, INPUT);
    pinMode(speaker, OUTPUT);
        pinMode(ledout, OUTPUT);

            pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, HIGH);   // turn the LED on (HIGH is the voltage level)


//calibration
int numofcalibrations=10;
 for(int i = 0; i<numofcalibrations;i++) {
    value = value +analogRead(sensor);
delay(10);
 }
 value=value/numofcalibrations;
calibrationavg=value;
}

// the loop function runs over and over again forever
void loop() {
  
  
  //value =constrain(map(analogRead(sensor),0,1023,0,255),1,255);
//invert
  value =constrain(map(calibrationavg - analogRead(sensor),0,1023,0,255),0,255);
//debugging
//value =0;
analogWrite(ledout,value);
//analogWrite(speaker,value);

//differnt range for music
    value =constrain(map(analogRead(sensor),calibrationavg,1023,5,200),5,250);

playTune(value);

}




void TinyTone(unsigned char divisor, unsigned char octave, unsigned long duration)
{
  TCCR1 = 0x90 | (8-octave); // for 1MHz clock
  // TCCR1 = 0x90 | (11-octave); // for 8MHz clock
  OCR1C = divisor-1;         // set the OCR
  delay(duration);
  TCCR1 = 0x90;              // stop the counter
}

// Play a scale
void playTune(int tempo)
{
 TinyTone(Note_C, 4, tempo);
 TinyTone(Note_D, 4, tempo);
// TinyTone(Note_E, 4, tempo);
 TinyTone(Note_F, 4, tempo);

}
