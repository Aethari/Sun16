-- Export Aseprite spritesheet to Sun16's `sdat` format
-- 2025 Aethari

-- == Functions ================================================

-- gets the provided color and returns the corresponding Sun16
-- palette index (integer 1-16)
local function color_index(pv)
	local pc = app.pixelColor

	local r = pc.rgbaR(pv)
	local b = pc.rgbaB(pv)
	local g = pc.rgbaG(pv)
	local a = pc.rgbaA(pv)

	-- white
	if r == 255 and g == 255 and b == 255 then
		return 1
	-- black
	elseif r == 0 and g == 0 and b == 0 and a > 0 then
		return 2
	-- gray
	elseif r == 178 and g == 178 and b == 178 then
		return 3
	-- red
	elseif r == 203 and g == 23 and b == 23 then
		return 4
	-- orange
	elseif r == 229 and g == 131 and b == 23 then
		return 5
	-- yellow
	elseif r == 228 and g == 233 and b == 27 then
		return 6
	-- green
	elseif r == 22 and g == 204 and b == 33 then
		return 7
	-- blue
	elseif r == 22 and g == 149 and b == 204 then
		return 8
	-- purple
	elseif r == 164 and g == 22 and b == 204 then
		return 9
	-- dark gray
	elseif r == 82 and g == 80 and b == 80 then
		return "a"
	-- dark red
	elseif r == 112 and g == 13 and b == 13 then
		return "b"
	-- brown
	elseif r == 130 and g == 60 and b == 17 then
		return "c"
	-- dark yellow
	elseif r == 201 and g == 178 and b == 22 then
		return "d"
	-- dark green
	elseif r == 32 and g == 108 and b == 37 then
		return "e"
	-- dark blue
	elseif r == 31 and g == 59 and b == 121 then
		return "f"
	-- dark purple
	elseif r == 85 and g == 18 and b == 104 then
		return "g"
	-- transparent
	else
		return 0
	end
end

-- == Script ===================================================
-- Code beyond this point is automatically ran

-- path dialog - asks user for output path
local pd = Dialog("Sun16 Spritesheet Exporter")

local filepath = app.fs.userDocsPath.."/spritesheet.sdat"
pd:entry{id="file_path", label = "Ouput file path:", text=filepath}
pd:button{id="confirm", text="Confirm"}
pd:button{id="cancel", text="Cancel"}
pd:show()

local pd_data = pd.data

if not pd_data.confirm then
	return
end

-- getting the image and confirming it exists
local img = app.image
if not img then
	app.alert("Error: No image found. Please run this script with an active image in the editor (i.e. not in the home tab)")
	return
end

-- getting the cel and confirming it exists
local cel = app.cel
if not cel then
	app.alert("Error: No cel found. Please run this script with an active sprite in the editor (i.e. not in the home tab)")
	return
end

-- open the sdat file at the specified path, creating it if it doesn't exist
local out = io.open(pd_data.file_path, "w")

-- generate the output using the sprite
for y = 0, 255 do
	for x = 0, 255 do
		local img_x = x - cel.position.x
		local img_y = y - cel.position.y

		local pix_value = 0

		if
			img_x > -1 and
			img_x < img.width and
			img_y > -1 and
			img_y < img.height
		then
			pix_value = img:getPixel(img_x, img_y)
		end

		local col_index = color_index(pix_value)
		out:write(col_index)
	end
	out:write("\n")
end

out:close()
