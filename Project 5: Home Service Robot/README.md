# Project 5: Home Service Robot  

A home service robot was simulated in Gazebo.  This robot simulated going to a specified location, picking up an object, going to another specified location, and putting down the object.  Various official ros packages were used along with a few user generated packages and resources:  

- amcl: with the amcl_demo.launch the robot was able to localize itself in the environment.  This node uses the ROS Navigation stack to plan robot trajectories that go around obstacles.
- turtlebot_teleop: keyboard_teleop.launch to manually control the robot with keyboard commands.  Mostly for debugging purposes.
- turtlebot_rviz_launchers: view_navigation.launch was used to automatically load the rviz workspace to view the laser images, map, robot, and navigation trajectories.
- turtlebot_gazebo: turtlebot_world.launch deploys the robot in the world I specified.

Additional packages and directories created:  

- map: directory where the world and its map are stored 
- scripts: shell scripts
- rvizConfig: customized rviz configuration files
- pick_objects: node written to command robot to move to pickup and dropoff locations.  Using the ros navigation stack and especially the MoveBaseAction and simple_action_client libraries to send the robot to goals.
- add_markers: node written to model virtual objects with marker in rviz.  The Marker library was used to create markers that rviz could subscribe to.
