//
// Created by Tanay Pareek on 25/04/2021.
//

#include "ball.h"
#include "cinder/gl/gl.h"
#include "paddle_shift_simulation_app.h"
#include <cinder/Font.h>
#include <cinder/Text.h>

namespace paddleshiftapp {

using cinder::Rectf;

Ball::Ball(const vec2 &position, const vec2 &velocity, const ci::Color &
color, const float &radius)
    : position_(position), velocity_(velocity), color_(color), radius_
    (radius) {
  if (position_.x < 0 || position_.y < 0) {
    throw std::invalid_argument("Invalid coordinates entered for position of"
                                "the ball");
  }
  if (radius_ <= 0) {
    throw std::invalid_argument("Invalid radius size entered");
  }
  paddle_one_score_ = 0;
  paddle_two_score_ = 0;
}

void Ball::Display() const {
  // Displaying the ball.
  ci::gl::color(color_);
  ci::gl::drawSolidCircle(vec2(position_.x, position_.y), radius_);

  // Displaying player one's score.
  ci::gl::drawStringCentered(std::to_string(paddle_one_score_),
                             vec2(200, 50), ci::Color("white"),
                             ci::Font("arial", 40));

  // Displaying player two's score.
  ci::gl::drawStringCentered(std::to_string(paddle_two_score_),
                             vec2(700, 50), ci::Color("white"),
                             ci::Font("arial", 40));
}

void Ball::UpdateVelocityWallCollision() {

  // Checks if the ball has hit upper or lower boundary.
  if (position_.y + velocity_.y - radius_ <= 0 ||
      position_.y + velocity_.y + radius_ >= PaddleShiftApp::kWindowSizeY) {
    velocity_.y *= -1;
  }

  // Checks if the ball has hit the right boundary.
  if (position_.x + velocity_.x > PaddleShiftApp::kWindowSizeX) {
    position_.x = PaddleShiftApp::kWindowSizeX / 2;
    position_.y = PaddleShiftApp::kWindowSizeY / 2;
    ++paddle_one_score_;
  }
  // Checks if the ball has hit the left boundary.
  if (position_.x + velocity_.x < 0) {
    position_.x = PaddleShiftApp::kWindowSizeX / 2;
    position_.y = PaddleShiftApp::kWindowSizeY / 2;
    ++paddle_two_score_;
  }
  position_ += velocity_;
}

void Ball::UpdateVelocityPaddleCollision(const Paddle &paddle_one, const
Paddle &paddle_two) {

  float ball_position_left = position_.x - radius_;
  double paddle_one_x_width = paddle_one.GetPosition()[0][0] +
                              PaddleShiftApp::kPaddleWidth;
  double paddle_one_y_height = paddle_one.GetPosition()[0][1] +
                               PaddleShiftApp::kPaddleHeight;

  // Checks if it hits the left paddle and updates velocity and color
  // accordingly.
  if (ball_position_left <= paddle_one_x_width && ball_position_left >=
                                                  paddle_one.GetPosition()[0][0] &&
      position_.y <= paddle_one_y_height &&
      position_.y >= paddle_one.GetPosition()[0][1]) {
    velocity_[0] -= 2 * velocity_[0];
    color_ = paddle_one.GetColor();
    ci::audio::SourceFileRef pong_sound = ci::audio::load
        (ci::app::loadAsset("Paddle.mp3"));
    paddle_sound_ = ci::audio::Voice::create(pong_sound);
    paddle_sound_->start();
  }

  float ball_position_right = position_.x + radius_;
  double paddle_two_x_width = paddle_two.GetPosition()[0][0] +
                              PaddleShiftApp::kPaddleWidth;
  double paddle_two_y_height = paddle_two.GetPosition()[0][1] +
                               PaddleShiftApp::kPaddleHeight;

  // Checks if it hits the right paddle and updates velocity and color
  // accordingly.
  if (ball_position_right >= paddle_two.GetPosition()[0][0] &&
      ball_position_right <= paddle_two_x_width && position_.y <=
                                                   paddle_two_y_height &&
      position_.y >= paddle_two.GetPosition()[0][1]) {
    velocity_[0] -= 2 * velocity_[0];
    color_ = paddle_two.GetColor();
    ci::audio::SourceFileRef pong_sound = ci::audio::load
        (ci::app::loadAsset("Paddle.mp3"));
    paddle_sound_ = ci::audio::Voice::create(pong_sound);
    paddle_sound_->start();
  }
  position_ += velocity_;
}

const vec2 &Ball::GetPosition() const {
  return position_;
}

const vec2 &Ball::GetVelocity() const {
  return velocity_;
}

const ci::Color &Ball::GetColor() const {
  return color_;
}

const float &Ball::GetRadius() const {
  return radius_;
}

const size_t &Ball::GetPlayerOneScore() const {
  return paddle_one_score_;
}

const size_t &Ball::GetPlayerTwoScore() const {
  return paddle_two_score_;
}

void Ball::SetVelocity(const vec2 &velocity) {
  velocity_ = velocity;
}

void Ball::SetPlayerOneScore(size_t paddle_one_score) {
  paddle_one_score_ = paddle_one_score;
}

void Ball::SetPlayerTwoScore(size_t paddle_two_score) {
  paddle_two_score_ = paddle_two_score;
}
} // namespace paddleshiftapp