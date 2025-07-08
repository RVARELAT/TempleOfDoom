# TempleOfDoom
The Temple of Doom is a simple, text-based action-adventure game where the player navigates through a multi-level temple in search of a golden idol. Inspired by classic adventure themes, the game challenges players to battle monsters, collect treasures, and strategically maneuver through a maze-like temple.

Gameplay Overview

<pre> 
•	Objective: Traverse the five levels of the temple, defeat monsters, collect items, and locate the golden idol to win the game.
•	Player Actions: Players can move, attack, pick up items, wield weapons, read scrolls, and descend deeper into the temple using a set of keyboard commands.
•	Monsters: Various monsters such as Bogeymen, Dragons, Goblins, and Snakewomen inhabit the temple. Each monster type has unique behaviors and attack strategies.
•	Items: Players can find and use weapons and magical scrolls that enhance their abilities, such as improving armor, strength, and health.
</pre>

Features

<pre> 
•	Randomly Generated Levels: Each level of the temple is procedurally generated, ensuring a unique experience with every game.
•	Turn-Based Combat: The game progresses one turn at a time, allowing players to strategize their moves against the various monsters.
•	Monster AI: Different monsters have distinct behaviors. For instance, Goblins use a recursive pathfinding algorithm to optimally chase the player, while Dragons guard their treasure and occasionally regain health.
•	Inventory Management: Players can manage an inventory of up to 25 items, including weapons and scrolls. Certain items, like the golden idol, end the game upon collection.
</pre>
  
How to Play

<pre> 
•	Movement: Use the arrow keys or h, j, k, l to move.
•	Attack: Move into the space of an adjacent monster to attack.
•	Pick Up Items: Stand on an item and press g to pick it up.
•	Wield Weapons: Press w and select a weapon from your inventory to wield it.
•	Read Scrolls: Press r and select a scroll from your inventory to read it.
•	Inventory: Press i to view your current items.
•	Descend Levels: Stand on a stairway and press > to descend to the next level.
•	Quit Game: Press q to quit.
•	Cheat Mode: Press c to activate cheat mode for easier gameplay.
</pre>
  
Development

This project is structured around a Game class that manages the game’s flow, including level generation, player actions, and monster behavior. The code is built on a provided skeleton with utility functions for input handling and random number generation.
