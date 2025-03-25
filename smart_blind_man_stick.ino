#define trigPin 13
#define echoPin 12
#define soundPin A0
#define obstacleBuzzerPin 8
#define soundBuzzerPin 9
#define smokeBuzzerPin 7
#define smokePin A2

const int DISTANCE_THRESHOLD = 20; // Distance threshold (cm) for obstacle detection
const int SOUND_THRESHOLD = 20;    // Sound threshold (analog value)
const int SMOKE_THRESHOLD = 120;   // Smoke threshold (analog value)
const unsigned long LOOP_INTERVAL = 250; // Loop interval (ms)

void setup() {
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(obstacleBuzzerPin, OUTPUT);
    pinMode(soundBuzzerPin, OUTPUT);
    pinMode(smokeBuzzerPin, OUTPUT);
}

void loop() {
    long duration, distance;

    // Trigger the ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure the pulse duration to calculate distance
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    // Read the sound sensor value
    int soundValue = analogRead(soundPin);
    
    // Read the smoke sensor value
    int smokeValue = analogRead(smokePin);

    // Obstacle detection
    bool obstacleDetected = (distance < DISTANCE_THRESHOLD);
    bool highSoundDetected = (soundValue > SOUND_THRESHOLD);
    bool smokeDetected = (smokeValue > SMOKE_THRESHOLD);

    // Control obstacle buzzer based on proximity
    if (obstacleDetected) {
        digitalWrite(obstacleBuzzerPin, HIGH);
    } else {
        digitalWrite(obstacleBuzzerPin, LOW);
    }

    // If sound is detected and object is nearby, turn on both buzzers
    if (obstacleDetected && highSoundDetected) {
        digitalWrite(obstacleBuzzerPin, HIGH);
        digitalWrite(soundBuzzerPin, HIGH);
    } else if (obstacleDetected) {
        digitalWrite(obstacleBuzzerPin, HIGH);
        digitalWrite(soundBuzzerPin, LOW);
    } else {
        digitalWrite(obstacleBuzzerPin, LOW);
        digitalWrite(soundBuzzerPin, LOW);
    }

    // Smoke detection
    if (smokeDetected) {
        digitalWrite(smokeBuzzerPin, HIGH);
        Serial.println("Smoke Detected!");
    } else {
        digitalWrite(smokeBuzzerPin, LOW);
    }

    // Print sensor values to Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm | Sound: ");
    Serial.print(soundValue);
    Serial.print(" | Smoke: ");
    Serial.println(smokeValue);

    delay(LOOP_INTERVAL); // Delay before next loop iteration
}
