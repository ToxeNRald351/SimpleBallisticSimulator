#include <entt/entt.hpp>
#include <iostream>
#include <cmath>
#include "simulation.hpp"

/*
In the given problem, the mass of the arrow does not directly affect the trajectory calculation 
because gravity acts uniformly on all masses. The gravitational force is given by F = m * g, where 
g is the acceleration due to gravity. In the equations of motion, the mass m cancels out, 
leaving the trajectory dependent only on the initial velocity, angle, and gravitational acceleration.

Therefore, while mass is crucial for real-world dynamics (like air resistance), 
it doesn't impact the parabolic trajectory under the idealized physics assumption (constant gravity and no air resistance).
*/

int main() {
    Position archerPos = {0.0, 0.0, 0.0};
    Position targetPos = {50.0, 0.0, 0.0};
    double v0 = 100.0;                              // initial arrow speed
    double m = 0.1;                                 // arrow mass
    double dt = 0.1;                                // time step

    simulateShot(archerPos, targetPos, v0, m, dt);

    return 0;
}