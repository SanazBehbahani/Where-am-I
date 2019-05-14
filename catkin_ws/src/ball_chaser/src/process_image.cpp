#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ROS_INFO_STREAM("Driving the robot");
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;
    client.call(srv);

    if(!client.call(srv)){
        ROS_ERROR("Failed to call service command_robot");
    }
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
    int white_pixel = 0;
    int x_position_sum = 0;

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera

    // ROS Image Message format
    //
    // Compact Message Definition
    // std_msgs/Header header
    // uint32 height
    // uint32 width
    // string encoding
    // uint8 is_bigendian
    // uint32 step
    // uint8[] data

    // Scan each pixel looking for a white one (Eacg pixel consists of 3 channels: R, G, and B)
    for (int i = 0; i < img.data.size(); i+=3){
        int red_ch = img.data[i];
	int green_ch = img.data[i+1];
	int blue_ch = img.data[i+2];
	
	if (red_ch == 255 && green_ch == 255 && blue_ch == 255){
	    int x_position = (i % (img.width * 3)) / 3;
      	    x_position_sum += x_position;
            white_pixel += 1;
        }
    }

    // Case 1: no white pixel detected -> ball not in the view of the robot
    if (white_pixel == 0){
        drive_robot(0.0, 0.0);
    }
    // Case 2: white ball in the view of the robot
    else {
        int mean_x_position = x_position_sum / white_pixel; // finding center of the ball
        
        // Option 1: center in the left of the image -> robot should turn left
	if (mean_x_position < img.width / 3){
	    drive_robot(0.1, 0.5);
        }

	// Option 2: center in the right of the image -> robot should turn right
	else if (mean_x_position > img.width * 2 / 3){
	    drive_robot(0.1, -0.5);
        }

	// Option 3: center of the ball in the middle of the image -> robot moves forward
	else{
	    drive_robot(0.5, 0.0);
    	}
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
