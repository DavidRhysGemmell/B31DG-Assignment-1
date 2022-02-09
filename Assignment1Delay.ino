#define a 700
#define b 500
#define c 17
#define d 6500
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

void setup() {
  // put your setup code here, to run once:
pinMode(RedLED, OUTPUT);
pinMode(GreenLED, OUTPUT);
pinMode(switch1, INPUT);
pinMode(switch2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

//SWITCH SETTINGS
  Switch1State=digitalRead(switch1);
  Switch2State=digitalRead(switch2);
  if (Switch1State==HIGH){ //Toggles Switch1Setting between 0 and 1.
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
    if (Switch2Setting==0){
      Switch2Setting=1;
    }
    else{
      Switch2Setting=0;
    }
  }

  
  if (Switch1Setting==0){
    if(Switch2Setting==0){
     digitalWrite(GreenLED,HIGH); // Green LED on for duration of 1 second.
     delay(1000);
     digitalWrite(GreenLED,LOW);
      for ( int i=1; i<=c; i++){ // repeats c number of times (17) for number of pulses in a block
       digitalWrite(RedLED, HIGH);
       delay(a+((i-1)*50));
       digitalWrite (RedLED,LOW);
       delay(b);
      }
      delay(d);
    }
    else { //Switch 2 Setting 2, Modified waveform
     digitalWrite(GreenLED,HIGH); // Green LED on for duration of d.
     delay(1000);
     digitalWrite(GreenLED,LOW);
      for ( int i=c; i>=1; i--){ // repeats c number of times (17) for number of pulses in a block
       digitalWrite(RedLED, HIGH);
       delay(a+((i-1)*50));
       digitalWrite (RedLED,LOW);
       delay(b);
      }
      delay(d);
    }
     
  } else {                      //Switch 1, setting 1, turns off LEDs
  digitalWrite(RedLED, LOW);
  digitalWrite(GreenLED, LOW);
  }
 
 

}
