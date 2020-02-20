#!/bin/sh
xterm -e " export TURTLEBOT_GAZEBO_WORLD_FILE="/home/workspace/catkin_ws/src/map/Plano_IL.world";
roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 5

xterm -e " roslaunch turtlebot_gazebo gmapping_demo.launch " &
# or use slam_gmapping
sleep 5

xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 5

xterm -e " roslaunch turtlebot_teleop keyboard_teleop.launch "

