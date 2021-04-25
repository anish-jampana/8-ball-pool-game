
#include "start_screen.h"
namespace poolgame {
    StartScreen::StartScreen() {

    }
    void StartScreen::Display() const {
        DrawTitle();
        DrawStartButton();
        DrawInstructionsButton();
    }

    void StartScreen::DrawTitle() const {
        cinder::gl::color(0.8f,0,0);
        cinder::gl::drawSolidCircle(glm::vec2(500, 365), 250, -1);
        cinder::gl::color(1,1,1);
        cinder::gl::drawSolidCircle(glm::vec2(500, 365), 170, -1);
        cinder::gl::drawStringCentered("Pool", glm::vec2(500, 280), cinder::ColorA(0, 0, 0, 1), ci::Font("georgia", 100));
        cinder::gl::drawStringCentered("Game", glm::vec2(500, 360), cinder::ColorA(0, 0, 0, 1), ci::Font("georgia", 100));
    }

    void StartScreen::DrawStartButton() const {
        cinder::gl::drawSolidRect(cinder::Rectf(400, 650, 600, 700));
        cinder::gl::drawStringCentered("Start", glm::vec2(500, 665), cinder::ColorA(0, 0, 0, 1), ci::Font("georgia", 30));
    }

    void StartScreen::DrawInstructionsButton() const {
        cinder::gl::drawSolidRect(cinder::Rectf(400, 725, 600, 775));
        cinder::gl::drawStringCentered("Instructions", glm::vec2(500, 740), cinder::ColorA(0, 0, 0, 1), ci::Font("georgia", 30));
    }
}

