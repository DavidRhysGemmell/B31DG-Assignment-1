#define a 700 //Width of first pulse, 7x100
#define b 500 // Width space between pulses
#define c 17 // Number of pulses in a block
#define d 6500 // Space between pulse blocks
#define WaveformCycle 33750 // Length of each waveform cycle, calculated manually myself in matlab, although could be implemented using a for loop to calculate the sum of pulses of a.



#define RedLED 32// insert red pin number
#define GreenLED 33//insert green pin number
#define Button1 22 //insert Button 1 pin
#define Button2 23//insert Button 2 pin

#define BlueLED 26 //Blue LED added to represent the values of the Switch 1. Not needed for program to work, but provides a visual of what settings the switch is in.
#define YellowLED 27 //Yellow LED added to represent the values of Switch 2. Not needed for program to work, but provides a visual of what settings the switch is in.

// Variables that will change
// Variables that relate to the switch settings.
int Button1State=0; // For reading whether the button is pressed.
int Button2State=0; // For reading whether the button is pressed.
int Switch1Setting=0; // The setting of the switch, depends on Button 1
int Switch2Setting=0; // The setting of the switch, depends on Button 2
int NextCycle1=0; //Locks in the setting of switch 1 for the next waveformcycle
int NextCycle2=0; //Locks in the setting of switch 2 for the next waveformcycle

//Variables that relate to the timings of the pulses etc.
int Maxa=a+(c-1)*(50); //Calculates maximum pulse length, used in modified waveform
int PreviousMicrosa =0;        // will store last time a was updated
int PreviousMicrosWaveform=0;  //Will be used to calculate how long the current Waveform has been going on for.
int aPulseLength=a; //This will determine how long each pulse length is
int BlockLength=WaveformCycle-d; //How long the block is

void setup() {
 // put your setup code here, to run once:
 pinMode(RedLED, OUTPUT);
 pinMode(GreenLED, OUTPUT);
 pinMode(Button1, INPUT);
 pinMode(Button2, INPUT);

 pinMode(BlueLED,OUTPUT);
 pinMode(YellowLED,OUTPUT);
}


void loop() {
 // put your main code here, to run repeatedly:
 unsigned long currentMicros=micros(); //Starts a timer which starts at 0 when the ESP 32 is turned on. We compare other timings to this to detect when certain time has elapsed.

  
 ////SWITCH SETTINGS////
 Button1State=digitalRead(Button1); //Tells when Button 1 is pressed
 Button2State=digitalRead(Button2); //Tells when Button 2 is pressed
 
 if (Button1State==HIGH){ //This section toggles our Switch 1 whenever the button is pressed.
    if (Switch1Setting==0){ // If Switch 1=0, then Switch 1 will toggle so =1. 
      Switch1Setting=1;
      digitalWrite(BlueLED,HIGH); //Blue LED turns on when Switch 1 = 1.
    } else { // If Switch 1 neq 0, then Switch 1=1 so Switch 1 is toggled to =0
      Switch1Setting=0;
      digitalWrite(BlueLED,LOW); //Blue LED is off when Switch 1 = 0.       
    }
 }

 if (Button2State==HIGH){ //This section toggles our Switch 2 whenever the button is pressed.
   if (Switch2Setting==0){ // If Switch 2=0, then Switch 2 will toggle so =1. 
      Switch2Setting=1;
     digitalWrite(YellowLED, HIGH); //Yellow LED turns on when Switch 2 = 1.
   } else { // If Switch 2 neq 0, then Switch 2=1 so Switch 2 is toggled to =0
      Switch2Setting=0;
      digitalWrite(YellowLED,LOW); //Yellow LED turns off when Switch 2 = 0.
   }   
 }

////Terminating condition for each WaveformCycle////
 if (currentMicros-PreviousMicrosWaveform>=WaveformCycle) { //Detects when a WaveformCycle has been completed and resets to start the next one. This is the "terminating condition" and caps how long the rest of the code continues for until it is reset.
    PreviousMicrosWaveform=currentMicros;
      NextCycle1=Switch1Setting; //At the end of every cycle it will check what settings have been decided for next. I have seperated these so that the change occurs in the next waveformcycle and does not interupt the current cycle.
      NextCycle2=Switch2Setting;
 }




////SIG B////
 if (currentMicros-PreviousMicrosWaveform<=50){ // Keeps Green LED on for the first 0-50 uS, does not depend on Switch Settings
   digitalWrite(GreenLED,HIGH);
 } else {
   digitalWrite(GreenLED,LOW);
 }


 

////SIG A////
 if (NextCycle1==0){ //Switch1Setting was 0 at the start of this cycle. NO "else" nescessary, else would mean Switch1Setting=1 -> disables RedLED pulses, and RedLED is set to LOW at the beginning/end of every cycle.  
   if (currentMicros-PreviousMicrosWaveform==50){ //At 50 uS, SIG B has completed its pulse. We now store the time that this waveformcycle has started. //Repeats until the WaveformCycle has completed//
      PreviousMicrosa=currentMicros; // Saves the time we start the SIG A so that we can compare the intervals so we know when to turn LED on.
      if (NextCycle2==0){
        aPulseLength=a; //For this default waveform, aPulselength starts at a and gets bigger.
      } else {
        aPulseLength=Maxa; // This time we set aPulseLength as the maximum value, and will get smaller for each loop. MODIFIED WAVEFORM.
      }
    }       
   if (currentMicros-PreviousMicrosWaveform>=50){ //Done 50uS signal, now ready to start SIG A      
     if (currentMicros-PreviousMicrosa<=aPulseLength){ // Turns red LED on for the required pulse length
       
       if (currentMicros-PreviousMicrosWaveform<BlockLength) { //Checks to see if there whether the pulses have "intruded" into the d part of waveform
          digitalWrite(RedLED,HIGH); //Turns on LED if there are more pulses needed
       } else {
          digitalWrite(RedLED,LOW); // for the values of intervals over the block length, LED is off. This is for d.
       }
       
     } else {
       digitalWrite(RedLED,LOW); // LED is off for the gap between pulses; b
     }
                     
     if (currentMicros-PreviousMicrosa>=(aPulseLength+b)){ // after the "a" pulse plus "b" for LED being off, we reset
       PreviousMicrosa=currentMicros;
       if (NextCycle2==0){
           aPulseLength=aPulseLength+50; //Adds 50 to each pulse length      
       } else {
           aPulseLength=aPulseLength-50; //takes away 50 from each pulse length MODIFIED WAVEFORM
       }         
     }             
   }   
 } //Again, no else nescessary for Switch 1. //Repeats until the WaveformCycle has completed//
}
