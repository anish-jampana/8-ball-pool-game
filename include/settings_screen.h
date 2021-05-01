#pragma once

#include "cinder/gl/gl.h"

namespace poolgame {

    class SettingsScreen {
    public:
        SettingsScreen();
        void Display() const;
    private:
        void DrawWindow() const;
        void DrawButton() const;
    };
}
