#include <ESP8266WiFi.h>
#include <Servo.h>

const char* ssid = "ssid"; // write your WiFi name
const char* password = "password"; // write your WiFi password
const uint8_t LeftLegPin = D8; // D8 or 15
const uint8_t RightLegPin = D4; // D4 or 2
const uint8_t LeftFootPin = D7; // D7 or 13
const uint8_t RightFootPin = D3; // D3 or 0

// By default it will try to get this IP, but if it is already taken then it will take another free one.
// You can verify which IP the robot take by opening the Serial Monitor
IPAddress ip(10,0,0,208);     
IPAddress gateway(192,168,1,1);   
IPAddress subnet(255,255,255,0); 

// Creamos una instancia del servidor
// y especificamos el puerto a escuchar como un argumento.
WiFiServer server(80);

Servo LeftLeg;
Servo LeftFoot;
Servo RightFoot;
Servo RightLeg;

bool walkMode = false;
bool rollMode = false;
int roll_right_forward_speed = 40;
int roll_left_forward_speed = 40;
int roll_right_backward_speed = 40;
int roll_left_backward_speed = 40;
String command = "";
int currentmillis1 = 0;
int currentmillis2 = 0;
int currentmillis3 = 0;

long ultrasound_distance_1() {
   long duration, distance;
   digitalWrite(12,LOW);
   delayMicroseconds(2);
   digitalWrite(12, HIGH);
   delayMicroseconds(10);
   digitalWrite(12, LOW);
   duration = pulseIn(14, HIGH);
   distance = duration/58;
   return distance;
}

void AvoidanceWalk() {
  if (ultrasound_distance_1() <= 15) {
    Home();
    delay(50);
    WalkRight();
  }
  WalkForward();
}

void AvoidanceRoll() {
  if (ultrasound_distance_1() <= 15) {
    NinjaRollStop();
    NinjaRollRight(roll_right_forward_speed, roll_left_forward_speed);
  }
  NinjaRollForward(roll_right_forward_speed, roll_left_forward_speed);
}

void Home() {

  LeftFoot.attach(LeftFootPin, 544, 2400);
  RightFoot.attach(RightFootPin, 544, 2400);
  LeftLeg.attach(LeftLegPin, 544, 2400);
  RightLeg.attach(RightLegPin, 544, 2400);
  delay(100);

  LeftFoot.write(90);
  RightFoot.write(90);
  LeftLeg.write(60);
  RightLeg.write(120);
  delay(100);
  LeftLeg.detach();
  RightLeg.detach();
}

void SetWalk() {
  walkMode = true;
  rollMode = false;
  LeftLeg.attach(LeftLegPin, 544, 2400);
  RightLeg.attach(RightLegPin, 544, 2400);
  LeftLeg.write(60);
  RightLeg.write(120);
  delay(100);
  LeftLeg.detach();
  RightLeg.detach();
  delay(100);
}

void SetRoll() {
  walkMode = false;
  rollMode = true;
  LeftLeg.attach(LeftLegPin, 544, 2400);
  RightLeg.attach(RightLegPin, 544, 2400);
  LeftLeg.write(170);
  RightLeg.write(10);
  delay(100);
  LeftLeg.detach();
  RightLeg.detach();
  delay(100);
}

void TiltToRight() {
  LeftLeg.attach(LeftLegPin, 544, 2400);
  RightLeg.attach(RightLegPin, 544, 2400);
  LeftLeg.write(0);
  RightLeg.write(65);
  delay(300);
  LeftLeg.detach();
  RightLeg.detach();
  delay(300);
}

void TiltToLeft() {
  LeftLeg.attach(LeftLegPin, 544, 2400);
  RightLeg.attach(RightLegPin, 544, 2400);
  LeftLeg.write(120);
  RightLeg.write(180);
  delay(300);
  LeftLeg.detach();
  RightLeg.detach();
  delay(300);
}

void MoveRightFoot(int s, int t) {
  RightFoot.attach(RightFootPin, 544, 2400);
  RightFoot.write(s);
  delay(t);
  RightFoot.write(90);
  delay(100);
  RightFoot.detach();
  delay(300);
}

void MoveLeftFoot(int s, int t) {
  LeftFoot.attach(LeftFootPin, 544, 2400);
  LeftFoot.write(s);
  delay(t);
  LeftFoot.write(90);
  delay(100);
  LeftFoot.detach();
  delay(300);
}

