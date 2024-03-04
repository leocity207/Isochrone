#ifndef COORDINATE_PROJECTOR_TEST_H
#define COORDINATE_PROJECTOR_TEST_H

#include <gtest/gtest.h>

// STL
#include <optional>
#include <tuple>

// Coordinate
#include "includes/coordinate/sphere.h"
#include "includes/coordinate/planar.h"


class Equirectangular_Test : public ::testing::Test, public ::testing::WithParamInterface<std::tuple<Coordinate::Spherical,std::optional<Coordinate::Planar<double>>>>{

};

class Azimuthal_Equidistant_test : public ::testing::Test, public ::testing::WithParamInterface<std::tuple<Coordinate::Spherical, std::optional<Coordinate::Planar<double>>>> {

};


#endif //COORDINATE_PROJECTOR_TEST_H