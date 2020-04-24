#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "std_msgs/String.h"
#include <gtest/gtest.h>

#include <klepsydra/mem_core/basic_middleware_provider.h>
#include <klepsydra/core/cache_listener.h>

#include <kpsr_ros_serialization/primitive_type_ros_mapper.h>

#include <kpsr_ros_core/to_ros_middleware_provider.h>
#include <kpsr_ros_core/from_ros_middleware_provider.h>

#include "pose_builder.h"

#include "pose_mapper.h"
#include "posestamped_mapper.h"
#include "pose_with_covariance_mapper.h"
#include "posestamped_with_covariance_mapper.h"

TEST(KpsrRosGeometryTest, quaternionToEulerTest) {

    kpsr::geometry::PoseEventData poseEventData;

    // Rotations by pi/2
    {
        double qx = 1.0;
        double qy = 0.0;
        double qz = 0.0;
        double qw = 1.0;

        kpsr::geometry::ros_mdlw::PoseBuilder::createPoseEvent("", 0, 0, 0, qx, qy, qz, qw, nullptr, true, poseEventData);

        ASSERT_DOUBLE_EQ(poseEventData.roll, M_PI/2);
        ASSERT_DOUBLE_EQ(poseEventData.pitch, 0);
        ASSERT_DOUBLE_EQ(poseEventData.yaw, 0);
    }
    {
        double qx = 0.0;
        double qy = 1.0;
        double qz = 0.0;
        double qw = 1.0;

        kpsr::geometry::ros_mdlw::PoseBuilder::createPoseEvent("", 0, 0, 0, qx, qy, qz, qw, nullptr, true, poseEventData);

        ASSERT_DOUBLE_EQ(poseEventData.roll, 0);
        ASSERT_DOUBLE_EQ(poseEventData.pitch, M_PI/2);
        ASSERT_DOUBLE_EQ(poseEventData.yaw, 0);
    }
    {
        double qx = 0.0;
        double qy = 0.0;
        double qz = 1.0;
        double qw = 1.0;

        kpsr::geometry::ros_mdlw::PoseBuilder::createPoseEvent("", 0, 0, 0, qx, qy, qz, qw, nullptr, true, poseEventData);

        ASSERT_DOUBLE_EQ(poseEventData.roll, 0);
        ASSERT_DOUBLE_EQ(poseEventData.pitch, 0);
        ASSERT_DOUBLE_EQ(poseEventData.yaw, M_PI/2);
    }
}

TEST(KpsrRosGeometryTest, eulerToQuaternionTest) {

    geometry_msgs::Pose pose;

    // Rotations by pi/2
    {
        double roll = M_PI/2;
        double pitch = 0.0;
        double yaw = 0.0;

        kpsr::geometry::ros_mdlw::PoseBuilder::createPose(0, 0, 0, 0, 0 , 0 , 0, roll, pitch, yaw, true, pose);

        ASSERT_DOUBLE_EQ(pose.orientation.x, 1.0/sqrt(2));
        ASSERT_DOUBLE_EQ(pose.orientation.y, 0.0);
        ASSERT_DOUBLE_EQ(pose.orientation.z, 0.0);
        ASSERT_DOUBLE_EQ(pose.orientation.w, 1.0/sqrt(2));
    }
    {
        double roll = 0.0;
        double pitch = M_PI/2;
        double yaw = 0.0;

        kpsr::geometry::ros_mdlw::PoseBuilder::createPose(0, 0, 0, 0, 0 , 0 , 0, roll, pitch, yaw, true, pose);

        ASSERT_DOUBLE_EQ(pose.orientation.x, 0.0);
        ASSERT_DOUBLE_EQ(pose.orientation.y, 1.0/sqrt(2));
        ASSERT_DOUBLE_EQ(pose.orientation.z, 0.0);
        ASSERT_DOUBLE_EQ(pose.orientation.w, 1.0/sqrt(2));
    }
    {
        double roll = 0.0;
        double pitch = 0.0;
        double yaw = M_PI/2;

        kpsr::geometry::ros_mdlw::PoseBuilder::createPose(0, 0, 0, 0, 0 , 0 , 0, roll, pitch, yaw, true, pose);

        ASSERT_DOUBLE_EQ(pose.orientation.x, 0.0);
        ASSERT_DOUBLE_EQ(pose.orientation.y, 0.0);
        ASSERT_DOUBLE_EQ(pose.orientation.z, 1.0/sqrt(2));
        ASSERT_DOUBLE_EQ(pose.orientation.w, 1.0/sqrt(2));
    }
}

