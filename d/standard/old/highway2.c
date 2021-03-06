#include <std.h>

inherit ROOM;

void create() {
    ::create();
    set_property("light", 3);
    set_property("no castle", 1);
    set("short", "The Great Western Highway");
    set("long",
	"You are on the Great Western Highway linking the western "
	"lands beyond the mountains to the populated lands of the "
	"valley.  Beyond the Daroq Mountains is the Qajip Desert where "
	"too many adventurers lose their way.");
    set_items(
	(["highway" : "A well-traveled dirt road between the "
	    "mountains in the west and the populated towns of the east.",
	  "lands" : "You are in a forested valley with the Daroq "
	    "Mountains in the west.",
	  "mountains" : "The Daroq Mountains, home of vile goblins.",
	  "mountain" : "Trendahl Mountain.",
	  "daroq mountains" : "Evil goblins live in the "
	    "tunnels that thread the mountains."]) );
    set_exits( 
	      (["west" : "/d/standard/highway3",
                "east" : "/d/standard/highway1"]) );
}

void reset() {
  ::reset();
    if(!present("bag")) 
      new("/d/standard/obj/misc/bag")->move(this_object());
}

