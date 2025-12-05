; setup.iss - instaliacijos skriptas Inno Setup

#define MyAppName "Studentų rūšiavimo sistema"
#define MyAppVersion "3.0"
#define MyAppPublisher "VU - Kevinas Kuznecovas"
#define MyAppExeName "studentu_app.exe"
#define MyAppDirName "VU\\Kevinas-Kuznecovas"

[Setup]
; Unikalus ID (gali palikti šitą)
AppId={{A1B2C3D4-E5F6-47A8-90AB-1234567890AB}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}

; C:\Program Files\VU\Kevinas-Kuznecovas
DefaultDirName={pf}\{#MyAppDirName}

; Start Menu grupė: VU -> Kevinas-Kuznecovas
DefaultGroupName=VU\Kevinas-Kuznecovas

OutputBaseFilename=Setup
Compression=lzma
SolidCompression=yes

; Admin teisės diegikliui
PrivilegesRequired=admin

[Files]
; build katalogas yra vienu lygiu aukščiau už installer, todėl reikia ..\build\...
Source: "..\build\studentu_app.exe";    DestDir: "{app}"; Flags: ignoreversion
Source: "..\build\libSkaiciavimai.dll"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
; Start Menu nuoroda
Name: "{group}\Studentų rūšiavimo sistema"; Filename: "{app}\{#MyAppExeName}"

; Darbalaukio nuoroda
Name: "{commondesktop}\Studentų rūšiavimo sistema"; Filename: "{app}\{#MyAppExeName}"

[Run]
; Paleisti programą po diegimo
Filename: "{app}\{#MyAppExeName}"; Description: "Paleisti programą dabar"; Flags: nowait postinstall skipifsilent
