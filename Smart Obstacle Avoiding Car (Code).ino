int motor1Pin1 = 32;
int motor1Pin2 = 33;
int motor2Pin1 = 25;
int motor2Pin2 = 26;

int trigPin = 18;
int echoPin = 19;

int turnAmount = 500;

void setup() {
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

}

bool isOn = false;
void toggleLight(){
  if (isOn == true) {
    digitalWrite(LED_BUILTIN, LOW);
    isOn = false;
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    isOn = true;
  }
}

int getDistance(){
  Serial.println("Beem");
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034/2;
  Serial.println(distance);
  return distance;
}

void moveBack(){
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  toggleLight(); 
}

void moveForward(){
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  toggleLight(); 
}

void turnRight(){
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  toggleLight();  
}

void turnLeft(){
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  toggleLight();  
}

void Stop(){
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  toggleLight();  
}

void loop() {
  if (getDistance() > 40){
    moveForward();
    delay(200);
  }else {
    turnRight();
    delay(turnAmount);
    if (getDistance() < 40){
      turnLeft();
      delay(turnAmount * 2);
      moveForward();
      delay(800);
      turnRight();
      delay(turnAmount);
    }else{
      moveForward();
      delay(800);
      turnLeft();
      delay(turnAmount);
    }
  }
}
