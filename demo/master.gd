extends Node

@onready var bullet_pool: BulletPool = $BulletPool

@onready var fps_label: Label = $FPSLabel
@onready var bulletcount_label: Label = $BulletcountLabel


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta: float) -> void:
	fps_label.text = str(Engine.get_frames_per_second())
	bulletcount_label.text = str(bullet_pool.get_current_bullets())
