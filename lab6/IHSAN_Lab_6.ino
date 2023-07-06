#include <NewPing.h>
#include <LiquidCrystal.h>
//HC-SR04 with Trig to Arduino Pin 9, Echo to Arduino pin 8
#define TRIGGER_PIN 9
#define ECHO_PIN 8
//Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400  
// NewPing setup of pins and maximum distance.
//REFERENCES
//I used for the information about ultrasonic sensor https://www.youtube.com/watch?v=jgPZsxYvSIk
//https://www.youtube.com/watch?v=IKD5Jhyg_cc (Buzzer music_tone use)
//https://www.arduinomedia.com/arduino-ile-buzzer-kullanimi-buzzer-ile-ses-cikarma/ (Music_note type)
//I applied my arduino new ping.h library for ultrasonic sensor

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
float distance;
const int buzzer_Pin=6;
unsigned long currentmillisecond =0;
unsigned long tempMil = 0;
const long TIME_SCREEN_INFO = 1000;

//Time and Date Variables
char* TIME_STRING = "2021.06.16 - 12:59:56";
int day=0;
int month=0;
int year=0;
int hour=0;
int min=0;
int sec=0;
int two_sec_display=0;//A variable that decides how much time it takes to display data on a serial monitor.

//musical note variables(frequency)
int Do = 262;
int Re = 294;
int Mi = 330;
int Fa = 349;
int Sol = 392;
int La = 440;
int Si = 494;
int Do_ = 523;
int la_diyez=466;
int note_gs4=415;
 
void setup() {
  set_time(TIME_STRING); //Places the incoming time in the appropriate variables.
  Serial.begin(9600); 
  lcd.begin(16, 2);
  pinMode(buzzer_Pin, OUTPUT);
}
void loop(){
  distance = sonar.ping_cm();
  Date_control();//Controls time progression.
  currentmillisecond = millis();
  play_Tone(distance);
  //Read and print operation takes place in two seconds.
  if(two_sec_display==2){ 
     Display_Date(); //Prints time and date data to the serial monitor.
     Distance_check(); //Distances info screen on lcd and seri monitor.
     two_sec_display=0;
   }
   //1-second pass measurement is performed.  
  if (currentmillisecond - tempMil >= TIME_SCREEN_INFO){
    tempMil = currentmillisecond;   
    sec+=1;
    two_sec_display+=1;
  }
  
}

void set_time(char* TIME){
   char* section = strtok(TIME, " - ");
  //Date data is fragmented and assigned to variables using the strtok command.
  char* sectionDate = section;
  section = strtok(NULL, " - ");
  char* sectionTime = section;
  char* first = strtok(sectionDate, ".");
  year = atol(first);
  first = strtok(NULL, ".");
  month = atol(first);
  first = strtok(NULL, ".");
  day = atol(first);
  first = strtok(NULL, ".");
  //The time data is fragmented and assigned to variables by the strtok command.
  char* second = strtok(sectionTime, ":");
  int temp_day=day;
  int temp_year=year;
  hour = atol(second);
  second = strtok(NULL, ":");
  min = atol(second);
  second = strtok(NULL, ":");
  sec = atol(second);
  second = strtok(NULL, ":");
 }
 //Controlled progression of other types of time is calculated based on the progression of seconds.
