#include <std.h>
#include <daemons.h>
inherit WEAPONLESS;

create() {
  	::create();
  	set_name("rat");
  	set_id( ({ "rat", "monster", "vermin", "mouse" }) );
  	set_short("A medium sized rat");
  	set("aggressive", 0);
  	set_level(2);
  	set_hd(2,0);
  	set_long("This is a tiny rat, scurrying around eating corn.\n");
  	set_body_type("quadruped");
  	set_alignment(6);
  	set_race("rat");
  	set_exp(100);
}
