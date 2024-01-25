
#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial23(USART3)  <-OpenCM 485EXP
  #define vacuum_pump 8
  #define vacuum_key 9
  #define RED_BUTTON 10
#elif defined(__OPENCR__)
  #define vacuum_pump 51
  #define vacuum_key 57
  #define RED_BUTTON 63
  #define DEVICE_NAME ""
#endif

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(vacuum_pump, OUTPUT);
  pinMode(vacuum_key, OUTPUT);
  digitalWrite(vacuum_pump, LOW);
  digitalWrite(vacuum_key, LOW);
}

void loop() {
  if(!digitalRead(RED_BUTTON))
  { 
    digitalWrite(vacuum_pump, LOW);
    digitalWrite(vacuum_key, LOW); 
  }
  else
  {
    digitalWrite(vacuum_pump, HIGH);
    digitalWrite(vacuum_key, HIGH);
  }
  delay(100);
}