void ReturnFromRight() {
  LeftLeg.attach(LeftLegPin, 544, 2400);
  LeftLeg.write(60);
  RightLeg.attach(RightLegPin, 544, 2400);
  for(int count=65;count<=120;count+=2) {
    RightLeg.write(count);
    delay(25);
  }
  delay(300);
  LeftLeg.detach();
  RightLeg.detach();
}

void ReturnFromLeft() {
  RightLeg.attach(RightLegPin, 544, 2400);
  RightLeg.write(120);
  LeftLeg.attach(LeftLegPin, 544, 2400);
  for(int count=120;count>=60;count-=2) {
    LeftLeg.write(count);
    delay(25);
  }
  delay(300);
  LeftLeg.detach();
  RightLeg.detach();
}

void WalkForward() {
  TiltToRight();
  delay(100);
  MoveRightFoot(70, 250);
  delay(100);
  ReturnFromRight();
  
  TiltToLeft();
  delay(100);
  MoveLeftFoot(140, 350);
  delay(100);
  ReturnFromLeft();
}

void WalkRight() {
  TiltToRight();
  delay(100);
  MoveRightFoot(70, 350);
  delay(100);
  ReturnFromRight();
}

void WalkBackward() {
  TiltToRight();
  delay(100);
  MoveRightFoot(120, 250);
  delay(100);
  ReturnFromRight();
  
  TiltToLeft();
  delay(100);
  MoveLeftFoot(60, 350);
  delay(100);
  ReturnFromLeft();
}

void WalkLeft() {
  TiltToLeft();
  delay(100);
  MoveLeftFoot(140, 350);
  delay(100);
  ReturnFromLeft();
}

void NinjaRollForward(int speedR, int speedL) {
  LeftFoot.attach(LeftFootPin, 544, 2400);
  RightFoot.attach(RightFootPin, 544, 2400);
  LeftFoot.write(90 + speedL);
  RightFoot.write(90 - speedR);
}

void NinjaRollRight(int speedR, int speedL) {
  LeftFoot.attach(LeftFootPin, 544, 2400);
  RightFoot.attach(RightFootPin, 544, 2400);
  LeftFoot.write(90 + speedL);
  RightFoot.write(90 + speedR);
}

void NinjaRollLeft(int speedR, int speedL) {
  LeftFoot.attach(LeftFootPin, 544, 2400);
  RightFoot.attach(RightFootPin, 544, 2400);
  LeftFoot.write(90 - speedL);
  RightFoot.write(90 - speedR);
}

void NinjaRollBackward(int speedR, int speedL) {
  LeftFoot.attach(LeftFootPin, 544, 2400);
  RightFoot.attach(RightFootPin, 544, 2400);
  LeftFoot.write(90 - speedL);
  RightFoot.write(90 + speedR);
}

void NinjaRollStop() {
  LeftFoot.write(90);
  RightFoot.write(90);
  LeftFoot.detach();
  RightFoot.detach();
}

void joystickWalk(int x, int y) {
  if ((x >= -5)&&(x <= 5)&&(y >= -5)&&(y <= 5)){ command = "home"; }
  else if (y < -25 && x < -25 || y > 25 && x < -25) { command = "left"; }
  else if (y < -25 && x > 25 || y > 25 && x > 25) { command = "right"; }
  else if (y < -25) { command = "forward"; }
  else if (y > 25) { command = "backward"; }
}
  
void joystickRoll(int x, int y) {
  if ((x >= -5)&&(x <= 5)&&(y >= -5)&&(y <= 5)){NinjaRollStop();}
  else{
    LeftFoot.attach(LeftFootPin, 544, 2400);
    RightFoot.attach(RightFootPin, 544, 2400);
    int LWS= map(y, -50, 50, 135, 45);
    int RWS= map(y, -50, 50, 45, 135);
    int LWD= map(x, 50, -50, 45, 0);
    int RWD= map(x, 50, -50, 0, -45);
    LeftFoot.write(LWS+LWD);
    RightFoot.write(RWS+RWD);
    }
}

void Settings(String speeds) {
  decodeSpeeds(speeds);
}

