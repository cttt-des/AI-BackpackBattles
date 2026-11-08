## Fetch the public Steam opponent index and its UGC metadata into an isolated batch.
## Run through the packaged Windows runner with bounded UGC splitting, retry and payload-free diagnostics; no gameplay autoloads or save paths are used.
extends SceneTree

var deadline_ms = 115000
var range_start = 1
var range_end = 2000
const RETRY_DELAY_MS = 3000
const RETRY_RESULTS = [2, 3, 10, 16, 20, 35, 37, 38]
const SPLIT_RESULTS = [2, 16]
const SPLIT_SIZE = 500
const MAX_SPLITS = 2
const RESULT_NAMES = {
	1: "k_EResultOK", 2: "k_EResultFail", 3: "k_EResultNoConnection",
	8: "k_EResultInvalidParam", 9: "k_EResultFileNotFound", 10: "k_EResultBusy",
	15: "k_EResultAccessDenied", 16: "k_EResultTimeout", 17: "k_EResultBanned", 20: "k_EResultServiceUnavailable",
	21: "k_EResultNotLoggedOn", 24: "k_EResultInsufficientPrivilege", 25: "k_EResultLimitExceeded", 26: "k_EResultRevoked",
	35: "k_EResultConnectFailed", 37: "k_EResultIOFailure", 38: "k_EResultRemoteDisconnect", 43: "k_EResultAccountDisabled",
	84: "k_EResultRateLimitExceeded", 105: "k_EResultIPBanned"
}

var output_path: String
var leaderboard = 0
var query = 0
var ids = []
var seen_ids = {}
var page_ids = []
var page_start = 0
var split_end = 0
var request_started = 0
var started = 0
var finished = false
var initialized = false
var retry_used = false
var retry_at = -1
var page_attempt = 0
var response = {"status": "running", "pages": [], "entries": [], "metadata": [], "diagnostics": {"stage": "initialization", "elapsed_ms": 0, "request_count": 0, "split_count": 0, "attempts": []}}

func _init():
	var args = OS.get_cmdline_args()
	var marker = args.find("--")
	if marker < 0 or marker + 1 >= args.size():
		quit(2)
		return
	output_path = args[marker + 1]
	started = OS.get_ticks_msec()
	var manifest_file = File.new()
	if manifest_file.open(output_path.get_base_dir().plus_file("manifest.json"), File.READ) != OK:
		_fail("Invalid opponent request manifest")
		return
	var parsed = JSON.parse(manifest_file.get_as_text())
	manifest_file.close()
	if parsed.error != OK or typeof(parsed.result) != TYPE_DICTIONARY or not parsed.result.has("request"):
		_fail("Invalid opponent request manifest")
		return
	var request = parsed.result.request
	if typeof(request) != TYPE_DICTIONARY:
		_fail("Invalid opponent request manifest")
		return
	range_start = int(request.get("start", 0))
	range_end = int(request.get("end", 0))
	if range_start < 1 or range_end < range_start or range_end > 2147483647 or range_end - range_start + 1 > 60000 or request.get("app_id") != 2427700 or request.get("board") != "bpb-runs3" or request.get("type") != 0:
		_fail("Invalid opponent request manifest")
		return
	response["request"] = request
	if range_end - range_start + 1 > 2000:
		deadline_ms = 595000
	call_deferred("_start")

func _start():
	var init = Steam.steamInit(false)
	response["initialization"] = init
	if init.get("status", 0) != 1:
		response.diagnostics.initialization_status = init.get("status", 0)
		_fail("Steam initialization failed")
		return
	initialized = true
	_set_stage("session")
	response["app_id"] = str(Steam.getAppID())
	if Steam.getAppID() != 2427700 or not Steam.loggedOn():
		_fail("Expected an online Steam session for AppID 2427700")
		return
	Steam.connect("leaderboard_find_result", self, "_found")
	Steam.connect("leaderboard_scores_downloaded", self, "_entries")
	Steam.connect("ugc_query_completed", self, "_metadata")
	_set_stage("leaderboard")
	Steam.findLeaderboard("bpb-runs3")

