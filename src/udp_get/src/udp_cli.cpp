//xx  2018-10-04
//实现laserscan数据读取并在udp下以结构体的形式发送出去

#include "ros/ros.h"

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include <udp_get.h>

void *udp_get( void *arg )
{
   // udp 
   int client_fd;
   struct sockaddr_in ser_addr;
    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_fd < 0)
    {
        printf("create socket fail!\n");
      //  return -1;
    }
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //注意网络序转换
    ser_addr.sin_port = htons(SERVER_PORT);  //注意网络序转换

  while(ros::ok())
    {     
      udp_data_buf.flag = 10;
      udp_data_buf.ch = "oooooookk";
      std::cout<<udp_data_buf.ch<<"  "<<std::endl;
      std::cout<<udp_data_buf.flag<<std::endl; 
      sendto(client_fd, (char *)&udp_data_buf, sizeof(udp_data_buf)+1,0,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
    }
}
void create_all_thread(void)
{
	pthread_t thread_udp_get;
	if( (pthread_create( &thread_udp_get , NULL , udp_get, NULL )) != 0 )
	{
		perror("Create the thread_joy fail");
		exit( 1 );
	}
}



int main(int argc, char **argv)
{
   ros::init(argc, argv, "scan_data_get");
 //  ros::NodeHandle n;
   create_all_thread();
    ros::spin();


  return 0;
}
