// ===============================
// SMART CAR PARKING SYSTEM
// Optimized Version
// ===============================

constexpr uint8_t TRIG_PIN = 9;
constexpr uint8_t ECHO_PIN = 10;

// Distance threshold in cm
constexpr float OCCUPIED_DISTANCE = 15.0;

// Hysteresis buffer to prevent rapid state changes
constexpr float HYSTERESIS = 2.0;

// Sensor timeout (microseconds)
constexpr unsigned long SENSOR_TIMEOUT = 30000UL;

// Reading interval
constexpr unsigned long READ_INTERVAL = 500UL;

enum ParkingStatus {
    AVAILABLE,
    OCCUPIED,
    SENSOR_ERROR
};

ParkingStatus currentStatus = AVAILABLE;

unsigned long lastReadTime = 0;

// --------------------------------------------------
// Function Prototypes
// --------------------------------------------------

float getDistance();
float getFilteredDistance();
void updateParkingStatus(float distance);
void printStatus(float distance);

// --------------------------------------------------
// Setup
// --------------------------------------------------

void setup() {

    Serial.begin(9600);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    digitalWrite(TRIG_PIN, LOW);

    Serial.println(F("SMART CAR PARKING SYSTEM STARTED"));
}

// --------------------------------------------------
// Main Loop
// --------------------------------------------------

void loop() {

    unsigned long currentMillis = millis();

    if (currentMillis - lastReadTime >= READ_INTERVAL) {

        lastReadTime = currentMillis;

        float distance = getFilteredDistance();

        updateParkingStatus(distance);

        printStatus(distance);
    }
}

// --------------------------------------------------
// Get Single Distance Reading
// --------------------------------------------------

float getDistance() {

    // Ensure clean trigger pulse
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Read echo pulse
    unsigned long duration =
        pulseIn(ECHO_PIN, HIGH, SENSOR_TIMEOUT);

    // Timeout check
    if (duration == 0) {
        return -1.0;
    }

    // Distance in cm
    return (duration * 0.0343f) / 2.0f;
}

// --------------------------------------------------
// Filtered Distance (Average of Multiple Samples)
// --------------------------------------------------

float getFilteredDistance() {

    constexpr int samples = 5;

    float total = 0;
    int validSamples = 0;

    for (int i = 0; i < samples; i++) {

        float d = getDistance();

        if (d > 0) {
            total += d;
            validSamples++;
        }

        delay(20);
    }

    if (validSamples == 0) {
        return -1.0;
    }

    return total / validSamples;
}

// --------------------------------------------------
// Update Parking Status with Hysteresis
// --------------------------------------------------

void updateParkingStatus(float distance) {

    if (distance < 0) {
        currentStatus = SENSOR_ERROR;
        return;
    }

    switch (currentStatus) {

        case AVAILABLE:

            if (distance <= OCCUPIED_DISTANCE) {
                currentStatus = OCCUPIED;
            }

            break;

        case OCCUPIED:

            if (distance >= OCCUPIED_DISTANCE + HYSTERESIS) {
                currentStatus = AVAILABLE;
            }

            break;

        case SENSOR_ERROR:

            if (distance > 0) {

                if (distance <= OCCUPIED_DISTANCE) {
                    currentStatus = OCCUPIED;
                }
                else {
                    currentStatus = AVAILABLE;
                }
            }

            break;
    }
}

// --------------------------------------------------
// Print System Status
// --------------------------------------------------

void printStatus(float distance) {

    Serial.print(F("Distance: "));

    if (distance < 0) {
        Serial.println(F("ERROR"));
    }
    else {
        Serial.print(distance, 1);
        Serial.println(F(" cm"));
    }

    Serial.print(F("STATUS: "));

    switch (currentStatus) {

        case AVAILABLE:
            Serial.println(F("SLOT AVAILABLE"));
            break;

        case OCCUPIED:
            Serial.println(F("SLOT OCCUPIED"));
            break;

        case SENSOR_ERROR:
            Serial.println(F("SENSOR ERROR"));
            break;
    }

    Serial.println(F("------------------------"));
}
