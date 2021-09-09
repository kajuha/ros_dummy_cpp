#include <std_msgs/Empty.h>
#include <boost/thread.hpp>

#include <eigen3/Eigen/Dense>

using Eigen::MatrixXd;

#include "dummy_cpp/msg_int.h"
#include "dummy_cpp/msg_float.h"

#include <ros/ros.h>

#include <string>

class ClassTest {
    public:
    // short *array;
    std::vector<short> array;

    public:
    ClassTest(int num) {
        std::cout << "construct class : " << array.size() << std::endl;
        array.push_back(1);
        array.push_back(2);
        array.push_back(3);
        std::cout << "allocate array: " << array.size() << std::endl;
    }

    ClassTest(int num, int abc) {
        std::cout << "construct class : " << array.size() << std::endl;
        array = std::vector<short>(num);
        array[0] = 3;
        array[1] = 4;
        array[2] = 5;
        std::cout << "allocate array: " << array.size() << std::endl;
    }

    ~ClassTest() {
        std::cout << "destruct array: " << array.size() << std::endl;
    }
};

void callBackInt(const dummy_cpp::msg_int::ConstPtr& vel) {
}

void callBackFloat(const dummy_cpp::msg_float::ConstPtr& vel) {
}

void fThread(int* thread_rate) {
    ros::NodeHandlePtr node = boost::make_shared<ros::NodeHandle>();
    ros::Rate rate(*thread_rate);

    // while (ros::ok())
    // {
    //     rate.sleep();
    // }
}

int main(int argc, char** argv)
{
    ClassTest test1(11);
    test1 = ClassTest(11, 11);

    for (short x: test1.array) {
        std::cout << "indexing: " << x << std::endl;
    }
    // ClassTest test2(11, 11);
    // other library include test
    MatrixXd a(2, 2);
    MatrixXd b(2, 2);
    MatrixXd c(2, 2);
    a << 1, 0, 0, 1;
    b << 1, 2, 3, 4;
    c = a * b;
    // std::cout << c << std::endl;

    ros::init(argc, argv, "dummy_cpp");
    ros::NodeHandle nh("~");

    std::vector<std::string> keys;
    // nh.getParamNames(keys);
    // std::cout << "getParamNames : " << std::endl;
    // for (int i=0; i<keys.size(); i++) {
    //     std::cout << keys[i];
    //     std::cout << "\n";
    // }
    // std::cout << std::endl;
    
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

//     while(ros::ok())
//     {
//         time_cur = ros::Time::now().toSec();
//         time_diff = time_cur - time_pre;
// #define PERIOD  0.1
//         if ( time_diff > PERIOD) {
//             time_pre = time_cur;
//         }

//         // printf("timd_diff: %lf\n", time_diff);

//         ros::spinOnce();

//         main_rate.sleep();
//     }

    hThread.join();
}
