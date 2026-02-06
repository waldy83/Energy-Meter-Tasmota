/*
  user_config_override.h - user configuration overrides my_user_config.h for Tasmota

  Copyright (C) 2021  Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

/*****************************************************************************************************\
 * USAGE:
 *   To modify the stock configuration without changing the my_user_config.h file:
 *   (1) copy this file to "user_config_override.h" (It will be ignored by Git)
 *   (2) define your own settings below
 *
 ******************************************************************************************************
 * ATTENTION:
 *   - Changes to SECTION1 PARAMETER defines will only override flash settings if you change define CFG_HOLDER.
 *   - Expect compiler warnings when no ifdef/undef/endif sequence is used.
 *   - You still need to update my_user_config.h for major define USE_MQTT_TLS.
 *   - All parameters can be persistent changed online using commands via MQTT, WebConsole or Serial.
\*****************************************************************************************************/


/*********************************************************************************************\
 * This file consists of TWO sections.
 *
 * SECTION 1:
 * The first section contains PARAMETERS overriding flash settings if define CFG_HOLDER is CHANGED.
 * All parameters can be persistent changed online using commands via MQTT, WebConsole or Serial.
 *   Corresponding MQTT/Serial/Console commands are shown in [brackets]
 *
 * SECTION 2:
 * The second section contains Enabled and Disabled FEATURES allowing different program size.
 *   Changes in this section do NOT need a change of define CFG_HOLDER.
 *
 * ATTENTION:
 * Users are advised to use the user_config_override.h file for most changes.
\*********************************************************************************************/

/*********************************************************************************************\
 * SECTION 1
 * - After initial load any change here only take effect if CFG_HOLDER is changed too
\*********************************************************************************************/

// -- Project -------------------------------------
#define PROJECT                "gaszaehler"         // PROJECT is used as the default topic delimiter


// -- MQTT - Telemetry ----------------------------
#define TELE_PERIOD            10                 // [TelePeriod] Telemetry (0 = disable, 10 - 3600 seconds) - CHANGED BY WALDY


// -- HTTP ----------------------------------------
#define FRIENDLY_NAME          "Gaszaehler"         // [FriendlyName] Friendlyname up to 32 characters used by webpages and Alexa


// TEMPLATE
// If not selected the default will be SONOFF_BASIC
//#define MODULE                 SONOFF_BASIC      // [Module] Select default module from tasmota_template.h


// -- Eigenes Template - Start -------------------------------------
#ifdef MODULE
#undef MODULE
#endif
#define MODULE                 USER_MODULE   // [Module] Select default model (the list is kModuleNiceList() in file tasmota_template.h) USER_MODULE is the TEMPLATE

#ifdef FALLBACK_MODULE
#undef FALLBACK_MODULE
#endif
#define FALLBACK_MODULE        USER_MODULE   // to Select the default model as FALLBACK when the user does a RESET 1 

#ifdef USER_TEMPLATE
#undef USER_TEMPLATE
#endif
#define USER_TEMPLATE          "{\"NAME\":\"Gaszaehler\",\"GPIO\":[1,1,1,1,1,1,1,1,1,1,1,1,1,1],\"FLAG\":0,\"BASE\":18}" // [Template] Set JSON template


// -- Eigenes Template - Ende -------------------------------------

// -- Application ---------------------------------
#define APP_TIMEZONE           99                // [Timezone] +1 hour (Amsterdam) (-13 .. 14 = hours from UTC, 99 = use TIME_DST/TIME_STD)

// Time ENDE

/*********************************************************************************************\
 * END OF SECTION 1
 *
 * SECTION 2
 * - Enable a feature by removing both // in front of it
 * - Disable a feature by preceding it with //
\*********************************************************************************************/

// -- Localization --------------------------------
// If non selected the default en-GB will be used

#define MY_LANGUAGE            de_DE           // German in Germany

//#define MY_LANGUAGE            en_GB           // English in Great Britain. Enabled by Default


// -- MQTT - Domoticz -----------------------------
#undef USE_DOMOTICZ                             // Enable Domoticz (+6k code, +0.3k mem)

