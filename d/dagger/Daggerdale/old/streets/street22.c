#include <std.h>
inherit ROOM;

void create(){
  ::create();
   set_terrain(CITY);
   set_travel(PAVED_ROAD);
set_property("light", 2);
  set_short("A Street in Daggerdale.");
  set("day long",
@GIL
%^ORANGE%^You are at the Eastern end of the Market Square.
The street runs North, South and East from here.
The city Fountain lies to the West of here.
A metal pole holds an unlit lantern aloft here.
Many carts line the square here.
A metal grate is in the middle of the street here.
GIL
);
  set("night long",
@GIL
%^YELLOW%^You are at the Eastern end of the Market Square.
The street runs North, South and East from here.
The city Fountain lies to the West of here.
A metal pole here holds a lit lantern aloft and brightens the night.
Many locked carts line the square here.
A metal grate is in the middle of the street here.
GIL
);
set_smell("default", "You catch the scent of food cooking on the breeze.");
set_listen("default", "You can hear the sounds of a Bard singing.");
  set_items(([
"pole" : "It's made of steel and holds a lantern to light the darkness",
"street" : "It's made of clean polished cobblestones.",
"lantern" : "It's a large oil lantern with crystal glass windows.",
"carts" : "These carts carry and sell many things not available in the shops.",
"square" : "This is the central square of Daggerdale, many people sell their wares here.",
"grate" : "It's a metal sewer grate, the rainwater goes down here and you can be sure that nasty, filthy, things live down there.",
]));

  set_exits(([
"north" : "/d/dagger/Daggerdale/streets/street29",
"south" : "/d/dagger/Daggerdale/streets/street16",
"west" : "/d/dagger/Daggerdale/fountain/fountain",
"east" : "/d/dagger/Daggerdale/streets/street23",
     ]));
}
void reset(){
   ::reset();
if(!present("lantern pole")){
new("/d/dagger/Daggerdale/streets/items/objs/lantern_pole.c")->move(TO);
}
   if(query_night() != 1 && !present("kedathia")) {
      new("/d/dagger/Daggerdale/shops/npcs/kedathia")->move(TO);
   }
}
