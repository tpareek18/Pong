#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "paddle.h"
#include "paddle_shift_simulation_app.h"


namespace paddleshiftapp {

using cinder::Rectf;
using cinder::app::KeyEvent;

Paddle::Paddle(const vector<vec2> &position, const vec2 &velocity,
               const ci::Color &color)
    : position_(position), velocity_(velocity), color_(color) {
  if (position_.size() != 2) {
    throw std::invalid_argument("2 coordinates are required for the paddle");
  }
  if (velocity_.x != 0) {
    throw std::invalid_argument("Invalid value entered for velocity");
  }
  is_moving_up_ = false;
  is_moving_down_ = false;
}

void Paddle::Display() {
  ci::gl::color(color_);
  ci::gl::drawSolidRect(ci::Rectf(position_[0], position_[1]));
}

void Paddle::UpdatePosition() {
  if (is_moving_up_) {
    MoveUp();
  } else if (is_moving_down_) {
    MoveDown();
  }
}

void Paddle::MoveUp() {
  for (size_t i = 0; i < position_.size(); ++i) {
    if (position_[i].y < 0) {
      break;
    }
    position_[i] -= velocity_;
  }
}

void Paddle::MoveDown() {
  for (size_t i = 0; i < position_.size(); ++i) {
    if (position_[1].y > PaddleShiftApp::kWindowSizeY) {
      break;
    }
    position_[i] += velocity_;
  }
}

void Paddle::SetIsMovingUp(bool is_moving_up) {
  is_moving_up_ = is_moving_up;
}

void Paddle::SetIsMovingDown(bool is_moving_down) {
  is_moving_down_ = is_moving_down;
}

const vector<vec2> &Paddle::GetPosition() const {
  return position_;
}

const vec2 &Paddle::GetVelocity() const {
  return velocity_;
}

const ci::Color &Paddle::GetColor() const {
  return color_;
}

void Paddle::SetPosition(const vector<vec2> &position) {
  position_ = position;
}
} // namespace paddleshiftapp