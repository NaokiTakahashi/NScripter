function NSCOM_test1()
	NSOkBox("ちゃんとtest1が呼ばれてますよー","結果表示")
	NSExec("bg #883333,10,500") --命令も実行できます。
	-- ちなみに、文字列中に"が書きたい場合は\"とします。
	-- 詳しくは、Luaの入門書等をお確かめください。
end

function NSCOM_test2()
	local str=NSPopStr()
	NSOkBox("test2が引数「"..str.."」で呼ばれましたよー","結果表示")
end

function NSCOM_test3()
	local iindex=NSPopIntRef()
	NSPopComma()
	local str=NSPopStr()
	NSOkBox("test3が引数２「"..str.."」で呼ばれましたよー","結果表示")
	NSSetIntValue(iindex,10)
end

function NSCOM_test4()
	if (NSYesNoBox("goto *labelしますか？","ジャンプ確認")==true) then
		NSGoto("*label")
	end
end