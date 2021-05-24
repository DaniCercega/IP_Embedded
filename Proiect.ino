#include "Adafruit_Si7021.h"
#include <SoftwareSerial.h> 
#include <PulseSensorPlayground.h>




SoftwareSerial Serial1(2, 3); 
PulseSensorPlayground pulseSensor; 
uint8_t loopCnt = 0;

            // we start, assuming no motion detected
int valPir = 0;  
int valHum=0;
int valTemp=0;
String deTrimis;
Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(A0,INPUT);
  pulseSensor.analogInput(A2);;
  pinMode(A3,INPUT);
  pinMode(5,INPUT);
  // wait for serial port to open
  while (!Serial) {
    delay(10);
  }

  Serial.println("Si7021 test!");
  
  if (!sensor.begin()) {
    Serial.println("Did not find Si7021 sensor!");
    while (true)
      ;
  }

  
}

void loop() {

  delay(1000);
  
  valPir = digitalRead(5);
  Serial.println("M" + String(valPir));

  int valGaz=analogRead(A3);
 
  Serial.println("G" + String(valGaz));
  delay(50);

  int myBPM = pulseSensor.getBeatsPerMinute();
  
  Serial.println("P" + String(myBPM));
  delay(50);

  int valLumina=analogRead(A0);
  
  Serial.println("L" + String(valLumina));
  delay(50);
  
  valHum=sensor.readHumidity();
  Serial.println("H" + String(valHum, 0));

  delay(50);

  valTemp=sensor.readTemperature();
  Serial.println("T" + String(valTemp, 0));
  delay(50);

  deTrimis="  INSERT INTO sql11414385.sensor(id, pir ,gaz ,puls ,lumina ,umiditate ,temperatura ) VALUES ('1','" +  String(valPir) + "','" +  String(valGaz) + "','" + String(myBPM) + "','" + String(valLumina) + "','" + String(sensor.readHumidity(), 0) + "','" + String(sensor.readTemperature(), 0) + "')";
  Serial1.println(deTrimis);

  delay(2000);

  

  // Toggle heater enabled state every 30 seconds
  // An ~1.8 degC temperature increase can be noted when heater is enabled
  
}
