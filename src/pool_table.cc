#include <ball_generator.h>
#include "pool_table.h"

namespace poolgame {

    PoolTable::PoolTable() {
        friction_ = 0.01;
        top_left_x_ = 100;
        top_left_y_ = 250;
        bottom_right_x_ = 900;
        bottom_right_y_ = 750;
        collection_of_balls_ = BallGenerator();
        ball_positions_ = collection_of_balls_.GetPositions();
        ball_velocities_ = collection_of_balls_.GetVelocities();
        ball_colors_ = collection_of_balls_.GetColors();
        num_of_balls_ = collection_of_balls_.GetBalls().size();
        cue_end_ = ball_positions_.at(0);
        holes_ = GenerateHoles();
    }

    void PoolTable::Display() const {
        DrawTable();
        DrawHoles();
        DrawBalls();
        if (Movement() == false) {
            DrawCue();
        }
    }

    void PoolTable::Update() {
        for (size_t i = 0; i < num_of_balls_; i++) {
            //HoleCollision(i);
            BallCollisions(i);
            EdgeCollisions(i);
            ball_positions_.at(i) = ball_positions_.at(i) + ball_velocities_.at(i);
            Friction(i);
        }
    }

    std::vector<glm::vec2> PoolTable::GenerateHoles() {
        std::vector<glm::vec2> holes = {glm::vec2(120, 270), glm::vec2(880, 730), glm::vec2(120, 730),
                                        glm::vec2(880, 270), glm::vec2(500, 730), glm::vec2(500, 270)};
        return holes;
    }

    void PoolTable::EdgeCollisions(int specific_particle) {
        // updates velocities for bounce left and right walls
        if (ball_positions_.at(specific_particle).x - 10 <= top_left_x_ + 25 || ball_positions_.at(specific_particle).x + 10 >= bottom_right_x_ - 25) {
            ball_velocities_.at(specific_particle).x = ball_velocities_.at(specific_particle).x * -1;
        }
        // updates velocities for bounce up and down walls
        if (ball_positions_.at(specific_particle).y - 10 <= top_left_y_ + 25 || ball_positions_.at(specific_particle).y + 10 >= bottom_right_y_ - 25) {
            ball_velocities_.at(specific_particle).y = ball_velocities_.at(specific_particle).y * -1;
        }
    }

    void PoolTable::HoleCollision(int specific_particle) {
        for(size_t i = 0; i < holes_.size(); i++) {
            if (glm::distance(ball_positions_.at(specific_particle), holes_.at(i)) <= 25) {
                ball_positions_.erase(ball_positions_.begin() + specific_particle);
            }
        }
    }
    // make changes
    void PoolTable::Friction(int specific_particle) {
        if (ball_velocities_.at(specific_particle).x > 0) {
            ball_velocities_.at(specific_particle).x = ball_velocities_.at(specific_particle).x - friction_;
            if (ball_velocities_.at(specific_particle).x < 0) {
                ball_velocities_.at(specific_particle).x = 0;
            }
        } else if (ball_velocities_.at(specific_particle).x < 0) {
            ball_velocities_.at(specific_particle).x = ball_velocities_.at(specific_particle).x + friction_;
            if (ball_velocities_.at(specific_particle).x > 0) {
                ball_velocities_.at(specific_particle).x = 0;

            }
        } else if (ball_velocities_.at(specific_particle).y > 0) {
            ball_velocities_.at(specific_particle).y = ball_velocities_.at(specific_particle).y - friction_;
            if (ball_velocities_.at(specific_particle).y < 0) {
                ball_velocities_.at(specific_particle).y = 0;
            }
        } else if (ball_velocities_.at(specific_particle).y < 0) {
            ball_velocities_.at(specific_particle).y = ball_velocities_.at(specific_particle).y + friction_;
            if (ball_velocities_.at(specific_particle).y > 0) {
                ball_velocities_.at(specific_particle).y = 0;
            }
        }
    }

    void PoolTable::BallCollisions(int specific_particle) {
        if (!FindCollidedBalls().empty()) {
            int first_ball = FindCollidedBalls().at(0);
            int second_ball = FindCollidedBalls().at(1);

            if (CheckBallsMovingTowardsEachOther(first_ball, second_ball)) {
                glm::vec2 updated_first =
                        CalculateCollidedVelocity(first_ball, second_ball);
                glm::vec2 updated_second =
                        CalculateCollidedVelocity(second_ball, first_ball);

                ball_velocities_[first_ball] = updated_first;
                ball_velocities_[second_ball] = updated_second;
            }
        }
    }

