//
//  DataHome.cpp
//  changeableball
//
//  Created by huge on 8/9/14.
//
//

#include "DataHome.h"

static DataHome* m_s_data;

DataHome* DataHome:: getInstance()
{
    if (!m_s_data)
    {
        m_s_data = new DataHome();
    }
    return m_s_data;
}
DataHome::DataHome()
{
 wZoomvalue = 1;
 wFontSize = wZoomvalue*12;
    wLevel = 0;
}