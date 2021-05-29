// _________ Define global variables _____________________

// Pin definitions
int PIN_LED_Red =  12;
int PIN_LED_Green =  10;      
int PIN_LED_Blue =  11;
int PIN_return_button = 8;
int PIN_emergency_button = 4;
int PIN_urgent_button = 3;
int PIN_casual_button = 2;
int PIN_buzzer = 9;


int buzz_state = 0;      // Keeps track of if light is on or off

// Other variables
int toggleState_return = 0;                // Keeps track if LED status, or toggle state, is 1 or 0
int toggleState_emergency = 0; 
int toggleState_urgent  = 0; 
int toggleState_casual = 0; 
int lastButtonState_return = 1;            // Helps remember whether the button was last pressed or released
int lastButtonState_emergency = 1;
int lastButtonState_urgent = 1;
int lastButtonState_casual = 1;
long unsigned int lastPress_return = 0;    
long unsigned int lastPress_emergency= 0; 
long unsigned int lastPress_urgent = 0; 
long unsigned int lastPress_casual = 0; 
int debounceTime = 20;          


// _________ Put your setup code here, to run once: ____________________
// the setup function runs once when you press reset or power the board

void setup() {
 
// Start serial communication so Arduino can send commands through USB connection
  Serial. begin(9600);
  
// Initialize digital LED pins as outputs.
  pinMode(PIN_LED_Red, OUTPUT);
  pinMode(PIN_LED_Green, OUTPUT);
  pinMode(PIN_LED_Blue, OUTPUT);
  
// Initialize digital buzzer pin as output
  pinMode(PIN_buzzer, OUTPUT);


// Initialize switch pins as inputs; using the built-in pullup resistors in the arduino. 
 // Open switch = 1, closed (pressed button) = 0; this is active low logic, often standard for buttons
  pinMode(PIN_return_button, INPUT_PULLUP);
  pinMode(PIN_emergency_button, INPUT_PULLUP);
  pinMode(PIN_urgent_button, INPUT_PULLUP);
  pinMode(PIN_casual_button, INPUT_PULLUP);
}

void loop() {
  int ButtonState_return = digitalRead(PIN_return_button);          // Read state of button pin and store it as buttonState (0 or 1)
  int ButtonState_emergency = digitalRead(PIN_emergency_button);
  int ButtonState_urgent = digitalRead(PIN_urgent_button);
  int ButtonState_casual = digitalRead(PIN_casual_button);
 
  // Debounce the buttons

  // Debounce emergency button
  if((millis() - lastPress_emergency) > debounceTime)                  // If the time between the last button change is greater than the debounceTime; millis() is software timer
  { 
    lastPress_emergency = millis();                                     // Update last press
    
    if(ButtonState_emergency == 0 && lastButtonState_emergency == 1)             // If button is pressed and was released last change
    {
      toggleState_emergency =! toggleState_emergency;                     // Toggle the LED state
      digitalWrite(PIN_LED_Red, toggleState_emergency);
      lastButtonState_emergency = 0;                                    // Record the last button state
    }
    
    if(ButtonState_emergency == 1 && lastButtonState_emergency == 0)  // If button is released
    {
      lastButtonState_emergency = 1;
    }
      
    while (toggleState_emergency ==1)
    {
      digitalWrite(PIN_buzzer, HIGH);
      delay(500);
      digitalWrite(PIN_buzzer, LOW);
      delay(500); 
      
      if((millis() - lastPress_return)> debounceTime)
      {
        lastPress_return = millis();
        int ButtonState_return = digitalRead(PIN_return_button);
        
        if(ButtonState_return == 0 && lastButtonState_return == 1)
        {
          digitalWrite(PIN_LED_Red, LOW);
          toggleState_emergency = 0;
          break;
        } 
      }
    }
  }

  // Debounce urgent button
  if((millis() - lastPress_urgent) > debounceTime)                  // If the time between the last button change is greater than the debounceTime
  { 
    lastPress_urgent = millis();                                     // Update last press
  
    if(ButtonState_urgent == 0 && lastButtonState_urgent == 1)             // If button is pressed and was released last change
    {
      toggleState_urgent =! toggleState_urgent;                     // Toggle the LED state
      digitalWrite(PIN_LED_Blue, toggleState_urgent);
      lastButtonState_urgent = 0;                                    // Record the last button state
    }
    
    if(ButtonState_urgent == 1 && lastButtonState_urgent == 0) 
    {
      lastButtonState_urgent = 1;
    }
    
    while (toggleState_urgent ==1)
    {
      digitalWrite(PIN_buzzer, HIGH);
      delay(500);
      digitalWrite(PIN_buzzer, LOW);
      delay(500); 
      
      if((millis() - lastPress_return)> debounceTime)
      {
        lastPress_return = millis();
        
        int ButtonState_return = digitalRead(PIN_return_button);
        
        if(ButtonState_return == 0 && lastButtonState_return == 1)
        {
          digitalWrite(PIN_LED_Blue, LOW);
          toggleState_urgent = 0;
          break;
        } 
      }
    }
   }
    
  // Debounce casual button
  if((millis() - lastPress_casual) > debounceTime)                  // If the time between the last button change is greater than the debounceTime
  { 
    lastPress_casual = millis();                                     // Update last press
  
    if(ButtonState_casual == 0 && lastButtonState_casual == 1)             // If button is pressed and was released last change
    {
      toggleState_casual =! toggleState_casual;                     // Toggle the LED state
      digitalWrite(PIN_LED_Green, toggleState_casual);
      lastButtonState_casual = 0;                                    // Record the last button state
    }

    if(ButtonState_casual == 1 && lastButtonState_casual == 0) 
    {
      lastButtonState_casual = 1;
    }
    
    while (toggleState_casual ==1)
    {
      digitalWrite(PIN_buzzer, HIGH);
      delay(500);
      digitalWrite(PIN_buzzer, LOW);
      delay(500); 
      
      if((millis() - lastPress_return)> debounceTime)
      {
        lastPress_return = millis();
        
        int ButtonState_return = digitalRead(PIN_return_button);
        
        if(ButtonState_return == 0 && lastButtonState_return == 1)
        {
          digitalWrite(PIN_LED_Green, LOW);
          toggleState_casual = 0;
          break;
        } 
      }
    }
   }
            
}
