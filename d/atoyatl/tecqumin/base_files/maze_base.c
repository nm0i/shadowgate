#include <std.h>
#include <move.h>
#include <daemons.h>
#include "../tecqumin.h" 

inherit J_ROOM;


void remove_maze();
mapping query_base_exits();
string r_path, n_room, s_room, e_room, w_room, * spec_rooms;  
mapping base_exits;
int map_size, last_updated, last_verified, last_described, last_initiated;


void set_basic_exits();

void create() {
  mapping map;
  ::create();
  map_size = 25;
  set_short( (: TO, "short_desc" :) );
  set_long( (:TO, "long_desc":) );
  base_exits = ([]);
  spec_rooms = ({});
  set_pre_exit_functions(({"north", "northeast", "east", "southeast", "south", "southwest", "west", "northwest"}), ({"GoNorth", "GoNortheast",
"GoEast", "GoSoutheast", "GoEast", "GoSouth", "GoSouthwest", "GoWest", "GoNorthwest"}));
  set_exits( ([]) );
  n_room = "none";
  s_room = "none";
  e_room = "none";
  w_room = "none";
  set_property("no scry",1);
  last_updated = 0;
  last_verified = 0;
  last_described = 0;
  last_initiated = 0;
}

void add_base_exit(string direction, string destination){
  base_exits[direction] = destination;
}

void set_basic_exits(){
  int i, num;
  string * directions, * destinations;
  num = sizeof(base_exits);
  if (num<1){return;}
  directions = keys(base_exits);
  destinations = values (base_exits);
  for (i=0;i<num;i++){
    add_exit(destinations[i], directions[i]);
  }
}

mapping query_base_exits(){
  return base_exits;
}

string query_n_room(){
  return n_room;
}

string query_e_room(){
  return e_room;
}
string query_s_room(){
  return s_room;
}
string query_w_room(){
  return w_room;
}

string query_r_path(){
  return r_path;
}

string get_name(){
  string file_name, path, room_name;
  file_name = base_name(TO);
  path = get_path();
  room_name = file_name[strlen(path)..strlen(file_name)-1];
  return room_name;
}

varargs void update_exits(int repeat){
  int i, num, maze_time, boot_time;
  string * exits, file_name, room_name, path;
  object maze_room;
  mapping m;
//  report("%^BOLD%^%^RED%^Starting update_exits");
  if (time()<last_updated+3)
  {
//    report("%^BOLD%^%^GREEN%^Time: " + time() + " last_updated: " + last_updated);
    return;
  }
//  report("%^BOLD%^%^RED%^Finishing update_exits");
  if (MAZE_D->count_saved_mazes()<1)
  {
    path = get_path();
//    report("%^BOLD%^%^RED%^No mazes exist. Making a new maze");
    if (catch(maze_room = find_object_or_load(path + "j_maze0") ))
    {
//      report ("%^BOLD%^%^BLUE%^ERROR Loading maze room");
    }
    if (!objectp(maze_room)){ //feh
//      report ("%^BOLD%^%^YELLOW%^ERROR - Unable to load maze room");
      last_updated += time();
      return;
    }
//    report("%^B_WHITE%^%^BOLD%^%^BLACK%^initiating maze room from update_exits. Maze_room: " + maze_room->get_name());
    initiate_maze_room(maze_room, path, repeat);
  }
  file_name = base_name(TO);
  path = get_path();
  room_name = file_name[strlen(path)..strlen(file_name)-1];
//  report ("Getting exits for path: " + path + "   room name: " + room_name);
  m = MAZE_D->query_room_exits(path,room_name );
//  report ("Exits found: " + sizeof(m));
  if (mapp(m) && sizeof (m)>0){
    exits = keys (m);
    num = sizeof(m);
    if (num>0){
      for (i=0;i<num;i++){
//        report("Adding exit " + exits[i] + " leading to " + m[exits[i]]);
        add_exit(path + m[exits[i]], exits[i]); 
      }
    }    
  }
  maze_time = MAZE_D->query_timing(path);
  boot_time = time() - uptime();
  if (maze_time>boot_time  && (!mapp(m) || sizeof(m)<1)){
//    report ("Maze up to date. No exits. Ejecting");
    last_updated += time();
    call_out("eject", 6);
    return;
  } 
  if (intp(repeat) && repeat == 1){
    last_updated += time();
    return;
  }
  if (maze_time>boot_time ){
//    report ("Maze up to date");
    last_updated += time();
    return;
  } else {
//    report("%^BOLD%^%^RED%^Maze out of date - remaking");
    if (file_name(TO) == path + "j_maze0")
    {
      maze_room = TO;
    } else
    {
      if (catch(maze_room = find_object_or_load(path + "j_maze0")) )
      {
//        report("%^BOLD%^%^YELLOW%^Error loading maze room: " + path + "j_maze0");
      }
    }
    if (!objectp(maze_room)){
//      report ("%^BOLD%^%^YELLOW%^ERROR - Unable to load maze room");
      last_updated += time();
      return;
    }
  }
  last_updated += time();
  if (last_initiated< time() -5)
  {
//    report("%^B_ORANGE%^Initiating maze room. Last initiated: " + last_initiated + " time: " + time());
//    report("%^B_WHITE%^%^BOLD%^%^BLACK%^initiating maze room from update_exits (2). Maze_room: " + maze_room->get_name());
    initiate_maze_room(maze_room, path, repeat);
    last_initiated = time();
  }
}



