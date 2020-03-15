#define owner ("abolition")
#define FIRENOTES ({"You order the crew to attack the ship!!",\
"The crew loads the guns!",\
"The crew starts the fuse to the gun.....",\
"hsssss.",\
"hsssss.",\
"hsssss.",\
"%^FLASH%^WHITE%^BOLD%^BOOM!!!!!!",\
"The fire ball launches out of the gun!",\
"The fire ball goes flying through the air!",\
"You hear a loud %^BOLD%^RED%^FLASH%^BOOM!%^RESET%^BOLD%^CYAN%^, as the fire ball hits the ship!",\
"Pieces of the ship go flying everywhere!",\
})
#include <std.h>
inherit MONSTER;
object shiproom;
object timefuse;
void create() {
    ::create();
       set_name("+owner+'s ship");
set_id( ({ "+owner+'s ship", "psfvo" } ));
set_short(owner->query_cap_name()+"'s ship");
        set("long","This is a large sailboat");
set_race("sailboat");
set_gender("male");
set_class("boat");
set_hp(100);
shiproom=find_object_or_load("/d/mine2/virtualocean/boats/"+owner+"room.c");
        call_out("start_sink",1);
}
init() {
  ::init();
  add_action("attack","attack");
add_action("mon_look","mon_look");
}
int attack(string str) {
  if(!str) {
    write("Attack what?");
return 1;
}
 if(present("+owner+fuse")){
write("You are allready attacking!");
return 1;
}
 if(!present(str)){
       write("That ship isn't in the area!");
return 1;
}
  if(present(str)){
      write("%^BOLD%^YELLOW%^"+FIRENOTES[0]);
find_living(str)->add_hp(-10);
timefuse = new("/d/mine2/virtualocean/obj/fuse.c")->move(this_object());
timefuse->set_id( ({ "+owner+fuse" }));
        call_out("limbo",1,TP, 1);
        call_out("end_fuse", 10);
        }
}
void limbo(object ob, int flag){
        if(flag < sizeof(FIRENOTES)){
                   tell_object(ob,"%^BOLD%^CYAN%^"+FIRENOTES[flag]+"\n\n");
                flag++;
                call_out("limbo",2,ob,flag);
        }
}
void end_fuse(){
destruct(present("+owner+fuse"));
}
 
void catch_tell(string str)
{
tell_room(shiproom,str);
return;
}
void start_sink(){
if(TO->query_hp() > 20){
        call_out("start_sink",5);
return 1;
}
write("BOLD%^RED%^Your ship has been hurt to much!\n The ship is starting to sink!\n You find yourself drounding in the water!");
this_player("/d/mine2/virtualocean/boats/"+owner+"room")->move_environment("/d/mine2/virtualocean/rooms/sinking");
return 1;
} 

int mon_look()
{
  string tmp;
  object env;
object monster;
monster=this_object();
  env = environment(monster);
  message("room_description", (string)env->query_long(0), monster);
  message("room_exits", (string)env->query_long_exits(), monster);
  if( ( tmp = (string)env->describe_living_contents( ({ monster }) ) ) !=
"" )
    message("living_item", tmp, monster);
  if( ( tmp = (string)env->describe_item_contents( ({ }) ) ) != "" )
    message("inanimate_item", tmp, monster);
}
