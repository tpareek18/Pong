#pragma once

#include "cinder/gl/gl.h"
#include "cinder/app/Window.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "paddle.h"
#include "cinder/audio/Voice.h"
#include "cinder/audio/audio.h"

using glm::vec2;

namespace paddleshiftapp {

/**
 * This class stores all the information related to the ball and player
 * scores on the game board.
 */
class Ball {

 public:

  /**
   * Default constructor for ball class.
   */
  Ball() = default;

  /**
   * This constructor initializes the position vector, velocity vector
   * and vector of colors for the balls.
   * @param position The x and y coordinate of the ball.
   * @param velocity The x and y coordinate of the velocity of the ball.
   * @param color The color of the ball.
   * @param radius The radius of the ball.
   */
  Ball(const vec2 &position, const vec2 &velocity, const ci::Color &color,
       const float &radius);

  /**
   * Displays the ball and the player scores.
   */
  void Display() const;

  /**
   * This function updates the velocity of the ball and the score of the player
   * based on collision with the wall/boundary.
   */
  void UpdateVelocityWallCollision();

  /**
   * This function updates the velocity based on the collision with the left
   * or right paddle.
   * @param paddle_one A constant reference of the paddle class (left paddle).
   * @param paddle_two A constant reference of the paddle class (right paddle).
   */
  void UpdateVelocityPaddleCollision(const Paddle &paddle_one, const Paddle &
  paddle_two);

  const vec2 &GetPosition() const;

  const vec2 &GetVelocity() const;

  const ci::Color &GetColor() const;

  const float &GetRadius() const;

  const size_t &GetPlayerOneScore() const;

  const size_t &GetPlayerTwoScore() const;

  void SetVelocity(const vec2 &velocity);

  void SetPlayerOneScore(size_t paddle_one_score);

  void SetPlayerTwoScore(size_t paddle_two_score);

 private:

  vec2 position_;
  vec2 velocity_;
  ci::Color color_;
  float radius_;
  size_t paddle_one_score_;
  size_t paddle_two_score_;
  ci::audio::VoiceRef paddle_sound_;

};
} // namespace paddleshiftapp