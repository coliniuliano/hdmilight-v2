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
	{0x98, 0xFF, 0x80},		// I2C Reset
	{0xFF, 0xFF, 0xFF},		// (give it time to reset)(0xFF 0xFF is treated as a delay)

	{0x98, 0xFD, 0x44},		// CP I2C address = 0x44

	// IO Module
	{0x98, 0x00, 0x1E},		// VID_STD = 1920x1080 (fpga expects 1080p)
	{0x98, 0x01, 0x05},		// PRIM_MODE = HDMI Component
	{0x98, 0x02, 0xF0},		// Output color space RGB
	{0x98, 0x03, 0x40},		// OP_FORMAT_SEL = 24-bit 4:4:4 SDR Mode 0
	{0x98, 0x05, 0x28},		// Disable AV Codes
	{0x98, 0x0B, 0x44},		// Power up
	{0x98, 0x0C, 0x42},		// Power up part (draws 80mA from 1.8v line)
	{0x98, 0x14, 0x7F},		// Drive strength high
	{0x98, 0x15, 0x80},		// Disable Tristate (pixel bus, LLC, output, audio)
	{0x98, 0x19, 0x83},		// LLC DLL enable + phase (3)
	{0x98, 0x33, 0x40},		// ?? "LLC DLL MUX enable"

	// CP Module
	{0x44, 0xBA, 0x01},		// Free run mode 0 (default)
	{0x44, 0xBF, 0x17},		// Force free run, custom color
	{0x44, 0xC0, 0xA0},		// DEF_COL_CHA (G)
	{0x44, 0xC1, 0x00},		// DEF_COL_CHB (R)
	{0x44, 0xC2, 0x00},		// DEF_COL_CHC (B)
	{0x44, 0xC9, 0x05},		// Free run resolution set by PRIM_MODE and VID_STD
	{0x00}
};

// COLIN TODO: Get updated I2C config scripts from
// https://ez.analog.com/video/w/documents/773/adv7619-design-support-files
// See AD7619-VER.1.9c.txt (2047.ADV7619-VER.1.9c.zip link)
static const struct ConfigTable g_configTablePreEdid[] PROGMEM = 
{
	// Configure the variable I2C map addresses
	// The only fixed I2C address on startup is for the IO I2C map (0x98)
	// https://docplayer.net/134237248-Adv7619-register-settings-recommendations-rev-1-1.html
	// 6457.ADV7619_Required_Settings_Manual_1.8_031115.pdf
	{ 0x98, 0xF4, 0x80 },  // CEC
	{ 0x98, 0xF5, 0x7C },  // INFOFRAME
	{ 0x98, 0xF8, 0x4C },  // DPLL
	{ 0x98, 0xF9, 0x64 },  // KSV
	{ 0x98, 0xFA, 0x6C },  // EDID
	{ 0x98, 0xFB, 0x68 },  // HDMI
	{ 0x98, 0xFD, 0x44 },  // CP

	{ 0x64, 0x77, 0x00 },  // Disable the Internal EDID

	{ 0x00 }
};

// Colin note - TODO 0x14 drive strength should be set to high for 4k LLC clock
static const struct ConfigTable g_configTablePostEdid[] PROGMEM = 
{
	{ 0x64, 0x77, 0x00 },  // Set the Most Significant Bit of the SPA location to 0
	{ 0x64, 0x52, 0x20 },  // Set the SPA for port B.
	{ 0x64, 0x53, 0x00 },  // Set the SPA for port B.
	{ 0x64, 0x70, 0x9E },  // Set the Least Significant Byte of the SPA location
	{ 0x64, 0x74, 0x03 },  // Enable the Internal EDID for Ports

	{ 0x98, 0x01, 0x06 },  // Prim_Mode =110b HDMI-GR
	{ 0x98, 0x02, 0xF2 },  // Auto CSC, YCrCb out, Set op_656 bit
	{ 0x98, 0x03, 0x40 },  // 24 bit SDR 444 Mode 0 
	{ 0x98, 0x05, 0x28 },  // AV Codes Off
	{ 0x98, 0x0B, 0x44 },  // Power up part
	{ 0x98, 0x0C, 0x42 },  // Power up part
	{ 0x98, 0x14, 0x55 },  // Min Drive Strength
	{ 0x98, 0x15, 0x80 },  // Disable Tristate of Pins
	{ 0x98, 0x19, 0x85 },  // LLC DLL phase
	{ 0x98, 0x33, 0x40 },  // LLC DLL enable
	{ 0x44, 0xBA, 0x01 },  // Set HDMI FreeRun
	{ 0x64, 0x40, 0x81 },  // Disable HDCP 1.1 features
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
	{ 0x68, 0x8D, 0x04 },  // LFG
	{ 0x68, 0x8E, 0x1E },  // HFG
	{ 0x68, 0x1A, 0x8A },  // unmute audio
	{ 0x68, 0x57, 0xDA },  // ADI recommended setting
	{ 0x68, 0x58, 0x01 },  // ADI recommended setting
	{ 0x68, 0x75, 0x10 },  // DDC drive strength
	{ 0x98, 0x40, 0xE2 },  // INT1 active high, active until cleared

	{ 0x00 }
};

