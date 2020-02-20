#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/String.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "pick_objects");
	ros::NodeHandle n;

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

	// Create publisher for goals status
	ros::Publisher pick_status_pub = n.advertise<std_msgs::String>("/pick_status", 1);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;
	
	// set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

	
	// define a position and orientation for pickup
	// Pickup Location x= 1, y=-1, w=1
	goal.target_pose.pose.position.x = 5;
	goal.target_pose.pose.position.y = 8;
 	goal.target_pose.pose.orientation.w = 1;
	
	// Send the goal position and orientation for pickup
	ROS_INFO("Sending pickup goal");
	ac.sendGoal(goal);

	// Wait an infinite time for the results
	ac.waitForResult();

	// Check if the robot reached pickup
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
	  ROS_INFO("The robot has landed at the pickup");
		
		// Publish message for marker
		std_msgs::String msg;
		msg.data = "at_pickup";
		ROS_INFO("Publishing message: %s", msg.data.c_str());
		pick_status_pub.publish(msg);

		// Pause 5 seconds at pickup
		ROS_INFO("Pausing 5 seconds at pickup");
		ros::Duration(5.0).sleep();

		// define a position and orientation for dropoff
		// Dropoff location x=0, y=0, w=1
		goal.target_pose.pose.position.x = 0;
		goal.target_pose.pose.position.y = 8.0;
 		goal.target_pose.pose.orientation.w = 1;

		// Send the goal position and orientation for dropoff
		ROS_INFO("Sending dropoff goal");
		ac.sendGoal(goal);

		// Wait an infinite time for the results
		ac.waitForResult();

		if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
			ROS_INFO("The robot has landed at the dropoff");

			// Publish message for marker
			std_msgs::String msg;
			msg.data = "at_dropoff";
			ROS_INFO("Publishing message: %s", msg.data.c_str());
			pick_status_pub.publish(msg);

			// Delay to ensure messages are read
			ros::Duration(5.0).sleep();

			}
		else {
			ROS_INFO("The robot failed to reach the dropoff");
			ROS_INFO("The robot is out there somewhere holding the object");
		}
	}
	else {
	  ROS_INFO("The base failed to reach pickup");
	}
	



  return 0;
}
