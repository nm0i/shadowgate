#include <std.h>
#include <objects.h>

inherit ROOM;

void create() {
    room::create();
    set_property("light",2);
    set_property("indoors",0);
    set_short("Town of Sanctuary");
    set_long("%^CYAN%^%^BOLD%^
This is a side street through the town of %^GREEN%^Sanctuary%^CYAN%^.  Buildings
line the street.  This place, buildings and all, looks as though something
terrible has ravaged the land.  The street is bare except for the few
strange people walking around.  To the east a sign reads %^RED%^Alchemist
%^CYAN%^and the street continues to the south.
    ");
    set_exits(([
        "south" : "/d/dragon/town/roadSW2",
        "north" : "/d/dragon/town/roadW4",
       "east" : "/d/dragon/town/magic"
    ] ));
    set_items(([
    ] ));
}
