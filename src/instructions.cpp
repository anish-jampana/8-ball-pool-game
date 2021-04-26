#include "instructions.h"

namespace poolgame {
    Instructions::Instructions() {

    }

    void Instructions::Display() const {
        DrawTitle();
        DrawInstructions();
        DrawBackButton();
    }

    void Instructions::DrawTitle() const {

    }

    void Instructions::DrawInstructions() const {

    }

    void Instructions::DrawBackButton() const {
        cinder::gl::drawSolidRect(cinder::Rectf(400, 650, 600, 700));
        cinder::gl::drawStringCentered("Back", glm::vec2(500, 665), cinder::ColorA(0, 0, 0, 1), ci::Font("georgia", 30));
    }
}