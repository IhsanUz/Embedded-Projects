int pushbutton = 0; //button control
int COUNTER_VALUE=1;
int hexanumber=0;
//Count_value=2 0→2→4→6→8→a→c→e→0→2→4→6→8→a→c→e→0→…
//Count_value=7 0→7→e→5→c→3→a→1→8→f→6→d→…
void setup()
{
  pinMode(13, INPUT); //Button
  pinMode(2, OUTPUT); //a segment
  pinMode(3, OUTPUT); //b segment
  pinMode(4, OUTPUT); //c segment
  pinMode(5, OUTPUT); //d segment
  pinMode(6, OUTPUT); //e segment
  pinMode(8, OUTPUT); //f segment
  pinMode(9, OUTPUT); //g segment
}
void loop()
{ 
 //First Experiment
 pushbutton = digitalRead(13);
  if (pushbutton == HIGH)
  {
    hexanumber=hexanumber%16;//The mode is taken sixteen.The remaining value is transferred to the function. 
    segment_display(hexanumber);
    for(int i = 0; i<COUNTER_VALUE; i++){//In each step, the hexanumber value is incremented until the number specified in counter_value.
    hexanumber++;
    }   
  }
  while(pushbutton == HIGH){ //When the button is pressed, the control is performed to show the processes that progress one by one.
    pushbutton = digitalRead(13);
  }
  delay(50);
 
}

void segment_display(int hexa_numb){
//Looking at all if structures, it is based on which segments will burn or not burn in which case as common properties in 7segmentdisplay representations of hexadecimal numbers.
//The common feature here is to check the numbers in which segment, respectively, cannot be represented by this segment.

//when the first "if" is examined, segment A is opened because Position A is closed during the hexadecimal 7segmentdisplay representation of the numbers 1,4,11 and 13.
  if(hexa_numb!=1 && hexa_numb != 4 && hexa_numb != 11 && hexa_numb != 13)
  {
    digitalWrite(2, HIGH); //a segment high
  }
  else
  {
    digitalWrite(2, LOW);
  }
  if(hexa_numb!=5 && hexa_numb != 6 && hexa_numb != 11 && hexa_numb != 12 && hexa_numb != 14 && hexa_numb != 15)
  {
    digitalWrite(3, HIGH); //b segment high
  }
  else
  {
    digitalWrite(3, LOW);
  }
  if(hexa_numb != 2 && hexa_numb != 12 && hexa_numb != 14 && hexa_numb != 15)
  {
    digitalWrite(4, HIGH); //c segment high
  }
  else
  {
    digitalWrite(4, LOW);
  }
  if(hexa_numb != 1 && hexa_numb != 4 && hexa_numb != 7 && hexa_numb != 10 && hexa_numb != 15)
  {
    digitalWrite(5, HIGH); //d segment high
  }
  else
  {
    digitalWrite(5, LOW);
  }
  if(hexa_numb != 1 && hexa_numb != 3 && hexa_numb != 4 && hexa_numb != 5 && hexa_numb != 7 && hexa_numb != 9)
  {
    digitalWrite(6, HIGH); //e segment high
  }
  else
  {
    digitalWrite(6, LOW);
  }
  if(hexa_numb != 1 && hexa_numb != 2 && hexa_numb != 3 && hexa_numb != 7 && hexa_numb != 13)
  {
    digitalWrite(8, HIGH); //f segment high
  }
  else
  {
    digitalWrite(8, LOW);
  }
  if(hexa_numb != 0 && hexa_numb != 1 && hexa_numb != 7 && hexa_numb != 12)
  {
    digitalWrite(9, HIGH); //g segment high
  }
  else
  {
    digitalWrite(9, LOW);
  } 
}
