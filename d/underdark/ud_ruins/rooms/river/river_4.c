#include "../../ud_ruins.h"
inherit STORAGE"_river_base";

void create() {
    ::create();
    set_exits(([
        "north" : ROOMS"river/river_8",
        "south" : ROOMS"river/river_2",
        "east" :ROOMS"river/river_3",
        ]));
}
