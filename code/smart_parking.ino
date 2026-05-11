#define TRIG_PIN 9
#define ECHO_PIN 10

long duration;
float distance;

const int thresholdDistance = 15;

void setup() {
    Serial.begin(9600);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    digitalWrite(TRIG_PIN, LOW);

    Serial.println("SMART CAR PARKING SYSTEM STARTED");
}

void loop() {

    distance = getDistance();

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance == -1) {
        Serial.println("STATUS: SENSOR ERROR");
    }
    else if (distance < thresholdDistance) {
        Serial.println("STATUS: SLOT OCCUPIED");
    }
    else {
        Serial.println("STATUS: SLOT AVAILABLE");
    }

    Serial.println("------------------------");

    delay(500);
}

float getDistance() {

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH, 30000);

    if (duration == 0) {
        return -1; // no echo received
    }

    return duration * 0.034 / 2;
}
