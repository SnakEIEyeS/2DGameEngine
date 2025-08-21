GameObject =
{
name = "PongBall",
class = "Ball",
controller = "BallController",
initial_position = { 0.0, 0.0},
movable = 1,

bounding_box = {
	center = { 0.0, 11.0},
	extents = { 11.0, 11.0}
},

physics_settings =
{
	mass = 10.0,
	drag = 0.5
},

collision_killing = 0,

render_settings =
{
	sprite_file = "..\\Game\\data\\PongBall.dds",
		--offset = { 0.0, 0.0},
				-- left, top, right, bottom
	sprite_extents = { -1.0, -1.0, 1.0, 1.0},
	sprite_color = { 255, 255, 255, 255}
}
}