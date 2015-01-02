/*
	Copyright (c) 2011, pGina Team
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
		* Redistributions of source code must retain the above copyright
		  notice, this list of conditions and the following disclaimer.
		* Redistributions in binary form must reproduce the above copyright
		  notice, this list of conditions and the following disclaimer in the
		  documentation and/or other materials provided with the distribution.
		* Neither the name of the pGina Team nor the names of its contributors 
		  may be used to endorse or promote products derived from this software without 
		  specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once

#include "TileUiTypes.h"

namespace pGina
{
	namespace CredProv
	{
		// Fields for unlock and logon:
		typedef enum LOGON_UI_FIELD_ID
		{
			LUIFI_TILEIMAGE       = 0,
			LUIFI_MOTD            = 1,
			LUIFI_USERNAME        = 2,
			LUIFI_PASSWORD        = 3,
			LUIFI_SUBMIT          = 4, 
			LUIFI_STATUS		  = 5,
			LUIFI_NUM_FIELDS      = 6, 
		};

		static const UI_FIELDS s_logonFields =
		{
			LUIFI_NUM_FIELDS,		// Number of fields total
			LUIFI_PASSWORD,			// Field index which submit button should be adjacent to
			LUIFI_USERNAME,			// Username field index value
			LUIFI_PASSWORD,			// Password field index value
			LUIFI_STATUS,			// Status field
			{
				//  when to display,               style,             field id,        type,               name           data source     value			callback
				{ { CPFS_DISPLAY_IN_BOTH,          CPFIS_NONE },    { LUIFI_TILEIMAGE, CPFT_TILE_IMAGE,    L"Image" },    SOURCE_NONE,    NULL,			NULL },	
			    { { CPFS_DISPLAY_IN_BOTH,          CPFIS_NONE },    { LUIFI_MOTD,      CPFT_SMALL_TEXT,    L"MOTD" },     SOURCE_DYNAMIC, L"pGina",     NULL }, 
				{ { CPFS_DISPLAY_IN_SELECTED_TILE, CPFIS_FOCUSED }, { LUIFI_USERNAME,  CPFT_EDIT_TEXT,     L"Username" }, SOURCE_NONE,    NULL,			NULL },	
				{ { CPFS_DISPLAY_IN_SELECTED_TILE, CPFIS_NONE },	{ LUIFI_PASSWORD,  CPFT_PASSWORD_TEXT, L"Password" }, SOURCE_NONE,    NULL,			NULL }, 
				{ { CPFS_DISPLAY_IN_SELECTED_TILE, CPFIS_NONE },    { LUIFI_SUBMIT,    CPFT_SUBMIT_BUTTON, L"Submit" },   SOURCE_NONE,    NULL,			NULL }, 
				{ { CPFS_DISPLAY_IN_BOTH,		   CPFIS_NONE },    { LUIFI_STATUS,    CPFT_SMALL_TEXT,    L"Status" },   SOURCE_STATUS,  L"Status",    NULL },
			}
		};
	}
}