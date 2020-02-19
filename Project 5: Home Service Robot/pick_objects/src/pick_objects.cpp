#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;
	
	// set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // array of goals for the robot 
	float goals[2][3] = {{-1.0, -1.0, 1.0},{0, 0, 1.0}};
	
	for (int i=0; i < sizeof(goals)/sizeof(goals[0]); i++) {

		// define a position and orientation for the robot to reach
		goal.target_pose.pose.position.x = goals[i][0];
		goal.target_pose.pose.position.y = goals[i][1];
  		goal.target_pose.pose.orientation.w = goals[i][2];
  
		// Send the goal position and orientation for the robot to reach
		ROS_INFO("Sending goal");
  	ac.sendGoal(goal);

		// Wait an infinite time for the results
	  ac.waitForResult();

		// Check if the robot reached its goal
  	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    	ROS_INFO("Hooray, the base reached its goal");
  	else
    	ROS_INFO("The base failed to reach its goal some reason");

		// Pause 5 seconds after reaching the pickup zone
		ros::Duration(5.0).sleep();
	}


  return 0;
}
