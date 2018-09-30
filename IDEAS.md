# Lux ideas
### General
* goal is to reach top of the map (unsure)
### Map
* infinite 3d map
* map is grid based
* whole map is filled with dungeons
* ancient mayan inspired dungeons
    * some are active with no vines
        * filled with monsters, guardians and traps
        * high-value treasure/gear/materials inside
    * the rest is like a wilderness
        * filled with animals and "plants"
    * the high levels have cracks that let sunlight in
    * there are different zones or "biomes" of dungeons
        * they are procedurally generated
        * generated monsters and items
        * different levels and rewards
        * zones have random names
            * maybe like in dwarf fortress?
    * random plague in rooms
    * the plague takes over nearby open rooms slowly
    * the plague is dark, it eats all light
    * the plague grows much quicker in darkness
    * the plague can be fought with, but its quite slow
    * the plague turns entities into a dark, fast and aggressive version
        * dark entities will have a negative effect on light
* occasional towns and caverns
* some source of light exists but its mostly dark
* various game modes
    * start in a cold biome with a furnace
    * start without eyes but with very good hearing abilities
### Mechanics
* co-op survival multiplayer
    * players specializing in various schools of magic being efficient
    * estimated amounts of players: from 1 to 8
* food water and light are neccesary to survive
    * survival should be a hard in beginning
    * survival shouldnt limit the player later
    * lack of light affecting sanity
* player is free to build and rearrange the dungeons
    * player could build mechanisms and fortify the dungeons
    * exploring each dungeon is a risk to take, especially in some biomes
* dynamic combat system
* some sort of crafting system
* mining would be possible, but slow
* the game should be realistic, but not based on grinding and prefereable not time-consuming
    * magic might greatly help with that
* weapons are hotline miami-like
    * sword slashes
    * bows
    * maybe primitive guns
* game assets loadable with lua or other language
    * the game engine should be completely written in C++
    * game objects should be defined in scripts
        * this includes monsters, items, biomes
        * maybe even the generator, interface and spells
            * this would require an exposed API
* mod-friendly
    * again - exposed API
    * open-source helps
* physics engine
* block placing shouldn't be too limiting, it would be nice to place non-overlapping blocks
  on the same tile
* inventory shouldn't be limiting, as in Minecraft
    * the major factor there was, that many items that were not needed were often carried
    * additionaly a quick-stack feature like in Terraria would be good
* entities move freely or on a smaller grid
* entities can fall down
* realistic health system
    * various statistics like consciousness or vision
        * affecting each other and character's activities and senses
        * the player wouldn't be able to see all the statistics immediately, it would be
          another skill - knowing oneself
            * could be trained by regular meditation or a similar mechanic
    * hitboxes which localize the damage
        * a character could lose an arm or eye for example
* the game should have various ways to achieve automatization
    * one way is magic, either by inanimate objects or animate servants
    * another way is pure industry, pipes and engines
    * the ways can be combined, they should be perfectly compatible
* action system
    * every thing a player can do is an action
    * actions can be bound to keys, for example movement or attack/interaction
    * you can combine actions, similarly to "macros"
        * the system could resemble visual programming
        * you would set various parameters, such as paths, radiuses, etc.
    * spells are also actions
        * this can enable rebinding standard actions such as attacks to something different
            * example: enchant sword before attacking, then attack, as a single action
* advanced magic system
    * magic works on the principle of equivalent exchange
    * basic magic can be cast using one's lifeforce
        * the magical power can also be held in special items
        * the power is collected by slow destruction of things
        * or other alternative forms of energy
    * two schools of magic, theoretical and practical
        * theoretical magic is much more powerful, but requires more mastery
            * it deals in in-depth knowledge of basic spells, from which more complex ones
              are built
            * theoretical magic is also more "compatible" with industrial machines, as
              they work on a more fundamental level
            * theoretical magic could include manipulating essences and magical forces
        * practical magic is easier to achieve strong effects with
            * it can enable complex spells casting, without knowing the spells that they
              are built from
            * additionally practical spells could have an additional level of expertise
              that enchances its power much easier than going the theoretical path
            * practical magic is a good way to use magic without understanding the complex
              mechanics behind it, begineer friendly
    * ritual circles
        * they enable permanent bind to a certain location, for example to target a teleport
          spell
        * they can also decrease concentration cost of the spell casting,
          runes that are written on the floor are like a "spell-plan" that decreases the
          amount of "mind work" needed to cast the spell
        * one idea is also for the runes to be a way to contact other beings, such as gods
          that grant especially powerful spells
    * every creature will have a "soul", souls represent consciousness and can be used
      to create your own servants
    * possible spells are based on knowledge
        * a chemist can create flammable substances to create fire
        * biologists can heal wounds
            * on advanced levels they would be able to synthesize organic materials
        * a person with engineering knowledge can create and repair mechanisms
        * schools like enchanting or biology could allow recreating lost limbs
        * biologists have access to blood magic that has horryfing consequences
    * advanced combinations of spells can be created in a menu (action system)
        * various materials and spells can take various forms and shapes
        * combinations allowing to cast many spells at once
        * thanks to the menu, the player can create his spells before fighting
* non-grindy and perhaps innovative research system
* sanity system
    * whispers and blurred visions
    * on very low sanity you see horryfing abominations and the world becomes bloody
    * dark magic should be really dark and dangerous to play with, but equally powerful
### Graphics
* top-down 2d
* you can see levels below, darker or something
* extensive light system
* extensive field of vision system
* minimap showing the dungeon zones
* pixelated textures
