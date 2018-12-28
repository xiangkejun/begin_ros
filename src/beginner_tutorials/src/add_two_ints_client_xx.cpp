#include "ros/ros.h"
#include "beginner_tutorials/AddTwoInts.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "add_two_ints_client");
  
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<beginner_tutorials::AddTwoInts>("add_two_ints");
    beginner_tutorials::AddTwoInts srv;

    int a,b;
    while(ros::ok())
    {
        std::cout << "please input a and b"<< std::endl;
        std::cin >> a;
        std::cin >> b;
        srv.request.a = a;
        srv.request.b = b;
        if (client.call(srv))
        {
        ROS_INFO("Sum: %ld", (long int)srv.response.sum);
        }
        else
        {
        ROS_ERROR("Failed to call service add_two_ints");
        return 1;
        }

    }





    // srv.request.a = atoll(argv[1]);
    // srv.request.b = atoll(argv[2]);
 

    return 0;
}