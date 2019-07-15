#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>


SoftwareSerial mySerial (8,9);
String payload;
int temp;
 
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
float pH, pHraw;
int sensorValue;
float v;
float turbidity;

 
void setup(void)
{
  // start serial port
Serial.begin(115200);
mySerial.begin(115200);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin ();
}
 
 
void loop(void)
{
   v=analogRead(A1);
turbidity=(v*5)/1024;//Converting digital value to analog value
Serial.print("turbidity :");
Serial.println(turbidity);

    pHraw =analogRead(A0);
    Serial.print("pHraw:  ");
    Serial.println(pHraw);
  if (pHraw<100){
     pH = 7.2;
     Serial.println(pH); 
  }
  
  if (pHraw>=100 && pHraw <250){
     pH = 7.1;
     
    Serial.println(pH);
  }
  
  if (pHraw>=250 && pHraw <400){
    pH = 6.97;
    Serial.println(pH);
  }
  if (pHraw>=400 && pHraw <600){
    pH = 6.45;
    Serial.println(pH);
  }

  if (pHraw>=600 && pHraw <800){
    pH = 7.23;
    Serial.println(pH);
  }

  if (pHraw>=800 && pHraw <1010){
    pH = 7.45;
    Serial.println(pH);
  }
  
  if (pHraw > 1010){
  float pH = 0;
  Serial.println(pH);
  }
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print(" Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");

  Serial.print("Temperature is: ");
  Serial.println(sensors.getTempCByIndex(0)); // Why "byIndex"? 
  temp=sensors.getTempCByIndex(0);
 payload  = "@{\"d\":{\"temp\":";
  payload += temp;
  payload+="," "\"turb\":";
  payload += turbidity;
  payload+="," "\"pH\":";
  payload += pH;
  payload += "}}";
 Serial.print("Sending payload: ");
Serial.println(payload);
mySerial.println(payload);
delay(1000);
 }
