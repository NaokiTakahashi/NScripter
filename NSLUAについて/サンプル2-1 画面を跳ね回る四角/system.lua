function NSCOM_animestart()
	x=100
	y=100
	vx=-8
	vy=-8
	NSExec("erasetextwindow 0") --これがないと、テキスト文字が消えてしまうので
	NSExec("lsp 0,\":c;>50,50,#FF0000\",0,0")
	NSExec("print 1")
	NSLuaAnimationMode(true);
end

function NSCOM_animestop()
	NSLuaAnimationMode(false);
	NSExec("vsp 0,0")
	NSExec("print 1")
end

function NSCALL_animation ()
	x=x+vx;
	y=y+vy;
	if (x<0) then x=0 vx=-vx end
	if (y<0) then y=0 vy=-vy end
	if (x>590) then x=590 vx=-vx end
	if (y>430) then y=430 vy=-vy end
	NSExec("amsp 0,"..x..","..y)
	NSExec("print 1")
	return true
end
