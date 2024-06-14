#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "simulation.hpp"

TEST_CASE("Simple test 1") {
    Position archerPos = {0.0, 0.0, 0.0};
    Position targetPos = {50.0, 0.0, 0.0};
    double v0 = 100.0;
    double m = 0.1;
    double dt = 0.1;

    REQUIRE(simulateShot(archerPos, targetPos, v0, m, dt) == 0);
}

TEST_CASE("Simple test 2 Archer negative position") {
    Position archerPos = {-10.0, -10.0, 0.0};
    Position targetPos = {100.0, 0.0, 0.0};
    double v0 = 150.0;
    double m = 0.15;
    double dt = 0.05;

    REQUIRE(simulateShot(archerPos, targetPos, v0, m, dt) == 0);
}

TEST_CASE("Simple test 3 Far target") {
    Position archerPos = {0.0, 5.0, 0.0};
    Position targetPos = {480.0, 5.0, 0.0};
    double v0 = 120.0;
    double m = 0.2;
    double dt = 0.2;

    REQUIRE(simulateShot(archerPos, targetPos, v0, m, dt) == 0);
}

TEST_CASE("Simple test 4 Close target") {
    Position archerPos = {0.0, 0.0, 0.0};
    Position targetPos = {10.0, 0.0, 0.0};
    double v0 = 50.0;
    double m = 0.05;
    double dt = 0.1;

    REQUIRE(simulateShot(archerPos, targetPos, v0, m, dt) == 0);
}

TEST_CASE("Simple test 5 Negative initial velocity") {
    Position archerPos = {0.0, 0.0, 0.0};
    Position targetPos = {100.0, 0.0, 0.0};
    double v0 = -10.0;
    double m = 0.1;
    double dt = 0.1;

    REQUIRE(simulateShot(archerPos, targetPos, v0, m, dt) == -1);
}


TEST_CASE("Simple test 6 Archer Target same position") {
    Position archerPos = {0.0, 0.0, 0.0};
    Position targetPos = {0.0, 0.0, 0.0};
    double v0 = 10.0;
    double m = 0.1;
    double dt = 0.1;

    REQUIRE(simulateShot(archerPos, targetPos, v0, m, dt) == -1);
}

int main(int argc, char* argv[]) {
    int result = Catch::Session().run(argc, argv);
    
    return result;
}