extends CharacterBody2D

signal hit(rid: RID)

const SPEED: float = 500.0


func _physics_process(_delta: float) -> void:
	var input_direction: Vector2 = Input.get_vector("left", "right", "up", "down")
	var slow_factor: float = 1.0
	if Input.is_action_pressed("slow"):
		slow_factor = 0.5
	velocity = input_direction * SPEED * slow_factor
	move_and_slide()


func _on_area_2d_body_shape_entered(body_rid: RID, _body: Node2D, _body_shape_index: int, _local_shape_index: int) -> void:
	hit.emit(body_rid)
	print("HIT!")


func _on_bullet_pool_collision(collider: Dictionary) -> void:
	print("hit " + str(collider["collider"]))
