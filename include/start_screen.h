#pragma once

#include "cinder/gl/gl.h"

namespace poolgame {

    class StartScreen {
    public:
        StartScreen();
        void Display() const;
    private:
        void DrawTitle() const;
        void DrawStartButton() const;
        void DrawInstructionsButton() const;
    };
}