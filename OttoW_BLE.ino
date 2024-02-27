/*  
*                        
*    ______________      ____                                _____    _  _     _
*   |   __     __  |    / __ \ _________ _________   ____   |  __ \  | | \\   //  
*   |  |__|   |__| |   | |  | |___   ___ ___   ___  / __ \  | |  | | | |  \\ //  
*   |_    _________|   | |  | |   | |       | |    | |  | | | |  | | | |   | |
*   | \__/         |   | |__| |   | |       | |    | |__| | | |__| | | |   | |
*   |              |    \____/    |_|       |_|     \____/  |_____/  |_|   |_|
*   |_    _________|
*     \__/            
*
*    This Sketch was created to control Otto Wheels with the Offical Web Bluetooth Controller for Otto DIY Robots.
*    For any question about this script you can contact us at education@ottodiy.com
*    By: Iván R. Artiles
*/

#ifdef ARDUINO_ARCH_ESP32
#include <ESP32Servo.h>
#else
#include <Servo.h>
#endif

#define RIGHTSERVO 2
#define LEFTSERVO 3
#define TRIG 8
#define ECHO 9
#define BLE_TX 11
#define BLE_RX 12

#if not defined(ARDUINO_ARCH_ESP32) // disable LineFollower ... Esp32 only has one analog ... maybe fix to use with digital line sensors
int line_sensor_right = A0;
int line_sensor_left = A1;
#endif

int speed_right_forward = 60;
int speed_right_backward = 120;
int speed_left_forward = 150;
int speed_left_backward = 40;
int speed_stop = 90;
int right_threeshold = 35;
int left_threeshold = 35;
int ultrasound_threeshold = 15;
int rightValue, leftValue = 0;
String command = "";

#if defined(ARDUINO_ARCH_ESP32)
  #include "BluetoothSerial.h"
  String device_name = "Otto BT Esp32";
  BluetoothSerial bluetooth;
#else
  #include <SoftwareSerial.h>
  String device_name = "Otto BT";
  SoftwareSerial bluetooth(BLE_TX, BLE_RX);
#endif

Servo servo_right;
Servo servo_left;

long ultrasound_distance() {
   long duration, distance;
   digitalWrite(TRIG,LOW);
   delayMicroseconds(2);
   digitalWrite(TRIG, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIG, LOW);
   duration = pulseIn(ECHO, HIGH);
   distance = duration/58;
   return distance;
}

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  servo_right.write(speed_stop);
  servo_left.write(speed_stop);
  servo_right.attach(RIGHTSERVO);
  servo_left.attach(LEFTSERVO);

#if defined(ARDUINO_ARCH_ESP32)
  bluetooth.begin(device_name);
  //bluetooth.deleteAllBondedDevices(); // Uncomment this to delete paired devices; Must be called after begin
#else
  bluetooth.begin(9600);
  bluetooth.print("AT+NAME" + device_name);
#endif

}

void loop() {
  
  checkBluetooth();
  
  if (command == "avoidance") {
    Avoidance();
  }
  else if (command == "linefollower") {
    LineFollower();
  }
  
}

void checkBluetooth() {
  
  char charBuffer[30];
  
  if (bluetooth.available() > 0) {
    
    int numberOfBytesReceived = bluetooth.readBytesUntil('\n', charBuffer, 29);
    charBuffer[numberOfBytesReceived] = NULL;
    Serial.print("Received: ");
    Serial.println(charBuffer);
    
    if (strstr(charBuffer, "forward") == &charBuffer[0]) {
      Forward();
    }   
    else if (strstr(charBuffer, "backward") == &charBuffer[0]) {
       Backward();
    }
    else if (strstr(charBuffer, "right") == &charBuffer[0]) {
       Right();
    }
    else if (strstr(charBuffer, "left") == &charBuffer[0]) {
       Left();
    }
    else if (strstr(charBuffer, "stop") == &charBuffer[0]) {
      command = "";
      Stop();
    }
    else if (strstr(charBuffer, "J") == &charBuffer[0]) {
      command = "joystick";
      GetCoords(charBuffer);
    }
    else if (strstr(charBuffer, "ultrasound") == &charBuffer[0]) {
      servo_right.detach();
      servo_left.detach();
      bluetooth.print(ultrasound_distance());
    }
    else if (strstr(charBuffer, "infrared") == &charBuffer[0]) {
      servo_right.detach();
      servo_left.detach();
#if not defined(ARDUINO_ARCH_ESP32) // disable LineFollower ... Esp32 only has one analog ... maybe fix to use digital line sensors
      rightValue = analogRead(line_sensor_right);
      leftValue = analogRead(line_sensor_left);
      String txt = "R: " + String(rightValue) + " L: " + String(leftValue);
      bluetooth.print(txt);
#endif
    }
    else if (strstr(charBuffer, "avoidance") == &charBuffer[0]) {
      command = "avoidance";
    }
    else if (strstr(charBuffer, "line_follower") == &charBuffer[0]) {
      command = "linefollower";
      servo_right.attach(RIGHTSERVO);
      servo_left.attach(LEFTSERVO);
    }
    else if (strstr(charBuffer, "S") == &charBuffer[0]) {
      Settings(charBuffer);
    }
  }
}

