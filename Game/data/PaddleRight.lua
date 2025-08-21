GameObject =
{
name = "PaddleRight",
class = "Paddle",
controller = "PaddleController",
initial_position = { 525.0, -48.5},
movable = 1,

bounding_box = {
	center = { 0.0, 48.5},
	extents = { 8.5, 48.5}
},

controls = { 0x49, 0x4b },

physics_settings =
{
	mass = 10.0,
	drag = 0.5
},

collision_killing = 0,

render_settings =
{
	sprite_file = "..\\Game\\data\\PongPaddle.dds",
		--offset = { 0.0, 0.0},
				-- left, top, right, bottom
	sprite_extents = { -1.0, -1.0, 1.0, 1.0},
	sprite_color = { 255, 255, 255, 255}
}
}