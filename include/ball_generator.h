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
        std::vector<glm::vec2> GetVelocities();
        std::vector<glm::vec3> GetColors();
        std::vector<bool> GetShows();
        std::vector<bool> GetStripes();
    private:
        void GenerateBalls();
        void GenerateColors();
        void GeneratePositions();
        void GenerateVelocities();
        void GenerateShows();
        void GenerateStripes();
        std::vector<Ball> balls_;
        std::vector<glm::vec3> colors_;
        std::vector<glm::vec2> positions_;
        std::vector<glm::vec2> velocities_;
        std::vector<bool> shows_;
        std::vector<bool> striped_;
    };
}
