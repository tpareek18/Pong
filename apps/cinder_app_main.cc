//
// Created by Tanay Pareek on 19/04/2021.
//

#include "paddle_shift_simulation_app.h"

using paddleshiftapp::PaddleShiftApp;

void prepareSettings(PaddleShiftApp::Settings *settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(PaddleShiftApp, ci::app::RendererGl, prepareSettings);