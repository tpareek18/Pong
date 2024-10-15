#include "paddle_shift_simulation_app.h"
#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::app::KeyEvent;
using namespace std;

namespace paddleshiftapp {

PaddleShiftApp::PaddleShiftApp() {
  ci::app::setWindowSize(kWindowSizeX, kWindowSizeY);
  // Initializing position of player one's paddle.
  vec2 point_one((kMargin),
                 (((kWindowSizeY - 2 * kMargin) / 2) - kPaddleHeight / 2));
  vec2 point_two((kMargin + kPaddleWidth),
                 (((kWindowSizeY - 2 * kMargin) / 2) + kPaddleHeight / 2));
  player_1_position_ = {point_one, point_two};
  // Initializing position of player two's paddle.
  point_one = vec2((kWindowSizeX - kMargin - kPaddleWidth),
                   (((kWindowSizeY - 2 * kMargin) / 2) - kPaddleHeight / 2));
  point_two = vec2((kWindowSizeX - kMargin),
                   (((kWindowSizeY - 2 * kMargin) / 2) + kPaddleHeight / 2));
  player_2_position_ = {point_one, point_two};
  // Initializing both paddles with their attributes
  paddle_one_ = Paddle(player_1_position_, paddle_velocity_,
                       paddle_colors_[0]);
  paddle_two_ = Paddle(player_2_position_, paddle_velocity_,
                       paddle_colors_[1]);
  // Initializing ball's starting position.
  ball_position_ = vec2(kWindowSizeX / 2, kWindowSizeY / 2);
  ball_ = Ball(ball_position_, ball_velocity_, paddle_colors_[0], radius_);
}

void PaddleShiftApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);
  cinder::gl::color(1, 1, 1);
  if (game_state_ == GameState::kGameNotStarted) {
    string image_path = "Paddle_Shift_Start_Window.png";
    ci::gl::draw(ci::gl::Texture2d::create(loadImage
    (ci::app::loadAsset(image_path))),vec2(0, 0));
  } else if (game_state_ == GameState::kGameStartedSelectDifficulty) {
    string image_path = "Paddle_Shift_Second_Window.png";
    ci::gl::draw(ci::gl::Texture2d::create(loadImage
    (ci::app::loadAsset(image_path))),vec2(0, 0));
  } else if (game_state_ == GameState::kGameStartedSelectWinningScore) {
    string image_path = "Paddle_Shift_Third_Window.png";
    ci::gl::draw(ci::gl::Texture2d::create(loadImage
    (ci::app::loadAsset(image_path))),vec2(0, 0));
  } else if (game_state_ == GameState::kGamePlaying) {
    cinder::gl::drawLine(cinder::vec2(kWindowSizeX / 2, kWindowSizeY),
                         cinder::vec2(kWindowSizeX / 2, 0));
    paddle_one_.Display();
    paddle_two_.Display();
    ball_.Display();
  } else if (game_state_ == GameState::kGameEnded) {
    string image_path = "Paddle_Shift_Game_Over.png";
    ci::gl::draw(
        ci::gl::Texture2d::create(loadImage(ci::app::loadAsset(image_path))),
        vec2(0, 0));
    if (player_one_ && !player_two_) {
      ci::gl::drawStringCentered("Player 1 wins!",
                                 vec2(kWindowSizeX / 2, kWindowSizeY / 2),
                                 ci::Color("white"),
                                 ci::Font("arial", 40));
    } else if (player_two_ && !player_one_) {
      ci::gl::drawStringCentered("Player 2 wins!",
                                 vec2(kWindowSizeX / 2, kWindowSizeY / 2),
                                 ci::Color("white"),
                                 ci::Font("arial", 40));
    } else {
      ci::gl::drawStringCentered("You have quit the game!",
                                 vec2((kWindowSizeX / 2) - 50,
                                          kWindowSizeY / 2),
                                 ci::Color("white"),
                                 ci::Font("arial", 40));
    }
  }
}

