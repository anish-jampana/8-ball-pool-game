#include "pool_game_app.h"

using poolgame::PoolGameApp;

void prepareSettings(PoolGameApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(PoolGameApp, ci::app::RendererGl, prepareSettings);
