//xx
// 两个进程 1.实现udp下激光数据接受
//2.对接受到的数据进行封装以 “/scan1”形式发布
// 更改： 使用vector 的reserve(897) 进行直接拷贝提高效率

#include "ros/ros.h"

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include <udp_get.h>

#define BUFF_LEN 128

void *udp_get( void *arg )
{
    int server_fd, ret;
    struct sockaddr_in ser_addr; 
    server_fd = socket(AF_INET, SOCK_DGRAM, 0); //AF_INET:IPV4;SOCK_DGRAM:UDP
    if(server_fd < 0)
    {
        printf("create socket fail!\n");
     //   return -1;
    }
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  //  ser_addr.sin_addr.s_addr = htonl(INADDR_ANY); //IP地址，需要进行网络序转换，INADDR_ANY：本地地址
    ser_addr.sin_port = htons(SERVER_PORT);  //端口号，需要网络序转换
    ret = bind(server_fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
    if(ret < 0)
    {
        printf("socket bind fail!\n");
      //  return -1;  //scan_pub.publish(scan_msg);

    }
   // close(server_fd);
    char buf[BUFF_LEN] = {0};  //接收缓冲区，1024字节
    socklen_t len;
    int count;
    struct sockaddr_in clent_addr;  //clent_addr用于记录发送方的地址信息
    while(ros::ok())
    {
        len = sizeof(clent_addr);
        count = recvfrom(server_fd, buf, BUFF_LEN, 0, (struct sockaddr*)&clent_addr, &len);  //recvfrom是拥塞函数，没有数据就一直拥塞
        if(count == -1)
        {
            printf("recieve data fail!\n");
          //  return;
        }     
        memcpy(&udp_data_buf,buf,sizeof(udp_data_buf)+1);
         std::cout<<udp_data_buf.ch<<"  ";
         std::cout<<udp_data_buf.flag<<"  "<< std::endl;
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

  ros::init(argc, argv, "scan_ser1");
  //ros::NodeHandle n;
    create_all_thread();
  //   ros::Rate loop_rate(10);
  ros::spin();
  return 0;
}
