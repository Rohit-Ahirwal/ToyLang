!include "MUI.nsh"

Name "ToyLang"
OutFile "ToyLangInstaller.exe"
InstallDir "$PROGRAMFILES\ToyLang"

!define MUI_ICON "..\..\asset\ToyLang.ico"
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "..\LICENSE"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

Section "Install ToyLang" 
    SetOutPath "$INSTDIR"

    File "..\..\build\Release\ToyLang.exe"
    WriteRegStr HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment" "Path" "$INSTDIR;$%PATH%"
    System::Call 'Kernel32::SetEnvironmentVariableA(t, t) i("Path", "$INSTDIR;$%PATH%").r0'

SectionEnd

Section "Unistall" 
    Delete "$INSTDIR\*.*"

    RMDir "$INSTDIR"

    DeleteRegKey HKLM "Software\ToyLang"
    System::Call 'Kernel32::SetEnvironmentVariableA(t, t) i("Path", "$%PATH%").r0'
SectionEnd