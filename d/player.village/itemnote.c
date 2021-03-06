#include "pvillage.h"
inherit OBJECT;

int nummer;
string filer;
int current_page;

void create(){
    ::create();
    set_name("note");
    set_id( ({ "note","itemnote" }) );
    set_short("A note");
    set_long(
	"\nYou look at the note, the header reads:\n"
	"\n        Item Wizard Instructions!\n"
	"Maybe you should read it."
    );
    set_weight(0);

}

init() {
    add_action("read_note","read");
}

int read_note(string str)
{
	if ((!str) || (str != "note")) return notify_fail("Read what??\n");
	write("%^BOLD%^%^GREEN%^Greetings!");
	write("%^BOLD%^%^BLUE%^----------");
	write("%^BOLD%^%^GREEN%^Since our toymaker is an old wizard, he only understands certain");
	write("%^BOLD%^%^GREEN%^key phrases.\n");
	write("%^BOLD%^%^CYAN%^You can use the following commands that our toymaker understands:");
	write("%^BOLD%^%^BLUE%^-----------------------------------------------------------------------");
	write("%^RESET%^%^YELLOW%^make <itemname>  %^CYAN%^Will add a new item to the room, if possible.");
	write("%^RESET%^%^YELLOW%^remove <itemname>  %^CYAN%^Will remove an item in the room.");
	write("%^YELLOW%^done  %^CYAN%^This is when you are finished with the Toymaker.");
	write("%^BOLD%^%^BLUE%^-----------------------------------------------------------------------");
	return 1;
}

get(str) {
    ::get();
	if( str == "note") return 1;
	return 0;
}

drop() {
	say("A note blows away in the wind...");
	write("A note blows away in the wind...");
	destruct(this_object()); 
	return 1;
}




