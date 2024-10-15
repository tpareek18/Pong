//
// Created by Tanay Pareek on 20/04/2021.
//
#include <catch2/catch.hpp>
#include "cinder/gl/gl.h"
#include "paddle.h"

using paddleshiftapp::Paddle;
using glm::vec2;
using std::vector;

TEST_CASE("Paddle class constructor initializes attributes correctly") {
  vector<vec2> test_valid_position({vec2(0, 1), vec2(2, 0)});
  vec2 test_valid_velocity(0, 10);
  ci::Color test_valid_color("blue");
  Paddle test_paddle_one(test_valid_position, test_valid_velocity,
                         test_valid_color);

  SECTION("Testing valid position vector") {
    REQUIRE(test_paddle_one.GetPosition() == test_valid_position);
  }

  SECTION("Testing valid velocity") {
    REQUIRE(test_paddle_one.GetVelocity() == test_valid_velocity);
  }

  SECTION("Testing valid color") {
    REQUIRE(test_paddle_one.GetColor() == test_valid_color);
  }

  SECTION("Testing invalid position vector") {
    vector<vec2> test_invalid_position({vec2(0, 1), vec2(2, 0), vec2(3, 0)});
    REQUIRE_THROWS_AS(Paddle(test_invalid_position, test_valid_velocity,
                             test_valid_color), std::invalid_argument);
  }

  SECTION("Testing invalid velocity") {
    vec2 test_invalid_velocity_one(8, 10);
    REQUIRE_THROWS_AS(Paddle(test_valid_position, test_invalid_velocity_one,
                             test_valid_color), std::invalid_argument);
  }
}

TEST_CASE("Setters are working correctly") {
  vector<vec2> test_valid_position({vec2(0, 1), vec2(2, 0)});
  vec2 test_valid_velocity(0, 10);
  ci::Color test_valid_color("blue");
  Paddle test_paddle_one(test_valid_position, test_valid_velocity,
                         test_valid_color);
  SECTION("Position setter is working properly") {
    vector<vec2> new_position({vec2(1, 3), vec2(5, 6)});
    test_paddle_one.SetPosition({vec2(1, 3), vec2(5, 6)});
    REQUIRE(test_paddle_one.GetPosition() == new_position);
  }
}

TEST_CASE("Position is being updated correctly") {
  vector<vec2> test_valid_position({vec2(25, 50), vec2(125, 195)});
  vec2 test_valid_velocity(0, 10);
  ci::Color test_valid_color("blue");
  Paddle test_paddle_one(test_valid_position, test_valid_velocity,
                         test_valid_color);
  SECTION("Position is being updated correctly when moving down") {
    vector<vec2> test_final_position({vec2(25, 60), vec2(125, 205)});
    test_paddle_one.SetIsMovingDown(true);
    test_paddle_one.SetIsMovingUp(false);
    test_paddle_one.UpdatePosition();
    REQUIRE(test_paddle_one.GetPosition() == test_final_position);
  }

  SECTION("Position is being updated correctly when moving up") {
    vector<vec2> test_final_position({vec2(25, 40), vec2(125, 185)});
    test_paddle_one.SetIsMovingDown(false);
    test_paddle_one.SetIsMovingUp(true);
    test_paddle_one.UpdatePosition();
    REQUIRE(test_paddle_one.GetPosition() == test_final_position);
  }

  SECTION("Position is being updated correctly when not moving") {
    vector<vec2> test_final_position({vec2(25, 50), vec2(125, 195)});
    test_paddle_one.SetIsMovingDown(false);
    test_paddle_one.SetIsMovingUp(false);
    test_paddle_one.UpdatePosition();
    REQUIRE(test_paddle_one.GetPosition() == test_final_position);
  }
}