void initiate_maze_room(object maze_room, string path, int repeat){
  int i;
//  if (maze_room ==TO)
//  {
//    for (i=0;i<10;i++) report("%^B_RED%^%^BOLD%^%^CYAN%^Not initiating maze room because this IS the maze room");
//    return;
//  }
//  report("%^BOLD%^%^YELLLOW%^Initiating maze room: " + maze_room->query_name());
  n_room = maze_room->query_n_room();
  s_room = maze_room->query_s_room();
  e_room = maze_room->query_e_room();
  w_room = maze_room->query_w_room();
//  report(maze_room->get_name() + "%^B_CYAN%^n_room: " + n_room + " s_room: " + s_room + " e_room: " + e_room + " w_room: " + w_room ); 
  spec_rooms = maze_room->query_spec_rooms();
  MAZE_D->clear_maze(path);
  MAZE_D->build_maze(path, "j_maze", 35, 68);
//moved from further down
  maze_room->check_maze(); // This will put in any river rooms
  if (stringp(n_room) && n_room != "none"){
//    report ("%^BOLD%^%^GREEN%^Setting north room");
     MAZE_D->place_north_exit(path, n_room);
  } // else report("%^B_CYAN%^No North room to place");
  if (stringp(s_room) && s_room != "none"){
//    report ("%^BOLD%^%^GREEN%^Setting south room");
    MAZE_D->place_south_exit(path, s_room);
  } // else report("%^B_CYAN%^No South room to place");
  if (stringp(e_room) && e_room != "none"){
//    report ("%^BOLD%^%^GREEN%^Setting east room");
    MAZE_D->place_east_exit(path, e_room);    
  } // else report("%^B_CYAN%^No East room to place");
  if (stringp(w_room) && w_room != "none"){
//    report ("%^BOLD%^%^GREEN%^Setting west room");
    MAZE_D->place_west_exit(path, w_room);
  } // else report("%^B_CYAN%^No North room to place");
//  report ("%^BOLD%^%^MAGENTA%^CHECKING FOR SPECIAL ROOMS");
  if (sizeof(spec_rooms)>0){
//    report("Special rooms found - \n%^BOLD%^%^CYAN%^Placing special rooms");
    for (i=0;i<sizeof(spec_rooms);i++){
      if (strlen(spec_rooms[i])> strlen(path)){
        spec_rooms[i] = spec_rooms[i][strlen(path)-1..strlen(spec_rooms[i])-1];
      }
      MAZE_D->add_special_room(path, spec_rooms[i]);
    }
  }
//  if (!intp(repeat) || repeat != 1){
//    report ("%^BOLD%^%^MAGENTA%^REPEATING UPDATE EXITS");
 //moved from here?
//    update_exits(1);
//  }
}

