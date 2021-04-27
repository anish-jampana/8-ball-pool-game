#include "pool_game_app.h"

namespace poolgame {

    PoolGameApp::PoolGameApp() {
        ci::app::setWindowSize(kWindowSize, kWindowSize);
        start_screen_status_ = true;
    }

    void PoolGameApp::draw() {
        ci::Color background_color("black");
        if (start_screen_status_ == true) {
            ci::gl::clear(background_color);
            screen_.Display();
        }
        if (game_screen_status_ == true) {
            ci::gl::clear(background_color);
            table_.Display();
        }
        if (instructions_screen_status_ == true) {
            ci::gl::clear(background_color);
            instructions_.Display();
        }
    }
    void PoolGameApp::update() {
        table_.Update();
    }

    void PoolGameApp::mouseUp(ci::app::MouseEvent event) {
        table_.MouseRelease();
    }

    void PoolGameApp::mouseDrag(ci::app::MouseEvent event) {
        table_.MouseDrag(event.getPos());
    }

    void PoolGameApp::mouseDown(ci::app::MouseEvent event) {
        if (start_screen_status_ == true) {
            if (event.getPos().x >= 400 && event.getPos().x <= 600 && event.getPos().y >= 650 &&
                event.getPos().y <= 700) {
                game_screen_status_ = true;
                start_screen_status_ = false;
                instructions_screen_status_ = false;
            } else if (event.getPos().x >= 400 && event.getPos().x <= 600 && event.getPos().y >= 725 &&
                       event.getPos().y <= 775) {
                instructions_screen_status_ = true;
                game_screen_status_ = false;
                start_screen_status_ = false;
            }
        }
        if (instructions_screen_status_ == true) {
            if (event.getPos().x >= 400 && event.getPos().x <= 600 && event.getPos().y >= 650 &&
                event.getPos().y <= 700) {
                start_screen_status_ = true;
                instructions_screen_status_ = false;
                game_screen_status_ = false;
            }
        }
        if (game_screen_status_ == true) {
            table_.MouseDown(event.getPos());
        }
    }

}