// -- HTTP ----------------------------------------
#undef USE_EMULATION_HUE                      // Enable Hue Bridge emulation for Alexa (+14k code, +2k mem common)
#undef USE_EMULATION_WEMO                     // Enable Belkin WeMo emulation for Alexa (+6k code, +2k mem common)

// -- Time ----------------------------------------

//-- Diese Features deaktivieren weil Script verwendet wird ???
#undef USE_TIMERS             // Add support for up to 16 timers (+2k2 code)
#undef USE_TIMERS_WEB         // Add timer webpage support (+4k5 code)

// -- Rules or Script  ----------------------------
// Select none or only one of the below defines USE_RULES or USE_SCRIPT

#ifdef USE_RULES
#undef USE_RULES                                // Add support for rules (+13k code, +768 bytes mem)
#endif

#ifndef USE_SCRIPT
#define USE_SCRIPT                              // Add support for script (+36k code, +1k mem)
#endif

#ifndef USE_SCRIPT_WEB_DISPLAY
#define USE_SCRIPT_WEB_DISPLAY                  // enable >W section (modify web UI)
#endif

#ifndef LARGE_ARRAYS
#define LARGE_ARRAYS                            // enables arrays of up to 1000 entries instead of max 127
#endif

//-- ESP8266: WENN IHR 1M FLASHSPEICHER HABT - most useful definition for larger scripts
#ifndef USE_EEPROM
#define USE_EEPROM
#endif
#define EEP_SCRIPT_SIZE 8192

// -- SML Support ---------------------------------

#ifndef USE_SML_M                               // SML Support - Tasmota's scripting language
#define USE_SML_M
#endif

#ifndef USE_SML_SCRIPT_CMD
#define USE_SML_SCRIPT_CMD                      // some special SML script cmds and allows access to sml vars in other parts of the script
#endif

#ifndef USE_SML_SPECOPT
#define USE_SML_SPECOPT                         // DWS74 Bugfix (bei negativen Werten <650W) und "1,=so2,1" im Skript eingeben
#endif

/*
#ifndef USE_SML_AUTHKEY
#define USE_SML_AUTHKEY                         // enables authentication, this is not needed by most energy meters. M,=so5
#endif
*/

/*
#ifndef USE_SML_TCP
#define USE_SML_TCP                             // Modbus TCP SML Support (kann beim ESP32 immer aktiviert werden)
#endif
*/


// -- GOOGLE_CHARTS ---------------------------------

#ifndef USE_GOOGLE_CHARTS
#define USE_GOOGLE_CHARTS
#endif

// -- Optional modules ----------------------------
#undef ROTARY_V1                                // Add support for Rotary Encoder as used in MI Desk Lamp (+0k8 code)
#undef USE_SONOFF_RF                            // Add support for Sonoff Rf Bridge (+3k2 code)
#undef USE_SONOFF_SC                            // Add support for Sonoff Sc (+1k1 code)
#undef USE_TUYA_MCU                             // Add support for Tuya Serial MCU
#undef USE_ARMTRONIX_DIMMERS                    // Add support for Armtronix Dimmers (+1k4 code)
#undef USE_PS_16_DZ                             // Add support for PS-16-DZ Dimmer (+2k code)
#undef USE_SONOFF_IFAN                          // Add support for Sonoff iFan02 and iFan03 (+2k code)
#undef USE_BUZZER                               // Add support for a buzzer (+0k6 code)
#undef USE_ARILUX_RF                            // Add support for Arilux RF remote controller (+0k8 code, 252 iram (non 2.3.0))
#undef USE_SHUTTER                              // Add Shutter support for up to 4 shutter with different motortypes (+11k code)
#undef USE_DEEPSLEEP                            // Add support for deepsleep (+1k code)
#undef USE_EXS_DIMMER                           // Add support for ES-Store Wi-Fi Dimmer (+1k5 code)
#undef USE_DEVICE_GROUPS                        // Add support for device groups (+5k5 code)
#undef USE_PWM_DIMMER                           // Add support for MJ-SD01/acenx/NTONPOWER PWM dimmers (+2k3 code, DGR=0k7)
#undef USE_SONOFF_D1                            // Add support for Sonoff D1 Dimmer (+0k7 code)
#undef USE_SHELLY_DIMMER                        // Add support for Shelly Dimmer (+3k code)

