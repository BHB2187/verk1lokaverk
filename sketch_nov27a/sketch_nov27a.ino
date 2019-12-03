/* Servo mótor.
 * Brúnn tengist í GND, rauður tengist í 5V og 
 * appelsínugulur í pinnann sem stjórnar snúningnum
 */

#include <Servo.h> // Sambærilegt og import í python

Servo motor; // bý til tilvik af Servo klasanum
int motor_pinni = 9; // pinninn sem ég nota til að stjórna mótornum

/*
  VCC tengist í 5V
  Trig tengist í digital pinna.
  Echo tegist í digital pinna.
  Gnd tengist í GND.
*/

const int TrigPin = 2; 
const int EchoPin = 3; 
float fjarlaegd; // fjarlægð þess sem mælt er

void setup() {
  motor.attach(motor_pinni); // segi servo tilvikinu hvaða pinna á að nota
  Serial.begin(9600); 
  pinMode(TrigPin,OUTPUT);
  pinMode(EchoPin,INPUT);
}

void loop () {

  // sendir út púlsar
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin,LOW);
  // Servo mótorinn getur snúist 90° til vinstri og 90° til hægri, samtals 180°.
  // write fallið tekur á móti gráðunum
  motor.write(60); // mótorinn fer lengst til vinstri
  delay(1000);
  motor.write(110); // mótorinn fer lengst til hægri
  delay(1000);

  // mælt hvað púlsarnir voru lengi að berast til baka
  fjarlaegd = pulseIn(EchoPin,HIGH)/58.0; // deilt með 58 til að breyta í cm

  if(fjarlaegd < 0) { // fjarlægð getur ekki verið mínustala
    fjarlaegd = 0;
  } 

  Serial.println(fjarlaegd);
}
