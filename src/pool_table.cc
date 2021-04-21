#include <ball_generator.h>
#include "pool_table.h"

namespace poolgame {

    PoolTable::PoolTable() {
        friction_ = 0.0015;
        top_left_x_ = 100;
        top_left_y_ = 250;
        bottom_right_x_ = 900;
        bottom_right_y_ = 750;
        collection_of_balls_ = BallGenerator();
        ball_positions_ = collection_of_balls_.GetPositions();
        ball_velocities_ = collection_of_balls_.GetVelocities();
        ball_colors_ = collection_of_balls_.GetColors();
        num_of_balls_ = collection_of_balls_.GetBalls().size();

        std::cout<<ball_positions_.size()<<std::endl;
        std::cout<<ball_velocities_.size()<<std::endl;
        std::cout<<ball_colors_.size()<<std::endl;
    }

    void PoolTable::Display() const {
        DrawTable();
        DrawHoles();
        DrawBalls();
    }

    void PoolTable::Update() {
        for (size_t i = 0; i < num_of_balls_; i++) {
            EdgeCollisions(i);
            ball_positions_.at(i) = ball_positions_.at(i) + ball_velocities_.at(i);
            Friction(i);
        }
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

    void PoolTable::DrawTable() const {
        cinder::gl::color(0, 0.38f, 0.11f);
        cinder::gl::drawSolidRect(cinder::Rectf(top_left_x_, top_left_y_, bottom_right_x_, bottom_right_y_));
        cinder::gl::color(0.36f, 0.20f, 0.09f);
        cinder::gl::drawStrokedRect(cinder::Rectf(top_left_x_, top_left_y_, bottom_right_x_, bottom_right_y_), 50);
    }

    void PoolTable::DrawHoles() const {
        glm::vec2 hole_1 = glm::vec2(120, 270);
        cinder::gl::color(0,0,0);
        cinder::gl::drawSolidCircle(hole_1, 25, -1);

        glm::vec2 hole_2 = glm::vec2(880, 730);
        cinder::gl::color(0,0,0);
        cinder::gl::drawSolidCircle(hole_2, 25, -1);

        glm::vec2 hole_3 = glm::vec2(120, 730);
        cinder::gl::color(0,0,0);
        cinder::gl::drawSolidCircle(hole_3, 25, -1);

        glm::vec2 hole_4 = glm::vec2(880, 270);
        cinder::gl::color(0,0,0);
        cinder::gl::drawSolidCircle(hole_4, 25, -1);

        glm::vec2 hole_5 = glm::vec2(500, 730);
        cinder::gl::color(0,0,0);
        cinder::gl::drawSolidCircle(hole_5, 25, -1);

        glm::vec2 hole_6 = glm::vec2(500, 270);
        cinder::gl::color(0,0,0);
        cinder::gl::drawSolidCircle(hole_6, 25, -1);
    }

    void PoolTable::DrawBalls() const {
        for (size_t i = 0; i < ball_positions_.size(); i++) {
            cinder::gl::color(ball_colors_.at(i).x, ball_colors_.at(i).y, ball_colors_.at(i).z);
            cinder::gl::drawSolidCircle(ball_positions_.at(i), 10, -1);
        }
    }

}  // namespace idealgas
