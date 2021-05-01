#include "ball.h"
#include "ball_generator.h"

namespace poolgame {

    BallGenerator::BallGenerator() {
        GenerateColors();
        GeneratePositions();
        GenerateVelocities();
        GenerateBalls();
        GenerateShows();
        GenerateStripes();
    }

//    void BallGenerator::DrawBalls() const {
//        for (size_t i = 0; i < balls_.size(); i++) {
//            if (shows_.at(i) == true) {
//                cinder::gl::color(colors_.at(i).x, colors_.at(i).y, colors_.at(i).z);
//                cinder::gl::drawSolidCircle(positions_.at(i), radius_, -1);
//                if (i > 8) {
//                    cinder::gl::color(1,1,1);
//                    cinder::gl::drawStrokedCircle(positions_.at(i), radius_, -1);
//                    cinder::gl::drawStrokedCircle(positions_.at(i), radius_ - 1, -1);
//                }
//            }
//        }
//    }
//
//    void BallGenerator::UpdateBalls() {
//        for (size_t i = 0; i < balls_.size(); i++) {
//            if (shows_.at(i) == true) {
//                BallCollisions(i);
//                EdgeCollisions(i);
//                float time_step = 1;
//                positions_.at(i) = positions_.at(i) + (velocities_.at(i) * time_step);
//                Friction(i);
//            }
//        }
//    }
//
//    void BallGenerator::Friction(int specific_particle) {
//        float friction_ = 0.994;
//        velocities_.at(specific_particle).x = friction_ * velocities_.at(specific_particle).x;
//        velocities_.at(specific_particle).y = friction_ * velocities_.at(specific_particle).y;
//        if (abs(velocities_.at(specific_particle).x - 0) < 0.01) {
//            velocities_.at(specific_particle).x = 0;
//        }
//        if (abs(velocities_.at(specific_particle).y - 0) < 0.01) {
//            velocities_.at(specific_particle).y = 0;
//        }
//    }
//
//    void BallGenerator::EdgeCollisions(int specific_particle) {
//        int top_left_x_ = 100;
//        int top_left_y_ = 250;
//        int bottom_right_x_ = 900;
//        int bottom_right_y_ = 750;
//        // updates velocities for bounce left and right walls
//        if (positions_.at(specific_particle).x - 10 <= top_left_x_ + 25 || positions_.at(specific_particle).x + 10 >= bottom_right_x_ - 25) {
//            velocities_.at(specific_particle).x = velocities_.at(specific_particle).x * -1;
//        }
//        // updates velocities for bounce up and down walls
//        if (positions_.at(specific_particle).y - 10 <= top_left_y_ + 25 || positions_.at(specific_particle).y + 10 >= bottom_right_y_ - 25) {
//            velocities_.at(specific_particle).y = velocities_.at(specific_particle).y * -1;
//        }
//    }
//
//    void BallGenerator::BallCollisions(int specific_particle) {
//        if (!FindCollidedBalls().empty()) {
//            int first_ball = FindCollidedBalls().at(0);
//            int second_ball = FindCollidedBalls().at(1);
//
//            if (CheckBallsMovingTowardsEachOther(first_ball, second_ball)) {
//                glm::vec2 updated_first =
//                        CalculateCollidedVelocity(first_ball, second_ball);
//                glm::vec2 updated_second =
//                        CalculateCollidedVelocity(second_ball, first_ball);
//
//                velocities_[first_ball] = updated_first;
//                velocities_[second_ball] = updated_second;
//            }
//        }
//    }
//
//    bool BallGenerator::Movement() const {
//        bool movement = false;
//        for(size_t i = 0; i < balls_.size(); i++) {
//            if (shows_.at(i) == true) {
//                if (velocities_.at(i) != glm::vec2(0, 0)) {
//                    movement = true;
//                }
//            }
//        }
//        return movement;
//    }
//
//    bool BallGenerator::AllBallsGoneSolid() const {
//        bool all_gone = true;
//        for (size_t i = 1; i < 8; i++) {
//            if (shows_.at(i) == true) {
//                all_gone = false;
//            }
//        }
//        return all_gone;
//    }
//
//    bool BallGenerator::AllBallsGoneStriped() const {
//        bool all_gone = true;
//        for (size_t i = 9; i < 16; i++) {
//            if (shows_.at(i) == true) {
//                all_gone = false;
//            }
//        }
//        return all_gone;
//    }
//
//    bool BallGenerator::CheckBallsMovingTowardsEachOther(int first, int second) {
//        glm::vec2 subtracted_velocities = velocities_.at(first) - velocities_.at(second);
//        glm::vec2 subtracted_positions = positions_.at(first) - positions_.at(second);
//        if (glm::dot(subtracted_velocities, subtracted_positions) < 0) {
//            return true;
//        }
//        return false;
//    }
//
//    std::vector<int> BallGenerator::FindCollidedBalls() {
//        std::vector<int> collided_balls;
//        for (size_t i = 0; i < balls_.size(); i++) {
//            for (size_t j = 0; j < balls_.size(); j++) {
//                int contact_distance = 2 * radius_;
//                if (glm::distance(positions_.at(i), positions_.at(j)) <=
//                    (contact_distance) &&
//                    i != j) {
//                    if (shows_.at(i) == true && shows_.at(j) == true) {
//                        collided_balls.push_back(i);
//                        collided_balls.push_back(j);
//                    }
//                }
//            }
//        }
//        return collided_balls;
//    }
//
//    glm::vec2 BallGenerator::CalculateCollidedVelocity(int first, int second) {
//        glm::vec2 subtraction_velocities = velocities_.at(first) -
//                                           velocities_.at(second);
//        glm::vec2 subtraction_positions = positions_.at(first) -
//                                          positions_.at(second);
//        float dot_product = glm::dot(subtraction_velocities, subtraction_positions);
//        float position_length_squared =
//                glm::length(subtraction_positions) * glm::length(subtraction_positions);
//        glm::vec2 multiplication = (dot_product / position_length_squared) * subtraction_positions;
//        glm::vec2 collided_velocity = velocities_.at(first) - multiplication;
//        return collided_velocity;
//    }
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
        radius_ = balls_.at(0).GetRadius();
    }

    void BallGenerator::GenerateColors() {
        colors_ = {glm::vec3(1,1,0), glm::vec3(0,0,1),
                   glm::vec3(1,0,0), glm::vec3(0.5f,0,0.5f),
                   glm::vec3(1,0.4f,0), glm::vec3(0,0.8f,0),
                   glm::vec3(0.72f,0.07f,0.14f), glm::vec3(0,0,0)};
    }

    void BallGenerator::GeneratePositions() {
        positions_ = {glm::vec2(250, 500), glm::vec2(700, 500), glm::vec2(720.1, 510.05),
                      glm::vec2(720.1, 489.95), glm::vec2(740.2, 520.1), glm::vec2(740.2, 500),
                      glm::vec2(740.2, 479.9), glm::vec2(760.3, 530.15), glm::vec2(760.3, 510.05),
                      glm::vec2(760.3, 489.95), glm::vec2(760.3, 469.85), glm::vec2(780.4, 540.2),
                      glm::vec2(780.4, 520.1), glm::vec2(780.4, 500), glm::vec2(780.4, 479.9),
                      glm::vec2(780.4, 459.8)};
    }

    void BallGenerator::GenerateVelocities() {
        for(size_t i = 0; i < positions_.size(); i++) {
            velocities_.push_back(glm::vec2(0,0));
        }
    }

    void BallGenerator::GenerateShows() {
        for (size_t i = 0; i < balls_.size(); i++) {
            shows_.push_back(balls_.at(i).GetShow());
        }
    }

    void BallGenerator::GenerateStripes() {
        for (size_t i = 0; i < balls_.size(); i++) {
            striped_.push_back(balls_.at(i).GetStriped());
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

    std::vector<bool> BallGenerator::GetShows() {
        return shows_;
    }

    std::vector<bool> BallGenerator::GetStripes() {
        return striped_;
    }


}

