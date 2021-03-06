#pragma once

#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>

#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/physics.hh>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/tfMessage.h>

#include <realtime_tools/realtime_buffer.h>
#include <realtime_tools/realtime_publisher.h>

#include <nav_msgs/Odometry.h>

namespace gazebo {

// Kinematics parameters
#define TIGRA_STEERING_RATIO      1       // Ratio between steering wheel angle and tire angle

// Drag parameters
#define ROLLING_RESISTANCE_COEFF  0.01
#define AERO_DRAG_COEFF           0.35
#define GRAVITY_ACCEL             9.81
#define VEHICLE_MASS              1700.0
#define MAX_BRAKE_TORQUE          3000.0

#define STEER_P_RATE    10.0
#define SPEED_P_RATE    10.0

class TigraPlugin : public ModelPlugin {
public:
    TigraPlugin();
    virtual ~TigraPlugin();

protected:
    virtual void Load(physics::ModelPtr model, sdf::ElementPtr sdf);
    virtual void Reset();

private:
    void onCmdVel(const geometry_msgs::Twist& command);
    void updateCurrentState();
    void updateOdometry(double time_step);

    void twistTimerCallback(const ros::TimerEvent& event);
    void tfTimerCallback(const ros::TimerEvent& event);
    void OnUpdate(const common::UpdateInfo& info);

    void driveUpdate();
    void steeringUpdate(double time_step);

    void stopWheels();
    
    ros::NodeHandle n_;
    ros::Publisher pub_twist_;
    ros::Subscriber sub_vel_cmd_;
    ros::Timer twist_timer_;
    ros::Timer tf_timer_;

    tf::TransformBroadcaster br_;
    geometry_msgs::Twist twist_;
    bool rollover_;
    #if GAZEBO_MAJOR_VERSION >= 9
    ignition::math::Pose3d world_pose_;
    #else
    gazebo::math::Pose world_pose_;
    #endif
    event::ConnectionPtr update_connection_;
    physics::JointPtr steer_fl_joint_;
    physics::JointPtr steer_fr_joint_;
    physics::JointPtr wheel_rl_joint_;
    physics::JointPtr wheel_rr_joint_;
    physics::JointPtr wheel_fl_joint_;
    physics::JointPtr wheel_fr_joint_;
    physics::LinkPtr footprint_link_;
    common::Time last_update_time_;

    std::shared_ptr<realtime_tools::RealtimePublisher<nav_msgs::Odometry> > odom_pub_;
    std::shared_ptr<realtime_tools::RealtimePublisher<tf::tfMessage> > tf_odom_pub_;

    std::string odom_frame_id_;
    std::string base_frame_id_;

    double mps2rpm;
    double mps2rps;

    double linear_;  //   [m/s]
    double angular_; // [rad/s]

    // Arbitrarily set maximum steering rate to 800 deg/s
    const double MAX_STEERING_RATE = 800.0 * M_PI / 180.0 * TIGRA_STEERING_RATIO;

    // Odometry
    double x_;
    double y_;
    double yaw_;
    double publish_period_;
    common::Time last_odom_update_time_;

    // SDF parameters
    std::string robot_name_;
    std::string odom_frame_;
    bool pub_tf_;
    double max_steer_rad_;
    double tf_freq_;
    double wheelbase_;
    double track_width_;
    double wheel_radius_;

    // Steering values
    double right_angle_;
    double left_angle_;
    double target_angle_;
    double current_steering_angle_;

    double cur_virtual_steering_rad_;
    double cur_virtual_speed_rps_;

    // Throttle
    double target_speed_mps_;
    double throttle_cmd_;
    ros::Time throttle_stamp_;
    };

    GZ_REGISTER_MODEL_PLUGIN(TigraPlugin)

}