TEST(KpsrRosGeometryTest, poseToPoseEvent) {
    geometry_msgs::Pose pose;
    kpsr::geometry::PoseEventData poseEventData;

    std::srand(std::time(0));
    pose.position.x = 1.0 * std::rand();
    pose.position.y = 1.0 * std::rand();
    pose.position.z = 1.0 * std::rand();
    
    pose.orientation.x = 1.0;
    pose.orientation.y = 0.0;
    pose.orientation.z = 0.0;
    pose.orientation.w = 1.0;

    kpsr::Mapper<kpsr::geometry::PoseEventData, geometry_msgs::Pose> mapper;
    mapper.fromMiddleware(pose, poseEventData);

    ASSERT_EQ(pose.position.x, poseEventData.x);
    ASSERT_EQ(pose.position.y, poseEventData.y);
    ASSERT_EQ(pose.position.z, poseEventData.z);

    ASSERT_EQ(pose.orientation.x, poseEventData.qx);
    ASSERT_EQ(pose.orientation.y, poseEventData.qy);
    ASSERT_EQ(pose.orientation.z, poseEventData.qz);
    ASSERT_EQ(pose.orientation.w, poseEventData.qw);

    ASSERT_DOUBLE_EQ(poseEventData.roll, M_PI/2);
    ASSERT_DOUBLE_EQ(poseEventData.pitch, 0);
    ASSERT_DOUBLE_EQ(poseEventData.yaw, 0);
}

TEST(KpsrRosGeometryTest, poseEventToPose) {
    geometry_msgs::Pose pose;
    kpsr::geometry::PoseEventData poseEventData;

    ros::Time::init();
    std::srand(std::time(0));
    poseEventData.x = 1.0 * std::rand();
    poseEventData.y = 1.0 * std::rand();
    poseEventData.z = 1.0 * std::rand();
    poseEventData.qx = 0.0;
    poseEventData.qy = 0.0;
    poseEventData.qz = 0.0;
    poseEventData.qw = 1.0;

    poseEventData.roll = 0.0;
    poseEventData.pitch = M_PI/2;
    poseEventData.yaw = 0.0;

    kpsr::Mapper<kpsr::geometry::PoseEventData, geometry_msgs::Pose> mapper;
    mapper.toMiddleware(poseEventData, pose);

    ASSERT_DOUBLE_EQ(pose.orientation.x, 0.0);
    ASSERT_DOUBLE_EQ(pose.orientation.y, 1.0/sqrt(2));
    ASSERT_DOUBLE_EQ(pose.orientation.z, 0.0);
    ASSERT_DOUBLE_EQ(pose.orientation.w, 1.0/sqrt(2));

    // Assure that roll/pitch/yaw data was used rather than quaternion info from poseEventData.
    ASSERT_NE(pose.orientation.y, poseEventData.qy);
}

TEST(KpsrRosGeometryTest, poseStampedToPoseEvent) {
    geometry_msgs::PoseStamped pose;
    kpsr::geometry::PoseEventData poseEventData;

    std::srand(std::time(0));
    pose.pose.position.x = 1.0 * std::rand();
    pose.pose.position.y = 1.0 * std::rand();
    pose.pose.position.z = 1.0 * std::rand();
    pose.pose.orientation.x = 1.0;
    pose.pose.orientation.y = 0.0;
    pose.pose.orientation.z = 0.0;
    pose.pose.orientation.w = 1.0;

    kpsr::Mapper<kpsr::geometry::PoseEventData, geometry_msgs::PoseStamped> mapper;
    mapper.fromMiddleware(pose, poseEventData);

    ASSERT_EQ(pose.pose.position.x, poseEventData.x);
    ASSERT_EQ(pose.pose.position.y, poseEventData.y);
    ASSERT_EQ(pose.pose.position.z, poseEventData.z);

    ASSERT_EQ(pose.pose.orientation.x, poseEventData.qx);
    ASSERT_EQ(pose.pose.orientation.y, poseEventData.qy);
    ASSERT_EQ(pose.pose.orientation.z, poseEventData.qz);
    ASSERT_EQ(pose.pose.orientation.w, poseEventData.qw);

    ASSERT_DOUBLE_EQ(poseEventData.roll, M_PI/2);
    ASSERT_DOUBLE_EQ(poseEventData.pitch, 0);
    ASSERT_DOUBLE_EQ(poseEventData.yaw, 0);
}