string * query_exits(){ //overriding this so that maze exits are picked up
//  report("%^BOLD%^%^CYAN%^Query_exits: last_updated: " + last_updated + " time: " + time());
  set_basic_exits();
  update_exits();
//  report("Calling :: query_exits() from query_exits");
  return ::query_exits();
}

void eject(){
  object * critters, room;
  int i, num;
//  report("Calling :: query_exits() from eject");
  if (sizeof(::query_exits())- sizeof(base_exits) >0) return;
  update_exits();
  if (sizeof(::query_exits())- sizeof(base_exits) >0) return;
  critters = all_living(TO);
  num = sizeof(critters);
  if (num<1){return;}
  room = find_object_or_load(WEMIC + "path14");
  for (i=0;i<1;i++){
//    if ((int)critters[i]->is_player()!=1) {
//      TP->move(find_object_or_load("/d/shadowgate/void"));
//      continue;
//    }
    tell_object(critters[i], "The jungle shifts around you"
     +" as the ancient spirits of the %^CYAN%^Tecqumin"
     +" %^RESET%^eject you from the jungle that holds"
     +" their lost city");
    critters[i]->move(room);
    critters[i]->force_me("look");
  }
}

string * query_spec_rooms(){
  return spec_rooms;
}

int GoNorth(){
  object targroom;
  string targ_roomname;
  targ_roomname = query_exit("north");
  if (targ_roomname == "/d/shadowgate/void"){
    return 0;
  }
  targroom = find_object_or_load(targ_roomname);
  if (objectp(targroom)){
//    report ("running on_enter function for " + targ_roomname);
    targroom->on_enter();
  } else {
//    report ("failed to load target room");
  }
  return 1;
}

int GoNortheast(){
  object targroom;
  string targ_roomname;
  targ_roomname = query_exit("northeast");
  if (targ_roomname == "/d/shadowgate/void"){
    return 0;
  }
  targroom = find_object_or_load(targ_roomname);
  targroom->on_enter();
  return 1;
}

int GoEast(){
  object targroom;
  string targ_roomname;
  targ_roomname = query_exit("east");
  if (targ_roomname == "/d/shadowgate/void"){
    return 0;
  }
  targroom = find_object_or_load(targ_roomname);
  targroom->on_enter();
  return 1;
}

int GoSoutheast(){
  object targroom;
  string targ_roomname;
  targ_roomname = query_exit("southeast");
  if (targ_roomname == "/d/shadowgate/void"){
    return 0;
  }
  targroom = find_object_or_load(targ_roomname);
  targroom->on_enter();
  return 1;
}

int GoSouth(){
  object targroom;
  string targ_roomname;
  targ_roomname = query_exit("south");
  if (targ_roomname == "/d/shadowgate/void"){
    return 0;
  }
  targroom = find_object_or_load(targ_roomname);
  targroom->on_enter();
  return 1;
}

int GoSouthwest(){
  object targroom;
  string targ_roomname;
  targ_roomname = query_exit("southwest");
  if (targ_roomname == "/d/shadowgate/void"){
    return 0;
  }
  targroom = find_object_or_load(targ_roomname);
  targroom->on_enter();
  return 1;
}

int GoWest(){
  object targroom;
  string targ_roomname;
  targ_roomname = ("west");
  if (targ_roomname == "/d/shadowgate/void"){
    return 0;
  }
  targroom = find_object_or_load(targ_roomname);
  targroom->on_enter();
  return 1;
}

int GoNorthwest(){
  object targroom;
  string targ_roomname;
  targ_roomname = query_exit("northwest");
  if (targ_roomname == "/d/shadowgate/void"){
    return 0;
  }
  targroom = find_object_or_load(targ_roomname);
  targroom->on_enter();
  return 1;
}

