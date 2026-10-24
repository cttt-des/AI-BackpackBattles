extends Node
class_name SteamLeaderboard

var findRetries = 0
var leaderboardHandle
var ugcQueryHandle = 0
var gotResponse = false
var isComplete = false
var largestSequenceNumber = 0
var parsedRuns = []
var ugcHandles = []
var numPages: int
var curPage = 0
var downloading = false
var downloadQueued = false
const PAGESIZE = 1000

func _ready():
	Steam.connect("leaderboard_find_result", self, "onSteamLeaderboardFindResult")
	Steam.connect("leaderboard_scores_downloaded", self, "onSteamLeaderboardDownloaded")
	Steam.connect("leaderboard_score_uploaded", self, "onSteamLeaderboardUploaded")
	Steam.connect("leaderboard_ugc_set", self, "onSteamLeaderboardUGCSet")
	Steam.connect("ugc_query_completed", self, "onQueryCompleted")
	
	Steam.findLeaderboard(RunDatabase.getLeaderboard())

func onSteamLeaderboardFindResult(handle: int, found: int) -> void :
	if found == 1:
		Util.eprint("Steam handle found.")
		leaderboardHandle = handle
		if downloadQueued:
			downloadScores()
	else:
		print("No steam handle was found.")
		if findRetries < 3:
			findRetries += 1
			print("Trying again.")
			Steam.findLeaderboard(RunDatabase.getLeaderboard())


func downloadScores():
	if downloading: return
	
	if leaderboardHandle:
		Util.eprint("Downloading runs")
		downloading = true
		downloadQueued = false
		
		
		var numRuns = 2000
		if RunDatabase.statisticsMode:
			numRuns = 60000
		Steam.downloadLeaderboardEntries(0, numRuns, 0, leaderboardHandle)
	else:
		downloadQueued = true

func onSteamLeaderboardDownloaded(message: String, leaderboard_handle: int, leaderboard_entries_array: Array) -> void :
	
	
	isComplete = false
	parsedRuns.clear()
	ugcHandles.clear()
	curPage = 0
	
	Util.eprint("#entries: ", leaderboard_entries_array.size())
	
	for entry in leaderboard_entries_array:
		var ugcHandle = Util.twoIntsToLong(entry.details)
		
		if ugcHandle != 0:
			
			
			ugcHandles.push_back(ugcHandle)
		largestSequenceNumber = max(entry.score + 1, largestSequenceNumber)
	
	gotResponse = true
	
	Util.eprint("#handles = ", ugcHandles.size())
	
	if not ugcHandles.empty():
		numPages = ceil(ugcHandles.size() / float(PAGESIZE))
		requestUGCs()



func requestUGCs():
	var startIndex = curPage * PAGESIZE
	var endIndex = min(ugcHandles.size() - 1, startIndex + PAGESIZE - 1)
	var ugcIds = ugcHandles.slice(startIndex, endIndex)
	
	
	curPage += 1
	
	
	ugcQueryHandle = Steam.createQueryUGCDetailsRequest(ugcIds)
	Steam.setReturnMetadata(ugcQueryHandle, true)
	Steam.sendQueryUGCRequest(ugcQueryHandle)















func onQueryCompleted(handle, result, results_returned, 
	total_matching, cached: bool):
	
	if handle != ugcQueryHandle:
		
		return
	
	Util.eprint("Query completed. # results = ", results_returned)
	
	
	parseMetadata(handle, results_returned, parsedRuns, false)
	
	Steam.releaseQueryUGCRequest(handle)
	ugcQueryHandle = 0
	
	if curPage < numPages:
		
		requestUGCs()
	else:
		
		finalize()


func parseMetadata(handle: int, results_returned: int, runArr: Array, lobbyMode: bool):
	var noMetadata = 0
	var outdatedRuns = 0
	var malformed = 0
	
	for i in results_returned:
		var metadata = Steam.getQueryUGCMetadata(handle, i)
		if metadata:
			if metadata.length() > 50:
				
				var parsed = JSON.parse(metadata)
				if parsed.error == OK or typeof(parsed.result) == TYPE_DICTIONARY:
					var dict = parsed.result
					dict["ugc"] = 1
					var runData = RunDatabase.parseSingleScore(dict, true, lobbyMode)
					if runData:
						runArr.push_back(runData)
					else:
						outdatedRuns += 1
				else:
					
					Util.eprint("JSON ERROR: ", parsed.error_string)
					Util.eprint(metadata)
					malformed += 1
			else:
				Util.eprint("metadata too short: ", metadata)
				malformed += 1
		else:
			noMetadata += 1
	
	
	print("metadata: ", outdatedRuns, ", ", malformed, ", ", noMetadata)

func finalize():
	isComplete = true
	downloading = false
	RunDatabase.onSteamRunsReceived()
	
	

func hasRuns() -> bool:
	return not parsedRuns.empty()



var steamMetaDataString
var sequenceNumber
var ugcItem


func pushScore(_steamMetaDataString: String, _sequenceNumber: int):
	steamMetaDataString = _steamMetaDataString
	sequenceNumber = _sequenceNumber
	ugcItem = UGCItem.new(steamMetaDataString)
	ugcItem.connect("item_updated", self, "onUgcUpdated")
	add_child(ugcItem)

func onUgcUpdated():
	var details = Util.longTo2Ints(ugcItem.get_id())
	
	Steam.uploadLeaderboardScore(sequenceNumber, true, details, leaderboardHandle)

func onSteamLeaderboardUploaded(result: int, this_handle: int, this_score: Dictionary) -> void :
	if result == 1:
		print("Success")
	else:
		print("Failed")

func onSteamLeaderboardUGCSet(leaderboard_handle, result: String):
	print("Steam leaderboard set UGC: ", result)
