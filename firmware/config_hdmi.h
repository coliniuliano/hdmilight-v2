/*

   Copyright (C) 2013 Stephen Robinson
  
   This file is part of HDMI-Light
  
   HDMI-Light is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 2 of the License, or
   (at your option) any later version.
  
   HDMI-Light is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this code (see the file names COPING).  
   If not, see <http://www.gnu.org/licenses/>.
  
*/

struct ConfigTable
{
	unsigned char address;
	unsigned char subaddress;
	unsigned char data;
};

static const struct ConfigTable g_configTableFreeRun[] PROGMEM = 
{
	{ 0x98, 0xFF, 0x80 },	// I2C Reset
	{ 0xFF, 0xFF, 0xFF },	// (give it time to reset)(0xFF 0xFF is treated as a delay)

	{ 0x98, 0xFD, 0x44 },	// CP I2C address = 0x44

	// IO Module
	{ 0x98, 0x00, 0x1E },	// VID_STD = 1920x1080 (fpga expects 1080p)
	{ 0x98, 0x01, 0x05 },	// PRIM_MODE = HDMI Component
	{ 0x98, 0x02, 0xF0 },	// Output color space RGB
	{ 0x98, 0x03, 0x40 },	// OP_FORMAT_SEL = 24-bit 4:4:4 SDR Mode 0
	{ 0x98, 0x05, 0x28 },	// Disable AV Codes
	{ 0x98, 0x0B, 0x44 },	// Power up
	{ 0x98, 0x0C, 0x42 },	// Power up part (draws 80mA from 1.8v line)
	{ 0x98, 0x14, 0x7F },	// Drive strength high (required for 4k signals)
	{ 0x98, 0x15, 0x80 },	// Disable Tristate (pixel bus, LLC, output, audio)
	{ 0x98, 0x19, 0x83 },	// LLC DLL enable + phase (3)
	{ 0x98, 0x33, 0x40 },	// Apply DLL to LLC pin

	// CP Module
	{ 0x44, 0xBA, 0x01 },	// Free run mode 0 (default)
	{ 0x44, 0xBF, 0x17 },	// Force free run, custom color
	{ 0x44, 0xC0, 0xA0 },	// DEF_COL_CHA (G)
	{ 0x44, 0xC1, 0x00 },	// DEF_COL_CHB (R)
	{ 0x44, 0xC2, 0x00 },	// DEF_COL_CHC (B)
	{ 0x44, 0xC9, 0x05 },	// Free run resolution set by PRIM_MODE and VID_STD

	{ 0x00 }
};

// https://ez.analog.com/video/w/documents/773/adv7619-design-support-files
// See AD7619-VER.1.9c.txt (2047.ADV7619-VER.1.9c.zip)
static const struct ConfigTable g_configTablePreEdid[] PROGMEM = 
{
	{ 0x98, 0xFF, 0x80 },	// I2C Reset
	{ 0xFF, 0xFF, 0xFF },	// (give it time to reset)(0xFF 0xFF is treated as a delay)

	// The following settings come from these sources with slight modifications:
	// https://ez.analog.com/video/w/documents/773/adv7619-design-support-files
	// AD7619-VER.1.9c.txt (2047.ADV7619-VER.1.9c.zip from above site)
	// 6457.ADV7619_Required_Settings_Manual_1.8_031115.pdf

	// Configure the variable I2C map addresses
	{ 0x98, 0xF4, 0x80 },	// CEC
	{ 0x98, 0xF5, 0x7C },	// INFOFRAME
	{ 0x98, 0xF8, 0x4C },	// DPLL
	{ 0x98, 0xF9, 0x64 },	// KSV
	{ 0x98, 0xFA, 0x6C },	// EDID
	{ 0x98, 0xFB, 0x68 },	// HDMI
	{ 0x98, 0xFD, 0x44 },	// CP

	{ 0x68, 0xC0, 0x03 },	// SCR "ADI Required Write"

	// IO Module
	//{ 0x98, 0x00, 0x1E },	// VID_STD = 1920x1080 (fpga expects 1080p)
	//{ 0x98, 0x01, 0x05 },	// PRIM_MODE = HDMI Component
	//{ 0x98, 0x02, 0xF0 },	// Output color space RGB
	{ 0x98, 0x01, 0x06 },	// (existing code) // PRIM_MODE = HDMI Graphic
	{ 0x98, 0x02, 0xF2 },	// (existing code) // Auto CSC, YCrCb out, Set op_656 bit
	{ 0x98, 0x03, 0x40 },	// OP_FORMAT_SEL = 24-bit 4:4:4 SDR Mode 0
	{ 0x98, 0x05, 0x28 },	// Disable AV Codes
	{ 0x98, 0x0B, 0x44 },	// Power up
	{ 0x98, 0x0C, 0x42 },	// Power up part (draws 80mA from 1.8v line)
	{ 0x98, 0x14, 0x55 },	// Drive strength high (required for 4k signals 7F) TODO
	{ 0x98, 0x15, 0x80 },	// Disable Tristate (pixel bus, LLC, output, audio)
	{ 0x98, 0x19, 0x83 },	// LLC DLL enable + phase (3)
	{ 0x98, 0x33, 0x40 },	// Apply DLL to LLC pin

	// CP
	{ 0x44, 0xBA, 0x01 },	// Free run mode 0 (default)
	{ 0x44, 0x6C, 0x00 },	// ADI Required write
	{ 0x44, 0xBF, 0x16 },	// Custom color
	{ 0x44, 0xC0, 0xA0 },	// DEF_COL_CHA (G)
	{ 0x44, 0xC1, 0x00 },	// DEF_COL_CHB (R)
	{ 0x44, 0xC2, 0x00 },	// DEF_COL_CHC (B)
	{ 0x44, 0xC9, 0x05 },	// Free run resolution set by PRIM_MODE and VID_STD

	// KSV
	{ 0x64, 0x40, 0x81 },  // Disable HDCP 1.1 features

	// DPLL
	//{ 0x4C, 0xB5, 0x01 }	// Audio MCLK to 256Fs (CI already a default)

	// HDMI
	// Required Settings 2.1.2 720p, 1080i, 1080p up to 36-bit
	{ 0x68, 0xC0, 0x03 },	// ADI Required write
	{ 0x68, 0x00, 0x00 },	// HDMI Input Port A
	{ 0x68, 0x03, 0x98 },	// ADI Required Write (CI likely audio related)
	{ 0x68, 0x10, 0xA5 },	// ADI Required Write (CI likely audio related)
	{ 0x68, 0x1B, 0x08 },	// ADI Required Write (CI disable "reset/recentering of video FIFO on video PLL unlock")
	{ 0x68, 0x45, 0x04 },	// ADI Required Write
	{ 0x68, 0x97, 0xC0 },	// ADI Required Write
	{ 0x68, 0x3D, 0x10 },	// ADI Required Write
	{ 0x68, 0x3E, 0x69 },	// ADI Required Write
	{ 0x68, 0x3F, 0x46 },	// ADI Required Write
	{ 0x68, 0x4E, 0xFE },	// ADI Required Write 
	{ 0x68, 0x4F, 0x08 },	// ADI Required Write
	{ 0x68, 0x50, 0x00 },	// ADI Required Write (CI default SPDIF "copyright")
	{ 0x68, 0x57, 0xA3 },	// ADI Required Write
	{ 0x68, 0x58, 0x07 },	// ADI Required Write
	{ 0x68, 0x6F, 0x08 },	// ADI Required Write
	{ 0x68, 0x83, 0xFE },	// Enable clock terminiation on Port A
	{ 0x68, 0x84, 0x03 },	// ADI Required Write 

	// HDMI
	// Required Settings 3.1.2 720p, 1080i, 1080p up to 36-bit
	// "Configure the TMDS Equalizer"
	{ 0x68, 0x85, 0x10 },	// ADI Required Write 
	{ 0x68, 0x86, 0x9B },	// ADI Required Write 
	{ 0x68, 0x89, 0x03 },	// ADI Required Write 
	{ 0x68, 0x9B, 0x03 },	// ADI Required Write
	{ 0x68, 0x93, 0x03 },	// ADI Required Write
	{ 0x68, 0x5A, 0x80 },	// ADI Required Write (CI likely a self-clearing reset, undocumented bit)
	{ 0x68, 0x9C, 0x80 },	// ADI Required Write (CI likely a reset since there's 3 in a row)
	{ 0x68, 0x9C, 0xC0 },	// ADI Required Write
	{ 0x68, 0x9C, 0x00 },	// ADI Required Write

	// From existing hdmilight code
	{ 0x64, 0x77, 0x00 },	//? Disable the Internal EDID

	{ 0x00 }
};

