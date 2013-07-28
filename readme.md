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

###Entity###

An entity should ideally simply be a container of components; other than perhaps an unique id, it should not contain 
variables or methods. As we will see, this is not quite as simple as it sounds.

###Components###

A component is defined as being the implementation of a very specific functionality, such as rendering or calculating
managing movement, and should ideally be completely self-contained by managing its own state; I quickly realized that 
this was not possible. Not only are there usually dependency requirements between different functionalities, but many 
components must also refer to the same state variable unique to the entity. Consider this structure :

![Entity prenormalization](Design\ Documents/EntityPrenormalization.jpg)

As you can see, each of these components add independent functionalities(each of them could be used individually)
to the entity, yet they duplicate state variables that should be unique to this instance. I tried to fix this by storing highly used variables in the entity itself, such as its
position and velocity. While it fixes this particular problem, there are fundamental architectural flaws :

- While a variable may be needed by multiple components, there will be cases where none of them are included in an 
entity. In this case, the variables are dead weight, suggesting bad design.
- Any developer can add a variable as long as two or more of his components use it; This will eventually lead entities
to be poorly managed containers of non-related variables.

Furthermore, this structure does not properly model component dependencies; the only way to communicate is 
through those instance variables; so what happens if you need access to an interface? Having already coded a big part
of the project, I was not able to churn out a proper solution due to the large amount of refactoring required, which 
lead to many problems during development.



  
