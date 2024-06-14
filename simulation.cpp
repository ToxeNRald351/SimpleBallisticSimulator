#include <entt/entt.hpp>
#include <iostream>
#include <cmath>
#include "simulation.hpp"

int calculateHit(entt::registry &registry, entt::entity &arrow, const Position &targetPos, double *thetaContainer) {
    auto &arrowVelocity = registry.get<Velocity>(arrow);
    auto &arrowDisplacement = registry.get<Displacement>(arrow);
    auto &arrowAngle = registry.get<Angle>(arrow);

    double A = (GRAVITY * std::pow(arrowDisplacement.x, 2)) / (2 * std::pow(arrowVelocity.v, 2));
    double B = -arrowDisplacement.x * std::cos(arrowAngle.phi);
    double C = arrowDisplacement.z * std::pow(std::cos(arrowAngle.phi), 2) + A;

    double D = std::pow(B, 2) - 4 * A * C;

    int n = 0;
    if (D < 0) {
        std::cout << "The archer cannot hit the target" << std::endl;
    }
    else if (D > 0) {
        std::cout << "The archer can hit the target from two different angles" << std::endl;
        n = 2;
        thetaContainer[0] = std::atan((-B + std::sqrt(D)) / (2 * A));
        thetaContainer[1] = std::atan((-B - std::sqrt(D)) / (2 * A));
    }
    else {
        std::cout << "The archer can hit the target from one angle" << std::endl;
        n = 1;
        thetaContainer[0] = std::atan(-B / (2 * A));
    }
    
    return n;
}

void simulate(entt::registry &registry, entt::entity &arrow) {
    auto &arrowDisplacement = registry.get<Displacement>(arrow);
    auto &arrowVelocity = registry.get<Velocity>(arrow);
    auto &arrowTimeStep = registry.get<TimeStep>(arrow);
    auto &arrowAngle = registry.get<Angle>(arrow);

    double time = arrowDisplacement.x / (arrowVelocity.v * std::cos(arrowAngle.theta) * std::cos(arrowAngle.phi));
    double x = 0.0, y = 0.0, z = 0.0;

    for (double t = 0.0; t < time; t += arrowTimeStep.dt) {
        x = arrowVelocity.v * std::cos(arrowAngle.theta) * std::cos(arrowAngle.phi) * t;
        y = arrowVelocity.v * std::cos(arrowAngle.theta) * std::sin(arrowAngle.phi) * t;
        z = arrowVelocity.v * std::sin(arrowAngle.theta) * t - 0.5 * GRAVITY * std::pow(t, 2);
        std::cout << "t = " << t << "s: (" << x << ", " << y << ", " << z << ")" << std::endl;
    }

    x = arrowVelocity.v * std::cos(arrowAngle.theta) * std::cos(arrowAngle.phi) * time;
    y = arrowVelocity.v * std::cos(arrowAngle.theta) * std::sin(arrowAngle.phi) * time;
    z = arrowVelocity.v * std::sin(arrowAngle.theta) * time - 0.5 * GRAVITY * std::pow(time, 2);
    std::cout << "t = " << time << "s: (" << x << ", " << y << ", " << z << ")" << std::endl;
}

int simulateShot(const Position &archerPos, const Position &targetPos, const double v0, const double arrowMass, const double timeStep) {
    if ((archerPos.x == targetPos.x && archerPos.y == targetPos.y && archerPos.z == targetPos.z) || v0 <= 0.0 || arrowMass <= 0.0 || timeStep <= 0.0) {
        std::cout << "Invalid input" << std::endl;
        return -1;
    }
    
    entt::registry registry;
    
    // Arrow entity
    entt::entity arrow = registry.create();
    // base attributes
    registry.emplace<Position>(arrow, archerPos.x, archerPos.y, archerPos.z);
    registry.emplace<Velocity>(arrow, v0);
    registry.emplace<Acceleration>(arrow, GRAVITY);
    registry.emplace<Mass>(arrow, arrowMass);
    registry.emplace<TimeStep>(arrow, timeStep);
    // additional attributes
    double dx = targetPos.x - archerPos.x, dy = targetPos.y - archerPos.y, dz = targetPos.z - archerPos.z;
    registry.emplace<Displacement>(arrow, dx, dy, dz);
    registry.emplace<Angle>(arrow, std::atan2(dy, dx), 0.0);

    double thetaContainer[2] = {0.0, 0.0};                                   // container for two possible angles
    int thetaN = calculateHit(registry, arrow, targetPos, thetaContainer);   // number of angles    

    // DEBUG INFO
    std::cout << "Number of calculated angles: " << thetaN << std::endl;
    std::cout << "Angle values: " << std::endl;
    for (int i = 0; i < thetaN; i++) {
        std::cout << "\t" << thetaContainer[i] << " rad" << std::endl;
    }
    
    if (thetaN == 0) {
        std::cout << "Nothing to simulate" << std::endl;
        return -1;
    }

    std::cout << "Starting the simulation" << std::endl;
    auto &arrowAngle = registry.get<Angle>(arrow);
    for (int i = 0; i < thetaN; i++) {
        std::cout << "Angle " << i + 1 << ":" << std::endl;
        arrowAngle.theta = thetaContainer[i];
        simulate(registry, arrow);
    }
    //*/
    
    return 0;
}