void on_enter(){
  check_maze();
  update_exits();
//  tell_room(TO, "Someone entered");
  tell_object(find_player("lujke"), "Psst...Someone entered");
  return;
}

void report(string str){
//  "/daemon/reporter_d"->report("lujke", "File name: " + file_name(TO) + str); 
}

void make_maze(){
  object mazeroom;
  string rname;
  int i, j, flag;
  flag = 1;
//  report( "Attempting to make maze");
  if (!stringp(r_path)){ return; }
  MAZE_D->build_maze(r_path, "j_maze", 30, 100);
  if (stringp (s_room)  && s_room != "none"){
//    report("Attempting to set southroom as " + s_room);
    MAZE_D->place_south_exit(get_path(), s_room);
  }
  if (stringp (n_room) && n_room != "none"){
//    report( "Attempting to set northroom as " + n_room);
    MAZE_D->place_north_exit(get_path(), n_room);
  } // else report("%^B_CYAN%^No North room to place");
  if (stringp (e_room) && e_room != "none"){
    report( "Attempting to set eastroom as " + e_room);
    MAZE_D->place_east_exit(get_path(), e_room);
  } else report("%^B_CYAN%^No East room to place");
  if (stringp (w_room) && w_room != "none"){
    report("Attempting to set westroom as " + w_room);
    MAZE_D->place_west_exit(get_path(), w_room);
  } else report("%^B_CYAN%^No West room to place");
  if (stringp (s_room) && s_room != "none"){
    report("Attempting to set southroom as " + s_room);
    MAZE_D->place_south_exit(get_path(), s_room);
  } else report("%^B_CYAN%^No South room to place");
//  call_out("place_special_rooms", 10);
  report( "%^BOLD%^%^YELLOW%^Yay! we have success!");
  report("Calling :: query_exits() from make_maze");
  if (sizeof(base_exits)>=sizeof(::query_exits())){
//     make_maze();
  }
}

void place_special_rooms(){
  int j;
  if (sizeof(spec_rooms)>0){
    report( "%^BOLD%^%^MAGENTA%^Adding special rooms:");
    for (j=0;j<sizeof(spec_rooms);j++){
      report( "Adding special room. Path: " + r_path + "Room: " + spec_rooms[j]);
//      MAZE_D->add_special_room(r_path, spec_rooms[j] );
      MAZE_D->add_special_room(spec_rooms[j] );
    }
    MAZE_D->place_special_rooms();  
  } else 
  {
    report( "No special rooms to add");
  }

}

void remove_maze(){
/*
  if (stringp(r_path)){
    MAZE_D->clear_maze(r_path);
    return;
  }
*/
  MAZE_D->clear_maze(get_path());
}


string get_path(){
  string f_name, junk, result;
  object mazeroom;
  f_name = file_name(TO);
  if (stringp(r_path)){
    result = r_path;
  } else {
    result = "";
    while (interact("/", f_name)){
      sscanf(f_name, "%s/%s", junk, f_name);
      if (!interact("/", junk)){
        result += "/";
      }
      result += junk;
    }
    result = result[1..strlen(result)-1];
    result += "/";
  }
  return result;
}

varargs int check_maze(string p){
  object maze_room;
  string filename;
  filename = get_path() + "j_maze0";
  if (filename == "0j_maze0")
  {
    return;
  }
  if (file_exists(filename)) maze_room = find_object_or_load(filename);
  if (objectp(maze_room) && maze_room !=TO ){
    maze_room->verify_maze(p);
  }
}


