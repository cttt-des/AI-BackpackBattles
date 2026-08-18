tool
extends RichTextEffect

export (Curve) var water_curve
export (Gradient) var water_gradient
export (float) var water_cycle
export (float) var water_offset
export (float) var water_frequency
export (float) var water_speed = 1.0
export (float) var water_starttimeoffset = 1.0

export (Curve) var shaky_curve
export (float) var shaky_cycle
export (float) var shaky_speed = 1.0
export (float) var shaky_strength = 1.0
export (float) var shaky_starttimeoffset = 1.0

export (Gradient) var ice_gradient
export (float) var ice_cycle = 1.0
export (float) var ice_speed = 1.0

export (Gradient) var spooky_gradient
export (float) var spooky_cycle = 1.0
export (float) var spooky_speed = 1.0

export (Gradient) var fire_gradient
export (float) var fire_cycle = 1.0
export (float) var fire_speed = 1.0

export (Gradient) var vampiric_gradient
export (float) var vampiric_cycle = 1.0
export (float) var vampiric_speed = 1.0

export (Gradient) var gold_gradient
export (float) var gold_cycle = 1.0
export (float) var gold_speed = 1.0

export (Gradient) var light_gradient
export (float) var light_cycle = 1.0
export (float) var light_speed = 1.0

export (Gradient) var nature_gradient
export (float) var nature_cycle = 1.0
export (float) var nature_speed = 1.0

export (Gradient) var magic_gradient
export (float) var magic_cycle = 1.0
export (float) var magic_speed = 1.0

export (Gradient) var steel_gradient
export (float) var steel_cycle = 1.0
export (float) var steel_speed = 1.0

export (Gradient) var stone_gradient
export (float) var stone_cycle = 1.0
export (float) var stone_speed = 1.0

export (Gradient) var poison_gradient
export (Curve) var poison_curve
export (float) var poison_cycle = 1.0
export (float) var poison_speed = 1.0
export (float) var poison_offset = 1.0

export (Gradient) var rainbow_gradient
export (float) var rainbow_cycle = 1.0
export (float) var rainbow_color_speed = 1.0
export (float) var rainbow_frequency = 1.0
export (float) var rainbow_offset = 10.0
export (Curve) var rainbow_curve
export (float) var rainbow_wave_speed = 1.0

export (Curve) var lightning_curve
export (float) var lightning_cycle
export (float) var lightning_speed = 1.0
export (float) var lightning_strength = 1.0
export (float) var lightning_starttimeoffset = 1.0
export (Gradient) var lightning_gradient
export (float) var lightning_offset = 0.1

export (Curve) var stompy_curve
export (Gradient) var stompy_gradient
export (float) var stompy_cycle
export (float) var stompy_offset
export (float) var stompy_frequency
export (float) var stompy_speed = 1.0
export (float) var stompy_starttimeoffset = 1.0

export (Curve) var mercury_curve
export (Gradient) var mercury_gradient
export (float) var mercury_cycle
export (float) var mercury_offset
export (float) var mercury_frequency
export (float) var mercury_speed = 1.0
export (float) var mercury_starttimeoffset = 1.0

export (Curve) var dog_curve
export (Gradient) var dog_gradient
export (float) var dog_cycle
export (float) var dog_strength
export (float) var dog_speed = 1.0
export (float) var dog_starttimeoffset = 1.0
export (float) var dog_randomness = 1.0

export (Curve) var spring_curve
export (float) var spring_cycle
export (float) var spring_strength
export (float) var spring_speed = 1.0
export (float) var spring_starttimeoffset = 1.0
export (float) var spring_randomness = 1.0

export (Curve) var hyper_curve
export (Gradient) var hyper_gradient
export (float) var hyper_cycle
export (float) var hyper_strength
export (float) var hyper_speed = 1.0
export (float) var hyper_starttimeoffset = 1.0
export (float) var hyper_randomness = 1.0

var bbcode = "item"

func rand1(a) -> float:
	return abs(sin(a * 47.0432572429))

func rand(a: int, b: int) -> float:
	return abs(sin(a * 2349.230948234 + b * 95834.0497502587))
	
