#include <ros.h>
#include <geometry_msgs/Twist.h>
#include "DualVNH5019MotorShield.h"
#include "keyboard/Key.h"
#include <std_msgs/Float32.h>

ros::NodeHandle nh_m;
DualVNH5019MotorShield md;

float vR; // -400 ile +400 arasinda degerler almali.
const int MAX_VEL = 400;
float hiz_katsayi = 1;
bool keyActive = 0;
unsigned long lastTime = 0;

void keydown_cb_m(const keyboard::Key& key_msg) {
  if(key_msg.code == 119) { // Front
    vR = -399;
    keyActive = 1;
  }
  else if(key_msg.code == 115) { // Back
    vR = 399;
    keyActive = 1;
  }
  
}

void keyup_cb_m(const keyboard::Key& key_msg) {
  if(key_msg.code == 119) { // Front
    vR = 0;
    keyActive = 0;
  }
  else if(key_msg.code == 115) { // Back
    vR = 0;
    keyActive = 0;
  }
}

void servDir_cb2 (const std_msgs::Float32& serv_msg) {
  vR = -399;
  lastTime = millis();
}



ros::Subscriber<keyboard::Key> keydown_sub_m ("keyboard/keydown", keydown_cb_m);
ros::Subscriber<keyboard::Key> keyup_sub_m   ("keyboard/keyup", keyup_cb_m);
ros::Subscriber<std_msgs::Float32> serv_sub2 ("/serv_dir", servDir_cb2);

void setup() {
    nh_m.initNode();
    md.init();
    nh_m.subscribe(keydown_sub_m);
    nh_m.subscribe(keyup_sub_m);
    nh_m.subscribe(serv_sub2);
    vR = 0;
}

void loop() {
  if ((millis() - lastTime > 1500) && !keyActive) {
    vR = 0;
  }
  
  if (fabs(vR) < 400) {
    md.setSpeeds(vR, vR); 
  }
  nh_m.spinOnce();
  delay(1);

}