TEST(KpsrRosGeometryTest, poseEventToPoseStamped) {
    geometry_msgs::PoseStamped pose;
    kpsr::geometry::PoseEventData poseEventData;
    ros::Time::init();

    std::srand(std::time(0));
    poseEventData.x = 1.0 * std::rand();
    poseEventData.y = 1.0 * std::rand();
    poseEventData.z = 1.0 * std::rand();
    poseEventData.qx = 0.0;
    poseEventData.qy = 0.0;
    poseEventData.qz = 0.0;
    poseEventData.qw = 1.0;

    poseEventData.roll = 0.0;
    poseEventData.pitch = M_PI/2;
    poseEventData.yaw = 0.0;

    kpsr::Mapper<kpsr::geometry::PoseEventData, geometry_msgs::PoseStamped> mapper;
    mapper.toMiddleware(poseEventData, pose);

    ASSERT_DOUBLE_EQ(pose.pose.orientation.x, 0.0);
    ASSERT_DOUBLE_EQ(pose.pose.orientation.y, 1.0/sqrt(2));
    ASSERT_DOUBLE_EQ(pose.pose.orientation.z, 0.0);
    ASSERT_DOUBLE_EQ(pose.pose.orientation.w, 1.0/sqrt(2));

    // Assure that roll/pitch/yaw data was used rather than quaternion info from poseEventData.
    ASSERT_NE(pose.pose.orientation.y, poseEventData.qy);
}

TEST(KpsrRosGeometryTest, poseWithCovarianceToPoseEvent) {
    geometry_msgs::PoseWithCovariance pose;
    kpsr::geometry::PoseEventData poseEventData;

    std::srand(std::time(0));
    pose.pose.position.x = 1.0 * std::rand();
    pose.pose.position.y = 1.0 * std::rand();
    pose.pose.position.z = 1.0 * std::rand();
    pose.pose.orientation.x = 1.0;
    pose.pose.orientation.y = 0.0;
    pose.pose.orientation.z = 0.0;
    pose.pose.orientation.w = 1.0;

    kpsr::Mapper<kpsr::geometry::PoseEventData, geometry_msgs::PoseWithCovariance> mapper;
    mapper.fromMiddleware(pose, poseEventData);

    ASSERT_EQ(pose.pose.position.x, poseEventData.x);
    ASSERT_EQ(pose.pose.position.y, poseEventData.y);
    ASSERT_EQ(pose.pose.position.z, poseEventData.z);

    ASSERT_EQ(pose.pose.orientation.x, poseEventData.qx);
    ASSERT_EQ(pose.pose.orientation.y, poseEventData.qy);
    ASSERT_EQ(pose.pose.orientation.z, poseEventData.qz);
    ASSERT_EQ(pose.pose.orientation.w, poseEventData.qw);

    ASSERT_DOUBLE_EQ(poseEventData.roll, M_PI/2);
    ASSERT_DOUBLE_EQ(poseEventData.pitch, 0);
    ASSERT_DOUBLE_EQ(poseEventData.yaw, 0);
}

