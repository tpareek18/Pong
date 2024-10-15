#pragma once

#include "cinder/gl/gl.h"
#include "cinder/app/Window.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"

using glm::vec2;
using std::vector;

namespace paddleshiftapp {

/**
 * This class stores all the information related to the paddles on the
 * game board.
 */
class Paddle {

 public:

  /**
   * Default constructor for paddle class.
   */
  Paddle() = default;

  /**
   * This constructor initializes the position vector, velocity vector
   * and vector of colors for the paddles.
   * @param position The x and y coordinate of the paddle.
   * @param velocity The x and y coordinate of the velocity of the paddle.
   * @param color The different colors for different paddles.
   */
  Paddle(const vector<vec2> &position, const vec2 &velocity,
         const ci::Color &color);

  /**
   * Displays the paddle.
   */
  void Display();

  /**
   * Updates the position of the paddle based on the direction it is
   * moving.
   */
  void UpdatePosition();

  /**
   * Sets the boolean value of the paddle depending on whether it is
   * moving up or not.
   * @param is_moving_up true or false depending on whether paddle is
   * moving up or not.
   */
  void SetIsMovingUp(bool is_moving_up);

  /**
   * Sets the boolean value of the paddle depending on whether it is
   * moving down or not.
   * @param is_moving_down true or false depending on whether paddle is
   * moving down or not.
   */
  void SetIsMovingDown(bool is_moving_down);

  const vector<vec2> &GetPosition() const;

  const vec2 &GetVelocity() const;

  const ci::Color &GetColor() const;

  void SetPosition(const vector<vec2> &position);

 private:

  /**
   * Moves the paddle up.
   */
  void MoveUp();

  /**
   * Moves the paddle down.
   */
  void MoveDown();

  vector<vec2> position_;
  vec2 velocity_;
  ci::Color color_;
  bool is_moving_up_;
  bool is_moving_down_;
};
} // namespace paddleshiftapp