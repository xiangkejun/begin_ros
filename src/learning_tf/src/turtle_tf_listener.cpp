#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf_listener");

  ros::NodeHandle node;

  ros::service::waitForService("spawn");
  ros::ServiceClient add_turtle =
    node.serviceClient<turtlesim::Spawn>("spawn");
  turtlesim::Spawn srv;
  add_turtle.call(srv);

  ros::Publisher turtle_vel =
  node.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 10);
  //  node.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/teleop", 10);
  tf::TransformListener listener;

  ros::Rate rate(10.0);   
  while (node.ok()){
    tf::StampedTransform transform;
    try{
    ros::Time now = ros::Time::now();
    ros::Time past = now - ros::Duration(0.1); //过去0.1秒
    // 延时的作用 使转化有效
    listener.waitForTransform("/turtle2", now,
                              "/turtle1", past,
                           //   "carrot1",past,
                              "/world", ros::Duration(1.0));
    //Get the transform between two frames by frame ID assuming fixed frame
    //跟随关键函数   turtle2 跟随turtle1
    listener.lookupTransform("/turtle2", now,    //目标点， 目标时间
                             "/turtle1", past,   //源点  源时间
                            //"carrot1",past,
                             "/world", transform);   //固定点  转换形式

 /*   listener.waitForTransform("/turtle2", now,
                              "/turtle1", past,
                             // "carrot1",past,
                              "/world", ros::Duration(1.0));

*/
    //Get the transform between two frames by frame ID assuming fixed frame
    //跟随关键函数   turtle2 跟随turtle1
/*    listener.lookupTransform("/turtle2",     //目标点， 目标时间
                             "/turtle1",    //源点  源时间
                            //"carrot1",past,
                             ros::Time(0),   //最近时刻
                              transform);   //固定点  转换形式
*/

    }
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
      continue;
    }

 //基于turtle1,计算出turtle2的线速度和角速度，然后发给turtle2
    geometry_msgs::Twist vel_msg;
    vel_msg.angular.z = 4.0 * atan2(transform.getOrigin().y(),
                                    transform.getOrigin().x());
    vel_msg.linear.x = 0.5 * sqrt(pow(transform.getOrigin().x(), 2) +
                                  pow(transform.getOrigin().y(), 2));
    turtle_vel.publish(vel_msg);

    rate.sleep();
  }
  return 0;
};