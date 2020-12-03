#include <DigiKeyboard.h>

int reading = 0;
bool muteState = true; //start muted

unsigned long CurTime = 0;
unsigned long ledPreTime = 0;
int ledState = LOW;

unsigned long buttonTime = 0;
unsigned long debounce = 500;
unsigned long blinkInterval = 500;

void setup()
{
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, INPUT);
}

void loop()
{
  //DigiKeyboard.update();
  //digitalWrite(1, HIGH);
  //delay(20);
  //digitalWrite(1, LOW);
  //delay(20);

  CurTime = millis();

  if (CurTime - ledPreTime > blinkInterval){

    ledPreTime = CurTime;

    if (ledState == LOW){
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    
    digitalWrite(1, ledState);
  }

  
  reading = digitalRead(2);
  if (reading == LOW && CurTime - buttonTime > debounce) { //button click

    buttonTime = millis();
    DigiKeyboard.sendKeyStroke(0); //to clear buffer
    
    //This presses the key combination that mutes or unmutes. If you
    //need a different combination, pick it here or put in your own.

    //Google Meet - Windows 
    DigiKeyboard.sendKeyStroke(KEY_D, MOD_CONTROL_LEFT );

    //Zoom - Chromebook/Linux
    //DigiKeyboard.sendKeyStroke(KEY_A, MOD_ALT_LEFT);
  
    muteState = !muteState;
    if (muteState == false) {
      //DigiKeyboard.print("UNMUTE!");
      digitalWrite(0, HIGH);
    } else {
      //DigiKeyboard.print("MUTE!");
      digitalWrite(0, LOW);      
    }
  }
}
