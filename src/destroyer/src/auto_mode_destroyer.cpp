#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <chrono>
#include <random>

using namespace std::chrono_literals;

class AutoModeDestroyer : public rclcpp::Node {
public:
    AutoModeDestroyer() : Node("auto_mode_destroyer") {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/autonomous_destroyer", 10);
        timer_ = this->create_wall_timer(500ms, std::bind(&AutoModeDestroyer::timer_callback, this));
        RCLCPP_INFO(this->get_logger(), "Auto Mode Destroyer is Online - Sending Random Missions!");
    }

private:
    void timer_callback() {
        auto msg = geometry_msgs::msg::Twist();
        
        // Random generator untuk arah
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-1.0, 1.0);

        msg.linear.x = 5.0;            // Kecepatan tetap 5m/s
        msg.angular.z = dis(gen);      // Rotasi acak antara -1 dan 1 rad/s

        publisher_->publish(msg);
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AutoModeDestroyer>());
    rclcpp::shutdown();
    return 0;
}