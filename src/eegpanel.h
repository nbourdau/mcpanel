/*
	Copyright (C) 2008-2009 Nicolas Bourdaud <nicolas.bourdaud@epfl.ch>

    This file is part of the eegpanel library

    The eegpanel library is free software: you can redistribute it and/or
    modify it under the terms of the version 3 of the GNU General Public
    License as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _EEGPANEL_H_
#define _EEGPANEL_H_

#include <stdint.h>


typedef struct _EEGPanelPrivateData EEGPanelPrivateData;
typedef struct _EEGPanel EEGPanel;

typedef enum
{
	EEG,
	EXG,
	TRIGGERS
} ChannelType;

typedef struct _ChannelSelection {
	unsigned int *selection;
	unsigned int num_chann;
	const char** labels;
} ChannelSelection;

typedef int (*ProcessSelectionFunc)(const ChannelSelection* selection, ChannelType type, void* user_data);
typedef int (*SystemConnectionFunc)(int start, void* user_data);
typedef int (*SetupRecordingFunc)(const ChannelSelection* eeg_sel, const ChannelSelection* exg_sel, void* user_data);
typedef int (*ToggleRecordingFunc)(int start, void* user_data);


struct _EEGPanel {
	// function supplied by the user
	ProcessSelectionFunc process_selection;
	SystemConnectionFunc system_connection;
	SetupRecordingFunc setup_recording;
	ToggleRecordingFunc toggle_recording; 

	// pointer used to pass data to the user functions
	void* user_data;

	// private data, don't touch
	EEGPanelPrivateData* priv;
};

void init_eegpanel_lib(int *argc, char ***argv);
EEGPanel* eegpanel_create(void);
void eegpanel_destroy(EEGPanel* panel);
void eegpanel_show(EEGPanel* panel, int state);
void eegpanel_popup_message(EEGPanel* panel, const char* message);
char* eegpanel_open_filename_dialog(EEGPanel* panel, const char* filter, const char* filtername);
void eegpanel_run(EEGPanel* panel, int nonblocking);
void eegpanel_add_samples(EEGPanel* panel, const float* eeg, const float* exg, const uint32_t* triggers, unsigned int num_samples);
int eegpanel_define_input(EEGPanel* panel, unsigned int num_eeg_channels,
				unsigned int num_exg_channels, unsigned int num_tri_lines,
				unsigned int sampling_rate);

#endif //_EEGPANEL_H_