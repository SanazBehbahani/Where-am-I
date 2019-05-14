# Go Chase It Project
This is the second project in the Robotics Software Engineer Nanodegree Program by Udacity.

## Project Description:
In this project, I created two ROS packages inside my `catkin_ws/src`: the `drive_bot` and the `ball_chaser`. Here are the steps to design the robot, house it inside the world, and program it to chase a white-colored ball:

1. `drive_bot`:
   - Create a `my_robot` ROS package to hold the robot, the white ball, and the world.
   - Design a differential drive robot with the Unified Robot Description Format. Add two sensors to your robot: a lidar and a camera. Add Gazebo plugins for your robot’s differential drive, lidar, and camera. The robot you design should be significantly different from the one presented in the project lesson. Implement significant changes such as adjusting the color, wheel radius, and chassis dimensions. Or completely redesign the robot model! After all you want to impress your future employers :bowtie:
   - House your robot inside the world you built in the **Build My World** project.
   - Add a white-colored ball to your Gazebo world and save a new copy of this world.
The `world.launch` file should launch your world with the white-colored ball and your robot.

2. `ball_chaser`:
   - Create a `ball_chaser` ROS package to hold your C++ nodes.
   - Write a `drive_bot` C++ node that will provide a `ball_chaser/command_robot` service to drive the robot by controlling its linear x and angular z velocities. The service should publish to the wheel joints and return back the requested velocities.
   - Write a `process_image` C++ node that reads your robot’s camera image, analyzes it to determine the presence and position of a white ball. If a white ball exists in the image, your node should request a service via a client to drive the robot towards it.
   - The `ball_chaser.launch` should run both the `drive_bot` and the `process_image` nodes.
   
## Directory Structure:
![md1](https://user-images.githubusercontent.com/7389485/57563287-1ac25780-7351-11e9-85d7-e9fd09e90e20.JPG)

## MyOfficeWorld Environment
![myworld](https://user-images.githubusercontent.com/7389485/57655141-c73b4e00-758a-11e9-94b8-ba5872852a4d.JPG)
