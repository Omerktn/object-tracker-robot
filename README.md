# object-tracker-robot
A object tracker surface robot project. It uses 2 Arduinos (One is possible with some moficiations) and a single board computer (in this case it is Raspberry Pi with Ubuntu Mate + ROS Kinetic).

The robot has only one motor in the front and it is controlled by a servo.
>roslaunch \<name of your package> pakize.launch

Video: https://youtu.be/IJI2XllGHek
It can be controlled by a ROS keyboard, in addition to object detection.

To have a better tuning with your camera, you have to change rL,rH,oL,oH values in the *trackobj.cpp*.

Dependencies:
- std_msgs
- geometry_msgs
- rosserial
- uvc_camera
- find_object_2d

Youu need to have:
- Robot Operating System (Kinetic or Melodic) installed in your Single Board Computer
- Arduino library for your own motor controller (in the project it is *DualVNH5019MotorShield.h*)

In order to make changes for object detection system, deleting find_object_2d package from *pakize.launch* file and running it from terminal is highly recommended.
