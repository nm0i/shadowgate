#include <std.h>
inherit "/d/deku/plains/plains03i";

void create() {
    ::create();
    set_exits(([
       "east" : "/d/deku/plains/plains04",
       "west" : "/d/deku/plains/plains06"
    ] ));
}
