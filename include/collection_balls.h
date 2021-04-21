// contains similarities in implementation to my ideal gas MP
#pragma once
#include "cinder/gl/gl.h"
#include "ball.h"

namespace poolgame {

    class CollectionBalls {
    public:
        CollectionBalls();
        std::vector<Ball> GetBalls();
        std::vector<glm::vec2> GetPositions();
        std::vector<glm::vec3> GetColors();
    private:
        std::vector<Ball> balls_;
        std::vector<glm::vec3> colors_ = {glm::vec3(1,1,0), glm::vec3(0,0,1),
                                          glm::vec3(1,0,0), glm::vec3(0.5f,0,0.5f),
                                          glm::vec3(1,0.4f,0), glm::vec3(0,0.8f,0),
                                          glm::vec3(0.72f,0.07f,0.14f), glm::vec3(0,0,0)};
        std::vector<glm::vec2> positions_ = {glm::vec2(700, 500), glm::vec2(720, 510),
                                             glm::vec2(720, 490), glm::vec2(740, 520),
                                             glm::vec2(740, 500), glm::vec2(740, 480),
                                             glm::vec2(760, 530), glm::vec2(760, 510),
                                             glm::vec2(760, 490), glm::vec2(760, 470),
                                             glm::vec2(780, 540), glm::vec2(780, 520),
                                             glm::vec2(780, 500), glm::vec2(780, 480),
                                             glm::vec2(780, 460)};
    };
}
