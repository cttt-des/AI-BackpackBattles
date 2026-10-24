extends Node
class_name UGCItem


signal item_updated
signal item_creation_failed
signal item_update_failed

var itemId: int
var metaDataString
var updateHandle
var tags: Array

enum Result{
	RESULT_OK = 1, RESULT_FAIL = 2, RESULT_NO_CONNECTION = 3, RESULT_INVALID_PASSWORD = 5, RESULT_LOGGED_IN_ELSEWHERE = 6, RESULT_INVALID_PROTOCOL_VER = 7, RESULT_INVALID_PARAM = 8, RESULT_FILE_NOT_FOUND = 9, RESULT_BUSY = 10, RESULT_INVALID_STATE = 11, RESULT_INVALID_NAME = 12, RESULT_INVALID_EMAIL = 13, RESULT_DUPLICATE_NAME = 14, RESULT_ACCESS_DENIED = 15, RESULT_TIMEOUT = 16, RESULT_BANNED = 17, RESULT_ACCOUNT_NOT_FOUND = 18, RESULT_INVALID_STEAM_ID = 19, RESULT_SERVICE_UNAVAILABLE = 20, RESULT_NOT_LOGGED_ON = 21, RESULT_PENDING = 22, RESULT_ENCRYPTION_FAILURE = 23, RESULT_INSUFFICIENT_PRIVILEGE = 24, RESULT_LIMIT_EXCEEDED = 25, RESULT_REVOKED = 26, RESULT_EXPIRED = 27, RESULT_ALREADY_REDEEMED = 28, RESULT_DUPLICATE_REQUEST = 29, RESULT_ALREADY_OWNED = 30, RESULT_IP_NOT_FOUND = 31, RESULT_PERSIST_FAILED = 32, RESULT_LOCKING_FAILED = 33, RESULT_LOG_ON_SESSION_REPLACED = 34, RESULT_CONNECT_FAILED = 35, RESULT_HANDSHAKE_FAILED = 36, RESULT_IO_FAILURE = 37, RESULT_REMOTE_DISCONNECT = 38, RESULT_SHOPPING_CART_NOT_FOUND = 39, RESULT_BLOCKED = 40, RESULT_IGNORED = 41, RESULT_NO_MATCH = 42, RESULT_ACCOUNT_DISABLED = 43, RESULT_SERVICE_READ_ONLY = 44, RESULT_ACCOUNT_NOT_FEATURED = 45, RESULT_ADMINISTRATOR_OK = 46, RESULT_CONTENT_VERSION = 47, RESULT_TRY_ANOTHER_CM = 48, RESULT_PASSWORD_REQUIRED_TO_KICK_SESSION = 49, RESULT_ALREADY_LOGGED_IN_ELSEWHERE = 50, RESULT_SUSPENDED = 51, RESULT_CANCELLED = 52, RESULT_DATA_CORRUPTION = 53, RESULT_DISK_FULL = 54, RESULT_REMOTE_CALL_FAILED = 55, RESULT_PASSWORD_UNSET = 56, RESULT_EXTERNAL_ACCOUNT_UNLINKED = 57, RESULT_PSN_TICKET_INVALID = 58, RESULT_EXTERNAL_ACCOUNT_ALREADY_LINKED = 59, RESULT_REMOTE_FILE_CONFLICT = 60, RESULT_ILLEGAL_PASSWORD = 61, RESULT_SAME_AS_PREVIOUS_VALUE = 62, RESULT_ACCOUNT_LOG_ON_DENIED = 63, RESULT_CANNOT_USE_OLD_PASSWORD = 64, RESULT_INVALID_LOGIN_AUTH_CODE = 65, RESULT_ACCOUNT_LOG_ON_DENIED_NO_MAIL = 66, RESULT_HARDWARE_NOT_CAPABLE_OF_IPT = 67, RESULT_IPT_INIT_ERROR = 68, RESULT_PARENTAL_CONTROL_RESTRICTED = 69, RESULT_FACEBOOK_QUERY_ERROR = 70, RESULT_EXPIRED_LOGIN_AUTH_CODE = 71, RESULT_IP_LOGIN_RESTRICTION_FAILED = 72, RESULT_ACCOUNT_LOCKED_DOWN = 73, RESULT_ACCOUNT_LOG_ON_DENIED_VERIFIED_EMAIL_REQUIRED = 74, RESULT_NO_MATCHING_URL = 75, RESULT_BAD_RESPONSE = 76, RESULT_REQUIRE_PASSWORD_REENTRY = 77, RESULT_VALUE_OUT_OF_RANGE = 78, RESULT_UNEXPECTED_ERROR = 79, RESULT_DISABLED = 80, RESULT_INVALID_CEG_SUBMISSION = 81, RESULT_RESTRICTED_DEVICE = 82, RESULT_REGION_LOCKED = 83, RESULT_RATE_LIMIT_EXCEEDED = 84, RESULT_ACCOUNT_LOGIN_DENIED_NEED_TWO_FACTOR = 85, RESULT_ITEM_DELETED = 86, RESULT_ACCOUNT_LOGIN_DENIED_THROTTLE = 87, RESULT_TWO_FACTOR_CODE_MISMATCH = 88, RESULT_TWO_FACTOR_ACTIVATION_CODE_MISMATCH = 89, RESULT_ACCOUNT_ASSOCIATED_TO_MULTIPLE_PARTNERS = 90, RESULT_NOT_MODIFIED = 91, RESULT_NO_MOBILE_DEVICE = 92, RESULT_TIME_NOT_SYNCED = 93, RESULT_SMS_CODE_FAILED = 94, RESULT_ACCOUNT_LIMIT_EXCEEDED = 95, RESULT_ACCOUNT_ACTIVITY_LIMIT_EXCEEDED = 96, RESULT_PHONE_ACTIVITY_LIMIT_EXCEEDED = 97, RESULT_REFUND_TO_WALLET = 98, RESULT_EMAIL_SEND_FAILURE = 99, RESULT_NOT_SETTLED = 100, RESULT_NEED_CAPTCHA = 101, RESULT_GSLT_DENIED = 102, RESULT_GS_OWNER_DENIED = 103, RESULT_INVALID_ITEM_TYPE = 104, RESULT_IP_BANNED = 105, RESULT_GSLT_EXPIRED = 106, RESULT_INSUFFICIENT_FUNDS = 107, RESULT_TOO_MANY_PENDING = 108
}