void decodeSpeeds(String c) {
  int counter = 0;
  String RF = "";
  String LF = "";
  String RB = "";
  String LB = "";
  
  for (int i=1; i<c.length(); i++) {
      if(isDigit(c[i])) {
          if(counter == 0) {
              RF += c[i];
          }
          else if (counter == 1) {
              LF += c[i];
          }
          else if (counter == 2) {
              RB += c[i];
          }
          else if (counter == 3) {
              LB += c[i];
          }
      }
      else if (c[i] == '&') {
          counter++;
      }
  }

  roll_right_forward_speed = RF.toInt();
  roll_left_forward_speed = LF.toInt();
  roll_right_backward_speed = RB.toInt();
  roll_left_backward_speed = LB.toInt();
  Serial.println("");
  Serial.println(c);
  Serial.println(RF.toInt());
  Serial.println(LF.toInt());
  Serial.println(RB.toInt());
  Serial.println(LB.toInt());
  
}

void setup() {
  Serial.begin(115200);
  delay(10);  
  pinMode(5, OUTPUT);
  // Imprimimos la información sobre la red WiFi.
  Serial.println();
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  
  // Iniciamos el servidor
  server.begin();
  Serial.println("Servidor iniciado");

  Serial.println(WiFi.localIP());

  tone(5, 440, 1000);
  Home();
}

void loop() {
  CheckClient();//if something is coming at us

  if (command == "walkmode") {
    SetWalk();
    command = "";
  }
  else if (command == "rollmode") {
    SetRoll();
    command = "";
  }
  else if (command == "home") {
    Home();
    command = "";
  }
  else if (command == "forward") {
    if(walkMode) {
      WalkForward();
      command = "";
    } else {
      NinjaRollForward(roll_right_forward_speed, roll_left_forward_speed);
    }
  }
  else if (command == "backward") {
    if(walkMode) {
      WalkBackward();
      command = "";
    } else {
      NinjaRollBackward(roll_right_backward_speed, roll_left_backward_speed);
    }
  }
  else if (command == "right") {
    if(walkMode) {
      WalkRight();
      command = "";
    } else {
      NinjaRollRight(roll_right_forward_speed, roll_left_forward_speed);
      command = "";
    }
  }
  else if (command == "left") {
    if(walkMode) {
      WalkLeft();
      command = "";
    } else {
      NinjaRollLeft(roll_right_backward_speed, roll_left_backward_speed);
      command = "";
    }
  }
  else if (command == "stop") {
    NinjaRollStop();
  }
  else if (command == "avoidancewalk") {
    AvoidanceWalk();
  }
  else if (command == "avoidanceroll") {
    AvoidanceRoll();
  }

}

void CheckClient() {
  // Verificamos si un cliente se ha conectado
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Esperamos hasta que un cliente envíe algún dato.
  Serial.println("nuevo cliente");
  while(!client.available()){
    delay(1);
  }
  
  // Leemos la primera línea de la petición
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  if (req.indexOf("/walkmode") != -1) {
    command = "walkmode";
  }
  else if (req.indexOf("/rollmode") != -1){
    command = "rollmode";
  }
  else if (req.indexOf("/home") != -1) {
    command = "home";
  }
  else if (req.indexOf("/forward") != -1){  
    command = "forward";
  }
  else if (req.indexOf("/right") != -1){
    command = "right";
  }
  else if (req.indexOf("/backward") != -1){
    command = "backward";
  }
  else if (req.indexOf("/left") != -1){
    command = "left";
  }
  else if (req.indexOf("/stop") != -1){
    command = "stop";
  }
  else if (req.indexOf("/avoidancewalk") != -1){
    command = "avoidancewalk";
  }
  else if (req.indexOf("/avoidanceroll") != -1){
    command = "avoidanceroll";
  }
  else if (req.indexOf("/R=") > 0){
    Settings(req);
    Home();
    command = "";
  }
  else if (req.indexOf("/J") > 0){
    command = "joystick";
    GetCoords(req);
  }
  else {
    Serial.println("petición inválida");
    client.stop();
    return;
  }
;
  
  client.flush();

  // Preparamos la respuesta
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += "</html>\n";

  // Enviamos la respuesta al cliente
  client.print(s);
  delay(1);
  Serial.println("Cliente desconectado");
}

void GetCoords(String str) {
  String x = str.substring(str.lastIndexOf('J')+1, str.lastIndexOf(','));
  String y = str.substring(str.lastIndexOf(',')+1,str.lastIndexOf('H')-1);
  //Serial.println("X:" + x + ", Y:" + y);
  walkMode == true ? joystickWalk(x.toInt(), y.toInt()) : joystickRoll(x.toInt(), y.toInt());
}
