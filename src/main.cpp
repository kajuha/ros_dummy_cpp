#include <std_msgs/Empty.h>
#include <boost/thread.hpp>

#include "dummy_cpp/msg_int.h"
#include "dummy_cpp/msg_float.h"

#include <ros/ros.h>

#include <string>

void callBackInt(const dummy_cpp::msg_int::ConstPtr& vel) {
}

void callBackFloat(const dummy_cpp::msg_float::ConstPtr& vel) {
}

void fThread(int* thread_rate) {
    ros::NodeHandlePtr node = boost::make_shared<ros::NodeHandle>();
    ros::Rate rate(*thread_rate);

    while (ros::ok())
    {
        rate.sleep();
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "dummy_cpp");
    ros::NodeHandle nh("~");
    
    ros::Subscriber test1_sub = nh.subscribe("test1_sub_topic", 100, callBackInt);
    ros::Subscriber test2_sub = nh.subscribe("test2_sub_topic", 100, callBackFloat);
    
    ros::Publisher test1_pub = nh.advertise<dummy_cpp::msg_int>("test1_pub_topic", 100);
    ros::Publisher test2_pub = nh.advertise<dummy_cpp::msg_float>("test2_pub_topic", 100);

    dummy_cpp::msg_int msg1;
    dummy_cpp::msg_float msg2;

    std::string pkg_test_name;
    double pkg_test_ver;
    nh.getParam("pkg_test_name", pkg_test_name);
    nh.getParam("pkg_test_ver", pkg_test_ver);

    int thread_rate = 200;
    boost::thread hThread(fThread, &thread_rate);

    ros::Rate main_rate(1000);

    double time_cur = ros::Time::now().toSec();
    double time_pre = time_cur;
    double time_diff;

    while(ros::ok())
    {
        time_cur = ros::Time::now().toSec();
        time_diff = time_cur - time_pre;
#define PERIOD  0.1
        if ( time_diff > PERIOD) {
            time_pre = time_cur;
        }

        ros::spinOnce();

        main_rate.sleep();
    }

    hThread.join();
}
