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
        cinder::gl::drawStringCentered("Instructions", glm::vec2(500, 100), cinder::ColorA(0, 1, 0, 1), ci::Font("georgia", 100));
    }

    void Instructions::DrawInstructions() const {
        cinder::gl::drawStringCentered("The object of the game is to pot all of your designated balls (striped or solids) excluding the 8 (black) ball.", glm::vec2(500, 300), cinder::ColorA(0, 1, 0, 1), ci::Font("georgia", 20));
        cinder::gl::drawStringCentered("Once all your designated balls are potted, you need to pot the 8 (black) ball to win.", glm::vec2(500, 400), cinder::ColorA(0, 1, 0, 1), ci::Font("georgia", 20));
        cinder::gl::drawStringCentered("If you accidentally pot the white ball, the opponent gets to place the ball at position of their choice on table.", glm::vec2(500, 500), cinder::ColorA(0, 1, 0, 1), ci::Font("georgia", 20));
        cinder::gl::drawStringCentered("If you accidentally pot the 8 (black) ball before all your other balls are potted, you automatically lose.", glm::vec2(500, 600), cinder::ColorA(0, 1, 0, 1), ci::Font("georgia", 20));
    }

    void Instructions::DrawBackButton() const {
        cinder::gl::drawSolidRect(cinder::Rectf(400, 650, 600, 700));
        cinder::gl::drawStringCentered("Back", glm::vec2(500, 665), cinder::ColorA(0, 0, 0, 1), ci::Font("georgia", 30));
    }
}