#include "DHT.h" //DHT Library
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
//REFERENCES
//1)The dht library belonging to AdaFruit was added to ardunio and heat and humidity values were measured using the reading functions contained in the library.
//2)Related to Dht sensor use=>  https://www.youtube.com/watch?v=eow26YMkJ0o
//3)For time setting=> https://www.arduino.cc/reference/en/language/functions/time/millis/
//4)Examining the ranges of measurement results=> https://wiki.wpi.edu/robotics/Arduino_Math_and_Logic_Operations
//5)Photoresistor usage=> https://www.youtube.com/watch?v=IcH-Ear9VVA

//That variables used in conjunction with the millis function
unsigned long currentmillisecond =0;
unsigned long tempMil = 0;
const long TIME_SCREEN_INFO = 1000;

//Time and Date Variables
char* TIME_STRING = "2021.06.02 - 15:59:56";
int day=0;
int month=0;
int year=0;
int hour=0;
int min=0;
int sec=0;

bool day_or_night;//If the value is true, day is selected, otherwise night is selected.
int three_sec_display=0;//A variable that decides how much time it takes to display data on a serial monitor.
int light_value; //Variable that determines the value that comes to the photoresistor.

void setup() {
  char* section = strtok(TIME_STRING, " - ");
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
  Serial.begin(9600);
  Serial.println(F("Starting."));
  dht.begin();
}

void loop() {
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
  currentmillisecond = millis();
  //In 3 seconds, a value is read and printed to the serial monitor.
  if(three_sec_display==3){
    light_value = analogRead(A0);
    //Read Humidity
    float humidity = dht.readHumidity();
    //Read temperature as Celsius
    float temperature = dht.readTemperature();
    // Check if any reads failed and exit early.
    if (isnan(humidity) || isnan(temperature)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
  }
  //Function called for full printing of date and time data on the screen.
  Display_Date_Clock();
  
  Serial.print(F(" Temperature: "));
  Serial.print((int)temperature);
  Serial.print(F("°C "));
  Serial.print(F(" - "));
  Serial.print(F("Humidity: "));
  Serial.print((int)humidity);
  Serial.print("%");
  Serial.println();
 //Function indicating that the value from the photoresistor is day or night 
  day_or_night=check_dayornight(day_or_night,light_value);
  //if day_or_night has a value of true, it is printed Day, otherwise is printed as Night.
  if(day_or_night==true){
     Serial.print("Day");
     Serial.print(" - ");
     //if the light_value >=400 and value of temperature between [20C-24C] then equal optimal temperature or less then 20 C Cold otherwise Hot.
    if((int)temperature>=20 && (int)temperature<=24 ){
   Serial.print("Optimal Temperature");
  }
   else if((int)temperature<20){
   Serial.print("Cold");
  }
  else{
   Serial.print("Hot");
  }
  Serial.print(" - ");
  }
  else{
     //if the light_value <400 and value of temperature between [18C-21C] then equal optimal temperature or less then 18C Cold otherwise Hot.
    Serial.print("Night");
    Serial.print(" - ");
      if((int)temperature>=18 && (int)temperature<=21 ){
   Serial.print("Optimal Temperature");
  }
   else if((int)temperature<18){
   Serial.print("Cold");
  }
  else{
   Serial.print("Hot");
  }
   Serial.print(" - ");
  }
  
  //if the value of humidity between [30%-50%] then equal Optimal Humidity or less then 30% Low Humidity otherwise High Humidity.
 if((int)humidity<=50 && (int)humidity>=30){
   Serial.print("Optimal Humidity");
  }
   else if((int)humidity<30){
   Serial.print("Low Humidity");
  }
  else{
   Serial.print("High Humidity");
  }
  Serial.println();
  Serial.print("--------------------------"); 
  Serial.println();
  //three_sec_display value is reset at 3 seconds.
  three_sec_display=0;
  }
  
   delay(100);
   //1 second pass is checked. Adding is done for both a one-second progress(sec+=1) and a 3-second print operation(three_sec_display).
  if (currentmillisecond - tempMil >= TIME_SCREEN_INFO){
    tempMil = currentmillisecond;   
    sec+=1;
    three_sec_display+=1;
  }
}

void Display_Date_Clock(){
    int hourtemp=0;
    if(hour>12) {
                 hourtemp=(hour-12);}
  else if(hour==0){hourtemp=12;} //12.00 AM
  else if(hour <= 12){
    hourtemp = hour;
  }
     Serial.print("Date: ");
     Serial.print(day);
     Serial.print(".");
     Serial.print(month);
     Serial.print(".");
     Serial.print(year);
     Serial.print(" - ");
     
     Serial.print("Hour: ");
     Serial.print(hourtemp);
     Serial.print(":");
     Serial.print(min);
     Serial.print(":");
     Serial.print(sec);
     Serial.print(" - ");
     Serial.print(F("Light: "));
     //The Light value is printed.
     Serial.print(light_value);
      Serial.print(" "); 
}
//if the value is less than 400, the flag is considered false, and in the other case it is considered true.
bool check_dayornight(bool flag,int value){ 
if(value<400){
    flag=false;
  }
  else{
    flag=true; 
  }
  return flag;
}
