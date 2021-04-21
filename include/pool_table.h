// contains similarities in implementation to my ideal gas MP
#pragma once

#include "cinder/gl/gl.h"
#include "collection_balls.h"


namespace poolgame {


    class PoolTable {
    public:

        PoolTable();
        void Display() const;
        void AdvanceOneFrame();
    private:
        void DrawTable() const;
        void DrawHoles() const;
        void DrawBalls() const;

        CollectionBalls collection_of_balls_ = CollectionBalls();
        std::vector<glm::vec2> ball_positions_;
        //std::vector<glm::vec2> ball_velocities_;
        //int ball_radius_;


    };

}  // namespace idealgas

