#include <catch2/catch.hpp>
#include "pool_table.h"
#include "ball_generator.h"

using poolgame::PoolTable;
using poolgame::BallGenerator;

PoolTable table = PoolTable();

TEST_CASE("Check Balls Moving By Velocity") {
    SECTION("No Velocity") {
        glm::vec2 single_ball_position = table.GetPositions().at(1);
        glm::vec2 single_ball_velocity = table.GetVelocities().at(1);
        REQUIRE(single_ball_velocity == glm::vec2(0, 0));
        REQUIRE(single_ball_position == glm::vec2(700, 500));
        table.Update();
        REQUIRE(single_ball_position == glm::vec2(700, 500));
    }

    SECTION("Moving Right - With Friction") {
        std::vector<glm::vec2> single_ball_position;
        std::vector<glm::vec2> single_ball_velocity;
        single_ball_position.push_back(glm::vec2(700, 500));
        single_ball_velocity.push_back(glm::vec2(50, 0));

        table.SetBallPositions(single_ball_position);
        table.SetBallVelocities(single_ball_velocity);
        table.SetNumOfBalls(1);
        table.Update();
        REQUIRE(table.GetPositions().at(0) == glm::vec2(750, 500));
        REQUIRE(table.GetVelocities().at(0) == glm::vec2(49.700, 0));
    }

    SECTION("Moving Left") {
        std::vector<glm::vec2> single_ball_position;
        std::vector<glm::vec2> single_ball_velocity;
        single_ball_position.push_back(glm::vec2(700, 500));
        single_ball_velocity.push_back(glm::vec2(-50, 0));

        table.SetBallPositions(single_ball_position);
        table.SetBallVelocities(single_ball_velocity);
        table.SetNumOfBalls(1);
        table.Update();
        REQUIRE(table.GetPositions().at(0) == glm::vec2(650, 500));
        REQUIRE(table.GetVelocities().at(0) == glm::vec2(-49.700, 0));
    }

    SECTION("Moving Up") {
        std::vector<glm::vec2> single_ball_position;
        std::vector<glm::vec2> single_ball_velocity;
        single_ball_position.push_back(glm::vec2(700, 500));
        single_ball_velocity.push_back(glm::vec2(0, -50));

        table.SetBallPositions(single_ball_position);
        table.SetBallVelocities(single_ball_velocity);
        table.SetNumOfBalls(1);
        table.Update();
        REQUIRE(table.GetPositions().at(0) == glm::vec2(700, 450));
        REQUIRE(table.GetVelocities().at(0) == glm::vec2(0, -49.700));
    }

    SECTION("Moving Down") {
        std::vector<glm::vec2> single_ball_position;
        std::vector<glm::vec2> single_ball_velocity;
        single_ball_position.push_back(glm::vec2(700, 500));
        single_ball_velocity.push_back(glm::vec2(0, 50));

        table.SetBallPositions(single_ball_position);
        table.SetBallVelocities(single_ball_velocity);
        table.SetNumOfBalls(1);
        table.Update();
        REQUIRE(table.GetPositions().at(0) == glm::vec2(700, 550));
        REQUIRE(table.GetVelocities().at(0) == glm::vec2(0, 49.700));
    }

    SECTION("Moving Diagonally") {
        std::vector<glm::vec2> single_ball_position;
        std::vector<glm::vec2> single_ball_velocity;
        single_ball_position.push_back(glm::vec2(700, 500));
        single_ball_velocity.push_back(glm::vec2(50, 50));

        table.SetBallPositions(single_ball_position);
        table.SetBallVelocities(single_ball_velocity);
        table.SetNumOfBalls(1);
        table.Update();
        REQUIRE(table.GetPositions().at(0) == glm::vec2(750, 550));
        REQUIRE(table.GetVelocities().at(0) == glm::vec2(49.700, 49.700));
    }
}

