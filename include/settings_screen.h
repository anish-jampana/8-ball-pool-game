#pragma once

#include "cinder/gl/gl.h"

namespace poolgame {

    class SettingsScreen {
    public:
        SettingsScreen();
        void Display() const;
    private:
        void DrawWindow() const;
        void DrawStartBackButtons() const;
        void DrawImages() const;
        void DrawText() const;
        void DrawArrowButtons() const;

//        int setting_radius_;
//        float setting_friction_;
    };
}
