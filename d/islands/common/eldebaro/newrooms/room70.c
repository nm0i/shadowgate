#include <std.h>
#include "../area_stuff.h"

inherit ELINH;

void create()
{
    ::create();
    set_exits(([
        
        //"north" : ELROOMSD+"79",
        "east" : ELROOMSD+"71",
        //"south" : ELROOMSD+"47",
        "west" : ELROOMSD+"69",
        
    ]));
}