TEST(KpsrRosGeometryTest, poseEventToPoseWithCovariance) {
    geometry_msgs::PoseWithCovariance pose;
    kpsr::geometry::PoseEventData poseEventData;
    ros::Time::init();

    std::srand(std::time(0));
    poseEventData.x = 1.0 * std::rand();
    poseEventData.y = 1.0 * std::rand();
    poseEventData.z = 1.0 * std::rand();
    poseEventData.qx = 0.0;
    poseEventData.qy = 0.0;
    poseEventData.qz = 0.0;
    poseEventData.qw = 1.0;

    poseEventData.roll = 0.0;
    poseEventData.pitch = M_PI/2;
    poseEventData.yaw = 0.0;

    kpsr::Mapper<kpsr::geometry::PoseEventData, geometry_msgs::PoseWithCovariance> mapper;
    mapper.toMiddleware(poseEventData, pose);

    ASSERT_DOUBLE_EQ(pose.pose.orientation.x, 0.0);
    ASSERT_DOUBLE_EQ(pose.pose.orientation.y, 1.0/sqrt(2));
    ASSERT_DOUBLE_EQ(pose.pose.orientation.z, 0.0);
    ASSERT_DOUBLE_EQ(pose.pose.orientation.w, 1.0/sqrt(2));

    // Assure that roll/pitch/yaw data was used rather than quaternion info from poseEventData.
    ASSERT_NE(pose.pose.orientation.y, poseEventData.qy);
}

TEST(KpsrRosGeometryTest, poseStampedWithCovarianceToPoseEvent) {
    geometry_msgs::PoseWithCovarianceStamped pose;
    kpsr::geometry::PoseEventData poseEventData;

    std::srand(std::time(0));
    pose.pose.pose.position.x = 1.0 * std::rand();
    pose.pose.pose.position.y = 1.0 * std::rand();
    pose.pose.pose.position.z = 1.0 * std::rand();
    pose.pose.pose.orientation.x = 1.0;
    pose.pose.pose.orientation.y = 0.0;
    pose.pose.pose.orientation.z = 0.0;
    pose.pose.pose.orientation.w = 1.0;

    kpsr::Mapper<kpsr::geometry::PoseEventData, geometry_msgs::PoseWithCovarianceStamped> mapper;
    mapper.fromMiddleware(pose, poseEventData);

    ASSERT_EQ(pose.pose.pose.position.x, poseEventData.x);
    ASSERT_EQ(pose.pose.pose.position.y, poseEventData.y);
    ASSERT_EQ(pose.pose.pose.position.z, poseEventData.z);

    ASSERT_EQ(pose.pose.pose.orientation.x, poseEventData.qx);
    ASSERT_EQ(pose.pose.pose.orientation.y, poseEventData.qy);
    ASSERT_EQ(pose.pose.pose.orientation.z, poseEventData.qz);
    ASSERT_EQ(pose.pose.pose.orientation.w, poseEventData.qw);

    ASSERT_DOUBLE_EQ(poseEventData.roll, M_PI/2);
    ASSERT_DOUBLE_EQ(poseEventData.pitch, 0);
    ASSERT_DOUBLE_EQ(poseEventData.yaw, 0);
}

TEST(KpsrRosGeometryTest, poseEventToPoseStampedWithCovariance) {
    geometry_msgs::PoseWithCovarianceStamped pose;
    kpsr::geometry::PoseEventData poseEventData;
    ros::Time::init();

    std::srand(std::time(0));
    poseEventData.x = 1.0 * std::rand();
    poseEventData.y = 1.0 * std::rand();
    poseEventData.z = 1.0 * std::rand();
    poseEventData.qx = 0.0;
    poseEventData.qy = 0.0;
    poseEventData.qz = 0.0;
    poseEventData.qw = 1.0;

    poseEventData.roll = 0.0;
    poseEventData.pitch = M_PI/2;
    poseEventData.yaw = 0.0;

    kpsr::Mapper<kpsr::geometry::PoseEventData, geometry_msgs::PoseWithCovarianceStamped> mapper;
    mapper.toMiddleware(poseEventData, pose);

    ASSERT_DOUBLE_EQ(pose.pose.pose.orientation.x, 0.0);
    ASSERT_DOUBLE_EQ(pose.pose.pose.orientation.y, 1.0/sqrt(2));
    ASSERT_DOUBLE_EQ(pose.pose.pose.orientation.z, 0.0);
    ASSERT_DOUBLE_EQ(pose.pose.pose.orientation.w, 1.0/sqrt(2));

    // Assure that roll/pitch/yaw data was used rather than quaternion info from poseEventData.
    ASSERT_NE(pose.pose.pose.orientation.y, poseEventData.qy);
}
