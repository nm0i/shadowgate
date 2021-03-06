// West Street, Azha, along the West Wall
// Thorn@ShadowGate
// 4/8/95
// Town of Azha
// modified to allow access to the new stable. Nienne, 10/04 //

#include <std.h>
#include "/d/azha/azha.h"
#include "/d/tsarven/include/southern.h"

inherit ROOM;

void create() {
  room::create();
   set_terrain(CITY);
   set_travel(PAVED_ROAD);
	set_light(2);
	set_indoors(0);  
	set_short("West Street, Azha");
  set_long(
@AZHA
%^BOLD%^West Street%^RESET%^
	West Road runs along the western wall of the Town of Azha.  
Looking up at the walls, you can see the guards patrolling some of
the towers rising above the palisade.  Some wooden houses have been 
built directly abutting the walls of the town, even overhanging.  In
the case of a seige, the occupants of that house can easily flee 
the city, or get food from the outside even when the gates are closed.
To the east of you is a sturdy-looking crenellated stone wall which 
seems to be guarding something on the inside of the town.  
	West Street continues to the north and south.
AZHA
    );
	set_exits(([
	"north" : "/d/azha/town/west3",
"south" : "/d/azha/town/south1",
"west" : "/d/azha/town/stable"
  ] ));     
	set_smell("default","You wrinkle your nose at the scent of refuse being dumped from above.");
	set_items(([
/*		"tower" : "Ya know, if you had some climbing tools or were a thief, you could climb into that tower.", */
		"wall" : "The wall appears to be sturdy and very smooth, no way in that way.\n",
	] ));
}

reset() {
        ::reset();
        AOVER->setup_monsters(TO, "street");
}
