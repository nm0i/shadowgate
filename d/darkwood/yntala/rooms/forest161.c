//forest161
#include <std.h>;
#include "../yntala.h"
inherit IHRMS+"forest1.c";

void create(){
::create();
set_exits(([
"west":INRMS+"forest160",
"east":INRMS+"forest153"
]));
}