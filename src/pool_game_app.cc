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

    void PoolGameApp::mouseDown(ci::app::MouseEvent event) {
        std::cout<<"Hi"<<std::endl;
    }

}