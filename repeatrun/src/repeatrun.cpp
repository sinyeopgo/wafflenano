#include "repeatrun.h"
#include "iostream"

void Repeatrun::resultCallback(const move_base_msgs::MoveBaseActionResult::ConstPtr& msg)
//목표에 도달했을 때 시작되는 콜백함수
{
  geometry_msgs::PoseStamped pose; //목표값을 퍼블리시할 변수 선언
  switch (bresult) //목표 순서 인식
  {
  case 0: //목표값이 초기위치(0번째)일때
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "map";

    pose.pose.position.x = 0.0920473701975;
    pose.pose.position.y = -0.0568635960137;
    pose.pose.position.z = 0.0;

    pose.pose.orientation.x = 0.0;
    pose.pose.orientation.y = 0.0;
    pose.pose.orientation.z = -0.00506686351129;
    pose.pose.orientation.w = 0.999987163365;
    //목표값 저장
    bresult = 1; //다음위치(1번째)
    pub.publish(pose); //목표값 퍼블리시
    break;
  case 1: //목표값이 1번째 일때
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "map";

    pose.pose.position.x = 3.65939569473;
    pose.pose.position.y = 0.00494170188904;
    pose.pose.position.z = 0.0;

    pose.pose.orientation.x = 0.0;
    pose.pose.orientation.y = 0.0;
    pose.pose.orientation.z = 0.707106796641;
    pose.pose.orientation.w = 0.707106765732;

    bresult = 2;
    pub.publish(pose);
    break;
  case 2: //목표값이 2번째 일때
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "map";

    pose.pose.position.x = 3.8541469574;
    pose.pose.position.y = 3.31570148468;
    pose.pose.position.z = 0.0;

    pose.pose.orientation.x = 0.0;
    pose.pose.orientation.y = 0.0;
    pose.pose.orientation.z = 1.0;
    pose.pose.orientation.w = 1.947071891e-07;

    bresult = 3;
    pub.publish(pose);
    break;
  default: //목표값이 3번째 일때
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "map";

    pose.pose.position.x = -0.214764147997;
    pose.pose.position.y = 3.28823661804;
    pose.pose.position.z = 0.0;

    pose.pose.orientation.x = 0.0;
    pose.pose.orientation.y = 0.0;
    pose.pose.orientation.z = -0.714918207066;
    pose.pose.orientation.w = 0.69920809292;

    bresult = 0; //다시 초기위치로
    pub.publish(pose);
    break;
  }
}
Repeatrun::Repeatrun(){
  pub = nh.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1000); //목표값 보낼 퍼블리셔선언
  init_pub = nh.advertise<geometry_msgs::PoseWithCovarianceStamped>("initialpose", 1000); //초기위치 보낼 퍼블리셔선언
  sub = nh.subscribe("/move_base/result", 1000, &Repeatrun::resultCallback,this); //목표에 도달했을 때 결과를 받을 섭스크라이버
}
void Repeatrun::initpose(){ //초기위치 설정 함수
  ROS_INFO("pose\n");
  geometry_msgs::PoseWithCovarianceStamped init_pose; //초기위치 퍼블리시할 변수 선언
  init_pose.header.stamp = ros::Time::now();
  init_pose.header.frame_id = "map";
  init_pose.pose.pose.position.x = 0.0920473701975;
  init_pose.pose.pose.position.y = -0.0568635960137;
  init_pose.pose.pose.position.z = 0.0;

  init_pose.pose.pose.orientation.x = 0.0;
  init_pose.pose.pose.orientation.y = 0.0;
  init_pose.pose.pose.orientation.z = -0.00506686351129;
  init_pose.pose.pose.orientation.w = 0.999987163365;

  init_pose.pose.covariance[0] = 0.25;
  init_pose.pose.covariance[7] = 0.25;
  init_pose.pose.covariance[35] = 0.06853892326654787;
  //초기위치 설정
  init_pub.publish(init_pose); //초기위치 퍼블리시
}
void Repeatrun::initrun(){ //처음 시작
  ROS_INFO("run\n");
  geometry_msgs::PoseStamped pose; //목표값 퍼블리시할 변수 선언
  pose.header.stamp = ros::Time::now();
  pose.header.frame_id = "map";

  pose.pose.position.x = 3.65939569473;
  pose.pose.position.y = 0.00494170188904;
  pose.pose.position.z = 0.0;

  pose.pose.orientation.x = 0.0;
  pose.pose.orientation.y = 0.0;
  pose.pose.orientation.z = 0.707106796641;
  pose.pose.orientation.w = 0.707106765732;
  //목표값 설정
  bresult = 2;
  pub.publish(pose); //목표값 퍼블리시
}
int main(int argc, char** argv){
  ros::init(argc, argv, "repeatrun_node");
  std::string goal,start;
  Repeatrun r;
  std::cin >> start; //초기위치
  if(start == "pose") r.initpose();
  std::cin >> goal; //목표
  if(start == "start") r.initrun();
  ros::spin();
  return 0;
};