#include "stdafx.h"

int CDebugSettings::m_RefCount = 0; 

bool CDebugSettings::m_bHaveDebugger = false;
bool CDebugSettings::m_bLogX86Code = false;
bool CDebugSettings::m_bShowTLBMisses = false;

CDebugSettings::CDebugSettings()
{
	m_RefCount += 1;
	if (m_RefCount == 1)
	{
		_Settings->RegisterChangeCB(Debugger_Enabled,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		_Settings->RegisterChangeCB(Debugger_GenerateLogFiles,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		_Settings->RegisterChangeCB(Debugger_ShowTLBMisses,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		
		RefreshSettings();
	}
}

CDebugSettings::~CDebugSettings()
{
	m_RefCount -= 1;
	if (m_RefCount == 0)
	{
		_Settings->UnregisterChangeCB(Debugger_Enabled,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		_Settings->UnregisterChangeCB(Debugger_GenerateLogFiles,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		_Settings->UnregisterChangeCB(Debugger_ShowTLBMisses,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
	}
}

void CDebugSettings::RefreshSettings()
{
	m_bHaveDebugger = _Settings->LoadBool(Debugger_Enabled);
	m_bLogX86Code = _Settings->LoadBool(Debugger_GenerateLogFiles);
	m_bShowTLBMisses = _Settings->LoadBool(Debugger_ShowTLBMisses);
}