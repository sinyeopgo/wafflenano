#include <iostream>
#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
int main(int argc, char** argv){
  ros::init(argc, argv, "remote_wafflenano");
  ros::NodeHandle nh;
  ros::Publisher pub, init_pub;
  float x,y,z,w;
  geometry_msgs::PoseWithCovarianceStamped init_pose; //초기위치 퍼블리시할 변수 선언
  pub = nh.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 1000); //목표값 보낼 퍼블리셔선언
  init_pub = nh.advertise<geometry_msgs::PoseWithCovarianceStamped>("initialpose", 1000); //초기위치 보낼 퍼블리셔선언
  ROS_INFO("initpose:");
  std::cin>>x>>y>>z>>w;
  init_pose.header.stamp = ros::Time::now();
  init_pose.header.frame_id = "map";
  init_pose.pose.pose.position.x = x;
  init_pose.pose.pose.position.y = y;
  init_pose.pose.pose.position.z = 0.0;

  init_pose.pose.pose.orientation.x = 0.0;
  init_pose.pose.pose.orientation.y = 0.0;
  init_pose.pose.pose.orientation.z = z;
  init_pose.pose.pose.orientation.w = w;

  init_pose.pose.covariance[0] = 0.25;
  init_pose.pose.covariance[7] = 0.25;
  init_pose.pose.covariance[35] = 0.06853892326654787;
  //초기위치 설정
  init_pub.publish(init_pose); //초기위치 퍼블리시
  while(ros::ok()){
    std::cin>>x>>y>>z>>w;
    geometry_msgs::PoseStamped pose; //목표값을 퍼블리시할 변수 선언
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "map";

    pose.pose.position.x = x;
    pose.pose.position.y = y;
    pose.pose.position.z = 0.0;

    pose.pose.orientation.x = 0.0;
    pose.pose.orientation.y = 0.0;
    pose.pose.orientation.z = z;
    pose.pose.orientation.w = w;
    //목표값 저장
    pub.publish(pose); //목표값 퍼블리시
    ros::spinOnce();
  }
  return 0;
};