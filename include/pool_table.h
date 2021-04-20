#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace poolgame {


    class PoolTable {
    public:

        PoolTable();


        void Display() const;


        void AdvanceOneFrame();

    private:

        int dummy_variable_ = 0;
    };

}  // namespace idealgas

