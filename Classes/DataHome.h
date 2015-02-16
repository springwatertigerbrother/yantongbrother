//
//  DataHome.h
//  changeableball
//
//  Created by huge on 8/9/14.
//
//

#ifndef __changeableball__DataHome__
#define __changeableball__DataHome__

#include <iostream>

class DataHome
{
private:
    DataHome();
public:

    float wZoomvalue;//ball zoom
    float wFontSize;//字体大小
    float wScore;
    float wFailNum;
    float wCountDown;
    float wWinNum;

    int wLevel;
    
    static DataHome* getInstance();
};

#endif /* defined(__changeableball__DataHome__) */
