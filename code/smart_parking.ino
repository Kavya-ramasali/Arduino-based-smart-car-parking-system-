#define TRIG_PIN 9
#define ECHO_PIN 10

long duration;
float distance;

const int thresholdDistance = 15;

void setup() {

Serial.begin(9600);

pinMode(TRIG_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);

Serial.println("================================");
Serial.println(" SMART CAR PARKING SYSTEM ");
Serial.println("================================");
}

void loop() {

distance = measureDistance();

Serial.print("Distance: ");
Serial.print(distance);
Serial.println(" cm");

if(distance < thresholdDistance) {
Serial.println("STATUS: SLOT OCCUPIED");
}
else {
Serial.println("STATUS: SLOT AVAILABLE");
}

Serial.println("--------------------------------");

delay(1000);
}

float measureDistance() {

digitalWrite(TRIG_PIN, LOW);
delayMicroseconds(2);

digitalWrite(TRIG_PIN, HIGH);
delayMicroseconds(10);

digitalWrite(TRIG_PIN, LOW);

duration = pulseIn(ECHO_PIN, HIGH);

float calculatedDistance = duration * 0.034 / 2;

return calculatedDistance;
} 
