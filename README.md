# ComS_327_Moving-from-map-to-map

Moving from map to map
In the first week we generated maps that had exits, theoretically to other maps. This week we’ll be using
those exits to connect to other terrain maps.
Later, we’ll use a library called curses to add a proper user interface. For now, we’ll simply print to
and read from the standard input at the terminal using standard I/O. We’re going to implement 6 commands,
all of which will have to be followed with the enter key because of buffered I/O (something curses will
eliminate for us). The commands are:
• n: Display the map immediately north of the current map.
• s: Display the map immediately south of the current map.
• e: Display the map immediately east of the current map.
• w: Display the map immediately west of the current map.
• f x y: x and y are integers; Fly1
to map (x, y).
• q: Quit the game.
Other input should be handled gracefully; don’t crash, and—ideally—print an error message.
Our world will measure 399 × 399 maps; we begin in the center, which we’ll call map (0,0) but may
be easier thought of internally as (199,199). Each movement command causes us to display the map in the
indicated direction or location. Movement commands that would cause display to move off the edge of the
world are ignored (i.e., redisplay the current map, optionally accompanied by an error message).
At all times, display the coordinates of the current map beneath the map itself.
Later, when we add Pokemon to the game, the levels of wild-spawned Pok ´ emon will be a function of ´
the distance from the center. Additionally, the frequency of Pokemarts and Pok ´ emon Centers should decline ´
as we move out in order to increase game difficulty. Your starting position (the center, map (0,0)) should
always have both buildings. As we move out, the probability of each building should be a function of the
distance. This is a value that may need to be tweaked for game balance later, but for now I think that
something like −45d/200+50
100 gives the chance of a building being created for distance less than 200, and a
flat 5% for distances 200+, where d is the Manhattan distance from the center, seems reasonable2
. This give
roughly a 50% probability of each building when close to the center, falling off linearly to 5% near a center
edge or farther.
When generating maps adjacent to previously-generated maps, exits should match up. For instance,
if you begin your game at (0,0) and move n n e e s s w n, you will be in (1,-1) (assuming n is the
negative y direction. All of (1,-1)’s neighbors will have been generated before (1,-1). The height position of
(1,-1)’s west exit should match that of (0,-1)’s east exit, (1,-1)’s north exit should align with (1,-2)’s south
exit, and so on for each direction. To implement this, you’ll want your map exits to be a parameter to your
map generator, which may require a small refactor of the 1.01 interface.
No map should ever be generated until it is visited. All visited maps should be saved such that they can
be visited again by going to the original coordinates.
In addition to aligning neighboring exits, maps on the edges of the world should not have exits on their
world-bordering edges.
1
It would be teleport or jump, but this is a Pokemon game ´
2
In case you’re wondering where this odd formulation came from, it’s just the slope-intercept form of a line through the points
(0, 50) and (200, 5).
