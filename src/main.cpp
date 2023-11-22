#include <Arduino.h>

#define trigPin1 2
#define echoPin1 3
#define trigPin2 4
#define echoPin2 5

#define ledPin 8
#define speakerPin 9

long duration, distance1, distance2;
bool objectDetected = false; // 물체 감지 여부
int alarmCount = 0; // 알람이 울린 횟수

void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // 첫 번째 센서
  digitalWrite(trigPin1, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  distance1 = (duration/2) / 29.1;

  // 두 번째 센서
  digitalWrite(trigPin2, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin2, LOW);
  duration = pulseIn(echoPin2, HIGH);
  distance2 = (duration/2) / 29.1;

  if ((distance1 < 10 || distance2 < 10) && !objectDetected) { // 두 센서 중 하나가 10보다 작은 거리를 감지하면
    objectDetected = true;
    alarmCount = 0; // 알람 카운트를 0으로 초기화
  }

  if(objectDetected && alarmCount < 5) { // 물체가 감지되고, 알람이 5번 미만으로 울렸을 경우 
    digitalWrite(ledPin, HIGH);
    tone(speakerPin, 1000); // 1000 Hz의 사운드 출력
    delay(500);
    digitalWrite(ledPin, LOW);
    noTone(speakerPin); // 사운드 출력 중지
    delay(500);
    alarmCount++; // 알람 카운트 증가
  }

  if(alarmCount >= 5) {
    digitalWrite(ledPin, LOW);
    noTone(speakerPin);
    objectDetected = false; // 알람이 5번 울린 후 물체 감지 상태를 초기화
  }

  Serial.print("Distance1: ");
  Serial.print(distance1);
  Serial.print(" cm, Distance2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  delay(500);
}