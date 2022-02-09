#define a 700 //Width of first pulse, 7x100
#define b 500 // Width space between pulses
#define c 17 // Number of pulses in a block
#define d 6500 // Space between pulse blocks
#define WaveformCycle 27750 // Length of each waveform cycle



#define RedLED 15// insert red pin number
#define GreenLED 21//insert green pin number
#define switch1 23 //insert switch1 pin
#define switch2 22//insert switch2 pin

// Variables that will change
int GreenLEDState = LOW;
int RedLEDState=LOW;
int Switch1Setting=0;
int Switch2Setting=0;
int Switch1State=0;
int Switch2State=0;

unsigned long previousMicros = 0;        // will store last time LED was updated
unsigned long PreviousMicrosa =0;        // will store last time a was updated
unsigned long PreviousMicrosb =0;        //will store last time b was updated
unsigned long PreviousMicrosWaveform=0;  //will store how long the current waveform has been going on for
void setup() {
  // put your setup code here, to run once:
pinMode(RedLED, OUTPUT);
pinMode(GreenLED, OUTPUT);
pinMode(switch1, INPUT);
pinMode(switch2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
//Start timer
unsigned long currentMicros=millis();



//SIG B
if (currentMicros-PreviousMicrosWaveform>=WaveformCycle){ //Resets PreviousMicrosWavefom once a waveformcycle has completed
  PreviousMicrosWaveform=currentMicros;
  
}
if (currentMicros-PreviousMicrosWaveform<=50){ // Keeps Green LED on for 0-50 uS
  digitalWrite(GreenLED,HIGH);
} else {
  digitalWrite(GreenLED,LOW);
}






//SWITCH SETTINGS
  Switch1State=digitalRead(switch1);
  Switch2State=digitalRead(switch2);
  if (Switch1State==HIGH){ //Toggles Switch1Setting between 0 and 1.
    previousMicros=currentMicros; //Resets interval to 0
    if (Switch1Setting==0){
      Switch1Setting=1;
      digitalWrite(GreenLED,HIGH); //Green LED blinks once for change in setting to setting 0
      delay(250);
      digitalWrite(GreenLED,LOW);
    }
    else{
      Switch1Setting=0;
      digitalWrite(GreenLED,HIGH); //Green LED blinks twice for change in setting to setting 1
      delay(250);
      digitalWrite(GreenLED,LOW);
      delay(250);
      digitalWrite(GreenLED,HIGH); 
      delay(250);
      digitalWrite(GreenLED,LOW);
    }
  }

  if (Switch2State==HIGH){ //Toggles Switch2Setting between 0 and 1.
    previousMicros=currentMicros; //Resets interval to 0
  
    if (Switch2Setting==0){
      Switch2Setting=1;
      digitalWrite(GreenLED,HIGH); //Green LED blinks once for change in setting to setting 0
      delay(250);
      digitalWrite(GreenLED,LOW);
    }
    else{
      Switch2Setting=0;
      digitalWrite(GreenLED,HIGH); //Green LED blinks twice for change in setting to setting 1
      delay(250);
      digitalWrite(GreenLED,LOW);
      delay(250);
      digitalWrite(GreenLED,HIGH); 
      delay(250);
      digitalWrite(GreenLED,LOW);
    }
  }

  //RUNS LOOP
  if (Switch1Setting==0){
    if(Switch2Setting==0){

      for ( int i=1; i<=c; i++){ // repeats c number of times (17) for number of pulses in a block
       unsigned long aPulseLength=a+((i-1)*50);
      
        if (currentMicros-previousMicros>=b){ //if the invterval since the last time the LED was on is greater/eq b(500)
          previousMicros=currentMicros; //Resets interval to 0
        
          digitalWrite(RedLED, HIGH);
          delay(a+((i-1)*50));
          digitalWrite (RedLED,LOW);
          delay(b);
      }
      delay(d);
    }
    else { //Switch 2 Setting 2, Modified waveform
    }
  }
 
 

}
