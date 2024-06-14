#ifndef SIMULATION_H
#define SIMULATION_H

#include <entt/entt.hpp>

struct Position {
    double x, y, z;
};

struct Displacement {
    double x, y, z;
};

struct Velocity {
    double v;
};

struct Acceleration {
    double a;
};

struct Mass {
    double m;
};

struct TimeStep {
    double dt;
};

struct Angle {
    double phi;
    double theta;
};

const double GRAVITY = 9.81f;
const double PI = 3.14f;

int simulateShot(const Position &archerPos, const Position &targetPos, const double v0, const double arrowMass, const double timeStep);
int calculateHit(entt::registry &registry, entt::entity &arrow, const Position &targetPos, double *thetaContainer);
void simulate(entt::registry &registry, entt::entity &arrow);

#endif // SIMULATION_H