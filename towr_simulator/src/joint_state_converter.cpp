#include <ros/ros.h>
#include <xpp_msgs/RobotStateJoint.h>
#include <std_msgs/Float64MultiArray.h>
#include <gazebo_msgs/SetModelState.h>

xpp_msgs::RobotStateJoint joints;

void jointCallback(const xpp_msgs::RobotStateJoint& msg) {
    joints = msg;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "converter");
    ros::NodeHandle nh, nh_private("~");

    std::vector<std::string> joint_names;
    nh.getParam("/hyq/default_controller/joints", joint_names);

    ros::Subscriber xpp_joint_sub = nh.subscribe("xpp/joint_hyq_des", 1, jointCallback);
    ros::Publisher command_pub = nh.advertise<std_msgs::Float64MultiArray>("default_controller/command", 1);
    ros::ServiceClient model_client = nh.serviceClient<gazebo_msgs::SetModelState>("/gazebo/set_model_state", 1);

    ros::Rate loop_rate(60);

    while(ros::ok()) {
        ros::spinOnce();
        std_msgs::Float64MultiArray msg;
        msg.data = joints.joint_state.position;
        gazebo_msgs::SetModelState state;
        state.request.model_state.model_name = "hyq";
        state.request.model_state.reference_frame = "world";
        state.request.model_state.pose = joints.base.pose;
        if(!msg.data.empty() && !joint_names.empty()){
            command_pub.publish(msg);
            // model_client.call(state);
        }
        loop_rate.sleep();
    }

}