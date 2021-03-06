//wstreet1.c

#include <std.h>
#include "../tharis.h";

inherit CROOM;

void create(){
    set_monsters(({"/d/tharis/monsters/citizen", "/d/tharis/monsters/thief", "/d/tharis/monsters/patrol"}),({ random(5), random(4), random(3) }));
    ::create();
    set_terrain(CITY);
    set_travel(PAVED_ROAD);
	
	set_property("light",2);
	set_property("indoors",0);
	
	set("short","The street on the West of Tharis");
	set("long",
@OLI
	%^BOLD%^%^YELLOW%^West street through Tharis%^RESET%^
This is the west street through Tharis. To the west will eventually
be the West gate. To the east is the market place. Through this part 
of the city, you find yourself leaving the comercial and entering a
middle class residential area. You are not really worried about pick pockets
here but you are worried a little about muggers. 
	To the south you see the side of the merchants guild and to the north
there is an entrance to the patrol headquarters.
OLI
	);
	set_exits(([
		"east":ROOMS"market3",
		"west":ROOMS"wstreet2",
		"north":ROOMS"jewelry",
      "southeast":ROOMS"market5",
      "northeast":ROOMS"market1",
		]));
	set_items(([]));
	set_smell("default","The unique smells of the city attack you.");
	set_listen("default","The city bustles around you.");
}

/* changed to using CROOM since they wander
void reset(){
	int i,j;
	::reset();
	
	if(!present("patrol")){
		j = random(4);
		for(i=0;i<j;i++)
			new("/d/tharis/monsters/patrol")->move(TO);
	}
	
	if(!present("citizen")){
		j = random(5);
		for(i=0;i<j;i++)
			new("/d/tharis/monsters/citizen")->move(TO);
	}
	
	if(!present("thief")){
		j = random(6) -3;
		for(i=0;i<j;i++)
			new("/d/tharis/monsters/thief")->move(TO);
	}
}
*/

/*
//This query weather is for a plot.  Remove when no longer needed.
//~Circe~ 7/15/08
query_weather() { return "%^BOLD%^%^BLACK%^Stormclouds %^CYAN%^roll in the %^BLUE%^sky%^CYAN%^, shedding a steady downpour of %^BLUE%^rain%^CYAN%^.%^RESET%^"; }
*/