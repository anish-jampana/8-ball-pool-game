// contains similarities in implementation to my ideal gas MP
#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "pool_game_app.h"
#include "pool_table.h"
#include "start_screen.h"


namespace poolgame {

    class PoolGameApp : public ci::app::App {
    public:
        PoolGameApp();
        void draw() override;
        void update() override;
        void mouseUp(ci::app::MouseEvent event) override;
        void mouseDrag(ci::app::MouseEvent event) override;

        const int kWindowSize = 1000;
        const int kMargin = 100;

    private:
        StartScreen screen_ = StartScreen();
        PoolTable table_ = PoolTable();
    };

}  // namespace idealgas

