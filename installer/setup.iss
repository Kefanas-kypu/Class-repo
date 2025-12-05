; setup.iss - instaliacijos skriptas Inno Setup

#define MyAppName "Studentų rūšiavimo sistema"
#define MyAppVersion "3.0"
#define MyAppPublisher "VU - Kevinas Kuznecovas"
#define MyAppExeName "studentu_app.exe"
#define MyAppDirName "VU\\Kevinas-Kuznecovas"

[Setup]
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
; ČIA SVARBU: pataisyk kelią iki savo exe ir dll.
; Jei po CMake turi build\studentu_app.exe ir build\Skaiciavimai.dll, naudok taip:

Source: "build\studentu_app.exe"; De_
