extends Reference

const MAX_RUNS = 1000
const SQLite = preload("res://addons/godot-sqlite/bin/gdsqlite.gdns")
const db_name = "user://{ID}{build}history"

var db


const verbose = false

func _init():
	Game.connect("fresh_run_started", self, "addRunEntry")
	Game.connect("round_result", self, "addRoundEntry")
	Game.connect("special_item_bought", self, "onSpecialItemBought")
	
	db = SQLite.new()
	
	db.verbosity_level = 0
	if SteamHelper.is_init() and SteamHelper.isIDValid():
		db.path = Game.expandPath(db_name, SteamHelper.STEAM_ID, true)
	else:
		db.path = Game.expandPath(db_name, null, true)
	
	db.open_db()
	
	var hasError: bool = db.error_message != ""
	var create = false
	
	
	var saveStateVersion = Game.getSavestateVersion()
	if saveStateVersion == null:
		create = true
	elif not Util.laterOrEqual(saveStateVersion, Game.runStateBreakingVersion):
		create = true
	elif not verifyTables():
		create = true
	
	if create:
		createTables()
	









const tableSchemas = {
	"runData": "CREATE TABLE runData (runID int, class int, loadout int, rank int, version int, time int, subclass int, skill1 int, skill2 int, custom text, PRIMARY KEY(runID))", 
	"roundData": "CREATE TABLE roundData (runID int, roundID int, result int, tries int, health int, stamina int, buildInfo text, PRIMARY KEY(runID, roundID))"
}

func verifyTables() -> bool:
	db.query("pragma integrity_check;")
	print(db.query_result)
	
	db.query("SELECT name, sql FROM sqlite_schema WHERE type='table';")
	var ok = 0
	for dict in db.query_result:
		var tableName = dict["name"]
		if not tableName in tableSchemas:
			return false
		elif tableSchemas[tableName] != dict["sql"]:
			return false
		else:
			ok += 1
	
	return ok == tableSchemas.size()

func createTables():
	
	db.query("drop table if exists runData")
	db.query("drop table if exists roundData")
	
	db.query(tableSchemas["roundData"])
	db.query(tableSchemas["runData"])
	
	if verbose:
		print("CREATE DB")

func addRunEntry():
	cleanup()
	
	var dict = {}
	dict["version"] = Game.versionToInt()
	
	dict["class"] = Game.curClass
	if Game.randomCharacter:
		dict["loadout"] = Game.Loadout.RandomCharacter
	else:
		dict["loadout"] = Game.curLoadout
	
	if Game.curMode == Game.Mode.Ranked:
		dict["rank"] = Game.getRunRating(Game.curClass)
	elif Game.isRankedSwitchMode():
		dict["rank"] = Game.getSwitchModeRating()
	elif Game.curMode == Game.Mode.Unranked:
		dict["rank"] = - 1
	elif Game.curMode == Game.Mode.Lobbies:
		dict["rank"] = - 2
	dict["runID"] = Game.getNumStartedRuns()
	dict["time"] = int(Time.get_unix_time_from_system())
	dict["custom"] = CustomRules.serialize()
	
	db.insert_row("runData", dict)
	
	if verbose:
		print("RUN ENTRY ", dict)

func onSpecialItemBought(item):
	var dict = {}
	
	var runID = Game.getRunState()["id"]
	var queryConditions = "RunID == " + String(runID)
	
	if Game.curRound == Game.SUBCLASS_ROUND:
		dict["subclass"] = item.descriptor.itemIndex
	elif Game.curRound == Game.SKILL_ROUND1:
		dict["skill1"] = item.descriptor.itemIndex
	elif Game.curRound == Game.SKILL_ROUND2:
		dict["skill2"] = item.descriptor.itemIndex
	
	if not dict.empty():
		var success = db.update_rows("runData", queryConditions, dict)
		if verbose:
			print("updated db: ", dict)


func addRoundEntry():
	var dict = {}
	var curRound = Game.curRound - 1
	dict["roundID"] = curRound
	dict["result"] = Game.roundResults[Game.curRound - 2]
	dict["tries"] = Game.getTries()
	dict["health"] = Game.PLAYER.getBaseMaxHealth()
	dict["stamina"] = Game.PLAYER.getBaseMaxStamina()
	dict["buildInfo"] = RunDatabase.getRoundData(Game.curRound - 2)
	dict["runID"] = Game.getRunState()["id"]
	db.insert_row("roundData", dict)
	if verbose:
		print("ROUND ENTRY ", dict)

func addRunResult():
	pass

func readRunHistory() -> Dictionary:
	
	
	var runs = {}
	
	db.query("select * from runData;")
	
	var runResults = db.query_result
	var numRuns = runResults.size()
	
	for i in range(numRuns):
		
		var runData = runResults[i]
		if verbose:
			print(runData)
		
		var buildHistoryData = BuildHistoryData.new()
		buildHistoryData.version = runData["version"]
		buildHistoryData.time = runData["time"]
		buildHistoryData.customRules = runData["custom"]
		buildHistoryData.classI = runData["class"]
		buildHistoryData.loadout = runData["loadout"]
		buildHistoryData.id = runData["runID"]
		buildHistoryData.subclassIndex = runData["subclass"]
		buildHistoryData.skill1Index = runData["skill1"]
		buildHistoryData.skill2Index = runData["skill2"]
		var rank = runData["rank"]
		if rank == - 1:
			buildHistoryData.mode = Game.Mode.Unranked
		elif rank == - 2:
			buildHistoryData.mode = Game.Mode.Lobbies
		else:
			buildHistoryData.mode = Game.Mode.Ranked
			buildHistoryData.rating = runData["rank"]
		runs[buildHistoryData.id] = buildHistoryData
	
	if verbose:
		print("----")
	
	db.query("select * from roundData;")
	var results = db.query_result
	var numRounds = results.size()
	
	
	for i in range(numRounds):
		
		var roundData = results[i]
		if verbose:
			print(roundData)
		
		
		
		var run = runs.get(roundData["runID"], null)
		
		if run != null:
			
			var valid = true
			for entry in roundData:
				if roundData[entry] == null:
					runs.erase(roundData["runID"])
					print("History error: ", entry, " == ", null)
					valid = false
					break
			
			if not valid: continue
			
			run.addRoundData(roundData["roundID"], roundData["result"], 
				roundData["tries"], roundData["health"], 
				roundData["stamina"], roundData["buildInfo"])
	
	if verbose:
		print("----")
	
	return runs

func cleanup():
	
	
		
	var cutoff = Game.getNumStartedRuns() - MAX_RUNS
	
	db.query("delete from runData where runId<" + str(cutoff))
	db.query("delete from roundData where runId<" + str(cutoff))
	
	if Game.getNumStartedRuns() % 1000 == 0:
		db.query("vacuum")






























