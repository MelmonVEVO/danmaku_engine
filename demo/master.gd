extends Node

@onready var bullet_pool: BulletPool = $BulletPool
@onready var emitter_2d: Emitter2D = $Emitter2D

@onready var fps_label: Label = $FPSLabel
@onready var bulletcount_label: Label = $BulletcountLabel


func _ready() -> void:
	seed(1337)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta: float) -> void:
	fps_label.text = "FPS " + str(Engine.get_frames_per_second())
	bulletcount_label.text = "Bullets " + str(bullet_pool.get_current_bullets())


func _on_button_pressed() -> void:
	bullet_pool.kill_em_all()
	emitter_2d.start_emitting()
