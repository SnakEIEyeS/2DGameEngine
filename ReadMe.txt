Pong -

I have created Pong with the Engine systems that I worked on for the class over the semester.

Use the W & S keys to move the Left Paddle. Use the I & K keys to move the Right Paddle. Press Space to start the round.
Press Esc to Quit.

Hit the ball with your Paddle and try to put it past your opponent's Paddle to score a point! 
This also means that you will want to make sure you do not miss the ball or you will risk giving your opponent a point.

The first player to score 5 points wins!



Technical Details -

Code inside the GLib project is not mine. It was provided by Joe Barnes.

I have tailored the Engine specifically for the game and changed the systems with that in mind.

The system only checks for collision of the Ball against all the other objects. The Paddles are kept within the play area by checking that they don't cross the bounds.

At any given time in the game, there are only 3 moving objects. So my Physics System only updates the objects that are set as Movable.

Furthermore, since only the Colliders of the Movable objects can change each frame, my system has a separate list of Colliders for Non-Movable objects.
The Colliders in this list are not updated each time the Collision Run happens as neither the position nor the velocity nor the rotation ever changes for these objects.
Colliders are added to this Collider list when Non-Movable objects are created and can be removed from the list when they are to be destroyed or by calling the specific function.
Although, the calculations that go into making these Colliders only happen once - upon creation - which was my motivation in making this almost static list.

I have also simplified the system to only find the earliest collision and move all objects to that collision, respond to it and move the remaining part of the frame accordingly.
My reason behind doing this is that the Game World is very sparse and objects are usually far away from each other. 
More importantly, we only check collision of only the ball against everything else, so there is a very low possibility that there are going to be two or more subsequent collisions within a frame.

All the aspects of the Physics & Collision system mentioned above can be found in Physics.h & Physics.cpp.


I have grouped collisions for the Ball against the other objects into two categories - Killing and Rebounding, which are basically set using a bool m_bCollisionKilling in PhysicsInfo.
Each collision type has its own type of response and the system also uses Delegates to relay each type of collision.

These can be found in Physics.cpp & Pong.cpp.


The game has functionality to be restarted along with a reset of the scores after completion of a game or match. So, players can play any number of matches they want.


