class_name SQLiteWrapper





var SQLite = preload("res://addons/godot-sqlite/bin/gdsqlite.gdns")
var db

enum VerbosityLevel{
	QUIET = 0, 
	NORMAL = 1, 
	VERBOSE = 2, 
	VERY_VERBOSE = 3
}

func _init():
	db = SQLite.new()







var path: String setget set_path, get_path
func set_path(value: String) -> void :
	if db: db.path = value

func get_path() -> String:
	if db: return db.path
	return ""





var error_message: String setget set_error_message, get_error_message
func set_error_message(message: String) -> void :
	if db: db.error_message = message

func get_error_message() -> String:
	if db: return db.error_message
	return ""






var default_extension: String setget set_default_extension, get_default_extension
func set_default_extension(value: String) -> void :
	if db: db.default_extension = value

func get_default_extension() -> String:
	if db: return db.default_extension
	return ""





var foreign_keys: bool setget set_foreign_keys, get_foreign_keys
func set_foreign_keys(value: bool) -> void :
	if db: db.foreign_keys = value

func get_foreign_keys() -> bool:
	if db: return db.foreign_keys
	return false






var read_only: bool setget set_read_only, get_read_only
func set_read_only(value: bool) -> void :
	if db: db.read_only = value

func get_read_only() -> bool:
	if db: return db.read_only
	return false






var query_result: Array setget set_query_result, get_query_result
func set_query_result(value: Array) -> void :
	if db: db.query_result = value

func get_query_result() -> Array:
	if db: return db.query_result
	return []






var query_result_by_reference: Array setget set_query_result_by_reference, get_query_result_by_reference
func set_query_result_by_reference(value: Array) -> void :
	if db: db.query_result_by_reference = value

func get_query_result_by_reference() -> Array:
	if db: return db.query_result_by_reference
	return []





var last_insert_rowid: int setget set_last_insert_rowid, get_last_insert_rowid
func set_last_insert_rowid(value: int) -> void :
	if db: db.last_insert_rowid = value

func get_last_insert_rowid() -> int:
	if not db: return db.last_insert_rowid
	return - 1











var verbosity_level: int setget set_verbosity_level, get_verbosity_level
func set_verbosity_level( var value) -> void :
	if db: db.verbosity_level = value

func get_verbosity_level() -> int:
	if db: return db.verbosity_level
	return - 1





func open_db() -> bool:
	return db.open_db()


func close_db() -> void :
	db.close_db()



func query(query_string: String) -> bool:
	return db.query(query_string)




func query_with_bindings(query_string: String, param_bindings: Array) -> bool:
	return db.query_with_bindings(query_string, param_bindings)




func create_table(table_name: String, table_dictionary: Dictionary) -> bool:
	return db.create_table(table_name, table_dictionary)


func drop_table(table_name: String) -> bool:
	return db.drop_table(table_name)




func insert_row(table_name: String, row_dictionary: Dictionary) -> bool:
	return db.insert_row(table_name, row_dictionary)




func insert_rows(table_name: String, row_array: Array) -> bool:
	return db.insert_rows(table_name, row_array)




func select_rows(table_name: String, query_conditions: String, selected_columns: Array) -> Array:
	return db.select_rows(table_name, query_conditions, selected_columns)




func update_rows(table_name: String, query_conditions: String, updated_row_dictionary: Dictionary) -> bool:
	return db.update_rows(table_name, query_conditions, updated_row_dictionary)






func delete_rows(table_name: String, query_conditions: String) -> bool:
	return db.delete_rows(table_name, query_conditions)


func import_from_json(import_path: String) -> bool:
	return db.import_from_json(import_path)


func export_to_json(export_path: String) -> bool:
	return db.export_to_json(export_path)



func create_function(function_name: String, function_reference: FuncRef, number_of_arguments: int) -> bool:
	return db.create_function(function_name, function_reference, number_of_arguments)




func get_autocommit() -> int:
	return db.get_autocommit()