varargs int verify_maze(string p){
  string result, temp;
  object mazeroom;
  int last_maze;
  if (time()<last_verified +3) return;
  report ("Verifying maze for path: " + get_path());
  if (stringp(p)){
    result = p;
  } else {
    result = get_path();
  }
//  tell_room(TO, "directory: " + result);
  last_maze = MAZE_D->query_timing(result);
  if (time()-uptime()>last_maze){
    report( "maze needs to be remade");
    report( "Time : " + time() + " Uptime: " + uptime() + " Last maze: " + last_maze);
    report ("%^BOLD%^%^MAGENTA%^Result: " + result);
    if (catch (mazeroom = find_object_or_load(result + "j_maze0")))
    {
      report ("%^BOLD%^%^RED%^ERROR Loading mazeroom: " + result + "j_maze0");
    } else 
    {
      report ("%^BOLD%^%^RED%^mazeroom loaded okay");
      mazeroom = find_object_or_load(result + "j_maze0");
      if (!objectp(mazeroom)) report("%^BOLD%^%^MAGENTA%^Mazeroom not a valid object");
    }
    if(objectp(mazeroom && mazeroom!=TO)){
      report("Maze room is valid. Removing maze");
      mazeroom->remove_maze();
      report("Making maze");
      mazeroom->make_maze();
    } else {
     if(mazeroom == TO) report("%^BOLD%^%^CYAN%^Maze room is this room");
     else report("Maze room is not valid. ");
    }
  } else {
    report( "Time now - uptime <= time maze was last made. Therefore maze does not need remaking");
  }
  last_verified = time();
  return 1;
}

string short_desc(){
  int i, num, count;
  string * exits;
  if (last_described < time()-5) {
    report ("%^B_CYAN%^1) In problem lines of short_desc. last described: " + last_described + " time: "+ time());
    check_maze();
    report ("%^B_BLUE%^2) In problem lines of short_desc. last described: " + last_described + " time: "+ time());
    report("Calling :: query_exits() from short_desc");
    exits = ::query_exits();
    report ("%^B_ORANGE%^3) In problem lines of short_desc. last described: " + last_described + " time: "+ time());
    num = sizeof(base_exits);
    update_exits();
    verify_maze();  // These lines are to try to make sure that a river loads when it should
    update_exits(); // Remove them if it doesn't work
    count = sizeof(exits)-num;
    report ("%^B_RED%^4) In problem lines of short_desc. last described: " + last_described + " time: "+ time());

    if (count<1){
      report ("%^B_MAGENTA%^5) In problem lines of short_desc. last described: " + last_described + " time: "+ time());
      report ("%^BOLD%^%^MAGENTA%^Updating exits from short_desc");
      update_exits(1); 
      verify_maze();  // These lines are to try to make sure that a river loads when it should
      update_exits(1); // Remove them if it doesn't work
    }
    report ("%^B_GREEN%^End of problem lines of short_desc. last described: " + last_described + " time: "+ time());
  }
  report ("%^BOLD%^%^CYAN%^Got past potentially problematic lines of short_desc. last described: " + last_described + " time: "+ time());
  report("Calling :: query_exits() from short_desc");
  if (sizeof(::query_exits())- sizeof(base_exits) <1){
    update_exits();

    if (sizeof(::query_exits())- sizeof(base_exits) <1){
      call_out ("eject", 6);
    }
  }
  last_described = time();
  return base_short_desc();
}

string long_desc(){
  int i, num, count;
  string * exits;
  check_maze();
  update_exits();
  verify_maze();  // These lines are to try to make sure that a river loads when it should
  update_exits(); // Remove them if it doesn't work
  report("Calling the main query_exits() from long_desc");
  exits = ::query_exits();
  num = sizeof(base_exits);
  if (sizeof(exits)-num<1)   update_exits();
  report("Calling :: query_exits() from long_desc");
  if (sizeof(::query_exits()) - sizeof(base_exits) <1)
  {
    update_exits();
    verify_maze();  // These lines are to try to make sure that a river loads when it should
    update_exits(); // Remove them if it doesn't work
    if (sizeof(::query_exits())- sizeof(base_exits) <1)
    {
      call_out ("eject", 6);
    }
  }
  return ::long_desc();
}



