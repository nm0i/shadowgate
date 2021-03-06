//evil1.c

#include <std.h>

inherit ROOM;

void create(){
    ::create();
    set_name("Forest Path");
    set_short("A small path through the forest");
    set_property("indoors",0);
    set_property("light",1);
    set_terrain(HEAVY_FOREST);
    set_travel(FOOT_PATH);
    set_long(
@OLI
    %^BOLD%^%^GREEN%^A small twisting path through the forest%^RESET%^
As you enter the forest you notice a quiet all around you. Tall trees
loom over you almost basking in their grandure. Around you you
sense a horrible feeling of pain. Nature's work here seems to be
almost undone. You look closely at the trees and see withering and
pain.

OLI
    );
    set_items((["floor":"The ground is cluttered  with twigs and leaves.",
                "trees":"These grand creatures range from oak and hickory to Pine and spruce."
                ]));
    set_exits(([
                "northwest":"/d/tharis/forest/evil6",
                "south":"/d/tharis/forest/evil9",
                ]));
    set_smell("default","The lush fragrances of the forest seem to be missing.");
    set_listen("default","The silence of the forest is unnatural, as if all the insects and birds are hiding.");
set_property("no teleport",1);
}

void reset(){
    ::reset();

    if(!present("mage"))
        new("/d/tharis/monsters/ogre_mage")->move(TO);
    if(!present("tree"))
        new("/d/tharis/monsters/hangman_tree")->move(TO);
    }
