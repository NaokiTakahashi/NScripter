function NSCOM_test1()
	NSOkBox("������test1���Ă΂�Ă܂���[","���ʕ\��")
	NSExec("bg #883333,10,500") --���߂����s�ł��܂��B
	-- ���Ȃ݂ɁA�����񒆂�"�����������ꍇ��\"�Ƃ��܂��B
	-- �ڂ����́ALua�̓��发�������m���߂��������B
end

function NSCOM_test2()
	local str=NSPopStr()
	NSOkBox("test2�������u"..str.."�v�ŌĂ΂�܂�����[","���ʕ\��")
end

function NSCOM_test3()
	local iindex=NSPopIntRef()
	NSPopComma()
	local str=NSPopStr()
	NSOkBox("test3�������Q�u"..str.."�v�ŌĂ΂�܂�����[","���ʕ\��")
	NSSetIntValue(iindex,10)
end

function NSCOM_test4()
	if (NSYesNoBox("goto *label���܂����H","�W�����v�m�F")==true) then
		NSGoto("*label")
	end
end