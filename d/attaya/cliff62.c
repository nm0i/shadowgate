#include <std.h>

inherit "/d/attaya/spec/ledge";

void create(){
	::create();
	set_name("Ledge on the Obsidian Staircase.");
    set_long(::query_long()+"You are just above the smokescreen that wafts up from the River of Flame. From here, you look out over the black clouds and see the beautiful ocean in the distance. At once, you long to be on the beach again. Far above you, are the walls to the Crystalline Tower of the Black Dawn. You cannot see the tower itself because the walls are too high, and you are a long way beneath them. The ledge disappears inside a small structure to the west.");
    set_exits(([
                   "west":"/d/attaya/cliff20",
                   "east":"/d/attaya/cliff63"
                   ]));
}