void Date_control(){
  if(sec==60){
    min+=1;
    sec=0;
    if(min==60){
      hour+=1;
      min=0;
      if(hour==24){
        day+=1;
        hour=0;
    //Depending on how many days the months attract, the state of increase in the lunar variable is examined.
       if( ((month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12) && (day>31))
    || ((month==4  || month==6  || month==9 ||  month==11) && (day>30)) || (month==2 && day>28)){
          month+=1;
          day=1;
          if(month==13){
            year+=1;
            month=1;
          }  
        }
      }
    }
  }
}
//Print date and time function
void Display_Date(){
  Serial.print("\nDate: " );
  if(day<10) Serial.print("0");
  Serial.print(day);
  Serial.print(".");
  Serial.print(month);
  Serial.print(".");
  Serial.print(year); 
  
  Serial.print(" - Hour: " );
  if((hour)<10) Serial.print("0");
  Serial.print(hour);
  Serial.print(":");
  if((min)<10) Serial.print("0");
  Serial.print(min);
  Serial.print(":");
  if((sec)<10) Serial.print("0");
  Serial.print(sec);
}
//Here are the tone settings and print settings performed based on the measurement made by the ultrasonic sensor.
void Distance_check(){ 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm");
  
  lcd.setCursor(0, 1);
  //In cases of 5 cm and lower, crash tone is played.
  if(distance<=5){
    lcd.print("Crashed.");
     display_distance(distance);
    Serial.print(" cm  Crashed.");
    Serial.println("\n-------------------------------------");   
  }
  //In the range of 5 to 20 cm, the emphasis is made that the object is very close to the sensor.
  else if(distance>5 && distance<=20){ 
    lcd.print("It is too close.");
    display_distance(distance);
    Serial.print(" cm  It is too close.");
    Serial.println("\n-------------------------------------");
  }
  //In the range of 21 to 50 cm, it is emphasized that the object is close to the sensor.
  else if(distance>=21 && distance <=50){ 
    lcd.print("It is close.");
    display_distance(distance);
    Serial.print(" cm  It is close.");
    Serial.println("\n-------------------------------------");
  }
  //In the range of 51 to 100 cm, the emphasis is made that the object is far from the sensor.
  else if(distance>=51 && distance<=100){ 
    lcd.print("It is far.");
    display_distance(distance);
    Serial.print(" cm  It is far.");
    Serial.println("\n-------------------------------------");
  }
  //In the range above 1 meter, the emphasis is made that the object is too far from the sensor.
   else if(distance>100){ 
    lcd.print("It is too far.");
    display_distance(distance);
    Serial.print(" cm  It is too far.");
    Serial.println("\n-------------------------------------");
  }
}

//The distance value is printed to the monitor.
void display_distance(int distance){
    Serial.print("\nDistance :");
    Serial.print(distance);
}
//Plays certain music tones for each distance range.
void play_Tone(int distance){
   if(distance<=5){
     crash();//game over sound function
   }
   else if(distance>5 && distance<=20){ 
    tone(buzzer_Pin,Fa);//349
    delay(50); 
    noTone(buzzer_Pin);
    delay(distance*3);
   }
    else if(distance>=21 && distance <=50){ 
    tone(buzzer_Pin,Sol);//392
    delay(50); 
    noTone(buzzer_Pin);
    delay(distance*5);
    }
    else if(distance>=51 && distance<=100){ 
    tone(buzzer_Pin,La);//440
    delay(50); 
    noTone(buzzer_Pin);
    delay(distance*3);
    }
    else if(distance>100){ 
    tone(buzzer_Pin,Si);//494
    delay(50); 
    noTone(buzzer_Pin);
    delay(distance*3);
    }
    
  }

  void crash(){
    //Mario game over sound
  delay(250);
  tone(buzzer_Pin, Do_);
  delay(100);
  noTone(buzzer_Pin);
  tone(buzzer_Pin, Sol);
  delay(100);
  noTone(buzzer_Pin);
  tone(buzzer_Pin, Mi);
  delay(100);
  noTone(buzzer_Pin);
  tone(buzzer_Pin, La);
  delay(100);
  noTone(buzzer_Pin);
  tone(buzzer_Pin, Si);
  delay(100);
  noTone(buzzer_Pin);
  tone(buzzer_Pin, La);
  delay(100);
  noTone(buzzer_Pin);
  tone(buzzer_Pin, note_gs4);
  delay(100);
  noTone(buzzer_Pin);
  tone(buzzer_Pin, la_diyez);
  delay(100);
  noTone(buzzer_Pin);
  tone(buzzer_Pin, note_gs4);
  delay(100);
  noTone(buzzer_Pin);
  tone(buzzer_Pin, Sol);
  delay(100);
  noTone(buzzer_Pin);
  tone(buzzer_Pin, Re);
  delay(100);
  noTone(buzzer_Pin);

}
