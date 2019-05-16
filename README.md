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
