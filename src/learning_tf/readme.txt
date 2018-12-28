http://wiki.ros.org/tf/Tutorials

roslaunch learning_tf start_demo.launch
rosrun rqt_graph rqt_graph 
rostopic echo /tf
rosrun tf tf_monitor turtle2 turtle1   //检查时间戳

跟随：启动start_demo.launch 后，   点击终端后，用上下左右键控制turtle1运动，观察turtle2跟随运动
