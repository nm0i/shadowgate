#include <std.h>
#include "/d/deku/inherits/forest.h"
inherit FTRAIL;

void create() {
    ::create();

    set_exits(([
       "west" : F_ROOMS"5-5",
       "east" : F_ROOMS"3-5",
       "north" : F_ROOMS"4-6",
       "south" : F_ROOMS"4-4",
       "southeast" : F_ROOMS"3-4",
       "southwest" : F_ROOMS"5-4",
       "northeast" : F_ROOMS"3-6",
       "northwest" : F_ROOMS"5-6",
    ] ));
}