func _process_custom_fx(char_fx: CharFXTransform):
	
	var style = int(char_fx.env.get("s", 0))
	
	if style == ItemToolTip.TextEffect.Water:
		wave(char_fx, water_frequency, water_starttimeoffset, 
			water_speed, water_cycle, water_gradient, 
			water_curve, water_offset)
	
	elif style == ItemToolTip.TextEffect.Ice:
		setColorFromGradient(char_fx, ice_gradient, ice_speed, 
			ice_cycle, 0.5)
	
	elif style == ItemToolTip.TextEffect.Fire:
		setColorFromGradient(char_fx, fire_gradient, fire_speed, 
			fire_cycle, 0.5)
	
	elif style == ItemToolTip.TextEffect.Vampiric:
		setColorFromGradient(char_fx, vampiric_gradient, vampiric_speed, 
			vampiric_cycle, 0.0, - 0.2)
	
	elif style == ItemToolTip.TextEffect.Spooky:
		setColorFromGradient(char_fx, spooky_gradient, spooky_speed, 
			spooky_cycle, 0.1)
	
	elif style == ItemToolTip.TextEffect.Gold:
		setColorFromGradient(char_fx, gold_gradient, gold_speed, 
			gold_cycle, 0.0, - 0.2)
	
	elif style == ItemToolTip.TextEffect.Light:
		setColorFromGradient(char_fx, light_gradient, light_speed, 
			light_cycle, 0.0, - 0.2)
	
	elif style == ItemToolTip.TextEffect.Nature:
		setColorFromGradient(char_fx, nature_gradient, nature_speed, 
			nature_cycle, 0.0, - 0.1)
	
	elif style == ItemToolTip.TextEffect.Magic:
		setColorFromGradient(char_fx, magic_gradient, magic_speed, 
			magic_cycle, 0.8)
	
	elif style == ItemToolTip.TextEffect.Steel:
		setColorFromGradient(char_fx, steel_gradient, steel_speed, 
			steel_cycle, 0.0, - 0.2)
	
	elif style == ItemToolTip.TextEffect.Stone:
		setColorFromGradient(char_fx, stone_gradient, stone_speed, 
			stone_cycle, 1.0, 1.0, 500.0)
	
	elif style == ItemToolTip.TextEffect.Poison:
		var phase = setColorFromGradient(char_fx, poison_gradient, poison_speed, 
			poison_cycle, 1.0, 1.0, 500.0)
		char_fx.offset.y = - poison_offset * poison_curve.interpolate(phase)
		
	elif style == ItemToolTip.TextEffect.Rainbow:
		setColorFromGradient(char_fx, rainbow_gradient, 
			rainbow_color_speed, rainbow_cycle, 0.0, - 0.2, 20.0)





		
		var phase = 20 + char_fx.absolute_index * - rainbow_frequency
		phase += char_fx.elapsed_time
		phase *= rainbow_wave_speed
		var sampleX = fmod(phase, rainbow_cycle)
		char_fx.offset.y = - rainbow_offset * rainbow_curve.interpolate(sampleX)
		
	elif style == ItemToolTip.TextEffect.Shaky:
		shake(char_fx, shaky_speed, shaky_starttimeoffset, shaky_cycle, 
		shaky_curve, shaky_strength, 0.2, 200.0)
	
	elif style == ItemToolTip.TextEffect.Lightning:
		var phase = char_fx.absolute_index * - lightning_offset
		phase += char_fx.elapsed_time * lightning_speed - lightning_starttimeoffset
		var iteration = int(phase / lightning_cycle)
		var rng = rand(char_fx.absolute_index, iteration)
		var angle = rng * 200 * PI
		var tInIteration = fmod(phase - rng * 0.2, lightning_cycle)
		var strength = 0.5 + lightning_strength * rand1(rng)
		char_fx.offset += Vector2(lightning_curve.interpolate(
			tInIteration) * strength, 0).rotated(angle)
		char_fx.color = lightning_gradient.interpolate(tInIteration)
	
	elif style == ItemToolTip.TextEffect.Stompy:
		wave(char_fx, stompy_frequency, stompy_starttimeoffset, 
			stompy_speed, stompy_cycle, stompy_gradient, 
			stompy_curve, stompy_offset)
	
	elif style == ItemToolTip.TextEffect.Mercury:
		wave(char_fx, mercury_frequency, mercury_starttimeoffset, 
			mercury_speed, mercury_cycle, mercury_gradient, 
			mercury_curve, mercury_offset)
	
	elif style == ItemToolTip.TextEffect.Dog:
		shake(char_fx, dog_speed, dog_starttimeoffset, dog_cycle, 
			dog_curve, dog_strength, dog_randomness, 0)
	
	elif style == ItemToolTip.TextEffect.Dog2:
		var phase = shake(char_fx, dog_speed, dog_starttimeoffset, dog_cycle, 
			dog_curve, dog_strength, dog_randomness, 0)
		char_fx.color = dog_gradient.interpolate(phase)
	
	elif style == ItemToolTip.TextEffect.Spring:
		shake(char_fx, spring_speed, spring_starttimeoffset, spring_cycle, 
			spring_curve, spring_strength, spring_randomness, 0)
	
	elif style == ItemToolTip.TextEffect.Hyper:
		var phase = shake(char_fx, hyper_speed, hyper_starttimeoffset, hyper_cycle, 
			hyper_curve, hyper_strength, hyper_randomness, 0)
		char_fx.color = hyper_gradient.interpolate(phase)
		
	return true

func setColorFromGradient(char_fx, gradient, speed, cycle, 
	rngFactor = 0.0, positionFactor = 1.0, preprocess = 0.0):
	
	var phase = preprocess + char_fx.absolute_index * positionFactor
	phase += char_fx.elapsed_time
	phase *= (1 + rand1(char_fx.absolute_index) * rngFactor) * speed
	var sampleX = fmod(phase, cycle)
	char_fx.color = gradient.interpolate(sampleX)
	return sampleX

func wave(char_fx, frequency, startTimeOffset, speed, 
		cycle, gradient, curve, offset):
	
	var phase = char_fx.absolute_index * - frequency
	phase += char_fx.elapsed_time - startTimeOffset
	phase *= speed
	var sampleX = fmod(phase, cycle)
	char_fx.color = gradient.interpolate(sampleX)
	char_fx.offset.y = - offset * curve.interpolate(sampleX)

func shake(char_fx, speed, startTimeOffset, cycle, curve, strength, 
			randomness, angleRange):
	
	var phase = char_fx.elapsed_time * speed - startTimeOffset
	var iteration = int(phase / cycle)
	var rng = rand(char_fx.absolute_index, iteration)
	var angle = rng * angleRange * PI
	var tInIteration = fmod(phase - rng * randomness, cycle)
	var totalStrength = 0.5 * rand1(rng) + strength
	char_fx.offset += Vector2(0, - curve.interpolate(
		tInIteration) * totalStrength).rotated(angle)
	return tInIteration
