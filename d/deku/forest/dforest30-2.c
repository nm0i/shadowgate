#include <std.h>
#include "/d/deku/inherits/forest.h"
inherit FTRAIL;

void create() {
    ::create();
    set_long(TO->query_long()+"  %^BOLD%^%^BLACK%^The bank of a "+
    "large %^BLUE%^lake%^BOLD%^%^BLACK%^ is visible to the north "+
    "of here.%^RESET%^");
    add_items(({"lake","large lake","shadowlord lake"}),"%^BLUE%^"+
    "Only the bank of this large lake is visible from here and "+
    "what you can make out of its surface paints it a "+
    "blue-green.%^RESET%^");

    set_exits(([
       "west" : F_ROOMS"31-2",
       "east" : F_ROOMS"29-2",
       "north" : F_ROOMS"30-3",
       "south" : F_ROOMS"30-1",
       "southeast" : F_ROOMS"29-1",
       "southwest" : F_ROOMS"31-1",
       "northeast" : F_ROOMS"29-3",
       "northwest" : F_ROOMS"31-3",
    ] ));
}
