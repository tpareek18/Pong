#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/app/Window.h"
#include "paddle.h"
#include "ball.h"
#include "cinder/audio/Voice.h"
#include "cinder/audio/audio.h"

using glm::vec2;

namespace paddleshiftapp {

enum class GameState {
  kGameNotStarted,
  kGameStartedSelectDifficulty,
  kGameStartedSelectWinningScore,
  kGamePlaying,
  kGameEnded,
};

enum class Difficulty {
  kEasy,
  kMedium,
  kHard,
};

/**
* An app for playing the Paddle Shift game.
*/
class PaddleShiftApp : public ci::app::App {

 public:
  PaddleShiftApp();

  void draw() override;

  void keyDown(ci::app::KeyEvent event) override;

  void keyUp(ci::app::KeyEvent event) override;

  void update() override;

  static constexpr double kWindowSizeX = 900;
  static constexpr double kWindowSizeY = 506;
  static constexpr double kMargin = 20;
  static constexpr double kPaddleWidth = 15;
  static constexpr double kPaddleHeight = 100;

 private:
  vector<vec2> player_1_position_;
  vector<vec2> player_2_position_;
  vec2 ball_position_;
  vec2 paddle_velocity_ = vec2(0, 6);
  vec2 ball_velocity_ = vec2(0, 0);
  vector<ci::Color> paddle_colors_ = {ci::Color("red"), ci::Color("white")};
  float radius_ = 10;
  Paddle paddle_one_;
  Paddle paddle_two_;
  Ball ball_;
  GameState game_state_ = GameState::kGameNotStarted;
  bool player_one_ = false;
  bool player_two_ = false;
  Difficulty game_difficulty_;
  size_t winning_score_ = 0;
  ci::audio::VoiceRef game_start_sound_;
  ci::audio::VoiceRef game_over_sound_;
  ci::audio::VoiceRef game_winner_sound_;
};

} // namespace paddleshiftapp