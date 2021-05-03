#include "settings_screen.h"

namespace poolgame {
    SettingsScreen::SettingsScreen() {
        increment_radius_ = 5;
        increment_friction_ = 0.99;
    }
    void SettingsScreen::Display() const {
        DrawWindow();
        DrawStartBackButtons();
        DrawArrowButtons();
        DrawImages();
        DrawText();
    }
    void SettingsScreen::DrawWindow() const {
        ci::gl::color(0, 0, 0.5f);
        ci::gl::drawSolidRect(cinder::Rectf(200, 100, 800, 800));
        ci::gl::color(1, 1, 1);
        cinder::gl::drawStrokedRect(cinder::Rectf(200, 100, 800, 800), 20);
    }

    void SettingsScreen::DrawStartBackButtons() const {
        ci::gl::color(1, 1, 1);
        cinder::gl::drawSolidRect(cinder::Rectf(400, 675, 600, 725));
        cinder::gl::drawSolidRect(cinder::Rectf(400, 735, 600, 785));
        cinder::gl::drawStringCentered("Start", glm::vec2(500, 690), cinder::ColorA(0, 0, 0, 1), ci::Font("georgia", 30));
        cinder::gl::drawStringCentered("Back", glm::vec2(500, 750), cinder::ColorA(0, 0, 0, 1), ci::Font("georgia", 30));
    }

    void SettingsScreen::DrawArrowButtons() const {
        cinder::gl::Texture2dRef left = ci::gl::Texture2d::create(cinder::loadImage("/Users/anishjampana/Desktop/left.png"));
        cinder::gl::Texture2dRef right = ci::gl::Texture2d::create(cinder::loadImage("/Users/anishjampana/Desktop/right.png"));

        cinder::Rectf rect_left1(380, 400, 420, 440);
        cinder::gl::draw(left, rect_left1);
        cinder::Rectf rect_left2(380, 550, 420, 590);
        cinder::gl::draw(left, rect_left2);

        cinder::Rectf rect_right1(580, 400, 620, 440);
        cinder::gl::draw(right, rect_right1);
        cinder::Rectf rect_right2(580, 550, 620, 590);
        cinder::gl::draw(right, rect_right2);
    }

    void SettingsScreen::DrawImages() const {
        cinder::gl::Texture2dRef meme = ci::gl::Texture2d::create(cinder::loadImage("/Users/anishjampana/Downloads/Trollface_non-free.png"));
        cinder::Rectf rect(210, 110, 400, 300);
        cinder::gl::draw(meme, rect);
    }

    void SettingsScreen::DrawText() const {
        cinder::gl::drawStringCentered("Hi! I am the game master of this game!", glm::vec2(600, 200), cinder::ColorA(1, 1, 1, 1), ci::Font("georgia", 14));
        cinder::gl::drawStringCentered("But for this once, I will let you customize the things below!", glm::vec2(600, 220), cinder::ColorA(1, 1, 1, 1), ci::Font("georgia", 14));

        cinder::gl::drawStringCentered("Ball Radius", glm::vec2(500, 350), cinder::ColorA(1, 1, 1, 1), ci::Font("georgia", 30));
        cinder::gl::drawStringCentered("Friction", glm::vec2(500, 500), cinder::ColorA(1, 1, 1, 1), ci::Font("georgia", 30));

        cinder::gl::drawStringCentered(std::to_string(increment_radius_), glm::vec2(500, 400), cinder::ColorA(1, 1, 1, 1), ci::Font("georgia", 30));
        cinder::gl::drawStringCentered(std::to_string(increment_friction_), glm::vec2(500, 550), cinder::ColorA(1, 1, 1, 1), ci::Font("georgia", 30));

    }
    
    void SettingsScreen::IncrementMouseDown(const glm::vec2 &pos) {
        if (pos.x >= 380 && pos.x <= 420 && pos.y >= 400 &&
                 pos.y <= 440) {
            std::cout<<"left button for radius working!";
            if (increment_radius_ > 1) {
                increment_radius_--;
            }
        } else if (pos.x >= 380 && pos.x <= 420 && pos.y >= 550 &&
                   pos.y <= 590) {
            std::cout<<"left button for friction working!";
            if (increment_friction_ > 0.85) {
                increment_friction_ -= 0.001;
            }
        } else if (pos.x >= 580 && pos.x <= 620 && pos.y >= 400 &&
                   pos.y <= 440) {
            std::cout<<"right button for radius working!";
            if (increment_radius_ < 10) {
                increment_radius_++;
            }
        } else if (pos.x >= 580 && pos.x <= 620 && pos.y >= 550 &&
                   pos.y <= 590) {
            std::cout<<"right button for friction working!";
            if (increment_friction_ < 1) {
                increment_friction_ += 0.001;
            }
        }
    }
}

