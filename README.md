# captain-sonar-blue
---
## Members:

Voss: Networking  
Laxamana: SDL  
Eggert: Game Logic  
Surin: Threading


## Captain Sonar v2.0

For this assignment, ADTify Captain Sonar.

1. Specifically, change the Submarine class to be an ADT, which means all member
variables are private and you have get/set methods for all of them. NOTE: Static constants should stay public.
(Leave the move class as it is, if you like, or ADTify it if you want more
experience.)

So you will switch, say, torpedoes to be private, and then write a get and set
method for them (i.e. get_torpedoes and set_torpedoes).

2. In main, you will have to change all the direct usages of the member
variables from .torpedoes (and so forth) to .get_torpedoes() or
.set_torpedoes() depending on if you are getting or setting them.

3. Write a constructor that will initialize all the private integers. You
don't need constructors for the move or the vector, because they have their
own.

4. Extra credit will be available for people who add cool new features to the
game.

On Canvas, write down which of the 4 bullet points you accomplished,
especially what additional features you added for #4.
