static func getRandomInt(max_value):
	randomize()
	return randi() % max_value

static func randomBytes(n):
	var r = []
	for index in range(0, n):
		r.append(getRandomInt(256))
	return r

static func uuidbin():
	var b = randomBytes(16)
	
	b[6] = (b[6] & 15) | 64
	b[8] = (b[8] & 63) | 128
	return b

static func generate_uuid_v4():
	var b = uuidbin()
	
	var low = "%02x%02x%02x%02x" % [b[0], b[1], b[2], b[3]]
	var mid = "%02x%02x" % [b[4], b[5]]
	var hi = "%02x%02x" % [b[6], b[7]]
	var clock = "%02x%02x" % [b[8], b[9]]
	var node = "%02x%02x%02x%02x%02x%02x" % [b[10], b[11], b[12], b[13], b[14], b[15]]
	return "%s-%s-%s-%s-%s" % [low, mid, hi, clock, node]
	
	

static func is_uuid(test_string):
	
	return test_string.length() == 36 and test_string.count("-") == 4















