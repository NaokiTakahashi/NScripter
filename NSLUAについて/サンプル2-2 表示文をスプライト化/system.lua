function NSCALL_tag (tag)
	if (tag~="") then
		NSExec("lsp 100,\":s/20,20,0;#FFFFFF"..tag.."\",20,300")
		--lsp 100,":s/20,20,0;#FFFFFF(タグ文字列)",20,300 を呼んでいます。
	else
		NSExec("csp 100")
	end
end

function NSCALL_text (text)
	NSExec("strsp 101,\""..text.."\",28,322,25,4,22,22,0,0,0,0,#FFFFFF")
	--strsp 101,"(表示文字列)",28,322,～　を呼んでいます。
	NSExec("print 1")
	NSGosub ("*textbtn") --サブルーチンコールしています。
end