// -- Optional light modules ----------------------
#undef USE_LIGHT                                // Add support for light control
#undef USE_WS2812                               // WS2812 Led string using library NeoPixelBus (+5k code, +1k mem, 232 iram) - Disable by //
#undef USE_MY92X1                               // Add support for MY92X1 RGBCW led controller as used in Sonoff B1, Ailight and Lohas
#undef USE_SM16716                              // Add support for SM16716 RGB LED controller (+0k7 code)
#undef USE_SM2135                               // Add support for SM2135 RGBCW led control as used in Action LSC (+0k6 code)
#undef USE_SM2335                               // Add support for SM2335 RGBCW led control as used in SwitchBot Color Bulb (+0k7 code)
#undef USE_BP1658CJ                             // Add support for BP1658CJ RGBCW led control as used in Orein OS0100411267 Bulb
#undef USE_BP5758D                              // Add support for BP5758D RGBCW led control as used in some Tuya lightbulbs (+0k8 code)
#undef USE_SONOFF_L1                            // Add support for Sonoff L1 led control
#undef USE_ELECTRIQ_MOODL                       // Add support for ElectriQ iQ-wifiMOODL RGBW LED controller (+0k3 code)
#undef USE_LIGHT_PALETTE                        // Add support for color palette (+0k7 code)
#undef USE_LIGHT_VIRTUAL_CT                     // Add support for Virtual White Color Temperature (+1.1k code)
#undef USE_DGR_LIGHT_SEQUENCE                   // Add support for device group light sequencing (requires USE_DEVICE_GROUPS) (+0k2 code)

// -- One wire sensors ----------------------------
#undef USE_DS18x20                              // Add support for DS18x20 sensors with id sort, single scan and read retry (+2k6 code)

// -- I2C sensors ---------------------------------
#undef USE_I2C                                  // I2C using library wire (+10k code, 0k2 mem, 124 iram)

// -- Serial sensors ------------------------------
#undef USE_SERIAL_BRIDGE                        // Add support for software Serial Bridge (+2k code)

// -- Power monitoring sensors --------------------
#undef USE_ENERGY_SENSOR                        // Add support for Energy Monitors (+14k code)
#undef USE_ENERGY_DUMMY                         // Add support for dummy Energy monitor allowing user values (+0k7 code)
#undef USE_HLW8012                              // Add support for HLW8012, BL0937 or HJL-01 Energy Monitor for Sonoff Pow and WolfBlitz
#undef USE_CSE7766                              // Add support for CSE7766 Energy Monitor for Sonoff S31 and Pow R2
#undef USE_PZEM004T                             // Add support for PZEM004T Energy monitor (+2k code)
#undef USE_PZEM_AC                              // Add support for PZEM014,016 Energy monitor (+1k1 code)
#undef USE_PZEM_DC                              // Add support for PZEM003,017 Energy monitor (+1k1 code)
#undef USE_MCP39F501                            // Add support for MCP39F501 Energy monitor as used in Shelly 2 (+3k1 code)
#undef USE_BL09XX                               // Add support for various BL09XX Energy monitor as used in Blitzwolf SHP-10 or Sonoff Dual R3 v2 (+1k6 code)

// -- Low level interface devices -----------------
#undef USE_DHT                                  // Add support for DHT11, AM2301 (DHT21, DHT22, AM2302, AM2321) and SI7021 Temperature and Humidity sensor (1k6 code)

// -- IR Remote features - subset of IR protocols --------------------------
#undef USE_IR_REMOTE                            // Send IR remote commands using library IRremoteESP8266 (+4k3 code, 0k3 mem, 48 iram)

//--------------------------------------------------------------------------

//#define OTA_URL "!!NEVER UPGRADE VIA WEB SERVER!!"
#define OTA_URL "!!! SOFTWARE NICHT UPDATEN !!!"

#endif  // _USER_CONFIG_OVERRIDE_H_
