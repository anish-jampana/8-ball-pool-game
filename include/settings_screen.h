#pragma once

#include "cinder/gl/gl.h"

namespace poolgame {

    class SettingsScreen {
    public:
        SettingsScreen();
        void Display() const;
        void IncrementMouseDown(const glm::vec2 &pos);
        int GetIncrementRadius();
        float GetIncrementFriction();
    private:
        void DrawWindow() const;
        void DrawStartBackButtons() const;
        void DrawImages() const;
        void DrawText() const;
        void DrawArrowButtons() const;

        int increment_radius_;
        float increment_friction_;
    };
}
