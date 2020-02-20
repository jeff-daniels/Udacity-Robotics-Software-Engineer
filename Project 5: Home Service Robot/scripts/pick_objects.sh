#!/bin/sh
xterm -e " export TURTLEBOT_GAZEBO_WORLD_FILE="$(cd ../ && pwd)/map/Plano_IL.world";
roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 5

xterm -e " export TURTLEBOT_GAZEBO_MAP_FILE="$(cd ../ && pwd)/map/map.yaml";
roslaunch turtlebot_gazebo amcl_demo.launch "  &
sleep 5

xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 5

xterm -e " rosrun pick_objects pick_objects "
