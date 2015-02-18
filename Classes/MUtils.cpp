

#include "MUtils.h"
#include "cocos2d.h"

float get_content_scale_factor()
{
    auto director = cocos2d::Director::getInstance();
    cocos2d::Size frameSize = director->getOpenGLView()->getFrameSize();
    if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    {
        switch (int(frameSize.width * frameSize.height))
        {
            case 480*320:
                return 0.5;
                break;
            case 960*640:
                return 1;
                break;
            case 1136*640:
                return 1;
                break;
            case 1024*768:
                return 1;
                break;
            case 2048*1536:
                return 2;
                break;
                
            default:
                break;
        }
    }
    else
    {
        switch (int(frameSize.width * frameSize.height))
        {
            case 320*240:
                return 240/640.f;
                break;
            case 480*320:
                return 320/640.f;
                break;
            case 640*460:
                return 460/640.f;
                break;
            case 800*480:
                return 480/640.f;
                break;
            case 854*480:
                return 480/640.f;
                break;
            case 888*540:
                return 540/640.f;
                break;
            case 960*540:
                return 540/640.f;
                break;
            case 960*640:
            {
                if (frameSize.width > 1000 || frameSize.height > 1000)
                {
                    // 1024*600
                    return 600/640.f;
                }
                else
                {
                    return 640/640.f;
                }
                break;
            }
            case 1184*720:
                return 720/640.f;
                break;
            case 1280*720:
                return 720/640.f;
                break;
            case 1280*768:
                return 768/640.f;
                break;
            case 1280*800:
                return 800/640.f;
                break;
            case 1800*1080:
                return 1080/640.f;
                break;
            case 1920*1080:
                return 1080/640.f;
                break;
                
            default:
            {
                auto width = frameSize.width;
                if (width > frameSize.height)
                {
                    width = frameSize.height;
                }
                return width/640.f;
                break;
            }
        }
    }
    
    return 1;
}
//
cocos2d::Size get_design_resolution_size()
{
    cocos2d::Size frameSize = cocos2d::Director::getInstance()-> getOpenGLView()->getFrameSize();
    float scaleFactor = get_content_scale_factor();
    
    auto size = cocos2d::Size(frameSize.width/scaleFactor, frameSize.height/scaleFactor);
//    M_ERROR("resolution size: " << size.width << ", " << size.height);
    return size;
}

void initialize_resolution()
{
    auto *pDirector = cocos2d::Director::getInstance();
    cocos2d::GLView *pEGLView = pDirector->getOpenGLView();
    pDirector->setOpenGLView(pEGLView);
    
    pDirector->setContentScaleFactor(get_content_scale_factor());
    
    cocos2d::Size drSize = get_design_resolution_size();
    pEGLView->setDesignResolutionSize(drSize.width, drSize.height, cocos2d::kResolutionShowAll);
    
}
