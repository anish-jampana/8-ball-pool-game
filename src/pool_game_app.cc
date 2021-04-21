#include "pool_game_app.h"

namespace poolgame {

    PoolGameApp::PoolGameApp() {
        ci::app::setWindowSize(kWindowSize, kWindowSize);
    }

    void PoolGameApp::draw() {
        ci::Color background_color("black");
        ci::gl::clear(background_color);
        table_.Display();
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

}