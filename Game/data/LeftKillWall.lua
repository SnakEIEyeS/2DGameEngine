GameObject =
{
name = "LeftKillWall",
class = "KillWall",
controller = "KillWallController",
initial_position = { -620.0, -400.0},
movable = 0,

bounding_box = {
	center = { 0.0, 400.0},
	extents = { 20.0, 400.0}
},

physics_settings =
{
	mass = 1000.0,
	drag = 0.5
},

collision_killing = 1,
is_leftkillwall = 1
}