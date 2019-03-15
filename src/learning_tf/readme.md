http://wiki.ros.org/tf/Tutorials


```
roslaunch learning_tf start_demo.launch

rosrun rqt_graph rqt_graph 

rostopic echo /tf

rosrun tf tf_monitor turtle2 turtle1   //检查时间戳
```


跟随：启动start_demo.launch 后，   点击终端后，用上下左右键控制turtle1运动，观察turtle2跟随运动

---

查看节点之间的tf关系

rosrun learning_tf tf_echo /odom /map
---

# test_urdf_tf.launch
使用urdf发布一个机器人上的坐标关系
(可能需要 robot_state_publisher joint_state_publisher搭配使用)

http://wiki.ros.org/robot_state_publisher
robot_state_publisher 用于发布link

http://wiki.ros.org/urdf/Tutorials/Using%20urdf%20with%20robot_state_publisher
state_publisher 用于发布joint(可以设置动态关系)

http://wiki.ros.org/joint_state_publisher
joint_state_publisher 用于发布joint联接

