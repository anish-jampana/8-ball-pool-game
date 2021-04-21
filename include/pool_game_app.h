// contains similarities in implementation to my ideal gas MP
#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "pool_game_app.h"
#include "pool_table.h"
//#include <Box2D/Box2D.h>


namespace poolgame {

    class PoolGameApp : public ci::app::App {
    public:
        PoolGameApp();
        void draw() override;
        void update() override;

        const int kWindowSize = 1000;
        const int kMargin = 100;

    private:
        PoolTable table_ = PoolTable();
    };

}  // namespace idealgas

