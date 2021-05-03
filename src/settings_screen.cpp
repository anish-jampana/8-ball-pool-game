#include "settings_screen.h"

namespace poolgame {
    SettingsScreen::SettingsScreen() {

    }
    void SettingsScreen::Display() const {
        DrawWindow();
        DrawButton();
        DrawImages();
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
        cinder::gl::drawStringCentered("Start", glm::vec2(500, 690), cinder::ColorA(0, 0, 0, 1), ci::Font("georgia", 30));
        cinder::gl::drawStringCentered("Back", glm::vec2(500, 750), cinder::ColorA(0, 0, 0, 1), ci::Font("georgia", 30));

    }

    void SettingsScreen::DrawImages() const {
        cinder::gl::Texture2dRef my_image = ci::gl::Texture2d::create(cinder::loadImage("/Users/anishjampana/Downloads/Trollface_non-free.png"));
        cinder::Rectf rect(210, 210, 400, 400);
        cinder::gl::draw(my_image, rect);
    }
}

