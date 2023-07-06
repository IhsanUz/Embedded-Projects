int ENA = 9; 
int IN1 = 8;
int IN2 = 7;
int buttonState = 0;
//Controls which direction the engine should turn.
bool rotate = true;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(2, INPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void loop() {
  //The potentiometer state is examined.
  int pot = analogRead(A5);
  int pwm;
  //PWM,Potentiometer power transfer status
  pwm = map(pot, 0, 1023, 0, 255);
  DirectionControl(pwm);
}

void DirectionControl(int speed) {
  //Enable opens. A for loop was created to ensure that three seconds of delay occurs and there is no delay problem if the button is pressed.
  analogWrite(ENA, speed);
  for(int i=0; i < 10; i++){
    //Button status is examined.If High, the state of the "rotate" variable is changed, and the signals coming to the input directions of the engine are changed, and this process continues.
    buttonState = digitalRead(2);
    if(buttonState == HIGH){
      i=0;
      rotate = !rotate;
    } 
    //Signals to the engine ends are determined.
    digitalWrite(IN1, rotate);
    digitalWrite(IN2, !rotate);   
    delay(300);
  }
  rotate = !rotate;
}