void PaddleShiftApp::keyDown(ci::app::KeyEvent event) {
  ci::audio::SourceFileRef game_start = ci::audio::load
      (ci::app::loadAsset("Game_Start.mp3"));
  game_start_sound_ = ci::audio::Voice::create(game_start);
  ci::audio::SourceFileRef game_over = ci::audio::load
      (ci::app::loadAsset("Game_Over.mp3"));
  game_over_sound_ = ci::audio::Voice::create(game_over);
  if (game_state_ == GameState::kGameNotStarted) {
    switch (event.getCode()) {
      case ci::app::KeyEvent::KEY_s: {
        game_state_ = GameState::kGameStartedSelectDifficulty;
        game_start_sound_->start();
        break;
      }
      case ci::app::KeyEvent::KEY_ESCAPE: {
        game_state_ = GameState::kGameEnded;
        game_over_sound_->start();
      }
    }
  }

  if (game_state_ == GameState::kGameStartedSelectDifficulty) {
    switch (event.getCode()) {
      case ci::app::KeyEvent::KEY_e: {
        game_difficulty_ = Difficulty::kEasy;
        game_state_ = GameState::kGameStartedSelectWinningScore;
        ball_velocity_ = vec2(2, 2);
        ball_.SetVelocity(ball_velocity_);
        break;
      }
      case ci::app::KeyEvent::KEY_m: {
        game_difficulty_ = Difficulty::kMedium;
        game_state_ = GameState::kGameStartedSelectWinningScore;
        ball_velocity_ = vec2(4, 4);
        ball_.SetVelocity(ball_velocity_);
        break;
      }
      case ci::app::KeyEvent::KEY_h: {
        game_difficulty_ = Difficulty::kHard;
        game_state_ = GameState::kGameStartedSelectWinningScore;
        ball_velocity_ = vec2(-5, 6);
        ball_.SetVelocity(ball_velocity_);
        break;
      }
    }
  }

  if (game_state_ == GameState::kGameStartedSelectWinningScore) {
    switch (event.getCode()) {
      case ci::app::KeyEvent::KEY_3: {
        winning_score_ = 3;
        game_state_ = GameState::kGamePlaying;
        break;
      }
      case ci::app::KeyEvent::KEY_6: {
        winning_score_ = 6;
        game_state_ = GameState::kGamePlaying;
        break;
      }
      case ci::app::KeyEvent::KEY_9: {
        winning_score_ = 9;
        game_state_ = GameState::kGamePlaying;
        break;
      }
    }
  }

  if (game_state_ == GameState::kGamePlaying) {
    switch (event.getCode()) {
      case ci::app::KeyEvent::KEY_w: {
        paddle_one_.SetIsMovingUp(true);
        paddle_one_.SetIsMovingDown(false);
        break;
      }
      case ci::app::KeyEvent::KEY_s: {
        paddle_one_.SetIsMovingUp(false);
        paddle_one_.SetIsMovingDown(true);
        break;
      }
      case ci::app::KeyEvent::KEY_UP: {
        paddle_two_.SetIsMovingUp(true);
        paddle_two_.SetIsMovingDown(false);
        break;
      }
      case ci::app::KeyEvent::KEY_DOWN: {
        paddle_two_.SetIsMovingUp(false);
        paddle_two_.SetIsMovingDown(true);
        break;
      }
      case ci::app::KeyEvent::KEY_ESCAPE: {
        game_state_ = GameState::kGameEnded;
        game_over_sound_->start();
        break;
      }
    }
  }

  if (game_state_ == GameState::kGameEnded) {
    switch (event.getCode()) {
      case ci::app::KeyEvent::KEY_RETURN: {
        game_state_ = GameState::kGameNotStarted;
        ball_.SetPlayerOneScore(0);
        ball_.SetPlayerTwoScore(0);
        ball_.SetVelocity(vec2(0, 0));
        paddle_one_.SetPosition(player_1_position_);
        paddle_two_.SetPosition(player_2_position_);
        player_one_ = false;
        player_two_ = false;
      }
    }
  }
}

void PaddleShiftApp::keyUp(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_w: {
      paddle_one_.SetIsMovingUp(false);
      break;
    }
    case ci::app::KeyEvent::KEY_s: {
      paddle_one_.SetIsMovingDown(false);
      break;
    }
    case ci::app::KeyEvent::KEY_UP: {
      paddle_two_.SetIsMovingUp(false);
      break;
    }
    case ci::app::KeyEvent::KEY_DOWN: {
      paddle_two_.SetIsMovingDown(false);
      break;
    }
  }
}

void PaddleShiftApp::update() {
  if (game_state_ == GameState::kGamePlaying) {
    ci::audio::SourceFileRef game_winner = ci::audio::load
        (ci::app::loadAsset("Game_Victory.mp3"));
    game_winner_sound_ = ci::audio::Voice::create(game_winner);
    paddle_one_.UpdatePosition();
    paddle_two_.UpdatePosition();
    ball_.UpdateVelocityWallCollision();
    ball_.UpdateVelocityPaddleCollision(paddle_one_, paddle_two_);
    if (ball_.GetPlayerOneScore() >= ball_.GetPlayerTwoScore()) {
      if (ball_.GetPlayerOneScore() == winning_score_) {
        game_state_ = GameState::kGameEnded;
        player_one_ = true;
        game_winner_sound_->start();
      }
    } else {
      if (ball_.GetPlayerTwoScore() == winning_score_) {
        game_state_ = GameState::kGameEnded;
        player_two_ = true;
        game_winner_sound_->start();
      }
    }
  }
}

} // namespace paddleshiftapp