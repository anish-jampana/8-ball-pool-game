// contains similarities in implementation to my ideal gas MP
#pragma once
#include "cinder/gl/gl.h"
#include "ball.h"

namespace poolgame {

    class BallGenerator {
    public:
        BallGenerator();
        std::vector<Ball> GetBalls();
        std::vector<glm::vec2> GetPositions();
        std::vector<glm::vec3> GetColors();
    private:
        void GenerateBalls();
        void GenerateColors();
        void GeneratePositions();
        void GenerateVelocities();
        std::vector<Ball> balls_;
        std::vector<glm::vec3> colors_;
        std::vector<glm::vec2> positions_;
        std::vector<glm::vec2> velocities_;
    };
}
