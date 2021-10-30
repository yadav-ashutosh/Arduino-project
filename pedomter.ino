#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_Sensor.h> 
#include <Adafruit_ADXL345_U.h>
//Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
int micPin = A0;          // pin that the mic is attached to
int gndPin = A1;
int powerPin = A2;
int micValue1 = 0;  
int micValue2 = 0; // the Microphone value
int led1 = 13;
int flag = 6;
boolean lightOn = false;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup(void) 
{
  pinMode(led1, OUTPUT);
  pinMode(powerPin, OUTPUT);
  pinMode(gndPin, OUTPUT);
  pinMode(micPin, INPUT);
  pinMode(8, INPUT); 
  digitalWrite(gndPin,LOW);
  delay(500);
  digitalWrite(powerPin,HIGH);
  Serial.begin(9600);  //for test the input value initialize serial
  
   if(!accel.begin())
   {
      Serial.println("No valid sensor found");
      while(1);
   }
     lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Steps:-");

  #ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif
  Serial.begin(9600);
  //Serial.println("Accelerometer Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  /* Set the range to whatever is appropriate for your project */
  //accel.setRange(ADXL345_RANGE_16_G);
  // accel.setRange(ADXL345_RANGE_8_G);
  // accel.setRange(ADXL345_RANGE_4_G);
  accel.setRange(ADXL345_RANGE_2_G);
  
  /* Display some basic information on this sensor */
  //displaySensorDetails();
  
  /* Display additional settings (outside the scope of sensor_t) */
  //displayDataRate();
  //displayRange();
  //Serial.println("");
}
int step = 0;
int mid_step =0;
void loop(void) 
{
 int Reading = digitalRead(8);
  if(Reading == HIGH)
  {
    Serial.println("HIGH");
    micValue1 = analogRead(micPin);  // read pin value
    Serial.println(micValue1);

  micValue2 = analogRead(micPin);
  Serial.println(micValue2);
  
  if (micValue1-micValue2 > 2||micValue2-micValue1 > 2){
  mid_step++;
  if(mid_step==2){
    step++;
    mid_step=0;
    }
  lightOn = !lightOn;
  Serial.println(lightOn);
  digitalWrite(led1, lightOn);
//  delay(1000);
  }
  }
  if(Reading == LOW)
  {
    
    Serial.println("LOW");
     
  /* Get a new sensor event */ 
  sensors_event_t event; 
  accel.getEvent(&event);
 
  /* Display the results (acceleration is measured in m/s^2) */

  float z = event.acceleration.z;
  float y = event.acceleration.y;
  float x = event.acceleration.x;
  
//  Serial.print("tot accl :");Serial.println(sqrt(x*x + y*y + z*z));
  
  if (sqrt(x*x + y*y + z*z)> 10 )
    {
      step = step + 1;
    }

//
//   Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
//   Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
//   Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");
//   Serial.println("m/s^2 ");

  delay(1000);
  }

   lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(step);
   
}
