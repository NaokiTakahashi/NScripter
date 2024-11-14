function NSCOM_sub ()
	local x,y,l
	while true do
		if NSDoEvents() then return end
		NSSleep(1)
		x,y=NSGetMouse()
		NSExec("caption \""..x..","..y.."\"")
		l=NSGetClick()
		if l then return end
		if NSGetKey("z") then return end
	end
end

