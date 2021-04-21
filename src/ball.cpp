#include "ball.h"

namespace poolgame {
    Ball::Ball(int number, bool striped, glm::vec3 color, glm::vec2 position, int radius) {
        ball_num_ = number;
        ball_striped_ = striped;
        ball_color_ = color;
        ball_position_ = position;
        radius_ = radius;
    }
    int Ball::GetBallNumber() {
        return ball_num_;
    }
    glm::vec3 Ball::GetBallColor() {
        return ball_color_;
    }
    bool Ball::GetStriped() {
        return ball_striped_;
    }
    glm::vec2 Ball::GetBallPosition() {
        return ball_position_;
    }

    int Ball::GetRadius() {
        return radius_;
    }
}

