#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/String.h>
#include <string>


std::string pick_status_msg = "unknown";

// Callback function gets called everytime /pick_status topic is updated
// The message is passed onto pick_status_msg
void callback(const std_msgs::String msg)
{
	pick_status_msg = msg.data;
	ROS_INFO("Message recieved: %s", pick_status_msg.c_str());
}

int main( int argc, char** argv )
{
	ros::init(argc, argv, "add_markers");
	ros::NodeHandle n;
	ros::Rate r(1);
	ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

	// Subscribe to /pick_status, whether robot has reached pickup or dropoff
	ros::Subscriber pick_status_sub = n.subscribe("/pick_status", 1, callback);

	// Set our initial shape type to be a cube
	uint32_t shape = visualization_msgs::Marker::CUBE;


  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "/map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "add_markers";
  marker.id = 0;

  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = shape;

  // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  marker.action = visualization_msgs::Marker::ADD;

  // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
  marker.pose.position.x = -1.0;
  marker.pose.position.y = -1.0;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 1.0;
  marker.scale.y = 1.0;
  marker.scale.z = 1.0;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 0.5;

  marker.lifetime = ros::Duration();

  // Publish the marker at the pickup zone
  while (marker_pub.getNumSubscribers() < 1)
  {
    if (!ros::ok())
    {
      return 0;
    }
    ROS_WARN_ONCE("Please create a subscriber to the marker");
    sleep(1);
  }
  marker_pub.publish(marker);
	ros::spinOnce();					//Make sure callbacks are called if needed

	while (ros::ok())
	{
		// Wait for pick_status_msg to be either "at_pickup" or "at_dropoff"
		
		ros::spinOnce();
		
		ROS_WARN_ONCE("pickup_status is : %s", pick_status_msg.c_str());
		
		// "at_pickup", wait 5 seconds to simulate a pickup, hide marker,
		if (pick_status_msg == "at_pickup") {
			ros::Duration(5).sleep();
			marker.action = visualization_msgs::Marker::DELETE;
			marker_pub.publish(marker);
			
			ROS_WARN_ONCE("Robot has picked up the marker");
		}
		
		// "at_dropoff", wait 5 seconds to simulate a dropoff, show marker
		if (pick_status_msg == "at_dropoff") {
				ROS_WARN_ONCE("Robot has reached the dropoff");
				ros::Duration(5).sleep();	
			  marker.action = visualization_msgs::Marker::ADD;
				marker.pose.position.x = 0.0;
				marker.pose.position.y = 0.0;
				marker.lifetime = ros::Duration();
				marker_pub.publish(marker);
				
				ROS_WARN_ONCE("Robot has dropped off the marker");
				
		}
		
		r.sleep();
	}	

	return 0;
  
}
