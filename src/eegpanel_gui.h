/*
	Copyright (C) 2008-2009 Nicolas Bourdaud <nicolas.bourdaud@epfl.ch>

    This file is part of the eegpanel library

    The eegpan library is free software: you can redistribute it and/or
    modify it under the terms of the version 3 of the GNU General Public
    License as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef EEGPANEL_GUI_H
#define EEGPANEL_GUI_H

#include <gtk/gtk.h>
#include "plot-area.h"
#include "scope.h"
#include "bargraph.h"
#include "binary-scope.h"
#include "labelized-plot.h"
#include "gtk-led.h"

typedef enum {
	ELEC_TYPE,
	BIPOLE_TYPE,
	OFFSET_TYPE
} ScopeType;

typedef enum {
	TOP_WINDOW,
	SCOPE_NOTEBOOK,
	TRI_SCOPE,
	TRI_AXES,
	STARTACQUISITION_BUTTON,
	CONNECT_LED,
	CMS_LED,
	BATTERY_LED,
	NATIVE_FREQ_LABEL,
	DISPLAYED_FREQ_LABEL,
	TIME_WINDOW_COMBO,
	RECORDING_LIMIT_ENTRY,
	RECORDING_LED,
	START_RECORDING_BUTTON,
	PAUSE_RECORDING_BUTTON,
	FILE_LENGTH_LABEL,
	NUM_PANEL_WIDGETS_DEFINED
} PanelWidgetEnum;

typedef struct _LinkWidgetName {
	PanelWidgetEnum id;
	const char* name;
	const char* type;
} LinkWidgetName;

struct PanelGUI {
	GtkWindow* window;
	GMutex* syncmtx;
	int is_destroyed;
	GObject* widgets[NUM_PANEL_WIDGETS_DEFINED];
	GtkNotebook* notebook;
	BinaryScope *tri_scope;
};


struct DialogParam {
	const char *str_in;
	char *str_out;
	struct PanelGUI* gui;
};

typedef int (*BCProc)(void* data);

struct BlockingCallParam {
	void* data;
	GMutex* mtx;
	GCond* cond;
	int done;
	int retcode;
	BCProc func;
};

LOCAL_FN int create_panel_gui(EEGPanel* pan, const char* uifile,
                              unsigned int ntab,
                              const struct panel_tabconf* tabconf);
LOCAL_FN void get_initial_values(EEGPanel* pan);
LOCAL_FN void destroy_panel_gui(EEGPanel* pan);
LOCAL_FN void update_triggers_gui(EEGPanel* pan);
LOCAL_FN int popup_message_dialog(struct DialogParam* dlgparam);
LOCAL_FN int open_filename_dialog(struct DialogParam* dlgparam);
LOCAL_FN int run_func_in_guithread(EEGPanel* pan, BCProc func, void* data);
LOCAL_FN void update_input_gui(EEGPanel* pan);
LOCAL_FN void updategui_toggle_recording(EEGPanel* pan, int state);
LOCAL_FN void updategui_toggle_connection(EEGPanel* pan, int state);
LOCAL_FN void updategui_toggle_rec_openclose(EEGPanel* pan, int state);


#endif /* EEGPANEL_GUI_H */

