#include <std.h>
#include "/d/islands/dinosaur/lake/lake.h"

inherit LAKETOP;

void create(){
    ::create();
    set_light(1);
    set_short("Under the lake.");
    set_long(
      "You are under the water from the lake.  You can easily see your way to the top of the lake from here in the light.  In the gloom of the dirty water, you can see little else."
    );
    set_smell("default", "Don't sniff too deep, you don't want water in your nose!");
    set_listen("default", "You hear the water in your ears.");
    set_items( ([
      "light" : "The light upwards is probably the sky.",
    ]) );
    set_exits( ([
      "west" : "/d/islands/dinosaur/lake/rooms/deep4d.c",
      "east" : "/d/islands/dinosaur/lake/rooms/deep6d.c",
      "south" : "/d/islands/dinosaur/lake/rooms/deep2d.c",
      "north" : "/d/islands/dinosaur/lake/rooms/deep8d.c",
      "up" : "/d/islands/dinosaur/lake/rooms/deep5u.c",
    ]) );
}
