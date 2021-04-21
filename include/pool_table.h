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
        //vec2

    };

}  // namespace idealgas

