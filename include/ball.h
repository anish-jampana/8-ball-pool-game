#pragma once
#include "cinder/gl/gl.h"

namespace poolgame {

    class Ball {

    public:

        Ball(int number, bool striped, glm::vec3 color, glm::vec2 position, int radius);

        int GetBallNumber();

        glm::vec3 GetBallColor();

        bool GetStriped();

        glm::vec2 GetBallPosition();

        int GetRadius();

    private:

        int ball_num_;

        glm::vec3 ball_color_;

        bool ball_striped_;

        glm::vec2 ball_position_;

        int radius_;
    };
}
