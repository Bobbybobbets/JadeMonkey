Portfolio - JadeMonkey
==========

This game was developed by a team of two programmers for the third-year game programming course. It is a first-person
shooter which requires the player to dodge incoming projectiles while trying to kill the enemies using his own arsenal.
This article will serve as a technical post-mortem of my experience, in which I will discuss the most interesting
topics encountered while developing the game.

My involvement
---

- System architecture : Entity-Component architecture
- Artifical intelligence : Pathfinding, Behaviors
- Graphics : Textures, Lighting
- Skills system design

System Architecture : Entity-Component architecture
---

The game uses an Entity-Component architecture in an effort to decouple the different systems included in an usual game. 
Instead of having a hierarchy of classes, which, in my opinion, isn't very well suited 
for adapting to constantly changing requirements, this architecture instead promotes heavy use of composition as a way
to define the entity's functionality.

![Entity-Component architecture](Design\ Documents/architecture.jpg)

###Components###

A component is defined as being the implementation of a very specific functionality and should ideally be completely 
self-contained by managing its own state; I quickly realized that this was not possible. Not only are there usually
dependency requirements between different functionalities, but many components must also refer to the same state variable
unique to the entity. Consider this structure :

![Entity prenormalization](Design\ Documents/EntityPrenormalization.jpg)