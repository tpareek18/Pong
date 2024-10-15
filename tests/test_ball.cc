//
// Created by Tanay Pareek on 25/04/2021.
//
#include "cinder/gl/gl.h"
#include "catch2/catch.hpp"
#include "ball.h"
#include "paddle.h"

using paddleshiftapp::Paddle;
using paddleshiftapp::Ball;
using glm::vec2;

TEST_CASE("Ball class constructor initializes attributes appropriately") {
  vec2 test_valid_position(0, 1);
  vec2 test_valid_velocity(0, 10);
  ci::Color test_valid_color("blue");
  float test_valid_radius = 10.0;
  Ball new_ball(test_valid_position, test_valid_velocity, test_valid_color,
                test_valid_radius);
  SECTION("Testing valid position vector") {
    REQUIRE(new_ball.GetPosition() == test_valid_position);
  }
  SECTION("Testing valid velocity") {
    REQUIRE(new_ball.GetVelocity() == test_valid_velocity);
  }
  SECTION("Testing valid color") {
    REQUIRE(new_ball.GetColor() == test_valid_color);
  }
  SECTION("Testing valid radius") {
    REQUIRE(new_ball.GetRadius() == test_valid_radius);
  }
  vec2 test_invalid_position(-1, -1);
  SECTION("Testing invalid position vector") {
    REQUIRE_THROWS_AS(Ball(test_invalid_position, test_valid_velocity, test_valid_color,
                                    test_valid_radius), std::invalid_argument);
  }
  float test_invalid_radius = -1.0;
  SECTION("Testing invalid radius") {
    REQUIRE_THROWS_AS(Ball(test_valid_position, test_valid_velocity, test_valid_color,
                                    test_invalid_radius), std::invalid_argument);
  }
}

TEST_CASE("Ball setters are working correctly") {
  vec2 test_valid_position(0, 1);
  vec2 test_valid_velocity(0, 10);
  ci::Color test_valid_color("blue");
  float test_valid_radius = 10.0;
  Ball new_ball(test_valid_position, test_valid_velocity, test_valid_color,
                test_valid_radius);
  SECTION("Velocity Setter works properly") {
    vec2 new_velocity(3,5);
    new_ball.SetVelocity(vec2(3,5));
    REQUIRE(new_ball.GetVelocity() == new_velocity);
  }
  SECTION("Player 1 Score Setter works properly") {
    size_t new_score_one = 8;
    new_ball.SetPlayerOneScore(8);
    REQUIRE(new_ball.GetPlayerOneScore() == new_score_one);
  }
  SECTION("Player 2 Score Setter works properly") {
    size_t new_score_two = 3;
    new_ball.SetPlayerOneScore(3);
    REQUIRE(new_ball.GetPlayerOneScore() == new_score_two);
  }
}
TEST_CASE("Velocity, position and scores are correctly updated on collision "
          "with wall") {
  vec2 position(10, 1);
  vec2 velocity(1, -2);
  ci::Color color("blue");
  float radius = 10.0;
  size_t paddle_one_score = 0;
  size_t paddle_two_score = 0;
  Ball new_ball(position, velocity, color, radius);
  SECTION("Ball collides with upper wall") {
    new_ball.UpdateVelocityWallCollision();
    REQUIRE(new_ball.GetVelocity() == vec2(1, 2));
    REQUIRE(new_ball.GetPosition() == vec2(11, 3));
  }
  SECTION("Ball collides with lower wall") {
    position = vec2(10, 699);
    velocity = vec2(1, 2);
    Ball ball_one(position, velocity, color, radius);
    ball_one.UpdateVelocityWallCollision();
    REQUIRE(ball_one.GetVelocity() == vec2(1, -2));
    REQUIRE(ball_one.GetPosition() == vec2(11, 697));
  }
  SECTION("Ball collides with left wall") {
    position = vec2(1, 10);
    velocity = vec2(-2, 2);
    Ball ball_two(position, velocity, color, radius);
    ball_two.UpdateVelocityWallCollision();
    REQUIRE(ball_two.GetVelocity() == vec2(-2, 2));
    REQUIRE(ball_two.GetPosition() == vec2(448, 255));
    REQUIRE(ball_two.GetPlayerOneScore() == paddle_one_score);
    REQUIRE(ball_two.GetPlayerTwoScore() == ++paddle_two_score);
  }
  SECTION("Ball collides with right wall") {
    position = vec2(899, 200);
    velocity = vec2(2, 3);
    Ball ball_three(position, velocity, color, radius);
    ball_three.UpdateVelocityWallCollision();
    REQUIRE(ball_three.GetVelocity() == vec2(2, 3));
    REQUIRE(ball_three.GetPosition() == vec2(452, 256));
    REQUIRE(ball_three.GetPlayerOneScore() == ++paddle_one_score);
    REQUIRE(ball_three.GetPlayerTwoScore() == paddle_two_score);
  }
}

TEST_CASE("Velocity, position and color are correctly updated on collision "
          "with paddle") {
  vec2 ball_position(50, 100);
  vec2 ball_velocity(-1, -2);
  ci::Color ball_color("blue");
  float ball_radius = 10.0;
  Ball new_ball(ball_position, ball_velocity, ball_color, ball_radius);

  vector<vec2> paddle_one_position({vec2(25, 50), vec2(40, 150)});
  vec2 paddle_one_velocity(0, 7);
  ci::Color paddle_one_color("blue");
  Paddle test_paddle_one(paddle_one_position, paddle_one_velocity, paddle_one_color);

  vector<vec2> paddle_two_position({vec2(850, 500), vec2(865, 600)});
  vec2 paddle_two_velocity(0, -6);
  ci::Color paddle_two_color("yellow");
  Paddle test_paddle_two(paddle_two_position, paddle_two_velocity,
                       paddle_two_color);

  SECTION("Attributes are correctly updated on collision with left paddle") {
    new_ball.UpdateVelocityPaddleCollision(test_paddle_one, test_paddle_two);
    REQUIRE(new_ball.GetVelocity() == vec2(1, -2));
    REQUIRE(new_ball.GetPosition() == vec2(51, 98));
    REQUIRE(new_ball.GetColor() == paddle_one_color);
    REQUIRE(new_ball.GetRadius() == ball_radius);
  }

  SECTION("Attributes are correctly updated on collision with right paddle") {
    ball_position = vec2(840, 550);
    ball_velocity = vec2(1, 2);
    new_ball = Ball(ball_position, ball_velocity, ball_color, ball_radius);
    new_ball.UpdateVelocityPaddleCollision(test_paddle_one, test_paddle_two);
    REQUIRE(new_ball.GetVelocity() == vec2(-1, 2));
    REQUIRE(new_ball.GetPosition() == vec2(839, 552));
    REQUIRE(new_ball.GetColor() == paddle_two_color);
    REQUIRE(new_ball.GetRadius() == ball_radius);
  }
}