func _init(_metaDataString = "", _itemId: int = 0, 
	_tags = []) -> void :
	
	metaDataString = _metaDataString
	tags = _tags
	var fileType = 15
	
	
	
	Steam.connect("item_updated", self, "_on_item_updated")

	if _itemId == 0:
		if tags.empty():
			Steam.connect("item_created", self, "_on_item_created")
		else:
			Steam.connect("item_created", self, "_on_item_created_lobbies")
		
		Steam.createItem(SteamHelper.APP_ID, fileType)
	else:
		itemId = _itemId
		start_update(_itemId)
		if metaDataString != "":
			set_metadata(metaDataString)

func start_update(_itemId: int = itemId) -> void :
	updateHandle = Steam.startItemUpdate(SteamHelper.APP_ID, _itemId)


func update(p_update_description: String = "") -> void :
	Steam.submitItemUpdate(updateHandle, p_update_description)


func set_title(p_title: String) -> void :
	if Steam.setItemTitle(updateHandle, p_title) == false:
		print("could not set title")


func set_description(p_description: String = "") -> void :
	if Steam.setItemDescription(updateHandle, p_description) == false:
		pass


func set_update_language(p_language: String) -> void :
	if Steam.setItemUpdateLanguage(updateHandle, p_language) == false:
		print("could not set language")


func set_visibility(p_visibility: int = 2) -> bool:
	Util.eprint("setting visibility to ", p_visibility)
	var res = Steam.setItemVisibility(updateHandle, p_visibility)
	if not res:
		print("could not set visibility")
	return res

func set_tags(p_tags: Array = []) -> bool:
	var res = Steam.setItemTags(updateHandle, p_tags)
	if not res:
		print("could not set tags")
	return res

func set_content(p_content: String) -> void :
	if Steam.setItemContent(updateHandle, p_content) == false:
		print("Could not set content")
	

func set_preview(p_image_preview: String = "") -> void :
	if Steam.setItemPreview(updateHandle, p_image_preview) == false:
		print("Could not set preview")


func set_metadata(p_metadata: String = "") -> bool:
	var res = Steam.setItemMetadata(updateHandle, p_metadata)
	if not res:
		print("Could not set metadata")
	return res

func get_id() -> int:
	return itemId


func _on_item_created_lobbies(result: int, _file_id: int, _accept_tos: bool) -> void :
	print("item created - result: ", result)
	
	itemId = _file_id





	start_update()
	set_title("Title2")
	set_tags(tags)
	set_visibility(0)
	set_metadata("Metadata")
	update()
	

func _on_item_created(result: int, _file_id: int, _accept_tos: bool) -> void :
	
	var success = (result == Result.RESULT_OK)
	
	if success:
		Util.eprint("item created")
		itemId = _file_id
		start_update()
		success = set_metadata(metaDataString)
		if success:
			success = set_visibility(3)
			if success:
				metaDataString = ""
				update()
				
	else:
		print("item creation failed: ", result)
	
	if not success:
		queue_free()
		emit_signal("item_creation_failed", result)


func _on_item_updated(result: int, _accept_tos: bool) -> void :
	if result == Result.RESULT_OK:
		
		Util.eprint("item updated")
		
		
		emit_signal("item_updated")
	else:
		print("item update failed: ", result)
		emit_signal("item_update_failed", result)
	
	queue_free()