func _idle(_delta):
	if not finished:
		if OS.get_ticks_msec() - started >= deadline_ms:
			_fail("Steam query timed out")
			return false
		if initialized:
			Steam.run_callbacks()
		if not finished and OS.get_ticks_msec() - started >= deadline_ms:
			_fail("Steam query timed out")
		elif not finished and retry_at >= 0 and OS.get_ticks_msec() >= retry_at:
			retry_at = -1
			_next_page(true)
	return false

func _found(handle, found):
	if finished or response.diagnostics.stage != "leaderboard":
		return
	if found != 1 or handle == 0:
		_fail("Leaderboard bpb-runs3 not found")
		return
	leaderboard = handle
	response["leaderboard_handle"] = str(handle)
	response["leaderboard_name"] = Steam.getLeaderboardName(handle)
	response["sort_method"] = Steam.getLeaderboardSortMethod(handle)
	response["leaderboard_entry_count"] = Steam.getLeaderboardEntryCount(handle)
	_set_stage("entries")
	_save()
	if not finished:
		Steam.downloadLeaderboardEntries(range_start, range_end, 0, handle)

func _entries(message, handle, entries):
	if finished or handle != leaderboard or response.diagnostics.stage != "entries":
		return
	response["entries_message"] = message
	response["entries_at_unix"] = OS.get_unix_time()
	response["entries"] = _json_safe(entries)
	response["leaderboard_entry_count"] = Steam.getLeaderboardEntryCount(handle)
	var expected = max(0, min(range_end, int(response.leaderboard_entry_count)) - range_start + 1)
	if entries.size() != expected:
		_fail("Missing, duplicate, or out-of-range leaderboard positions")
		return
	for index in entries.size():
		if int(entries[index].get("global_rank", -1)) != range_start + index:
			_fail("Missing, duplicate, or out-of-range leaderboard positions")
			return
	for entry in entries:
		var details = entry.get("details", [])
		if details.size() >= 2:
			var ugc_id = (int(details[0]) << 32) | (int(details[1]) & 0xffffffff)
			if ugc_id > 0 and not seen_ids.has(ugc_id):
				seen_ids[ugc_id] = true
				ids.append(ugc_id)
	_save()
	if entries.empty() and range_start > int(response.leaderboard_entry_count):
		_complete()
		return
	if ids.empty():
		_fail("Leaderboard returned no usable UGC references")
		return
	_next_page()

func _next_page(retrying = false):
	if finished:
		return
	if OS.get_ticks_msec() - started >= deadline_ms:
		_fail("Steam query timed out")
		return
	_set_stage("ugc")
	page_attempt = page_attempt + 1 if retrying else 1
	var end = min(page_start + 1000, ids.size())
	if page_start < split_end:
		end = min(page_start + SPLIT_SIZE, split_end)
	page_ids = ids.slice(page_start, end - 1)
	request_started = OS.get_ticks_msec()
	_page_result(0, 0)
	query = Steam.createQueryUGCDetailsRequest(page_ids)
	if query == 0 or query == -1:
		_fail("Could not create UGC details query")
		return
	if not Steam.setReturnMetadata(query, true):
		_fail("Could not request UGC metadata")
		return
	response.diagnostics.request_count += 1
	Steam.sendQueryUGCRequest(query)

