#include "/d/hm_quest/maze.h"

inherit "/d/hm_quest/maze";

create()
{
  ::create();
  new_disc(4);
  set_exits( ([
                "north" : MAZEDIR+"4/c/I,I",
                "south" : MAZEDIR+"4/c/I,III"
           ]) );
}
