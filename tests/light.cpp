#include "misc/base.h"

#include "types/scene/light.h"


TEST_CASE("point lights have position and intensity") {
    PointLight a = PointLight(Point(0,0,0), Colour(1,1,1));

    CHECK(a.position == Point(0,0,0));
    CHECK(a.intensity == Colour(1,1,1));
}