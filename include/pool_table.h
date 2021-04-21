// contains similarities in implementation to my ideal gas MP
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
    private:
        void DrawTable() const;
        void DrawHoles() const;
        void DrawBalls() const;
        void DrawCue() const;
        void EdgeCollisions(int specific_particle);
        void Friction(int specific_particle);

        bool CheckBallsMovingTowardsEachOther(int first, int second);
        std::vector<int> FindCollidedBalls();
        glm::vec2 CalculateCollidedVelocity(int first, int second);
        void BallCollisions(int specific_particle);
        bool Movement() const;

        glm::vec2 cue_end_;
        float friction_;
        int top_left_x_;
        int top_left_y_;
        int bottom_right_x_;
        int bottom_right_y_;
        BallGenerator collection_of_balls_;
        std::vector<glm::vec2> ball_positions_;
        std::vector<glm::vec2> ball_velocities_;
        std::vector<glm::vec3> ball_colors_;
        int num_of_balls_;
    };

}  // namespace idealgas

