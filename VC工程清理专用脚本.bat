@echo off
@rem by: yliu2
@for /r %%i in (
*.aps *.idb *.ncb *.obj *.pch *.sbr *.tmp *.pdb *.bsc *.ilk *.res
*.sdf *.dep *.ipch *.tlog *.exp *.hpj *.opt *.mdp *.plg *.clw
) do del /f /q "%%i"
@echo ������ɣ�
@pause>nul



