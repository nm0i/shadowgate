#include <std.h>
#include "../antioch.h"
inherit ROOM;

void create()
{
	::create();
   set_terrain(CITY);
   set_travel(PAVED_ROAD);
	set_property("indoors",0);
	set_property("light",2);
	set_short("Crescent Street");
	set_long(
	"%^YELLOW%^This part of the city lies in ruins, covered in a black haze.%^RESET%^"
	);
	set_smell("default","It smells of death and decay.");
	set_listen("default","The city is dead.");
	set_items(([
	({"street","cobblestones","cobbles","road","path"}) : "The"+
	" street is paved with cobblestones.",
	"street sign" : "This is Crescent street.",
	"church" : "The church is to your west, you can see the"+
	" entrance straight north of here. It is a few stories in"+
	" height and appears to be newly built.",
	]));
	set_exits(([
	"north" : ROOMS+"street14",
	"southwest" : ROOMS+"street16",
	]));
}
