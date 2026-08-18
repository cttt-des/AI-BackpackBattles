extends Reference
class_name FontData



var font = null
var size
var spaceTop
var spaceBottom

var bold_font = null
var bold_size
var bold_spaceTop
var bold_spaceBottom

var curLocale: = ""

func setFont(normalFont: DynamicFont) -> void :
	if normalFont:
		font = normalFont.font_data
		size = normalFont.size
		spaceTop = normalFont.extra_spacing_top
		spaceBottom = normalFont.extra_spacing_bottom

func setBoldFont(boldFont: DynamicFont) -> void :
	if boldFont:
		bold_font = boldFont.font_data
		bold_size = boldFont.size
		bold_spaceTop = boldFont.extra_spacing_top
		bold_spaceBottom = boldFont.extra_spacing_bottom

func applyToFont(normalFont: DynamicFont) -> void :
	normalFont.font_data = font
	normalFont.size = size
	normalFont.extra_spacing_top = spaceTop
	normalFont.extra_spacing_bottom = spaceBottom

func applyToBoldFont(boldFont: DynamicFont) -> void :
	boldFont.font_data = bold_font
	boldFont.size = bold_size
	boldFont.extra_spacing_top = bold_spaceTop
	boldFont.extra_spacing_bottom = bold_spaceBottom
