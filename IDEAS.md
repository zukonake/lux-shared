# Lux ideas
### Graphics
* top-down 2d
* extensive light system
* extensive field of vision system
* perhaps shadows
* pixelated textures
* noise in dark areas (just like IRL)
### Map
* infinite 2d map
* map is grid based
* wilderness with various biomes
    * free-roaming animals that you can tame and perhaps use in a practical way
    (horses etc.)
* some ruins, dungeons and caves as well
* occasional villages
    * villages grow on their own
    * dynamic economy system
    * every villager has a task they do everyday
    * you can create and manage your own villages with NPCs
* possible various starting points, for example:
    * start in a very cold biome with a cabin
    * start without eyes but with very good hearing and martial arts abilities
### Mechanics
* co-op survival multiplayer
    * players specializing in various schools of magic being efficient
    * estimated amounts of players: from 1 to 8
* food water and light are neccesary to survive
    * survival should be a hard in beginning
    * survival shouldnt limit the player later
    * hunting as a good source of food
    * farming as well, but needs to be developed early and requires a lot of
    land, suitable for long-term food source or multiplayer
* player is free to build and mine
    * mining and building should be somewhat slow, and save progress
* programmable AI
    * AI can be programmed using visual programming
    * you can program NPCs to manage/gain your resources etc.
* AI pathfinding is not all-knowing
    * AI will have to explore paths based on directions, instead of solving a
    maze with no exploration
    * AI will know paths to certain tiles, it can add relative paths to other
    neighboring tiles this way
    * AI will forget the paths after some time, this depends on memory skill etc.
    * this can actually be faster than standard pathfinding, but take more RAM
* industry
    * wheelbarrows and minecarts etc will be available early on, later ox-driven
    carts as well
        * they need to be designed in a way that is practical to the player
    * later on more advanced and automated industry will be available, in the
    beginning the NPCs or the player will have to do some parts
* dynamic combat system
* some sort of crafting system
* the game should be realistic, but not based on grinding
    * magic and industry might greatly help with that
* weapons are hotline miami-like
    * sword slashes
    * bows
    * maybe primitive guns
* game assets loadable with lua or other language
    * the game engine should be completely written in C++
    * game objects should be defined in scripts
        * this includes monsters, items, biomes
        * maybe even the generator, interface and spells
* mod-friendly
    * exposed API
    * being open-source helps
* physics engine
* inventory shouldn't be limiting, like it is in Minecraft
    * the major factor there was, that many items that were not needed were often carried
    * additionaly a quick-stack feature like in Terraria would be good
* entities move freely
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
    * another way are NPCs, either servants or villagers
    * the ways can be combined, they should be perfectly compatible
* action system
    * every thing a player can do is an action
    * actions can be bound to keys, for example movement or attack/interaction
    * you can combine actions, similarly to "macros"
        * the system could resemble visual programming
        * you would set various parameters, such as paths, radiuses, etc.
    * un-combined actions are called "basic"
    * combined actions are called "complex"
    * spells are also actions
        * this can enable rebinding standard actions such as attacks to something different
            * example: enchant sword before attacking, then attack, as a single action
    * perhaps the basic actions could have a skill counterpart, that increases
    the efficiency as the action is used
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
    * long-term low sanity makes your character develop psychological illnesses
    and makes gameplay very hard (and perhaps short)
* character system
    * besides sanity, your character will have certain needs that dictate what
    you need to do to stay effective
    * for example your character might be very curious, and so might have to do
    research in order not to be bored, and would as well have a bonus to
    research
    * boredom decreases effectivenes in all skills
    * character could be chosen randomly or created by the player