varargs void place_river(string path, int start_loc, int end_loc){

  string * river_path, original_room, new_room, * room_names, entry, exit, river_dir;
  int i, j, count, loc, river_num, left_loc;
  mapping locations;
  river_path = calculate_river_path(start_loc, end_loc);
  river_dir = "%^BOLD%^%^YELLOW%^River path: ";
  for (i=0;i<sizeof(river_path);i++){
    river_dir += river_path[i];
  }  
  tell_object(find_player("lujke"), river_dir);
  count = sizeof(river_path);
  if (count <1){
    report ("River path is too short. Aborting");
  }
  locations = MAZE_D->query_saved_locations(path);
  if (sizeof(locations)<1){
    report("Maze not built yet. Aborting place_river");
  }
  room_names = values(locations);
  for (j=1;j<51;j++){
    if (sizeof(room_names)<1 || member_array("rightbank" + j, room_names) ==-1){
      river_num = j;
      break;
    }
  }
  loc = start_loc; 
  for (i=0;i<count+1;i++){
    original_room = MAZE_D->query_room(path, loc);
    report("%^RESET%^%^GREEN%^Next location: " + loc + " Room name: " + original_room);
    if (i==0){
      entry = "north";
    } else {
      entry = MAZE_D->reverse_direction(river_path[i-1]);
    }
    if (i==count){
      exit = "south";
    } else {
      exit = river_path[i];
    }
    if (original_room != "none"){
      MAZE_D->replace_room(path, original_room, "rightbank" + river_num); 
      MAZE_D->set_river_entry(path, "rightbank" + river_num, entry);
      MAZE_D->set_river_exit(path, "rightbank" + river_num, exit);
    } else {
      report ("%^RED%^Adding rightbank to location with no original room. Loc no: " + loc);
      MAZE_D->add_location(path, loc, "rightbank" + river_num);
    }
    left_loc = calculate_leftbank_location(loc, entry, exit);
    original_room = MAZE_D->query_room(path, left_loc);
    if (original_room != "none"){
      MAZE_D->replace_room(path, original_room, "leftbank" + river_num); 
      MAZE_D->set_river_entry(path, "leftbank" + river_num, entry);
      MAZE_D->set_river_exit(path, "leftbank" + river_num, exit);
    } else {
      MAZE_D->add_location(path, left_loc, "leftbank" + river_num);
      report ("%^GREEN%^Adding leftbank to location with no original room. Loc no: " + loc);
    }
    report("%^BOLD%^%^BLUE%^Exit direction: " + exit);
    loc = calculate_location(loc, exit);
    river_num ++; 
  }
  report("%^BLUE%^Finished placing %^CYAN%^river");

}

string calculate_leftbank_direction(string enter_dir, string exit_dir){
  int ent, exi, result;
  string direction;
  if (enter_dir=="east"){ 
    return "south";
  }
  if (enter_dir=="west"){
    return "north";
  }
  return "east";
/*  ent = dir_no(enter_dir);
  exi = dir_no(exit_dir);
  result = (ent + exi)/2;
  direction = dir_name(result);
  if (ent > exi){
    direction = MAZE_D->reverse_direction(direction);
  }
  return direction; */
}

int calculate_location(int start_loc, string direction){
  int loc;
  switch(direction){
  case "north":
    loc = start_loc+1000;
    break;
  case "northeast":
    loc = start_loc + 1001;
    break;
  case "east":
    loc = start_loc+1;
    break;
  case "southeast":
    loc = start_loc - 999;
    break;
  case "south":
    loc = start_loc - 1000;
    break;
  case "southwest":
    loc = start_loc - 1001;
    break;
  case "west":
    loc = start_loc-1;
    break;
  case "northwest":
    loc = start_loc + 999;
    break;
  }
  return loc;
}

int calculate_leftbank_location(int start_loc, string enter_dir, string exit_dir){
  string direction;
  direction = calculate_leftbank_direction(enter_dir, exit_dir);
  return calculate_location(start_loc, direction);
}

