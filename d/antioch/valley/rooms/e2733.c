#include <std.h>
#include "../valley.h"
inherit EDGE2;

void create()
{
	::create();
	set_exits( ([
	"west" : ROOMS+"e2732",
	"south" : ROOMS+"e2633",
	]) );
	set_listen("default",
	"The raging of a river can be heard from nearby.",
	);
	set_invis_exits(({"south","west"}));
	set_pre_exit_functions(({"west"}),({"GoThroughDoor"}));
}

int GoThroughDoor()
{
	int i;
	object *global_array;
	global_array = TP->query_followers();

	if(TP->is_class("ranger") || TP->is_class("druid")) {
//adding druids since it seems logical ~Circe~ 4/7/13
		tell_object(this_player(),
		"%^GREEN%^You skillfully navigate your way"+
		" through the woods."
		);
		tell_room(environment(this_player()),
		"%^GREEN%^"+TP->query_cap_name()+" navigates"+
		" easily through the woods.",({TP})
		);
		return 1;
	} 

	if(!global_array) global_array = ({});

	if(member_array(TP,global_array) != -1) {
		global_array -= ({TP});
		return 1;
	}

	else {
		tell_object(this_player(),
		"You wonder lost through the woods."
		);
		tell_room(environment(this_player()), 
		""+TP->query_cap_name()+" wonders lost through"+
		" the woods.",({TP})
		);

	i = random(3);
	switch(i) {
		case 0:
			TP->move_player(ROOMS+"e2830");
			break;
		case 1:
			TP->move_player(ROOMS+"e2028");
			break;
		case 2:
			TP->move_player(ROOMS+"e2332");
			break;
		}

	}
}

void reset()
{
	::reset();
	if(!present("creeper")) {
		if(!random(3)) {
			new(MONS+"creeper")->move(TO);
			return 1;
		}
	}
}