    bool PoolTable::CheckBallsMovingTowardsEachOther(int first, int second) {
        glm::vec2 subtracted_velocities = ball_velocities_.at(first) - ball_velocities_.at(second);
        glm::vec2 subtracted_positions = ball_positions_.at(first) - ball_positions_.at(second);
        if (glm::dot(subtracted_velocities, subtracted_positions) < 0) {
            return true;
        }
        return false;
    }

    std::vector<int> PoolTable::FindCollidedBalls() {
        std::vector<int> collided_balls;
        for (size_t i = 0; i < num_of_balls_; i++) {
            for (size_t j = 0; j < num_of_balls_; j++) {
                int contact_distance = 10 + 10;
                if (glm::distance(ball_positions_.at(i), ball_positions_.at(j)) <=
                    (contact_distance) &&
                    i != j) {
                    collided_balls.push_back(i);
                    collided_balls.push_back(j);
                }
            }
        }
        return collided_balls;

    }

    glm::vec2 PoolTable::CalculateCollidedVelocity(int first, int second) {
        glm::vec2 subtraction_velocities = ball_velocities_.at(first) -
                                      ball_velocities_.at(second);
        glm::vec2 subtraction_positions = ball_positions_.at(first) -
                                     ball_positions_.at(second);
        float dot_product = glm::dot(subtraction_velocities, subtraction_positions);
        float position_length_squared =
                glm::length(subtraction_positions) * glm::length(subtraction_positions);
        glm::vec2 multiplication = (dot_product / position_length_squared) * subtraction_positions;
        glm::vec2 collided_velocity = ball_velocities_.at(first) - multiplication;
        return collided_velocity;
    }

    bool PoolTable::Movement() const {
        bool movement = false;
        for(size_t i = 0; i < num_of_balls_; i++) {
            if (ball_velocities_.at(i) != glm::vec2(0,0)) {
                movement = true;
            }
        }
        return movement;
    }

    void PoolTable::DrawTable() const {
        cinder::gl::color(0, 0.38f, 0.11f);
        cinder::gl::drawSolidRect(cinder::Rectf(top_left_x_, top_left_y_, bottom_right_x_, bottom_right_y_));
        cinder::gl::color(0.36f, 0.20f, 0.09f);
        cinder::gl::drawStrokedRect(cinder::Rectf(top_left_x_, top_left_y_, bottom_right_x_, bottom_right_y_), 50);
    }

    void PoolTable::DrawHoles() const {
        for (size_t i = 0; i < holes_.size(); i++) {
            cinder::gl::color(0,0,0);
            cinder::gl::drawSolidCircle(holes_.at(i), 25, -1);
        }
    }

    void PoolTable::DrawBalls() const {
        for (size_t i = 0; i < num_of_balls_; i++) {
            cinder::gl::color(ball_colors_.at(i).x, ball_colors_.at(i).y, ball_colors_.at(i).z);
            cinder::gl::drawSolidCircle(ball_positions_.at(i), 10, -1);
        }
    }

    void PoolTable::DrawCue() const {
        if (Movement() == false) {
            cinder::gl::color(0.53f, 0.26f, 0.12f);
            cinder::gl::drawLine(ball_positions_.at(0), cue_end_);
        }
    }

    void PoolTable::MouseDrag(const glm::vec2& end) {
        cue_end_ = end;
    }

    void PoolTable::MouseRelease() {
        if (Movement() == false) {
            glm::vec2 velocity = (ball_positions_.at(0) - cue_end_) / (float) 50;
            ball_velocities_.at(0) = velocity;
            cue_end_ = ball_positions_.at(0);
        }
    }

    std::vector<glm::vec2> PoolTable::GetPositions() {
        return ball_positions_;
    }

    std::vector<glm::vec2> PoolTable::GetVelocities() {
        return ball_velocities_;
    }

    void PoolTable::SetBallPositions(std::vector<glm::vec2> positions) {
        ball_positions_ = positions;
    }

    void PoolTable::SetBallVelocities(std::vector<glm::vec2> velocities) {
        ball_velocities_ = velocities;
    }

    void PoolTable::SetNumOfBalls(int num) {
        num_of_balls_ = num;
    }

}  // namespace idealgas
