#include <Servo.h>
#include <ros.h>
#include "keyboard/Key.h"
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Float32.h>

Servo myservo;
ros::NodeHandle nh;

int pos = 105;        // variable to store the servo position
int forwardPos = 105  // position when wheel is looking forward
bool keyR = 0;
bool keyL = 0;
unsigned long lastTime = 0;

void keydown_cb(const keyboard::Key& key_msg) {
  if(key_msg.code == 100) { // Right
    keyR = 1;
  }
  else if(key_msg.code == 97) { // Left
    keyL = 1;
  }
}

void keyup_cb(const keyboard::Key& key_msg) {
  
  if(key_msg.code == 100) { // Right
    keyR = 0;
    pos = forwardPos;
  }
  else if(key_msg.code == 97) { // Left
    keyL = 0;
    pos = forwardPos;
  }
}

void servDir_cb (const std_msgs::Float32& serv_msg) {
  pos = serv_msg.data; // Set the position.
  lastTime = millis();
}

ros::Subscriber<keyboard::Key> keydown_sub ("keyboard/keydown", keydown_cb);
ros::Subscriber<keyboard::Key> keyup_sub   ("keyboard/keyup", keyup_cb);
ros::Subscriber<std_msgs::Float32> serv_sub ("/serv_dir", servDir_cb);


void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  nh.initNode();
  nh.subscribe(keydown_sub);
  nh.subscribe(keyup_sub);
  nh.subscribe(serv_sub);
}

void loop() {
  if (millis() - lastTime > 1000) {
    pos = forwardPos;  // if there is no action for 1 sec, go to forward position
  }
  
  while ((keyR && pos < 160)) { // Right
      pos += 2;
      delay(1);
  }
  while (keyL && pos > 40) { // Left
      pos -= 2;
      delay(1);
  }

  myservo.write(pos); 
  nh.spinOnce();
  delay(1);
}
