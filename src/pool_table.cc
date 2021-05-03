#include <ball_generator.h>
#include "pool_table.h"

namespace poolgame {

    PoolTable::PoolTable() {
        friction_ = 0.994;
        top_left_x_ = 100;
        top_left_y_ = 250;
        bottom_right_x_ = 900;
        bottom_right_y_ = 750;

        collection_of_balls_ = BallGenerator();
        ball_striped_ = collection_of_balls_.GetStripes();
        ball_shows_ = collection_of_balls_.GetShows();
        ball_positions_ = collection_of_balls_.GetPositions();
        ball_velocities_ = collection_of_balls_.GetVelocities();
        ball_colors_ = collection_of_balls_.GetColors();
        num_of_balls_ = collection_of_balls_.GetBalls().size();
        holes_ = GenerateHoles();
        radius_ = collection_of_balls_.GetBalls().at(0).GetRadius();
        cue_end_ = ball_positions_.at(0);

        first_player_score_ = 0;
        second_player_score_ = 0;
    }

    void PoolTable::Display() const {
        if (ball_shows_.at(8) == true) {
            DrawTable();
            DrawHoles();
            DrawBalls();
            if (Movement() == false) {
                DrawCueIndicator();
                DrawCue();
            }
            DrawScoreBoard();
            DrawBackButton();
            DrawKey();
        } else if (ball_shows_.at(8) == false && AllBallsGoneSolid() == false && AllBallsGoneStriped() == false) {
            cinder::gl::drawStringCentered("YOU LOST", glm::vec2(500, 50), cinder::ColorA(1, 1, 1, 1), ci::Font("georgia", 100));
        } else if ((ball_shows_.at(8) == false && AllBallsGoneSolid() == true) || (ball_shows_.at(8) == false && AllBallsGoneStriped() == true)) {
            cinder::gl::drawStringCentered("YOU WON", glm::vec2(500, 50), cinder::ColorA(1, 1, 1, 1), ci::Font("georgia", 100));
        }
    }

    void PoolTable::Update() {
        for (size_t i = 0; i < num_of_balls_; i++) {
            if (ball_shows_.at(i) == true) {
                HoleCollision(i);
                BallCollisions(i);
                EdgeCollisions(i);
                float time_step = 1;
                ball_positions_.at(i) = ball_positions_.at(i) + (ball_velocities_.at(i) * time_step);
                Friction(i);
                if (Movement() == true) {
                    cue_end_ = ball_positions_.at(0);
                }
            }
        }
    }