static const struct ConfigTable g_configTablePostEdid[] PROGMEM = 
{
	// From existing hdmilight code
	// looks like they are related to EDID and CSC which might only be on port b (disconnected)
	
	{ 0x64, 0x77, 0x00 },	//? Set the Most Significant Bit of the SPA location to 0
	{ 0x64, 0x52, 0x20 },	//? Set the SPA for port B.
	{ 0x64, 0x53, 0x00 },	//? Set the SPA for port B.
	{ 0x64, 0x70, 0x9E },	//? Set the Least Significant Byte of the SPA location
	

	// From existing hdmilight code
	{ 0x64, 0x74, 0x01 },	// Enable the Internal EDID for Port A

	// Might be some necessary commands left in here!
	/*
	{ 0x68, 0x9B, 0x03 },  // ADI recommended setting
	{ 0x68, 0xC1, 0x01 },  // ADI recommended setting
	{ 0x68, 0xC2, 0x01 },  // ADI recommended setting
	{ 0x68, 0xC3, 0x01 },  // ADI recommended setting
	{ 0x68, 0xC4, 0x01 },  // ADI recommended setting
	{ 0x68, 0xC5, 0x01 },  // ADI recommended setting
	{ 0x68, 0xC6, 0x01 },  // ADI recommended setting
	{ 0x68, 0xC7, 0x01 },  // ADI recommended setting
	{ 0x68, 0xC8, 0x01 },  // ADI recommended setting
	{ 0x68, 0xC9, 0x01 },  // ADI recommended setting
	{ 0x68, 0xCA, 0x01 },  // ADI recommended setting
	{ 0x68, 0xCB, 0x01 },  // ADI recommended setting
	{ 0x68, 0xCC, 0x01 },  // ADI recommended setting
	{ 0x68, 0x00, 0x00 },  // Set HDMI Input Port A
	{ 0x68, 0x83, 0xFE },  // Enable clock terminator for port A
	{ 0x68, 0x6F, 0x0C },  // ADI recommended setting
	{ 0x68, 0x85, 0x1F },  // ADI recommended setting
	{ 0x68, 0x87, 0x70 },  // ADI recommended setting
	- { 0x68, 0x8D, 0x04 },  // LFG ?????
	- { 0x68, 0x8E, 0x1E },  // HFG ?????
	- { 0x68, 0x1A, 0x8A },  // unmute audio ?????
	{ 0x68, 0x57, 0xDA },  // ADI recommended setting
	{ 0x68, 0x58, 0x01 },  // ADI recommended setting
	- { 0x68, 0x75, 0x10 },  // DDC drive strength ?????
	*/

	{ 0x98, 0x40, 0xE2 },  // INT1 active high, active until cleared

	{ 0x00 }
};

