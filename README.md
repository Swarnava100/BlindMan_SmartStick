# Smart Blind Man Stick

## Overview
The Smart Blind Man Stick is designed to assist visually impaired individuals by providing real-time alerts for obstacles, loud environmental sounds, and smoke detection.

## Features

### Obstacle Detection
- Uses an ultrasonic sensor to detect nearby obstacles.
- Alerts the user via a buzzer when an obstacle is detected.

### Sound-Based Alert System
- Sound sensor detects loud sounds in the environment.
- Activates buzzers when an obstacle is detected along with a loud sound.
- Adjusts to background noise levels to prevent false alarms.

### Smoke Detection & Fire Alert
- Smoke sensor detects hazardous smoke levels.
- Activates a buzzer when smoke concentration is high.
- Displays "Smoke Detected!" in the Serial Monitor for debugging.

## Components Used
- Ultrasonic Sensor (HC-SR04)
- Sound Sensor (AI6337)
- Smoke Sensor
- Arduino Board
- Buzzers
- Resistors and Wiring

## How It Works
1. The ultrasonic sensor continuously measures distance and detects obstacles.
2. The sound sensor identifies loud noises and works in conjunction with obstacle detection.
3. The smoke sensor monitors air quality and triggers an alert if smoke is detected.
4. The system provides real-time feedback through buzzers to ensure user awareness.

## Installation & Usage
1. Connect all components as per the circuit diagram.
2. Upload the provided Arduino code to the board.
3. Open the Serial Monitor to view sensor readings in real time.
4. Test the system by introducing obstacles, loud sounds, and smoke to observe responses.

## Customization
- Adjust the distance threshold for obstacle detection in the code.
- Modify the sound sensitivity to better suit the environment.
- Set different thresholds for smoke detection based on sensor calibration.

## Applications
- Assists visually impaired individuals in navigation.
- Can be used in environments requiring real-time alerts for obstacles and hazards.
- Can be expanded to include additional safety features like GPS tracking.
