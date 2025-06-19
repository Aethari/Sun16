-- Export Aseprite tilemap to Sun16's `sdat` format
-- 2025 Aethari

-- path dialog - asks user for output path
local pd = Dialog("Sun16 Tilemap Exporter")

local filepath = app.fs.userDocsPath.."/tilemap.sdat"
pd:entry{id="file_path", label = "Output file path:", text=filepath}
pd:button{id="confirm", text = "Confirm"}
pd:button{id="cancel", text = "Cancel"}
pd:show()

local pd_data = pd.data

if not pd_data.confirm then return end

-- getting the layer and confirming it exists
local layer = app.activeLayer
if not layer then
	app.alert("Error: No layer found. Please run this script with an active sprite in the editor (i.e. not in the home tab)")
	return
end

if not layer.isTilemap then
	app.alert("Error: Active layer is not a tilemap. Please make sure you have properly set up your tilemap.")
	return
end

-- getting the cel and confirming it exists
local cel = app.cel
if not cel then
	app.alert("Error: No cel found. Plase run this script with an active sprite in the editor (i.e. not in the home tab)")
	return
end

-- getting the image and confirming it exists
local img = cel.image
if not img then
	app.alert("Error: No image found. Please run this script with an active sprite in the editor (i.e. not in the home tab)")
	return
end

-- open the sdat file at the specified path, creating it if it doesn't exist
local out = io.open(pd_data.file_path, "w")

-- generate the output using the tilemap
for y = 0, img.height-1 do
	for x = 0, img.width-1 do
		local img_x = x - cel.position.x
		local img_y = y - cel.position.y

		local index = img:getPixel(x, y)
		if index >= 0 and index <= 256 then
			out:write(index..",")
		else 
			out:write("0,")
		end
	end
	out:write("\n")
end

out:close()
