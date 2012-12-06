[33mcommit 24e5a73025dd60466318f24d11f83fe1f676e7c7[m
Author: Patrice Paquette <paquette.patrice@gmail.com>
Date:   Mon Dec 3 06:09:34 2012 -0500

    Slowed monster firing rate, respawn on death(no reinitialization)

[33mcommit 557b16e9f979599dbcb67256474b55c10c42d70b[m
Merge: 8349801 5d9e8cf
Author: Patrice Paquette <paquette.patrice@gmail.com>
Date:   Mon Dec 3 04:35:47 2012 -0500

    Merge branch 'master' of https://github.com/Bobbybobbets/JadeMonkey
    
    Conflicts:
    	JadeMonkey/JadeMonkey.vcxproj
    	JadeMonkey/JadeMonkey.vcxproj.filters

[33mcommit 8349801e307c78f8c9acad8308a970ff17b4e051[m
Author: Patrice Paquette <paquette.patrice@gmail.com>
Date:   Mon Dec 3 04:32:50 2012 -0500

    Added entities to map 1, added collision detection for firebolts

[33mcommit 9a7dc3b8a075d87c8fd2d8d28ba050e06e20634f[m
Author: Patrice Paquette <paquette.patrice@gmail.com>
Date:   Mon Dec 3 04:29:36 2012 -0500

    Added entities to map 1, added collision detection for firebolts

[33mcommit 5d9e8cf5273cf27bf9bd6a7d9a739d4271b8fc38[m
Author: Nicholas Bowen <swatawatataaa@hotmail.com>
Date:   Mon Dec 3 02:34:52 2012 -0500

    addedd poopy UI

[33mcommit aedbe7c4706d464f594cc6b2f132e01f759c5e4d[m
Merge: c47e728 022fc6a
Author: Patrice Paquette <paquette.patrice@gmail.com>
Date:   Mon Dec 3 00:28:39 2012 -0500

    Merge branch 'master' of https://github.com/Bobbybobbets/JadeMonkey
    
    Conflicts:
    	JadeMonkey/EntityFactory.h
    	JadeMonkey/JadeMonkey.vcxproj
    	JadeMonkey/MainEntityFactory.cpp
    	JadeMonkey/PatTestFactory.cpp
    	JadeMonkey/PlayerFPInputComponent.cpp
    	JadeMonkey/PlayerFPInputComponent.h

[33mcommit c47e72871eb58735a864d9e62dadc0980c27d433[m
Author: Patrice Paquette <paquette.patrice@gmail.com>
Date:   Mon Dec 3 00:03:46 2012 -0500

    smalle changes

[33mcommit 176b1bdc2083bf5a3c3f6fc70dc30b350fc7f5a7[m
Author: Patrice Paquette <paquette.patrice@gmail.com>
Date:   Sun Dec 2 23:40:10 2012 -0500

    strafe fix, behaviour trees, firebolts, tried to remove vcxproj files - hope it worked!

[33mcommit 022fc6a25890d10f7c52545ca5256b37cea201a1[m
Merge: 07f5361 6264ae1
Author: Nicholas Bowen <swatawatataaa@hotmail.com>
Date:   Sun Dec 2 22:50:24 2012 -0500

    Merge branch 'master' of https://github.com/Bobbybobbets/JadeMonkey
    
    Conflicts:
    	JadeMonkey/Game.h
    	JadeMonkey/JadeMonkey.vcxproj

[33mcommit 07f53614b1703e36e97c49d115a2b7b3a365b72f[m
Author: Nicholas Bowen <swatawatataaa@hotmail.com>
Date:   Sun Dec 2 22:46:17 2012 -0500

    Lets try this

[33mcommit 6264ae1a8bbcdbd157473ff72914f9ad3187a2b9[m
Merge: 847b726 fb16eb8
Author: Patrice Paquette <paquette.patrice@gmail.com>
Date:   Sun Dec 2 06:35:26 2012 -0500

    Merge branch 'master' of https://github.com/Bobbybobbets/JadeMonkey
    
    Conflicts:
    	JadeMonkey/EntityFactory.cpp
    	JadeMonkey/EntityFactory.h
    	JadeMonkey/KeyGraphicsComponent.cpp

[33mcommit 847b7266ac89e51ad33a2330f5beb287d7b9b3cf[m
Author: Patrice Paquette <paquette.patrice@gmail.com>
Date:   Sun Dec 2 06:01:46 2012 -0500

    Pathfinding, multiple entities collision, multiple entities pathfinding (can follow other entities)

[33mcommit fb16eb83c0b0558a991983e02d3a90a6cb71f7af[m
Author: Nicholas Bowen <swatawatataaa@hotmail.com>
Date:   Wed Nov 28 03:37:33 2012 -0500

    Completed a trap door

[33mcommit 6c3a4f379596a579c14bc6f5e5d4b067a115825a[m
Author: Nicholas Bowen <swatawatataaa@hotmail.com>
Date:   Tue Nov 27 22:07:57 2012 -0500

    Picking up keys

[33mcommit 6ae02b5fa28ea99b342ce29ac0b959c0633f643b[m
Author: Nicholas Bowen <swatawatataaa@hotmail.com>
Date:   Tue Nov 27 15:41:18 2012 -0500

    Started to add the keys

[33mcommit 3f1570e4e8e105ac974686eca149d11f0c1b77d7[m
Author: Patrice Paquette <paquette.patrice@gmail.com>
Date:   Tue Nov 27 14:36:16 2012 -0500

    Added files

[33mcommit 492540684a7a20586d91a5e342d2836960690d02[m
Author: Patrice Paquette <paquette.patrice@gmail.com>
Date:   Sun Nov 25 18:40:15 2012 -0500

    Abstracted EntityFactory in JadeMonkeyGame so that it's easier to work with test factories. You now have to input the wanted factory when creating the game object, in JadeMonkey.cpp.

[33mcommit 1fce39ffd29e7fbd493a4eb8e7541ec6f234c342[m
Author: Nicholas Bowen <swatawatataaa@hotmail.com>
Date:   Sat Nov 24 00:44:53 2012 -0500

    Cleaning up

[33mcommit 48d8904be6337a7c4081f167b7287e0c95a48dc8[m
Author: Nicholas Bowen <swatawatataaa@hotmail.com>
Date:   Fri Nov 23 18:14:00 2012 -0500

    Stairs actually working and the first level

[33mcommit aa3af6cacc4e4c6c1d3b7588b93155997669eba8[m
Author: Nicholas Bowen <swatawatataaa@hotmail.com>
Date:   Thu Nov 22 18:00:10 2012 -0500

    Stairs working

[33mcommit 38d17a026fd706bf8522dddbce659e763b060052[m
Author: Nicholas Bowen <swatawatataaa@hotmail.com>
Date:   Mon Nov 19 14:44:51 2012 -0500

    Got wall collisiosn working
    
    With what I added I'm assuming we'll only ever need one graphics
    component, and also atm everything will only have 1 collision component.
    Might have to change later but right now seems to work fine. Also for
    simplicity we'll only have walls at 0 and 90 degrees

[33mcommit 727ff03a07778352fa87c79db2440c1bd9b3f3b0[m
Author: Patrice Paquette <paquette.patrice@gmail.com>
Date:   Tue Nov 13 04:31:35 2012 -0500

    Half-ass collision detection (only works on floors); will improve later.

[33mcommit 8cc5485fd172baefc792bc33ac4197a9e0512f6d[m
Author: Patrice Paquette <paquette.patrice@gmail.com>
Date:   Mon Nov 12 17:53:49 2012 -0500

    tidied up

[33mcommit eae3da2d6ae5478311bcb97b03c7cd3621f40987[m
Author: Patrice Paquette <paquette.patrice@gmail.com>
Date:   Mon Nov 12 14:56:32 2012 -0500

    components work

[33mcommit 025d7690625743dd042e080bd5bba9db7a54839b[m
Author: Nicholas Bowen <swatawatataaa@hotmail.com>
Date:   Sat Nov 10 19:15:32 2012 -0500

    Got the WASD commands working

[33mcommit 926a20d41480a62a69d0c9732f06450b1e8cbf20[m
Author: Nicholas Bowen <swatawatataaa@hotmail.com>
Date:   Fri Nov 9 22:46:17 2012 -0500

    Got the camera working properly

[33mcommit 8775141bf85d67c6452e0e49ec3f6eb5b5d904b3[m
Author: Nicholas Bowen <swatawatataaa@hotmail.com>
Date:   Fri Nov 9 14:54:43 2012 -0500

    almost got the first person camera working

[33mcommit 279af6098ffa467b16da624ec7bf8d71be6f25b7[m
Author: Patrice Paquette <paquette.patrice@gmail.com>
Date:   Fri Nov 9 01:56:40 2012 -0500

    Added some getters and setters to gameEntity

[33mcommit 1e08e378d15e060914df2574098087f5153154e2[m
Author: Nicholas Bowen <swatawatataaa@hotmail.com>
Date:   Fri Nov 9 01:55:08 2012 -0500

    Got rid of the static d3ddevice in gamecomponent

[33mcommit 9e431228fe173437858e19644d804b2fbe03a670[m
Author: Nicholas Bowen <swatawatataaa@hotmail.com>
Date:   Fri Nov 9 01:50:42 2012 -0500

    Displaying a surface

[33mcommit 7f5f764c5a0ea83b77d9fd5c48305f90b85ef228[m
Author: Nicholas Bowen <swatawatataaa@hotmail.com>
Date:   Wed Nov 7 02:13:56 2012 -0500

    Fixing some errors and added a surface
    
    THIS FEATURE IS AMAZING

[33mcommit 5bd88e987d4026c80f7ddb0413a07780423b4387[m
Author: Patrice Paquette <paquette.patrice@gmail.com>
Date:   Mon Nov 5 10:14:29 2012 -0500

    1st commit
