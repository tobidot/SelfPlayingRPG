##################################
###      SelfPlaying RPG
##################################

### Shor description

This is a game based on interaction between human and artificial intelligence.
In an rpg-style world npc's are not bound to a simple script,
but are able to be just as equally able to jurney out and slay monsters.
The AI should learn how to survive in the world on its own.
The Player controls just another character that is no different from the ones the AI controlles.
In the end the AI should prefer the more 'simple' and 'boring' lifestyle and thus give the 
Player quests.


### World
Random 
	The world is generated and 
	basicly infinite in size
Terrain
	The world is divided into grids and every grid can hav its own terrain
Novotree
	The grids are stored in a novotree
	So every grid can be divided to 9 smaller grids to store the terrain more precisely.


### Objects

Memory
	The Objects are stored within the terrain grid they are in right now.

	# Effects
		Things that do not act in any complex way.
		Basicly a Placeholder for the game to remember it has to do something.
		(Projectiles, Fire)		
	
	# Characters
		All objects that can activly manipulate their environement (Player and NPCs)
		Control
			A single function determines, what this character is about to do.
			This can be based of the neural network, or the Player input. (And easily be swapped).
		Neural Network
			Input 
		Output 

	# Monsters 
		May be even AI controlled as well, 
		but not that complex and seem to have 
		a strong urge to kill, destroy and collect.

	# Fauna 
		May be Geneticly controlled to adapt to changes of the Characters.
		(Includes Rocks, Trees and the like)
		
	