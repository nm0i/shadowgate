#include <std.h>
#include "/d/deku/inherits/forest.h"
inherit FTRAIL;

void create() {
    ::create();

    set_exits(([
       "west" : F_ROOMS"5-9",
       "east" : F_ROOMS"3-9",
       "north" : F_ROOMS"4-10",
       "south" : F_ROOMS"4-8",
       "southeast" : F_ROOMS"3-8",
       "southwest" : F_ROOMS"5-8",
       "northeast" : F_ROOMS"3-10",
       "northwest" : F_ROOMS"5-10",
    ] ));
}