TEST_CASE("Check Balls Bouncing on Edges") {
    SECTION("Check Ball Bounces on Right Edge") {
        std::vector<glm::vec2> single_ball_position;
        std::vector<glm::vec2> single_ball_velocity;
        single_ball_position.push_back(glm::vec2(870, 500));
        single_ball_velocity.push_back(glm::vec2(50, 0));

        table.SetBallPositions(single_ball_position);
        table.SetBallVelocities(single_ball_velocity);
        table.SetNumOfBalls(1);
        table.Update();
        REQUIRE(table.GetVelocities().at(0) == glm::vec2(-49.700, 0));
    }
    SECTION("Check Ball Bounces on Left Edge") {
        std::vector<glm::vec2> single_ball_position;
        std::vector<glm::vec2> single_ball_velocity;
        single_ball_position.push_back(glm::vec2(130, 500));
        single_ball_velocity.push_back(glm::vec2(-50, 0));

        table.SetBallPositions(single_ball_position);
        table.SetBallVelocities(single_ball_velocity);
        table.SetNumOfBalls(1);
        table.Update();
        REQUIRE(table.GetVelocities().at(0) == glm::vec2(49.700, 0));
    }

    SECTION("Check Ball Bounces on Bottom Edge") {
        std::vector<glm::vec2> single_ball_position;
        std::vector<glm::vec2> single_ball_velocity;
        single_ball_position.push_back(glm::vec2(700, 730));
        single_ball_velocity.push_back(glm::vec2(0, 50));

        table.SetBallPositions(single_ball_position);
        table.SetBallVelocities(single_ball_velocity);
        table.SetNumOfBalls(1);
        table.Update();
        REQUIRE(table.GetVelocities().at(0) == glm::vec2(0, -49.700));
    }

    SECTION("Check Ball Bounces on Top Edge") {
        std::vector<glm::vec2> single_ball_position;
        std::vector<glm::vec2> single_ball_velocity;
        single_ball_position.push_back(glm::vec2(700, 280));
        single_ball_velocity.push_back(glm::vec2(0, -50));

        table.SetBallPositions(single_ball_position);
        table.SetBallVelocities(single_ball_velocity);
        table.SetNumOfBalls(1);
        table.Update();
        REQUIRE(table.GetVelocities().at(0) == glm::vec2(0, 49.700));
    }
}

