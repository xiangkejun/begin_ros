#include <ros/ros.h>
#include <tf/transform_broadcaster.h>


//基于turtle1,再生成一个子坐标 carrot1
int main(int argc, char** argv)
{
    ros::init(argc, argv, "my_tf_broadcaster");
    ros::NodeHandle node;
    
    tf::TransformBroadcaster br;  //发布转换的数据
    tf::Transform transform;   //用于严密的数据转换，没有缩减，长用于像四元数 3x3 linear algebra
   
     ros::Rate rate(10.0);   //10秒
     while (node.ok()){
      // 设置相对位姿（点位置 旋转角度）跟随时最终turtle2会在carrot1的左边2米
     //  transform.setOrigin( tf::Vector3(0.0, 2.0, 0.0) );
       transform.setOrigin( tf::Vector3(0.0, 0.0, 0.0) );
       transform.setRotation( tf::Quaternion(0, 0, 0, 1) );
 
      //设置动态相对位姿，最终效果为跟随turtle1转圈圈
    //   transform.setOrigin( tf::Vector3(2.0*sin(ros::Time::now().toSec()), 2.0*cos(ros::Time::now().toSec()), 0.0) );
    //   transform.setRotation( tf::Quaternion(0, 0, 0, 1) );       

       br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "turtle1", "carrot1"));
       rate.sleep();
     }
     return 0;
 };