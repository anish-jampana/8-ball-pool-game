#include "settings_screen.h"

namespace poolgame {
    SettingsScreen::SettingsScreen() {

    }
    void SettingsScreen::Display() const {
        DrawWindow();
        DrawButton();
    }
    void SettingsScreen::DrawWindow() const {
        ci::gl::color(0, 0, 0);
        ci::gl::drawSolidRect(cinder::Rectf(200, 200, 800, 800));
        ci::gl::color(1, 1, 1);
        cinder::gl::drawStrokedRect(cinder::Rectf(200, 200, 800, 800), 20);
    }

    void SettingsScreen::DrawButton() const {
        ci::gl::color(1, 1, 1);
        cinder::gl::drawSolidRect(cinder::Rectf(400, 675, 600, 725));
        cinder::gl::drawSolidRect(cinder::Rectf(400, 735, 600, 785));
    }
}

