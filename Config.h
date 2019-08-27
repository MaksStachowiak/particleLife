#pragma once

const double BALL_RADIUS = 5;
const double BALL_DIAM   = 2 * BALL_RADIUS;

const int NUMBER_OF_SPECIES = 5;
const int STARTING_POPULATION = 400;

const int MESSAGE_LIFESPAN = 5;
const int FONT_SIZE = 20;

namespace Display
{
    constexpr uint16_t WIDTH  = 1800;
    constexpr uint16_t HEIGHT = 900;    
}

namespace Physics
{
    const double OVERLAP_REPULSION_MULTIPLIER = 5;

    const double INTERACTION_FORCE_MULTIPLIER = 0.5;
 
    // 1 = one extra particle diameter of separation;
    const double MIN_RADIUS_MULTIPLIER = 1; // higher values make things more dynamic
    const double MAX_RADIUS_MULTIPLIER = 4; // higher values allow formation of bigger structures

    const double FRICTION = 0.975;
    const double EDGE_BOUNCE = 0.3;
}