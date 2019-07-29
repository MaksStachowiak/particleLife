#pragma once

const double BALL_RADIUS = 4;
const double BALL_DIAM   = 2 * BALL_RADIUS;

const int NUMBER_OF_SPECIES = 1;
const int STARTING_POPULATION = 1;

namespace Display
{
    constexpr uint16_t WIDTH  = 1280;
    constexpr uint16_t HEIGHT = 720;    
}

namespace Physics
{
    const double OVERLAP_REPULSION_MULTIPLIER = 1;

    const double INTERACTION_FORCE_MULTIPLIER = 0.8;
    const double MIN_RADIUS_MULTIPLIER = 3;
    const double MAX_RADIUS_MULTIPLIER = 6;
}