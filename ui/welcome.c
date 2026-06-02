/* Original work Copyright 2023 Dual Tachyon
 * https://github.com/DualTachyon
 *
 * Welcome screen reworked for ForestRadio (boot wolf logo + callsign)
 * by therudywolf, building on the EGZUMER / F4HWN lineage.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 */

#include <string.h>

#include "driver/eeprom.h"
#include "driver/st7565.h"
#include "external/printf/printf.h"
#include "helper/battery.h"
#include "settings.h"
#include "misc.h"
#include "ui/helper.h"
#include "ui/welcome.h"
#include "ui/status.h"
#include "version.h"
#include "bitmaps.h"

#ifdef ENABLE_FEAT_F4HWN_SCREENSHOT
    #include "screenshot.h"
#endif

void UI_DisplayReleaseKeys(void)
{
    memset(gStatusLine, 0, sizeof(gStatusLine));
#if defined(ENABLE_FEAT_F4HWN_CTR) || defined(ENABLE_FEAT_F4HWN_INV)
    ST7565_ContrastAndInv();
#endif
    UI_DisplayClear();

    UI_PrintString("RELEASE", 0, 127, 1, 10);
    UI_PrintString("ALL KEYS", 0, 127, 3, 10);

    ST7565_BlitStatusLine();  // blank status line
    ST7565_BlitFullScreen();
}

// ForestRadio boot screen: волчий силуэт 🐺 по центру + позывной снизу.
// Позывной берётся из редактируемой строки приветствия (меню POnMsg / EEPROM 0x0EB0);
// если пусто — показываем "FOREST".
void UI_DisplayWelcome(void)
{
    char callsign[16];
    char voltage[16];

    memset(gStatusLine, 0, sizeof(gStatusLine));
#if defined(ENABLE_FEAT_F4HWN_CTR) || defined(ENABLE_FEAT_F4HWN_INV)
    ST7565_ContrastAndInv();
#endif
    UI_DisplayClear();
    ST7565_BlitStatusLine();
    ST7565_BlitFullScreen();

    if (gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_NONE ||
        gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_SOUND)
    {
        ST7565_FillScreen(0x00);
        return;
    }

    memset(callsign, 0, sizeof(callsign));
    EEPROM_ReadBuffer(0x0EB0, callsign, 16);

    if (gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_VOLTAGE)
    {
        sprintf(voltage, "%u.%02uV %u%%",
                gBatteryVoltageAverage / 100,
                gBatteryVoltageAverage % 100,
                BATTERY_VoltsToPercent(gBatteryVoltageAverage));
        strcpy(callsign, voltage);
    }
    else if (strlen(callsign) == 0)
    {
        strcpy(callsign, "FOREST");
    }

    // Волк: 42x37px, 5 страниц, по центру по X (xoff = (128-42)/2 = 43)
    for (uint8_t p = 0; p < 5; p++)
        memcpy(gFrameBuffer[p] + 43, BITMAP_Wolf[p], sizeof(BITMAP_Wolf[p]));

    // Позывной мелким шрифтом по центру нижней строки
    UI_PrintStringSmallNormal(callsign, 0, 127, 6);

    ST7565_BlitFullScreen();

#ifdef ENABLE_FEAT_F4HWN_SCREENSHOT
    getScreenShot(true);
#endif
}
