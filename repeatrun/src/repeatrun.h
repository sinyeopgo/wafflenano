#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <move_base_msgs/MoveBaseActionResult.h>

class Repeatrun{
  ros::NodeHandle nh;
  ros::Publisher pub;
  ros::Publisher init_pub;
  ros::Subscriber sub;
  uint bresult;
public:
  Repeatrun();
  void resultCallback(const move_base_msgs::MoveBaseActionResult::ConstPtr& msg);
  void initrun();
  void initpose();
};