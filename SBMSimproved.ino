#define trigPin 13
#define echoPin 12
#define soundPin A0
#define obstacleBuzzerPin 8
#define soundBuzzerPin 9
#define smokeBuzzerPin 7
#define smokePin A2

const int DISTANCE_THRESHOLD = 20; // Distance threshold (cm) for obstacle detection
const int SOUND_BASELINE = 10;    // Baseline sound level (adjustable)
const int SOUND_VARIATION = 15;   // Required deviation from baseline to trigger sound detection
const int SMOKE_THRESHOLD = 120;  // Smoke threshold (analog value)
const unsigned long LOOP_INTERVAL = 250; // Loop interval (ms)

int soundBaseline = 0;  // Baseline sound level (calculated over time)

void setup() {
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(obstacleBuzzerPin, OUTPUT);
    pinMode(soundBuzzerPin, OUTPUT);
    pinMode(smokeBuzzerPin, OUTPUT);
    
    // Initialize sound baseline
    for (int i = 0; i < 50; i++) {
        soundBaseline += analogRead(soundPin);
        delay(10);
    }
    soundBaseline /= 50; // Average initial readings
    Serial.print("Initial Sound Baseline: ");
    Serial.println(soundBaseline);
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

    // Check if the current sound level deviates significantly from the baseline
    bool highSoundDetected = (soundValue > (soundBaseline + SOUND_VARIATION));
    bool obstacleDetected = (distance < DISTANCE_THRESHOLD);
    bool smokeDetected = (smokeValue > SMOKE_THRESHOLD);

    // Adaptive sound threshold update (to adjust dynamically to noise changes)
    soundBaseline = (soundBaseline * 0.9) + (soundValue * 0.1);

    // Obstacle detection
    digitalWrite(obstacleBuzzerPin, obstacleDetected ? HIGH : LOW);
    
    // Sound detection logic - only triggers when both sound and obstacles are present
    if (highSoundDetected && obstacleDetected) {
        digitalWrite(soundBuzzerPin, HIGH);
    } else {
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
