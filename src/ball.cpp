#include "ball.h"

namespace poolgame {
    Ball::Ball(int number, bool striped, glm::vec3 color, glm::vec2 position, glm::vec2 velocity, int radius) {
        ball_num_ = number;
        ball_striped_ = striped;
        ball_color_ = color;
        ball_position_ = position;
        ball_velocity_ = velocity;
        radius_ = radius;
        show_ = true;
    }
    int Ball::GetBallNumber() {
        return ball_num_;
    }
    glm::vec3 Ball::GetBallColor() const {
        return ball_color_;
    }
    bool Ball::GetStriped() {
        return ball_striped_;
    }
    glm::vec2 Ball::GetBallPosition() {
        return ball_position_;
    }

    glm::vec2 Ball::GetBallVelocity() {
        return ball_velocity_;
    }

    int Ball::GetRadius() {
        return radius_;
    }

    bool Ball::GetShow() {
        return show_;
    }
}

