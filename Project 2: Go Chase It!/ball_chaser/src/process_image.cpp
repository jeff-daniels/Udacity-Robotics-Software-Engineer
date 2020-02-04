#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
	ball_chaser::DriveToTarget srv;
	srv.request.linear_x = lin_x;
	srv.request.angular_z = ang_z;

	// Call the command_robot service and pass the requested velocities
	if (!client.call(srv))
		ROS_ERROR("Failed to call service command_robot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera

	// Default is to stop the robot	
	float lin_x = 0.0;
	float ang_z = 0.0;
	
	// Initialized to a negative number to indicate no white is present in the image
	int white_spot = -1;
	
	// Movement parameters 
	float left_boundary = 0.35;
	float right_boundary = 0.65;
	float forward_velocity = 0.5;
	float turning_velocity = 0.5;
	
	// Loop through each pixel in the image until a white one is found
	for (int i = 0; i < img.height * img.step; i+=3)	{
		if (img.data[i] == white_pixel && img.data[i+1] == white_pixel && img.data[i+2] == white_pixel)	{
			white_spot = i % img.step;
			break;
		}
	}

	// If white pixels are spotted, set lin_x to the forward velocity
	// Steer in the direction of the ball by setting ang_z to a non-zero value
	if (white_spot >= 0)	{
		lin_x = forward_velocity;

		if (white_spot < left_boundary*img.step)	{
			ang_z = turning_velocity; 
		}
		if (white_spot > right_boundary*img.step)	{
			ang_z = -turning_velocity;
		}
	}

	// Drive the robot
	drive_robot(lin_x, ang_z);

  // Stream info
  if (white_spot != -1) { 
    ROS_INFO_STREAM("White object detected, moving robot ...");
  } else {
    ROS_INFO_STREAM("Nothing detected; robot stopped");
  }

}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
