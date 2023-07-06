int pushbutton = 0;
int TIME_LED_COUNTER= 500;
int TIME_LED_SLIDER = 250;
int fourbitCount = 0; //4 bit led counter variable
int sliderCount =1; // slider counter variable
bool slider_Updown = true; // In the Slider process, it controls the movement of LEDs between MSB and LSB.
bool switchstate = true; //it controls which operation takes place with the Tach button.


void setup()
{
  pinMode(2, INPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop()
{
  if(fourbitCount == 16){fourbitCount = 0;}//The counter returns to the beginning again when it comes to 16.
  pushbutton = digitalRead(2);
  if (pushbutton == HIGH) {  //Checks whether the button is pressed.
    if(switchstate){//If the button is pressed or not, it determines which process to start.
      switchstate = false;
      sliderCount=1;
    }else{
      fourbitCount = 0;
      switchstate = true;
    }
  }
  if (switchstate) { //4 bit counter starting section
    fourbitCounter();
    delay(TIME_LED_COUNTER);

  } else {
    Slider(); //Slider starting section
    delay(TIME_LED_SLIDER); 
  }
 
}//end loop
 
    void Slider()
  {
    //With the for loop, the LEDs are shown off at first.
   for(int i = 8; i<12; i++){
      digitalWrite(i, LOW);
    }
  //indicates which LED will be lit.
    digitalWrite(sliderCount+7, HIGH);
    if(sliderCount == 1){ //if the counter is 1, the LEDs start to light from LSB to MSB.
      slider_Updown = true;
    }
    if(sliderCount == 4){ //if the counter is 4, the LEDs start to light from MSB to LSB.
      slider_Updown = false;
    }

    if(slider_Updown){
      sliderCount++;
    }else{
      sliderCount--;
    }
  }

   void fourbitCounter()
  {
     //the smallest bit burns in cases such as 1,3,5, it lights up if it is equal to 1 according to mod2.
    if((fourbitCount % 2) == 1){
      digitalWrite(8, HIGH); } 
    else { digitalWrite(8, LOW); }
  //it burns in cases such as 2,3,6,7, it burns in parts where it gives 2 or 3 according to mod4.
    if((fourbitCount % 4) >= 2){
      digitalWrite(9, HIGH); } 
    else { digitalWrite(9, LOW); }

      if((fourbitCount % 8) >= 4){
      digitalWrite(10, HIGH); } 
    else { digitalWrite(10, LOW); }

     // 3-bit processing up to the number 7 is done with the number 8 and 4-bit processing is switched and the last led starts to light up.
    if(fourbitCount >= 8){
      digitalWrite(11, HIGH); } 
    else { digitalWrite(11, LOW); }

      fourbitCount++;

}
