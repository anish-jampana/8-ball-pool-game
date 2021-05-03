#include "pool_game_app.h"

namespace poolgame {

    PoolGameApp::PoolGameApp() {
        ci::app::setWindowSize(kWindowSize, kWindowSize);
        game_state = GameState::START_SCREEN;
    }

    void PoolGameApp::draw() {
        ci::Color background_color("black");
        switch(game_state) {
            case GameState::START_SCREEN:
                ci::gl::clear(background_color);
                screen_.Display();
                break;
            case GameState::GAME_SCREEN:
                ci::gl::clear(background_color);
                table_.Display();
                break;
            case GameState::INSTRUCTIONS:
                ci::gl::clear(background_color);
                instructions_.Display();
                break;
            case GameState::SETTING_SCREEN:
                settings_.Display();
                break;
        }
    }
    void PoolGameApp::update() {
        if (game_state == GameState::GAME_SCREEN) {
            table_.Update();
        }
    }

    void PoolGameApp::mouseUp(ci::app::MouseEvent event) {
        if (game_state == GameState::GAME_SCREEN) {
            table_.MouseRelease();
        }
    }

    void PoolGameApp::mouseDrag(ci::app::MouseEvent event) {
        if (game_state == GameState::GAME_SCREEN) {
            table_.MouseDrag(event.getPos());
        }
    }

    void PoolGameApp::mouseDown(ci::app::MouseEvent event) {
        if (game_state == GameState::START_SCREEN) {
            if (event.getPos().x >= 400 && event.getPos().x <= 600 && event.getPos().y >= 650 &&
                event.getPos().y <= 700) {
                std::cout<< "Start";
                game_state = GameState::SETTING_SCREEN;
            } else if (event.getPos().x >= 400 && event.getPos().x <= 600 && event.getPos().y >= 725 &&
                       event.getPos().y <= 775) {
                game_state = GameState::INSTRUCTIONS;
            }
        }
        if (game_state == GameState::INSTRUCTIONS) {
            if (event.getPos().x >= 400 && event.getPos().x <= 600 && event.getPos().y >= 650 &&
                event.getPos().y <= 700) {
                game_state = GameState::START_SCREEN;
            }
        }
        if (game_state == GameState::GAME_SCREEN) {
            table_.MouseDown(event.getPos());
            if (event.getPos().x >= 400 && event.getPos().x <= 600 && event.getPos().y >= 780 &&
                event.getPos().y <= 830) {
                game_state = GameState::START_SCREEN;
            }
        }
        if (game_state == GameState::SETTING_SCREEN) {
            if (event.getPos().x >= 400 && event.getPos().x <= 600 && event.getPos().y >= 675 &&
                event.getPos().y <= 725) {
                game_state = GameState::GAME_SCREEN;
            } else if (event.getPos().x >= 400 && event.getPos().x <= 600 && event.getPos().y >= 735 &&
                event.getPos().y <= 785) {
                game_state = GameState::START_SCREEN;
            }
        }
    }


}