#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "pool_game_app.h"
#include "pool_table.h"

namespace poolgame {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
    class PoolGameApp : public ci::app::App {
    public:
        PoolGameApp();

        void draw() override;
        void update() override;

        // TODO: Delete this comment. Feel free to play around with these variables
        // provided that you can see the entire UI on your screen.
        const int kWindowSize = 875;
        const int kMargin = 100;

    private:
        PoolTable table_;
    };

}  // namespace idealgas

