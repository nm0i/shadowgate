//forest160.c

#include <std.h>
#include "./forest.h"

inherit BFOREST;

void create(){
    ::create();
    set_exits(([
                "northwest":TFOREST"forest161",
                "south":TFOREST"forest135"
                ]));
    find_object_or_load(TFOREST"forest166");
}

