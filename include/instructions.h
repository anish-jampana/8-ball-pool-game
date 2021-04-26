#pragma once

#include "cinder/gl/gl.h"

namespace poolgame {

    class Instructions {
    public:
        Instructions();
        void Display() const;
    private:
        void DrawTitle() const;
        void DrawInstructions() const;
        void DrawBackButton() const;
    };
}