    //Physics/Helper Methods
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
            if (glm::distance(ball_positions_.at(specific_particle), holes_.at(i)) <= 35) {
                ball_shows_.at(specific_particle) = false;
                if (specific_particle != 0) {
                    ball_positions_.at(specific_particle) = glm::vec2(0, 0);
                }
                if (ball_striped_.at(specific_particle) == true) {
                    second_player_score_++;
                } else {
                    if (specific_particle != 0) {
                        first_player_score_++;
                    }
                }
            }
        }
    }

    void PoolTable::Friction(int specific_particle) {
        ball_velocities_.at(specific_particle).x = friction_ * ball_velocities_.at(specific_particle).x;
        ball_velocities_.at(specific_particle).y = friction_ * ball_velocities_.at(specific_particle).y;
        if (abs(ball_velocities_.at(specific_particle).x - 0) < 0.01) {
            ball_velocities_.at(specific_particle).x = 0;
        }
        if (abs(ball_velocities_.at(specific_particle).y - 0) < 0.01) {
            ball_velocities_.at(specific_particle).y = 0;
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
                int contact_distance = 2 * radius_;
                if (glm::distance(ball_positions_.at(i), ball_positions_.at(j)) <=
                    (contact_distance) &&
                    i != j) {
                    if (ball_shows_.at(i) == true && ball_shows_.at(j) == true) {
                        collided_balls.push_back(i);
                        collided_balls.push_back(j);
                    }
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
            if (ball_shows_.at(i) == true) {
                if (ball_velocities_.at(i) != glm::vec2(0, 0)) {
                    movement = true;
                }
            }
        }
        return movement;
    }

    bool PoolTable::AllBallsGoneSolid() const {
        bool all_gone = true;
        for (size_t i = 1; i < 8; i++) {
            if (ball_shows_.at(i) == true) {
                all_gone = false;
            }
        }
        return all_gone;
    }

    bool PoolTable::AllBallsGoneStriped() const {
        bool all_gone = true;
        for (size_t i = 9; i < 16; i++) {
            if (ball_shows_.at(i) == true) {
                all_gone = false;
            }
        }
        return all_gone;
    }


    //Draw Functions
    void PoolTable::DrawTable() const {
        cinder::gl::color(0, 0.38f, 0.11f);
        cinder::gl::drawSolidRect(cinder::Rectf(top_left_x_, top_left_y_, bottom_right_x_, bottom_right_y_));
        cinder::gl::color(0.36f, 0.20f, 0.09f);
        cinder::gl::drawStrokedRect(cinder::Rectf(top_left_x_, top_left_y_, bottom_right_x_, bottom_right_y_), 50);
    }

    void PoolTable::DrawHoles() const {
        for (size_t i = 0; i < holes_.size(); i++) {
            cinder::gl::color(0,0,0);
            cinder::gl::drawSolidCircle(holes_.at(i), 35, -1);
        }
    }

    void PoolTable::DrawBalls() const {
        for (size_t i = 0; i < num_of_balls_; i++) {
            if (ball_shows_.at(i) == true) {
                cinder::gl::color(ball_colors_.at(i).x, ball_colors_.at(i).y, ball_colors_.at(i).z);
                cinder::gl::drawSolidCircle(ball_positions_.at(i), radius_, -1);
                if (i > 8) {
                    cinder::gl::color(1,1,1);
                    cinder::gl::drawStrokedCircle(ball_positions_.at(i), 10, -1);
                    cinder::gl::drawStrokedCircle(ball_positions_.at(i), 9, -1);
                }
            }
        }
    }

    void PoolTable::DrawCue() const {
        if (Movement() == false) {
            cinder::gl::color(0.53f, 0.26f, 0.12f);
            cinder::gl::drawLine(ball_positions_.at(0), cue_end_);
        }
    }

    void PoolTable::DrawScoreBoard() const {
        cinder::gl::color(0, 0.38f, 0.11f);
        cinder::gl::drawSolidRect(cinder::Rectf(250, 25, 750, 150));
        cinder::gl::drawStringCentered("Pool Game", glm::vec2(500, 50), cinder::ColorA(1, 1, 1, 1), ci::Font("georgia", 100));
        cinder::gl::drawStringCentered("Solid:", glm::vec2(460, 160), cinder::ColorA(1, 1, 1, 1), ci::Font("georgia", 30));
        cinder::gl::drawStringCentered("Striped:", glm::vec2(460, 190), cinder::ColorA(1, 1, 1, 1), ci::Font("georgia", 30));


        cinder::gl::drawStringCentered(std::to_string(first_player_score_), glm::vec2(540, 160), cinder::ColorA(1, 1, 1, 1), ci::Font("georgia", 30));
        cinder::gl::drawStringCentered(std::to_string(second_player_score_), glm::vec2(540, 190), cinder::ColorA(1, 1, 1, 1), ci::Font("georgia", 30));

    }

    void PoolTable::DrawCueIndicator() const {
        if (ball_shows_.at(0) == true) {
            cinder::gl::color(1, 0, 0);
            cinder::gl::drawStrokedCircle(ball_positions_.at(0), 10, -1);
            cinder::gl::drawStrokedCircle(ball_positions_.at(0), 9, -1);
        }
    }

    void PoolTable::DrawBackButton() const {
        cinder::gl::color(1, 1, 1);
        cinder::gl::drawSolidRect(cinder::Rectf(400, 780, 600, 830));
        cinder::gl::drawStringCentered("Back", glm::vec2(500, 795), cinder::ColorA(0, 0, 0, 1), ci::Font("georgia", 30));
    }

    void PoolTable::DrawKey() const {
        // striped
        cinder::gl::color(1, 0, 0);
        cinder::gl::drawSolidCircle(glm::vec2(800, 100), radius_, -1);
        cinder::gl::color(1, 1, 1);
        cinder::gl::drawStrokedCircle(glm::vec2(800, 100), 10, -1);
        cinder::gl::drawStrokedCircle(glm::vec2(800, 100), 9, -1);

        // solid
        cinder::gl::color(1, 0, 0);
        cinder::gl::drawSolidCircle(glm::vec2(800, 130), radius_, -1);

        // labels
        cinder::gl::drawStringCentered("Striped", glm::vec2(850, 90), cinder::ColorA(1, 1, 1, 1), ci::Font("georgia", 20));
        cinder::gl::drawStringCentered("Solid", glm::vec2(850, 120), cinder::ColorA(1, 1, 1, 1), ci::Font("georgia", 20));
    }


    //Mouse Functions
    void PoolTable::MouseDrag(const glm::vec2& end) {
        float d_x = ball_positions_.at(0).x - end.x;
        float d_y = ball_positions_.at(0).y - end.y;
        float distance = sqrt(d_x*d_x + d_y*d_y);
        if (distance <= 400) {
            cue_end_ = end;
        }
    }

    void PoolTable::MouseRelease() {
        if (Movement() == false) {
            glm::vec2 velocity = (ball_positions_.at(0) - cue_end_) / (float) 50;
            ball_velocities_.at(0) = velocity;
        }
    }

    void PoolTable::MouseDown(const glm::vec2 &pos) {
        if (ball_shows_.at(0) == false) {
            if (pos.x >= top_left_x_ + radius_ && pos.x <= bottom_right_x_ - radius_ && pos.y >= top_left_y_ + radius_ && pos.y <= bottom_right_y_ - radius_) {
                cue_end_ = pos;
                ball_positions_.at(0) = pos;
                ball_velocities_.at(0) = glm::vec2(0, 0);
                ball_shows_.at(0) = true;
                cinder::gl::color(ball_colors_.at(1).x, ball_colors_.at(1).y, ball_colors_.at(1).z);
            }
        }
    }


    //Getters and Setters
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

    void PoolTable::SetRadius(int num) {
        radius_ = num;
        for (size_t i = 0; i < num_of_balls_; i++) {
            collection_of_balls_.GetBalls().at(0).SetRadius(num);
        }
    }

    void PoolTable::SetFriction(float num) {
        friction_ = num;
    }
}  // namespace idealgas
