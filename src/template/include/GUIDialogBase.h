#pragma once
/*
 *      Copyright (C) 2005-2014 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "client.h"
#include <string>
#include <libKODI_guilib.h>

class CGUIDialogBase
{
public:
	CGUIDialogBase( std::string xmlFilename, bool ForceFallback, bool AsDialog, std::string DefaultSkin = "Confluence" );
	virtual ~CGUIDialogBase();

	bool Show();
	void Close();
	void DoModal();

private:
	static bool OnClickCB(GUIHANDLE cbhdl, int controlId);
	static bool OnFocusCB(GUIHANDLE cbhdl, int controlId);
	static bool OnInitCB(GUIHANDLE cbhdl);
	static bool OnActionCB(GUIHANDLE cbhdl, int actionId);

protected:
	CAddonGUIWindow          *m_window;	// window handle

private:	// private virtual methods
	virtual bool OnInit()               = 0;
	virtual bool OnClick(int controlId) = 0;
	virtual bool OnFocus(int controlId) = 0;
	virtual bool OnAction(int actionId) = 0;
  virtual void OnClose()              = 0;
};