TEST_CASE("Collision Between Balls Moving Towards Each Other") {
    SECTION("Collision Between Balls Moving Towards Each Other - Single Frame") {
        std::vector<glm::vec2> two_ball_position;
        std::vector<glm::vec2> two_ball_velocity;
        two_ball_position.push_back(glm::vec2(770, 500));
        two_ball_position.push_back(glm::vec2(740, 500));

        two_ball_velocity.push_back(glm::vec2(-30, 0));
        two_ball_velocity.push_back(glm::vec2(50, 0));

        table.SetBallPositions(two_ball_position);
        table.SetBallVelocities(two_ball_velocity);
        table.SetNumOfBalls(2);
        table.Update();
        table.Update();
        REQUIRE(abs(table.GetVelocities().at(0).x - (-29.64108)) < 0.01);
        REQUIRE(table.GetVelocities().at(0).y == 0);
        REQUIRE(abs(table.GetVelocities().at(1).x - 49.4018f) < 0.01);
        REQUIRE(table.GetVelocities().at(1).y == 0);

    }
}
//
//TEST_CASE(
//        "Collision Between Particles Moving Towards Each Other Within One Frame") {
//    SECTION(
//            "Collision Between Particles Horizontally Moving Towards Each Other "
//            "Within 1 Frame") {
//        vector<vec2> particle_positions;
//        particle_positions.push_back(vec2(260, 300));
//        particle_positions.push_back(vec2(300, 300));
//        collision_container.SetParticlesPositions(particle_positions);
//
//        vector<vec2> particle_velocities;
//        particle_velocities.push_back(vec2(10, 0));
//        particle_velocities.push_back(vec2(-10, 0));
//        collision_container.SetParticlesVelocities(particle_velocities);
//
//        vector<int> particle_radii;
//        particle_radii.push_back(20);
//        particle_radii.push_back(10);
//        collision_container.SetParticlesRadii(particle_radii);
//
//        vector<int> particle_masses;
//        particle_masses.push_back(20);
//        particle_masses.push_back(10);
//        collision_container.SetParticlesMasses(particle_masses);
//
//        collision_container.AdvanceOneFrame();
//        REQUIRE((double)collision_container.GetParticlesVelocities().at(0).x ==
//                Approx(-3.333).epsilon(0.01));
//        REQUIRE((double)collision_container.GetParticlesVelocities().at(0).y ==
//                Approx(0.000).epsilon(0.01));
//        REQUIRE((double)collision_container.GetParticlesVelocities().at(1).x ==
//                Approx(16.666).epsilon(0.01));
//        REQUIRE((double)collision_container.GetParticlesVelocities().at(1).y ==
//                Approx(0.000).epsilon(0.01));
//    }
//    SECTION(
//            "Collision Between Particles Vertically Moving Towards Each Other Within "
//            "1 Frame") {
//        vector<vec2> particle_positions;
//        particle_positions.push_back(vec2(260, 300));
//        particle_positions.push_back(vec2(260, 340));
//        collision_container.SetParticlesPositions(particle_positions);
//
//        vector<vec2> particle_velocities;
//        particle_velocities.push_back(vec2(0, 10));
//        particle_velocities.push_back(vec2(0, -10));
//        collision_container.SetParticlesVelocities(particle_velocities);
//
//        vector<int> particle_radii;
//        particle_radii.push_back(20);
//        particle_radii.push_back(10);
//        collision_container.SetParticlesRadii(particle_radii);
//
//        vector<int> particle_masses;
//        particle_masses.push_back(20);
//        particle_masses.push_back(10);
//        collision_container.SetParticlesMasses(particle_masses);
//
//        collision_container.AdvanceOneFrame();
//        REQUIRE((double)collision_container.GetParticlesVelocities().at(0).x ==
//                Approx(0.000).epsilon(0.01));
//        REQUIRE((double)collision_container.GetParticlesVelocities().at(0).y ==
//                Approx(-3.333).epsilon(0.01));
//        REQUIRE((double)collision_container.GetParticlesVelocities().at(1).x ==
//                Approx(0.000).epsilon(0.01));
//        REQUIRE((double)collision_container.GetParticlesVelocities().at(1).y ==
//                Approx(16.666).epsilon(0.01));
//    }
//
//    SECTION(
//            "Collision Between Particles Diagonally Moving Towards Each Other Within "
//            "1 Frame") {
//        vector<vec2> particle_positions;
//        particle_positions.push_back(vec2(270, 310));
//        particle_positions.push_back(vec2(300, 340));
//        collision_container.SetParticlesPositions(particle_positions);
//
//        vector<vec2> particle_velocities;
//        particle_velocities.push_back(vec2(10, 10));
//        particle_velocities.push_back(vec2(-10, -10));
//        collision_container.SetParticlesVelocities(particle_velocities);
//
//        vector<int> particle_radii;
//        particle_radii.push_back(20);
//        particle_radii.push_back(10);
//        collision_container.SetParticlesRadii(particle_radii);
//
//        vector<int> particle_masses;
//        particle_masses.push_back(20);
//        particle_masses.push_back(10);
//        collision_container.SetParticlesMasses(particle_masses);
//
//        collision_container.AdvanceOneFrame();
//        REQUIRE((double)collision_container.GetParticlesVelocities().at(0).x ==
//                Approx(-3.333).epsilon(0.01));
//        REQUIRE((double)collision_container.GetParticlesVelocities().at(0).y ==
//                Approx(-3.333).epsilon(0.01));
//        REQUIRE((double)collision_container.GetParticlesVelocities().at(1).x ==
//                Approx(16.666).epsilon(0.01));
//        REQUIRE((double)collision_container.GetParticlesVelocities().at(1).y ==
//                Approx(16.666).epsilon(0.01));
//    }
//}
//
//TEST_CASE(
//        "No Collision Between Particles Moving Towards Each Other - Not "
//        "Within 1 Frame") {
//    SECTION(
//            "No Collision Between Particles Horizontally Moving Towards Each "
//            "Other") {
//        vector<vec2> particle_positions;
//        particle_positions.push_back(vec2(250, 300));
//        particle_positions.push_back(vec2(300, 300));
//        collision_container.SetParticlesPositions(particle_positions);
//
//        vector<vec2> particle_velocities;
//        particle_velocities.push_back(vec2(10, 0));
//        particle_velocities.push_back(vec2(-10, 0));
//        collision_container.SetParticlesVelocities(particle_velocities);
//
//        vector<int> particle_radii;
//        particle_radii.push_back(20);
//        particle_radii.push_back(10);
//        collision_container.SetParticlesRadii(particle_radii);
//
//        vector<int> particle_masses;
//        particle_masses.push_back(20);
//        particle_masses.push_back(10);
//        collision_container.SetParticlesMasses(particle_masses);
//
//        collision_container.AdvanceOneFrame();
//        REQUIRE(collision_container.GetParticlesVelocities().at(0) == vec2(10, 0));
//        REQUIRE(collision_container.GetParticlesVelocities().at(1) == vec2(-10, 0));
//    }
//
//    SECTION(
//            "No Collision Between Particles Vertically Moving Towards Each "
//            "Other") {
//        vector<vec2> particle_positions;
//        particle_positions.push_back(vec2(260, 300));
//        particle_positions.push_back(vec2(260, 350));
//        collision_container.SetParticlesPositions(particle_positions);
//
//        vector<vec2> particle_velocities;
//        particle_velocities.push_back(vec2(0, 10));
//        particle_velocities.push_back(vec2(0, -10));
//        collision_container.SetParticlesVelocities(particle_velocities);
//
//        vector<int> particle_radii;
//        particle_radii.push_back(20);
//        particle_radii.push_back(10);
//        collision_container.SetParticlesRadii(particle_radii);
//
//        vector<int> particle_masses;
//        particle_masses.push_back(20);
//        particle_masses.push_back(10);
//        collision_container.SetParticlesMasses(particle_masses);
//
//        collision_container.AdvanceOneFrame();
//        REQUIRE(collision_container.GetParticlesVelocities().at(0) == vec2(0, 10));
//        REQUIRE(collision_container.GetParticlesVelocities().at(1) == vec2(0, -10));
//    }
//
//    SECTION(
//            "No Collision Between Particles Diagonally Moving Towards Each "
//            "Other") {
//        vector<vec2> particle_positions;
//        particle_positions.push_back(vec2(250, 300));
//        particle_positions.push_back(vec2(300, 350));
//        collision_container.SetParticlesPositions(particle_positions);
//
//        vector<vec2> particle_velocities;
//        particle_velocities.push_back(vec2(10, 10));
//        particle_velocities.push_back(vec2(-10, -10));
//        collision_container.SetParticlesVelocities(particle_velocities);
//
//        vector<int> particle_radii;
//        particle_radii.push_back(20);
//        particle_radii.push_back(10);
//        collision_container.SetParticlesRadii(particle_radii);
//
//        vector<int> particle_masses;
//        particle_masses.push_back(20);
//        particle_masses.push_back(10);
//        collision_container.SetParticlesMasses(particle_masses);
//
//        collision_container.AdvanceOneFrame();
//        REQUIRE(collision_container.GetParticlesVelocities().at(0) == vec2(10, 10));
//        REQUIRE(collision_container.GetParticlesVelocities().at(1) ==
//                vec2(-10, -10));
//    }
//}
//
//TEST_CASE("No Collision Between Particles Moving Away From Each Other") {
//    SECTION(
//            "No Collision Between Particles Horizontally Moving Away From Each "
//            "Other") {
//        vector<vec2> particle_positions;
//        particle_positions.push_back(vec2(250, 300));
//        particle_positions.push_back(vec2(300, 300));
//        collision_container.SetParticlesPositions(particle_positions);
//
//        vector<vec2> particle_velocities;
//        particle_velocities.push_back(vec2(-10, 0));
//        particle_velocities.push_back(vec2(10, 0));
//        collision_container.SetParticlesVelocities(particle_velocities);
//
//        vector<int> particle_radii;
//        particle_radii.push_back(20);
//        particle_radii.push_back(10);
//        collision_container.SetParticlesRadii(particle_radii);
//
//        vector<int> particle_masses;
//        particle_masses.push_back(20);
//        particle_masses.push_back(10);
//        collision_container.SetParticlesMasses(particle_masses);
//
//        collision_container.AdvanceOneFrame();
//        REQUIRE(collision_container.GetParticlesVelocities().at(0) == vec2(-10, 0));
//        REQUIRE(collision_container.GetParticlesVelocities().at(1) == vec2(10, 0));
//    }
//
//    SECTION(
//            "No Collision Between Particles Vertically Moving Away From Each Other") {
//        vector<vec2> particle_positions;
//        particle_positions.push_back(vec2(260, 300));
//        particle_positions.push_back(vec2(260, 350));
//        collision_container.SetParticlesPositions(particle_positions);
//
//        vector<vec2> particle_velocities;
//        particle_velocities.push_back(vec2(0, -10));
//        particle_velocities.push_back(vec2(0, 10));
//        collision_container.SetParticlesVelocities(particle_velocities);
//
//        vector<int> particle_radii;
//        particle_radii.push_back(20);
//        particle_radii.push_back(10);
//        collision_container.SetParticlesRadii(particle_radii);
//
//        vector<int> particle_masses;
//        particle_masses.push_back(20);
//        particle_masses.push_back(10);
//        collision_container.SetParticlesMasses(particle_masses);
//
//        collision_container.AdvanceOneFrame();
//        REQUIRE(collision_container.GetParticlesVelocities().at(0) == vec2(0, -10));
//        REQUIRE(collision_container.GetParticlesVelocities().at(1) == vec2(0, 10));
//    }
//
//    SECTION(
//            "No Collision Between Particles Diagonally Moving Away From Each Other") {
//        vector<vec2> particle_positions;
//        particle_positions.push_back(vec2(250, 300));
//        particle_positions.push_back(vec2(300, 350));
//        collision_container.SetParticlesPositions(particle_positions);
//
//        vector<vec2> particle_velocities;
//        particle_velocities.push_back(vec2(-10, -10));
//        particle_velocities.push_back(vec2(10, 10));
//        collision_container.SetParticlesVelocities(particle_velocities);
//
//        vector<int> particle_radii;
//        particle_radii.push_back(20);
//        particle_radii.push_back(10);
//        collision_container.SetParticlesRadii(particle_radii);
//
//        vector<int> particle_masses;
//        particle_masses.push_back(20);
//        particle_masses.push_back(10);
//        collision_container.SetParticlesMasses(particle_masses);
//
//        collision_container.AdvanceOneFrame();
//        REQUIRE(collision_container.GetParticlesVelocities().at(0) ==
//                vec2(-10, -10));
//        REQUIRE(collision_container.GetParticlesVelocities().at(1) == vec2(10, 10));
//    }
//}
//
//TEST_CASE("Three Particle Collisions") {
//    SECTION(
//            "Three Particle Collision Between Particles Moving Towards Each Other - "
//            "One Frame") {
//        vector<vec2> particle_positions;
//        particle_positions.push_back(vec2(290, 300));
//        particle_positions.push_back(vec2(310, 300));
//        particle_positions.push_back(vec2(300, 300 + sqrt(300)));
//        collision_container.SetParticlesPositions(particle_positions);
//
//        vector<vec2> particle_velocities;
//        particle_velocities.push_back(vec2(10, 0));
//        particle_velocities.push_back(vec2(-10, 0));
//        particle_velocities.push_back(vec2(0, -10));
//        collision_container.SetParticlesVelocities(particle_velocities);
//
//        vector<int> particle_radii;
//        particle_radii.push_back(10);
//        particle_radii.push_back(10);
//        particle_radii.push_back(10);
//        collision_container.SetParticlesRadii(particle_radii);
//
//        vector<int> particle_masses;
//        particle_masses.push_back(20);
//        particle_masses.push_back(10);
//        particle_radii.push_back(15);
//        collision_container.SetParticlesMasses(particle_masses);
//
//        collision_container.AdvanceOneFrame();
//        REQUIRE((double)collision_container.GetParticlesVelocities().at(0).x ==
//                Approx(-3.333).epsilon(0.01));
//        REQUIRE((double)collision_container.GetParticlesVelocities().at(0).y ==
//                Approx(0.000).epsilon(0.01));
//        REQUIRE((double)collision_container.GetParticlesVelocities().at(1).x ==
//                Approx(16.666).epsilon(0.01));
//        REQUIRE((double)collision_container.GetParticlesVelocities().at(1).y ==
//                Approx(0.000).epsilon(0.01));
//        REQUIRE((double)collision_container.GetParticlesVelocities().at(2).x ==
//                Approx(0.000).epsilon(0.01));
//        REQUIRE((double)collision_container.GetParticlesVelocities().at(2).y ==
//                Approx(-10.000).epsilon(0.01));
//    }
//
//    SECTION(
//            "Three Particle Collision Between Particles Moving Away From Each Other "
//            "- One Frame") {
//        vector<vec2> particle_positions;
//        particle_positions.push_back(vec2(290, 300));
//        particle_positions.push_back(vec2(310, 300));
//        particle_positions.push_back(vec2(300, 300 + sqrt(300)));
//        collision_container.SetParticlesPositions(particle_positions);
//
//        vector<vec2> particle_velocities;
//        particle_velocities.push_back(vec2(-10, 0));
//        particle_velocities.push_back(vec2(10, 0));
//        particle_velocities.push_back(vec2(0, 10));
//        collision_container.SetParticlesVelocities(particle_velocities);
//
//        vector<int> particle_radii;
//        particle_radii.push_back(10);
//        particle_radii.push_back(10);
//        particle_radii.push_back(10);
//        collision_container.SetParticlesRadii(particle_radii);
//
//        vector<int> particle_masses;
//        particle_masses.push_back(20);
//        particle_masses.push_back(10);
//        particle_radii.push_back(15);
//        collision_container.SetParticlesMasses(particle_masses);
//
//        collision_container.AdvanceOneFrame();
//        REQUIRE(collision_container.GetParticlesVelocities().at(0) == vec2(-10, 0));
//        REQUIRE(collision_container.GetParticlesVelocities().at(1) == vec2(10, 0));
//        REQUIRE(collision_container.GetParticlesVelocities().at(2) == vec2(0, 10));
//    }
//}
