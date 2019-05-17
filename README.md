# Where-am-I

This is a localization problem, where I utilize ROS AMCL package to accurately localize a mobile robot inside a map in the Gazebo simulation environments.

## Overall Summary:

1. Create a ROS package that launches a custom robot model in a custom Gazebo world

2. Utilize the ROS AMCL package and the Tele-Operation / Navigation Stack to localize the robot

3. Explore, add, and tune specific parameters corresponding to each package to achieve the best possible localization results

## Steps:

### Simulation Setup

The simulation environment and a robot is imported from Go_Chase_It repository. 


### Map Setup

We could generate the map from Gazebo world directly using a ROS package: `pgm_map_creator`.

![m1](https://user-images.githubusercontent.com/7389485/57892561-37004180-77f4-11e9-90fe-16666d707070.JPG)

### AMCL Package

Adaptive Monte Carlo Localization (AMCL) dynamically adjusts the number of particles over a period of time, as the robot navigates around in a map. 
This adaptive process offers a significant computational advantage over MCL.

#### AMCL Launch File

We need a launch file to use this package. 

Here is the list of nodes required for AMCL package to operate:
- Map Server Node `name="map_server"`
The `map_server` node provides map data as a ROS service to other nodes such as the `amcl` node. 
Here, `map_server` node will locate the map you created in the Map Setup step and send it out as the map data.
- AMCL Node `namd="AMCL"`
 `amcl` node takes `odometry` and `laser scan` data to perform the AMCL localization.
- Move Base Node `name="move_base"`
Using `move_base` package, you can define a navigation goal position for your robot in the map, and the robot will navigate to that goal position. 

The `move_base` package is a very powerful tool. 
It utilizes a costmap - where each part of the map is divided into which area is occupied, like walls or obstacles, and which area is unoccupied. 
As the robot moves around, a local costmap, in relation to the global costmap, keeps getting updated allowing the package to define a continuous path for the robot to move along.

What makes this package more remarkable is that it has some built-in corrective behaviors or maneuvers. 
Based on specific conditions, like detecting a particular obstacle or if the robot is stuck, it will navigate the robot around the obstacle or rotate the robot till it finds a clear path ahead.
