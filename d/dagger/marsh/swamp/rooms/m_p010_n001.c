#include <std.h>
#include "../marsh.h"

inherit MINH;

void create()
{
    ::create();
    set_exits(([
"southeast": RPATH "m_p011_n002",
"east": RPATH "m_p011_n001",
"west": RPATH "m_p009_n001",

    ]));
}

