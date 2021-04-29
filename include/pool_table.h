#pragma once

#include "cinder/gl/gl.h"
#include "ball_generator.h"


namespace poolgame {


    class PoolTable {
    public:

        PoolTable();
        void Display() const;
        void Update();
        void MouseDrag(const glm::vec2& length);
        void MouseRelease();
        void MouseDown(const glm::vec2& pos);

        std::vector<glm::vec2> GetPositions();
        std::vector<glm::vec2> GetVelocities();
        void SetBallPositions(std::vector<glm::vec2> positions);
        void SetBallVelocities(std::vector<glm::vec2> velocities);
        void SetNumOfBalls(int num);
    private:

        std::vector<glm::vec2> GenerateHoles();

        //draw functions
        void DrawTable() const;
        void DrawHoles() const;
        void DrawBalls() const;
        void DrawCue() const;
        void DrawScoreBoard() const;
        void DrawCueIndicator() const;
        void DrawBackButton() const;
        void DrawKey() const;

        // collision functions
        void EdgeCollisions(int specific_particle);
        void HoleCollision(int specific_particle);
        void Friction(int specific_particle);
        bool CheckBallsMovingTowardsEachOther(int first, int second);
        std::vector<int> FindCollidedBalls();
        glm::vec2 CalculateCollidedVelocity(int first, int second);
        void BallCollisions(int specific_particle);
        bool Movement() const;
        bool AllBallsGone() const;

        int first_player_score_;
        int second_player_score_;

        glm::vec2 cue_end_;
        float friction_;
        std::vector<glm::vec2> holes_;

        int top_left_x_;
        int top_left_y_;
        int bottom_right_x_;
        int bottom_right_y_;

        BallGenerator collection_of_balls_;

        std::vector<bool> ball_striped_;
        std::vector<bool> ball_shows_;
        std::vector<glm::vec2> ball_positions_;
        std::vector<glm::vec2> ball_velocities_;
        std::vector<glm::vec3> ball_colors_;
        int num_of_balls_;
        int radius_;
    };

}  // namespace idealgas