func _metadata(handle, result, count, total, cached):
	if finished or query == 0 or handle != query:
		return
	if OS.get_ticks_msec() - started >= deadline_ms:
		_fail("Steam query timed out")
		return
	_page_result(result, count)
	var attempt = response.diagnostics.duplicate()
	attempt.erase("attempts")
	response.diagnostics.attempts.append(attempt)
	if result != 1 or count != page_ids.size():
		Steam.releaseQueryUGCRequest(query)
		query = 0
		var can_wait = OS.get_ticks_msec() - started + RETRY_DELAY_MS < deadline_ms
		if result in SPLIT_RESULTS and page_ids.size() > SPLIT_SIZE and response.diagnostics.split_count < MAX_SPLITS and can_wait:
			split_end = page_start + page_ids.size()  # Keep both children inside the failed request's original range.
			response.diagnostics.split_count += 1
			page_attempt = 0
			retry_at = OS.get_ticks_msec() + RETRY_DELAY_MS
			printerr("Splitting failed UGC page in 3000 ms: ", _context())
			_save()
		elif result in RETRY_RESULTS and not retry_used and can_wait:
			retry_used = true
			retry_at = OS.get_ticks_msec() + RETRY_DELAY_MS
			printerr("Retrying UGC page in 3000 ms: ", _context())
			_save()
		else:
			_fail("UGC request failed or returned an incomplete page")
		return
	var page = {"requested_ids": _json_safe(page_ids), "result": result, "count": count, "total": total, "cached": cached}
	var records = []
	for i in count:
		if OS.get_ticks_msec() - started >= deadline_ms:
			_fail("Steam query timed out")
			return
		var details = Steam.getQueryUGCResult(handle, i)
		records.append({"page": response.pages.size(), "index": i, "details": _json_safe(details), "metadata": Steam.getQueryUGCMetadata(handle, i)})
	if OS.get_ticks_msec() - started >= deadline_ms:
		_fail("Steam query timed out")
		return
	response.pages.append(page)
	response.metadata.append_array(records)
	Steam.releaseQueryUGCRequest(query)
	query = 0
	_save()
	page_start += page_ids.size()
	if page_start < ids.size():
		_next_page()
	else:
		_complete()

func _complete():
	response.status = "complete"
	_set_stage("complete")
	_save()
	_finish(0)

func _set_stage(stage):
	for key in ["error", "result", "error_name", "page", "attempt", "requested", "returned", "initialization_status", "request_offset", "request_elapsed_ms"]:
		response.diagnostics.erase(key)
	response.diagnostics.stage = stage
	response.diagnostics.elapsed_ms = OS.get_ticks_msec() - started

func _page_result(result, count):
	response.diagnostics.result = result
	response.diagnostics.error_name = RESULT_NAMES.get(result, "Unknown")
	response.diagnostics.page = response.pages.size() + 1
	response.diagnostics.attempt = page_attempt
	response.diagnostics.requested = page_ids.size()
	response.diagnostics.returned = count
	response.diagnostics.elapsed_ms = OS.get_ticks_msec() - started
	response.diagnostics.request_offset = page_start
	response.diagnostics.request_elapsed_ms = OS.get_ticks_msec() - request_started

func _context():
	var fields = []
	for key in ["stage", "result", "error_name", "initialization_status", "page", "attempt", "requested", "returned", "elapsed_ms", "request_offset", "request_elapsed_ms", "request_count", "split_count"]:
		if response.diagnostics.has(key):
			fields.append(key + "=" + str(response.diagnostics[key]))
	return PoolStringArray(fields).join(", ")

func _json_safe(value):
	if typeof(value) == TYPE_INT:
		return str(value)  # Preserve 64-bit IDs through Godot's JSON writer.
	if typeof(value) == TYPE_DICTIONARY:
		var result = {}
		for key in value:
			result[str(key)] = _json_safe(value[key])
		return result
	if typeof(value) == TYPE_ARRAY or typeof(value) == TYPE_INT_ARRAY:
		var result = []
		for item in value:
			result.append(_json_safe(item))
		return result
	return value

func _save():
	var file = File.new()
	if file.open(output_path, File.WRITE) != OK:
		_set_stage("output")
		printerr("Cannot write opponent response: ", _context())
		_finish(3)
		return
	var saved = response
	if response.status == "running":
		saved = {"status": "running", "request": response.get("request", {}), "diagnostics": response.diagnostics, "completed_pages": response.pages.size(), "received_entries": response.entries.size()}
	file.store_string(JSON.print(saved))
	file.close()

func _fail(message):
	if finished:
		return
	response.status = "failed"
	response["error"] = message
	response.diagnostics.error = message
	response.diagnostics.elapsed_ms = OS.get_ticks_msec() - started
	if query != 0:
		response.diagnostics.request_elapsed_ms = OS.get_ticks_msec() - request_started
	printerr(message, ": ", _context())
	_save()
	_finish(1)

func _finish(code):
	if finished:
		return
	finished = true
	retry_at = -1
	if query != 0:
		Steam.releaseQueryUGCRequest(query)
		query = 0
	call_deferred("_shutdown", code)  # Shutdown must run after Steam finishes dispatching callbacks.

func _shutdown(code):
	quit(code)  # The engine owns Steam shutdown; an explicit second shutdown exits with code 5.
