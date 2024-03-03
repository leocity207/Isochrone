#include "projector_test.h"

// STL
#include <numbers>

// Coordiante
#include "includes/coordinate/projector/equirectangular.h"
#include "includes/coordinate/projector/azimuthal_equidistant.h"

// UTils
#include "includes/utils/exception_def.h"

constexpr double err = 6.1346820258134738e-10;

/////////////////////
/// Testing equality
/// TODO render combine
TEST_P(Equirectangular_Test, test_coordinate)
{
	auto [coordinate, expected] = GetParam();

	if (expected.has_value())
	{
		Coordinate::Projector::Equirectangular projector(Coordinate::Spherical(0,0));
		Coordinate::Base<double> projected = projector.Project(coordinate);
		EXPECT_DOUBLE_EQ(projected.first, expected.value().first);
		EXPECT_DOUBLE_EQ(projected.second, expected.value().second);
	}
	else
	{
		Coordinate::Projector::Equirectangular projector(Coordinate::Spherical(0, 0));
		EXPECT_THROW({ Coordinate::Base<double> projected = projector.Project(coordinate); }, BAD_ANGULAR_VALUE_PROJECTION);
	}
}

TEST_P(Azimuthal_Equidistant_test, test_coordinate)
{
	auto [coordinate, expected] = GetParam();

	if (expected.has_value())
	{
		Coordinate::Projector::Azimuthal_Equidistant projector(Coordinate::Spherical(0, 0));
		Coordinate::Base<double> projected = projector.Project(coordinate);
		EXPECT_DOUBLE_EQ(projected.first, expected.value().first);
		EXPECT_DOUBLE_EQ(projected.second, expected.value().second);
	}
	else
	{

		Coordinate::Projector::Equirectangular projector(Coordinate::Spherical(0, 0));
		EXPECT_THROW({ Coordinate::Base<double> projected = projector.Project(coordinate); }, BAD_ANGULAR_VALUE_PROJECTION);
	}
}


std::string Param_Label(testing::TestParamInfo<std::tuple<Coordinate::Spherical, std::optional<Coordinate::Planar<double>> >> id)
{
	switch (id.index)
	{
	case 0: return "0_0";
	case 1: return "0_180";
	case 2: return "180_180";
	case 3: return "180_minus180";
	case 4: return "180_0";
	case 5: return "180_5";
	case 6: return "90_0";
	case 7: return "0_90";
	case 8: return "90_90";
	case 9: return "minus90_0";
	case 10: return "0_minus90";
	case 11: return "90_minus_90";
	case 12: return "1_3";
	default:
		throw "not a good index for labeling";
	}
}

constexpr double quater_earth = Coordinate::Spherical::earth_radius * std::numbers::pi/2;

INSTANTIATE_TEST_SUITE_P(
	Equirectangular,
	Equirectangular_Test,
	::testing::Values(
		std::make_tuple( Coordinate::Spherical(0   , 0)    , Coordinate::Planar<double>(0, 0)),
		std::make_tuple( Coordinate::Spherical(0   , 180)  , std::nullopt),
		std::make_tuple( Coordinate::Spherical(180 , 180)  , std::nullopt),
		std::make_tuple( Coordinate::Spherical(180 , -180) , std::nullopt),
		std::make_tuple( Coordinate::Spherical(180 , 0)    , std::nullopt),
		std::make_tuple( Coordinate::Spherical(-180, 5)    , std::nullopt),
		std::make_tuple( Coordinate::Spherical(90  , 0)    , Coordinate::Planar<double>(quater_earth, 0)),
		std::make_tuple( Coordinate::Spherical(0   , 90)   , Coordinate::Planar<double>(0, quater_earth)),
		std::make_tuple( Coordinate::Spherical(90  , 90)   , Coordinate::Planar<double>(quater_earth, quater_earth)),
		std::make_tuple( Coordinate::Spherical(-90 , 0)    , Coordinate::Planar<double>(-quater_earth, 0)),
		std::make_tuple( Coordinate::Spherical(0   , -90)  , Coordinate::Planar<double>(0, -quater_earth)),
		std::make_tuple( Coordinate::Spherical(90  , -90)  , Coordinate::Planar<double>(quater_earth, -quater_earth)),
		std::make_tuple( Coordinate::Spherical(1   , 3)    , Coordinate::Planar<double>(111318.84502145034, 333956.53506435099))
	),
	Param_Label
);


INSTANTIATE_TEST_SUITE_P(
	Azimuthal_Equidistant,
	Azimuthal_Equidistant_test,
	::testing::Values(
		std::make_tuple( Coordinate::Spherical(0   , 0)    , Coordinate::Planar<double>(0, 0)),
		std::make_tuple( Coordinate::Spherical(0   , 180)  , std::nullopt),
		std::make_tuple( Coordinate::Spherical(180 , 180)  , std::nullopt),
		std::make_tuple( Coordinate::Spherical(180 , -180) , std::nullopt),
		std::make_tuple( Coordinate::Spherical(180 , 0)    , std::nullopt),
		std::make_tuple( Coordinate::Spherical(-180, 5)    , std::nullopt),
		std::make_tuple( Coordinate::Spherical(90  , 0)    , Coordinate::Planar<double>(quater_earth, err)),
		std::make_tuple( Coordinate::Spherical(0   , 90)   , Coordinate::Planar<double>(0           ,  quater_earth)),
		std::make_tuple( Coordinate::Spherical(90  , 90)   , Coordinate::Planar<double>(err,  quater_earth)),
		std::make_tuple( Coordinate::Spherical(-90 , 0)    , Coordinate::Planar<double>(quater_earth, err)),
		std::make_tuple( Coordinate::Spherical(0   , -90)  , Coordinate::Planar<double>(0            , quater_earth)),
		std::make_tuple( Coordinate::Spherical(90  , -90)  , Coordinate::Planar<double>(-err, quater_earth)),
		std::make_tuple(Coordinate::Spherical(1, 3), Coordinate::Planar<double>(111217.09331570369, 333973.4780952094))
	),
	Param_Label
);