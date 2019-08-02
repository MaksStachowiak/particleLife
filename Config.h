#pragma once

const double BALL_RADIUS = 5;
const double BALL_DIAM   = 2 * BALL_RADIUS;

const int NUMBER_OF_SPECIES = 5;
const int STARTING_POPULATION = 100;

namespace Display
{
    constexpr uint16_t WIDTH  = 1280;
    constexpr uint16_t HEIGHT = 720;    
}

namespace Physics
{
    const double OVERLAP_REPULSION_MULTIPLIER = 10;

    const double INTERACTION_FORCE_MULTIPLIER = 0.8;
 
    const double MIN_RADIUS_MULTIPLIER = 0; // 1 = one extra diameter of separation
    const double MAX_RADIUS_MULTIPLIER = 1;

    const double FRICTION = 0.99;
    const double EDGE_BOUNCE = 0.1;
}