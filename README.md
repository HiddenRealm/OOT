# OOT
This was my Object Orientended Techniques Assignment, for this we had to use a hash-table to sort and keep track of particles as they move around the screen. we had to the hash-table to split up collision detection and make the program run smooth, i was able to run smooth with about 60,000 particles on my screen.

Press "E" - to add more particles.
Press "Q" - to remove particles.

Inside of the Manager.cpp file in the constructer there is a bool "CollisionType"
You can set this to true to have the program do all of the collision at once
showing how the hashtable helps the program to function with stupidly high particle numbers.

The Particles are default white, 
Orange when colliding off of the bounder, 
Purple when colliding off of another particle.
