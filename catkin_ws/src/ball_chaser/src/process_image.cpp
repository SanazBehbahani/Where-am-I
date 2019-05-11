#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ROS_INFO_STREAM("Driving robot");
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if(!client.call(srv)){
        ROS_ERROR("Failed to call service command_robot");
    }
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;
    int count = 0;
    float offset = 0;
    float lin_x = 0.0;
    float ang_z = 0.0; 

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

    // calculate offset from center of picture to center of ball
    for (int i = 0; i < img.height; i++){
        for (int j = 0; j < img.step; j++){
            if (img.data[i * img.step + j] == white_pixel){
                offset += j - img.step / 2.0;  // calculates offset from the center of picture
                count++;  // the number of pixels detected
            }
        }
    }
    // Define the action
    if (count ==0){
        lin_x = 0.0;
        ang_z = 0.0;
    }
    else{
        lin_x = 0.1;
        ang_z = -4.0 * offset / count / (img.step / 2.0); // average offset from -step/2 ~ step/2, normalized, and multiplied by -4 to turn the robot to correct direction
    }
    drive_robot(lin_x, ang_z);
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
