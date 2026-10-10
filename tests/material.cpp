#include "misc/base.h"

#include "types/scene/material.h"


TEST_CASE("material smth smth im silly :3") {
    Material s = Material();

    CHECK(s.ambient == 0.1f);
    CHECK(s.diffuse == 0.9f);
    CHECK(s.specular == 0.9f);
    CHECK(s.shininess == 200.f);
}