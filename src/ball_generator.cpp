#include "ball.h"
#include "ball_generator.h"

namespace poolgame {
    BallGenerator::BallGenerator() {
        GenerateColors();
        GeneratePositions();
        GenerateVelocities();
        GenerateBalls();
    }

    void BallGenerator::GenerateBalls() {
        // white ball
        Ball white_ball = Ball(0, false, glm::vec3(1,1,1), positions_.at(0), velocities_.at(0), 10);
        balls_.push_back(white_ball);

        for (size_t i = 1; i < 9; i++) {
            Ball ball = Ball(i, false, colors_.at(i - 1), positions_.at(i), velocities_.at(i), 10);
            balls_.push_back(ball);
        }
        for (size_t i = 9; i < positions_.size(); i++) {
            Ball ball = Ball(i, true, colors_.at(i - 9), positions_.at(i), velocities_.at(i), 10);
            balls_.push_back(ball);
        }
    }

    void BallGenerator::GenerateColors() {
        colors_ = {glm::vec3(1,1,0), glm::vec3(0,0,1),
                   glm::vec3(1,0,0), glm::vec3(0.5f,0,0.5f),
                   glm::vec3(1,0.4f,0), glm::vec3(0,0.8f,0),
                   glm::vec3(0.72f,0.07f,0.14f), glm::vec3(0,0,0)};
    }

    void BallGenerator::GeneratePositions() {
        positions_ = {glm::vec2(250, 500), glm::vec2(700, 500), glm::vec2(720, 510),
                      glm::vec2(720, 490), glm::vec2(740, 520), glm::vec2(740, 500),
                      glm::vec2(740, 480), glm::vec2(760, 530), glm::vec2(760, 510),
                      glm::vec2(760, 490), glm::vec2(760, 470), glm::vec2(780, 540),
                      glm::vec2(780, 520), glm::vec2(780, 500), glm::vec2(780, 480),
                      glm::vec2(780, 460)};
    }

    void BallGenerator::GenerateVelocities() {
        for(size_t i = 0; i < positions_.size(); i++) {
            velocities_.push_back(glm::vec2(0,0));
        }
    }

    std::vector<Ball> BallGenerator::GetBalls() {
        return balls_;
    }

    std::vector<glm::vec3> BallGenerator::GetColors() {
        std::vector<glm::vec3> temp_colors;
        for (size_t i = 0; i < balls_.size(); i++) {
            temp_colors.push_back(balls_.at(i).GetBallColor());
        }
        return temp_colors;
    }

    std::vector<glm::vec2> BallGenerator::GetPositions() {
        return positions_;
    }

    std::vector<glm::vec2> BallGenerator::GetVelocities() {
        return velocities_;
    }
}

