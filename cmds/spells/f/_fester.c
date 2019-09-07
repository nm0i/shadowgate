#include <std.h>
#include <magic.h>
inherit SPELL;

int lower;

void create()
{
    ::create();
    set_spell_name("fester");
    set_spell_level(([ "inquisitor" : 3 ]));
    set_spell_sphere("necromancy");
    set_syntax("cast CLASS fester on TARGET");
    set_damage_desc("positive energy resistance");
    set_description("Necrotic energy permeates the target, blocking some of energy flow, impeding their healing abilities.");
    set_verbal_comp();
    set_somatic_comp();
    set_target_required(1);
}

string query_cast_string()
{
    return "%^MAGENTA%^"+caster->QCN+" proclaims and incantation, darkness forms behind "+caster->QO+".";
}

void spell_effect()
{
    tell_room(place,"%^MAGENTA%^You watch as bolt of darkness hits"+target->QCN+".",({caster,target}));
    tell_object(target,"%^MAGENTA%^You feel cold as bolt of darkness released by "+caster->QCN+" reaches you.");
    tell_object(caster,"%^MAGENTA%^You point a finger at "+target->QCN+" and release bolt of darkness.");

    if (target->query_property("fester"))
    {
        tell_object(caster,"%^BOLD%^The spell is repelled forcibly.");
        dest_effect();
        return;
    }

    tell_room(place,"%^MAGENTA%^The place gets a little cold...");

    lower = 4*clevel;

    target->set_property("positive energy resistance",lower);

    target->set_property("fester",1);
    call_out("dest_effect",clevel*ROUND_LENGTH,lower);
}

void dest_effect()
{
    if(objectp(target))
    {
        target->set_property("positive energy resistance",-lower);
        target->remove_property("fester");
    }
    ::dest_effect();
    if(objectp(TO))
        TO->remove();
}
