inherit "/std/barkeep";

create() {
    ::create();
set_name("D'seon");
set_id(({"D'seon", "d'seon", "innkeeper", "inn keeper"}));
set_short("%^GREEN%^D'seon, Innkeeper");
   set("aggressive", 0);
  set_level(10);
set_long("%^ORANGE%^D'seon runs the Inn.  He is a quiet looking elf with deep set blue eyes and long graceful fingers.  He appears to be waiting to attend to any needs his customers might have.  D'seon is dressed in a rust coloured tunic with matching pants.  A simple belt of beaten silver runs around his slender waist.  Should you require sustenance <read menu> is what D'seon suggests.");
	set_gender("male");
   set_alignment(4);
set("race", "elf");
set_size(2);
   set_hd(10,0);
	set_max_hp(query_hp());
set_max_sp(query_hp());
set_sp(query_max_sp());
set_mp(random(250));
set_max_mp(query_mp());
   add_money("copper", random(200));
   set_skill("melee",90);
    set_body_type("human");
set_currency("silver");

   set_menu(
       ({"good meal", "common meal", "poor meal", "cheese"}),
       ({ "food", "food", "food", "food" }),
       ({ 10, 7, 5, 3 })
   );
   set_my_mess(
       ({
       "Best meal in the house!\n",
       "A common meal for foreigners.\n",
       "A poor mans meal.\n",
       "Some of the native cheese. Very good!\n"
       })
   );
   set_your_mess(
       ({
       "enjoys a good meal.\n",
       "gobbles down a common meal.\n",
       "gags on the poor mans meal.\n",
       "eats some really good cheese.\n"
        })
    );
    set_menu_short(
        ({
        "A Good Meal",
        "A Common Meal",
        "A Poor Man's Meal",
        "Some Cheese"
        })
    );
    set_menu_long(
        ({
        "A tasty looking plate of some really good food.\n",
        "An appetizing plate of some food.\n",
        "A plate of what looks like slop.\n",
        "A slab of some really tasty cheese.\n"
   	})
    );
}