string * calculate_river_path(int start_loc, int end_loc){
  int start_x, end_x, start_y, end_y, i, count, x_distance, y_distance, distance, x, y, next_dir_no, last_dir_no, limit;
  string * result, next_direction;
  start_x = start_loc % 1000;
  start_y = start_loc / 1000;
  end_x = end_loc % 1000;
  end_y = end_loc / 1000;
  x_distance = start_x - end_x;
  if (x_distance<1){
    x_distance = x_distance *-1;
  }

  y_distance = start_y - end_y;
  if (y_distance<1){
    y_distance = y_distance *-1;
  }
  if (x_distance > y_distance){
    distance = x_distance;
  } else {
    distance = y_distance;
  }
  x = start_x;
  y = start_y;
  next_dir_no = 5;
  result = ({});
  limit = 0;
  while(y>end_y && limit <200){
    last_dir_no = next_dir_no;
    x_distance = end_x - x;
    y_distance = y- end_y; // River always flows north-south
    if (y_distance >4){
      next_dir_no = last_dir_no -1 + random(3);
      if (x > end_x && next_dir_no <6 && x_distance>= y_distance-1){
        next_dir_no ++;
      }
      if (x < end_x && next_dir_no >4 && x_distance>=y_distance-1){
        next_dir_no --;
      }
    } else { //if y_distance<=4
      if (x > end_x){ 
        report ("%^MAGENTA%^Nearing bottom of map. x location is east of target. Heading southwest");
        next_dir_no = 6;
      }
      if (x == end_x){
        report ("%^MAGENTA%^Nearing bottom of map. x location is in line with target. Heading south");
        next_dir_no = 5;
      }
      if (x < end_x){
        report ("%^MAGENTA%^Nearing bottom of map. x location is west of target. Heading southeast");
        next_dir_no = 4;
      }

    }
    if (x_distance >= y_distance){
      next_dir_no = last_dir_no -1;
      report ("%^GREEN%^X distance " + x_distance + " >= Y distance " + y_distance + ". decrememnting next_dir_no to " + next_dir_no);
    }
    if (x_distance *-1 >= y_distance){
      next_dir_no = last_dir_no + 1;
      report ("%^GREEN%^X distance " + x_distance + " *-1 >= Y distance " + y_distance + ". in crememnting next_dir_no to " + next_dir_no);
    }
    if (next_dir_no<3){
      report ("%^BLUE%^next_dir_no <3 Resetting to 3");
      next_dir_no = 3;
    }
    if (next_dir_no>7){
      report ("%^BLUE%^next_dir_no >7 Resetting to 7");
      next_dir_no = 7;
    }
    if (x<3 && next_dir_no > 5){
      next_dir_no --;
    }
    switch(next_dir_no){
    case 3:
      next_direction = "east";
      x+=1;
      break;
    case 4:
      next_direction = "southeast";
      x+= 1;
      y-=1;
      break;
    case 5: 
      next_direction = "south";
      y-=1;
      break;
    case 6:
      next_direction = "southwest";
      x-=1;
      y-=1;
      break;
    case 7:
      next_direction = "west";
      x-=1;
      break;
    }
    report ("%^YELLOW%^Next %^BLUE%^river%^YELLOW%^ direction: %^RESET%^" + next_direction);
    result += ({next_direction});
    limit ++;
  }
  return result;
}




int dir_no(string dir){
  switch (dir){
  case "north":
    return 1;
  case "northeast":
    return 2;
  case "east":
    return 3;
  case "southeast":
    return 4;
  case "south":
    return 5;
  case "southwest":
    return 6;
  case "west":
    return 7;
  case "northwest":
    return 8;
  }
  return 0;
}

string dir_name(int dir){
  if (dir>8){
    dir -=8;
  }
  switch (dir){
  case 1:
    return "north";
  case 2:
    return "northeast";
  case 3:
    return "east";
  case 4:
    return "southeast";
  case 5:
    return "south";
  case 6:
    return "southwest";
  case 7:
    return "west";
  case 8:
    return "northwest";
  }
}