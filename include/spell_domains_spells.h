/**
 * List of domain spell mapped by domain.
 *
 * Order of spells defines their levels
 *
 * This dataset should be queried from MAGIC_D with
 * query_domain_spells(domain) and query_domains() functions.
 */
mapping DOMAIN_SPELLS = ([]);
DOMAIN_SPELLS = ([
"plant" : ({ "entangle", "barkskin", "thorn body", "wall of thorns", "liveoak", "animate plants", "mind blank", "shambler" }),
"protection" : ({ "divine favor", "shield other", "resist energy", "lesser globe of invulnerability", "invisibility purge", "repulsion", "spell turning", "mind blank", "dimensional lock" }),
"cold" : ({ "biting wind", "frostfield", "serac", "ice shield", "cone of cold", "frost breath", "hypothermia", "ice mirror", "glacier" }),
"law" : ({ "protection from alignment", "align weapon", "prayer", "deathward", "domination", "repulsion", "dictum", "shield of law", "dominate monster" }),
"chaos" : ({ "protection from alignment", "align weapon", "garble", "chaos hammer", "dispel law", "animate object", "word of chaos", "cloak of chaos", "prismatic burst" }),
"magic" : ({ "color spray", "resist energy", "break curse", "freedom of movement", "mystic bolt", "protection from spells", "true seeing", "spellscar", "clashing rocks" }),
"darkness" : ({ "shadow stream", "fog cloud", "blindness", "shadow conjuration", "darkbolt", "shadow travel", "powerword blind", "listening shadow", "shades" }),
"earth" : ({ "stone throw", "soften earth", "strength of stone", "spike growth", "earth reaver", "stoneskin", "elemental body iv", "stone body", "elemental swarm" }),
"trickery" : ({ "conceal alignment", "invisibility", "displacement", "confusion", "false vision", "flee the scene", "mass invisibility", "screen", "timestop" }),
"charm" : ({ "sleep", "captivate", "charm monster", "heroism", "domination", "bliss", "insanity", "demand", "dominate monster" }),
"travel" : ({ "skate", "clairvoyance", "faithful mount", "dimension door", "teleport", "pass portal", "create portal", "phase door", "astral projection" }),
"repose" : ({ "spectral touch", "gentle repose", "phantom steed", "deathward", "slay living", "undeath is death", "waves of exhaustion", "destruction", "wail of the banshee" }),
"air" : ({ "whispering wind", "cloak of winds", "gaseous form", "air walk", "airbolt", "chain lightning", "elemental body iv", "windstorm", "elemental swarm" }),
"strength" : ({ "enlarge person", "distressing tone", "magic vestments", "lesser globe of invulnerability", "righteous might", "stoneskin", "placeholder", "placeholder", "crushing hand" }),
"evil" : ({ "protection from alignment", "align weapon", "placeholder", "unholy smite", "slay living", "unholy orb", "blasphemy", "unholy aura", "animus blast" }),
"war" : ({ "magic weapon", "spiritual weapon", "magic vestments", "placeholder", "flame strike", "transformation", "powerword blind", "powerword stun", "powerword kill" }),
"knowledge" : ({ "true strike", "placeholder", "tongues", "deathward", "false vision", "legend lore", "powerword blind", "powerword stun", "powerword kill" }),
"sun" : ({ "faerie fire", "detect invisibility", "searing light", "nimbus of light", "flame strike", "fire seeds", "sunbeam", "sunburst", "prismatic burst" }),
"renewal" : ({ "bless", "restoration", "rejuvenation", "freedom of movement", "waves of fatigue", "disintegrate", "waves of exhaustion", "rebirth", "greater ruin" }),
"destruction" : ({ "true strike", "shatter", "rage", "fear", "tremor", "disintegrate", "finger of death", "horrid wilting", "tidal surge" }),
"storms" : ({ "snowball", "lightning touch", "sleet storm", "ice storm", "stormwinds", "sirocco", "acid fog", "stormrage", "storm of vengeance" }),
"fire" : ({ "burning hands", "produce flame", "fireball", "wall of fire", "fire shield", "fire seeds", "elemental body iv", "incendiary cloud", "elemental swarm" }),
"animal" : ({ "magic fang", "hold animal", "charm monster", "polymorph self", "summon natures ally v", "antilife shell", "true seeing", "shapechange", "summon natures ally ix" }),
"good" : ({ "protection from alignment", "align weapon", "prayer", "holy smite", "burst of glory", "holy orb", "holy word", "holy aura", "gate" }),
"water" : ({ "touch of sickening", "acid arrow", "stinking cloud", "ice storm", "cone of cold", "sirocco", "elemental body iv", "horrid wilting", "tidal surge" }),
"vigilance" : ({ "divine favor", "orders oath", "heroism", "vicarious view", "domination", "inspiring recovery", "greater heroism", "placeholder", "overwhelming presence" }),
"mentalism":({"confusion", "placeholder", "clairvoyance", "modify memory", "telepathic bond", "bolt of force", "mind blank", "inner eye", "astral projection"}),
]);