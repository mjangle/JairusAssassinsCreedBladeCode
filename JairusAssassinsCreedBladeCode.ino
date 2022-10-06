#define buttonPin 6
#define sol1OutPin 13
#define sol2OutPin 12


int sol1State = LOW;
int sol2State = LOW;

int buttonState = HIGH;
int lastButtonState = HIGH;
int currentBladeState = 0;

const int bladeExtend = 0;
const int bladeRetract = 1;

unsigned long debounceDuration = 75;
unsigned long debounceTimeStamp = 0;

void setup() {
  pinMode(sol1OutPin, OUTPUT);
  pinMode(sol2OutPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  
}
 

void loop() {
  //check for button press, add debounce check
  buttonState = digitalRead(buttonPin);
  //check debounce - current time minus previous timestamp (duration since last timestamp) > duration
  if (millis() - debounceTimeStamp > debounceDuration) {
    //if button is pressed
    if (buttonState != lastButtonState) {
      //bank current button state
      lastButtonState = buttonState;
      // TimeStamp for button state change
      debounceTimeStamp = millis();
      // If button is depressed
      if (buttonState == LOW) {
        switch (currentBladeState) {
          case bladeExtend:
            digitalWrite(sol1OutPin, HIGH);
            currentBladeState++;
            break;
          case bladeRetract:
            //Turn off sol extending blade
            digitalWrite(sol1OutPin, LOW);
            // retract blade
            digitalWrite(sol2OutPin, HIGH);
            //Delay can be rewritten as a timer
            delay(200); 
            //Sol off
            digitalWrite(sol2OutPin, LOW);
            //reset state
            currentBladeState = 0;           
            break;
        }        
      }
    }
  }
}