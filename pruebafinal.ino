#include <HCSR04.h>
int triggerPin = 2;
int echoPin = 3;
int triggerPin2 = 4;
int echoPin2 = 5;
UltraSonicDistanceSensor Sensor(triggerPin, echoPin);
UltraSonicDistanceSensor Sensor2(triggerPin2, echoPin2);

int motor1_at = 6; //motor 1 para avanzar hacia adelante
int motor1_ad = 9; //motor 1 para avanzar hacia atras
int motor2_at = 10; //motor 2 para avanzar hacia adelante
int motor2_ad = 11; //motor 1 para avanzar hacia atras

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motor1_at, OUTPUT);
  pinMode(motor1_ad, OUTPUT);
  pinMode(motor2_at, OUTPUT);
  pinMode(motor2_ad, OUTPUT);
}

void loop() {
  double distancia1 = Sensor.measureDistanceCm();
  double distancia2 = Sensor2.measureDistanceCm();
  Serial.print(distancia1);
  Serial.print("  cm    ");
  Serial.print(distancia2);
  Serial.println("  cm2");
  delay(700);

  //inicia proceso del robot
  //las velocidades del motor estan en el rango de(0,255)
  analogWrite(motor1_ad, 0); //al encender todo, espera 2 segundos para no arrancar de un solo
  analogWrite(motor1_at, 0);
  analogWrite(motor2_ad, 0);
  analogWrite(motor2_at, 0);
  delay(2000);
  analogWrite(motor1_ad, 90); //el robot empieza a avanzar un poco rapido
  analogWrite(motor1_at, 0);
  analogWrite(motor2_ad, 90);
  analogWrite(motor2_at, 0);
  delay(2000);

  while (distancia1 > 6) { //mientras el sensor de enfrente no detecte un obstaculo adelante, el robot se enfoca en el sensor que va siguiendo la pared
    if ( distancia2 > 4 && distancia2 < 6 ) { //si el robot esta a la distancia adecuada de la pared avanza normal
      analogWrite(motor1_ad, 100);
      analogWrite(motor1_at, 0);
      analogWrite(motor2_ad, 100);
      analogWrite(motor2_at, 0);
    }
    if (distancia2 < 5) { //si el robot esta muy cerca de la pared si aleja un poco
      analogWrite(motor1_ad, 80);
      analogWrite(motor1_at, 0);
      analogWrite(motor2_ad, 130);
      analogWrite(motor2_at, 0);
    }
    if (5 < distancia2 &&  6 < distancia2) { //le pregunta si ya se alejo  lo suficiente
      analogWrite(motor1_ad, 150);//
      analogWrite(motor1_at, 0);
      analogWrite(motor2_ad, 80);
      analogWrite(motor2_at, 0);
    }
    if (6 < distancia2 &&  8 < distancia2) { //si no detecta una pared muy cerca gira a la derecha
      analogWrite(motor1_ad, 150);
      analogWrite(motor1_at, 0);
      analogWrite(motor2_ad, 75);
      analogWrite(motor2_at, 0);
    }
    if (8 < distancia2) {
      analogWrite(motor1_ad, 175);//retrocede
      analogWrite(motor1_at, 0);
      analogWrite(motor2_ad, 50);
      analogWrite(motor2_at, 0);
    }
  }
  if (distancia1 < 6) {
    analogWrite(motor1_ad, 0);//para
    analogWrite(motor1_at, 0);
    analogWrite(motor2_ad, 0);
    analogWrite(motor2_at, 0);
    delay(500);
    analogWrite(motor1_ad, 0);//retrocede
    analogWrite(motor1_at, 100);
    analogWrite(motor2_ad, 0);
    analogWrite(motor2_at, 100);
    delay(500);
    analogWrite(motor1_ad, 0);//gira a la izquierda
    analogWrite(motor1_at, 0);
    analogWrite(motor2_ad, 110);
    analogWrite(motor2_at, 0);
    delay(800);
  }
}