void GetCoords(String str) {
  String x = str.substring(str.lastIndexOf('J')+1, str.lastIndexOf(','));
  String y = str.substring(str.lastIndexOf(',')+1,str.lastIndexOf('H')-1);
  //Serial.println("X:" + x + " Y:" + y);
  joystickRoll(x.toInt(), y.toInt());
}

void joystickRoll(int x, int y) {
  if ((x >= -5)&&(x <= 5)&&(y >= -5)&&(y <= 5)){Stop();}
  else{
    servo_left.attach(LEFTSERVO);
    servo_right.attach(RIGHTSERVO);
    int LWS= map(y, -50, 50, 135, 45);
    int RWS= map(y, -50, 50, 45, 135);
    int LWD= map(x, 50, -50, 45, 0);
    int RWD= map(x, 50, -50, 0, -45);
    servo_left.write(LWS+LWD);
    servo_right.write(RWS+RWD);
    }
}

void Forward() {
  servo_right.write(speed_right_forward);
  servo_left.write(speed_left_forward);
  servo_right.attach(RIGHTSERVO);
  servo_left.attach(LEFTSERVO);
}

void Backward() {
  servo_right.write(speed_right_backward);
  servo_left.write(speed_left_backward);
  servo_right.attach(RIGHTSERVO);
  servo_left.attach(LEFTSERVO);
}

void Right() {
  servo_right.write(speed_right_backward);
  servo_left.write(speed_left_forward);
  servo_right.attach(RIGHTSERVO);
  servo_left.attach(LEFTSERVO);
}

void Left() {
  servo_right.write(speed_right_forward);
  servo_left.write(speed_left_backward);
  servo_right.attach(RIGHTSERVO);
  servo_left.attach(LEFTSERVO);
}

void Stop() {
  servo_right.write(speed_stop);
  servo_left.write(speed_stop);
  servo_right.attach(RIGHTSERVO);
  servo_left.attach(LEFTSERVO);
}

void Avoidance() {
  if (ultrasound_distance() < ultrasound_threeshold) {
      Backward();
      delay(500);
      Stop();
      delay(100);
      Right();
      delay(500);
      Stop();
      delay(100);
    }
    Forward();
}

void LineFollower() {
#if not defined(ARDUINO_ARCH_ESP32) // disable LineFollower ... Esp32 only has one analog ... maybe fix to use digital line sensors
  rightValue = analogRead(line_sensor_right);
  leftValue = analogRead(line_sensor_left);

  if(rightValue > right_threeshold && leftValue > left_threeshold) {
    servo_right.write(speed_right_forward+10);
    servo_left.write(speed_left_forward-10);
  }
  else if (leftValue > left_threeshold) {
    servo_right.write(speed_right_forward-40);
    servo_left.write(speed_left_forward-40);
  }
  else if (rightValue > right_threeshold) {
    servo_right.write(speed_right_forward+30);
    servo_left.write(speed_left_forward+30);
  }
#endif  
}

void Settings(String speeds) {
  decodeSpeeds(speeds);
}

void decodeSpeeds(String c) {
  int counter = 0;
  String rb = "";
  String rf = "";
  String lf = "";
  String lb = "";
  String ts_r = "";
  String ts_l = "";
  String ts_ultrasound = "";
  for (int i=1; i<c.length(); i++) {
      if(isDigit(c[i])) {
          if(counter == 0) {
              rf += c[i];
          }
          else if (counter == 1) {
              rb += c[i];
          }
          else if (counter == 2) {
              lf += c[i];
          }
          else if (counter == 3) {
              lb += c[i];
          }
          else if (counter == 4) {
              ts_r += c[i];
          }
          else if (counter == 5) {
              ts_l += c[i];
          }
          else if (counter == 6) {
              ts_ultrasound += c[i];
          }
      }
      else if (c[i] == '-') {
          counter++;
      }
  }

  speed_right_forward = rf.toInt();
  speed_right_backward = rb.toInt();
  speed_left_forward = lf.toInt();
  speed_left_backward = lb.toInt();
  right_threeshold = ts_r.toInt();
  left_threeshold = ts_l.toInt();
  ultrasound_threeshold = ts_ultrasound.toInt();
  
}
