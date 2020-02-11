# Project 3: Where Am I?

## Project Overview
Welcome to the Where Am I? localization project! In this project, you will learn to utilize ROS AMCL package to accurately localize a mobile robot inside a map in the Gazebo simulation environments.

Over the course of this lesson, you will learn several aspects of robotic software engineering with a focus on ROS:

Create a ROS package that launches a custom robot model in a custom Gazebo world

Utilize the ROS AMCL package and the Tele-Operation / Navigation Stack to localize the robot

Explore, add, and tune specific parameters corresponding to each package to achieve the best possible localization results

## Completed Robot  
The initial pose of the robot in its world.
![](https://github.com/jeff-daniels/Udacity-Robotics-Software-Engineer/blob/master/Project%203:%20Where%20Am%20I/screenshots/initial_pose.png)

Its task is to cross the living room.
But first it must get past the day bed.  
![](https://github.com/jeff-daniels/Udacity-Robotics-Software-Engineer/blob/master/Project%203:%20Where%20Am%20I/screenshots/Moving%20to%20daybed.png)

Obstacles don't faze the robot!  
![](https://github.com/jeff-daniels/Udacity-Robotics-Software-Engineer/blob/master/Project%203:%20Where%20Am%20I/screenshots/Going%20around%20daybed.png)

It has done it and looks out the window reflecting on it its triumphant crossing of the living room
![](https://github.com/jeff-daniels/Udacity-Robotics-Software-Engineer/blob/master/Project%203:%20Where%20Am%20I/screenshots/Triumphant%20crossing%20of%20living%20room.png)

Oh no!  The robot is in peril.  Some more intelligent god-like entity has kidnapped the robot and placed it in the utility closet.  The warning messages indicate that the robot is in a state of despair.
![](https://github.com/jeff-daniels/Udacity-Robotics-Software-Engineer/blob/master/Project%203:%20Where%20Am%20I/screenshots/Kidnapped%20and%20locked%20in%20the%20utility%20closet.png)

Deus ex machina!  Some deity has used something called "2D Pose Estimate" to help localize the robot.  Later, the deity changed the global_map update frequency.
![](https://github.com/jeff-daniels/Udacity-Robotics-Software-Engineer/blob/master/Project%203:%20Where%20Am%20I/screenshots/Saved%20by%20the%202D%20Pose%20Estimate.png)

