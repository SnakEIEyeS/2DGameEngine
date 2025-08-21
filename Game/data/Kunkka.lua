GameObject =
{
name = "Kunkka",
class = "Player",
controller = "PlayerController",
initial_position = { -180.0, -100.0},

bounding_box = {
	center = { 0.0, 103.5},
	extents = { 58.5, 103.5}
},

physics_settings =
{
	mass = 100.0,
	drag = 0.5
},

render_settings =
{
	sprite_file = "..\\Game\\data\\KunkkaDDS.dds",
		--offset = { 0.0, 0.0},
				-- left, top, right, bottom
	sprite_extents = { -1.0, -1.0, 1.0, 1.0},
	sprite_color = { 255, 255, 255, 255}
}
}