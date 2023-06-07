#pragma once
#include <array>
#include "U8g2lib.h"
#define SSD1306_DISPLAYOFF          0xAE
#include "ConfigurationManager.h"
#include <SSD1306.h>
#include <Wire.h>

class Calvalue
{
    std::array<int,100> m_calvalueArray{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
                                         60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
                                         80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100}};

    int m_selectedCalvalue = 0;

    unsigned long m_startMillis = 0;

    ConfigurationManager* m_configurationManager;
    //U8G2_SSD1327_MIDAS_128X128_F_4W_HW_SPI* m_u8g2;
    U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* m_u8g2;
    SSD1306* m_display;


public:

    Calvalue()
    {
        m_selectedCalvalue = 0;
    }

    ~Calvalue()=default;

    void init(ConfigurationManager* configurationManager, U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* u8g2)
    {
        m_configurationManager = configurationManager;
        m_u8g2 = u8g2;
    }

    void selectCalvalueByValueNoEEPROMSave(int calvalue)
    {
        for(int i=0; i < m_calvalueArray.size(); i++)
            if(m_calvalueArray[i] == calvalue)
            {
                m_selectedCalvalue = i;
                break;
            }

        return;
    }

    void selectCalvalueByIndex(int index)
    {
        if(index >= 0 && index < m_calvalueArray.size())
        {
            m_selectedCalvalue = index;
            EEPROM.writeInt(150, index);
            EEPROM.commit();
            Serial.print("Calvalue saved ");
            Serial.println(index);
        }

        return;
    }

    void selectCalvalueByValue(int calvalue)
    {
        for(int i=0; i < m_calvalueArray.size(); i++)
            if(m_calvalueArray[i] == calvalue)
            {
                m_selectedCalvalue = i;
                m_configurationManager->saveCalvalueToEEPROM(i);
                break;
            }

        return;
    }

    void selectNextCalvalue()
    {
        m_selectedCalvalue = (m_selectedCalvalue + 1) % m_calvalueArray.size();
    }

    void selectPreviousCalvalue()
    {
        if(m_selectedCalvalue == 0)
            m_selectedCalvalue = m_calvalueArray.size() - 1;
        else
            m_selectedCalvalue = m_selectedCalvalue - 1;
    }

    void resetIdleCounter()
    {
        m_startMillis = millis();
    }

    int getSelectedCalvalue() {
        int calvalue = EEPROM.read(150);
        return m_calvalueArray[calvalue];
    }

};
