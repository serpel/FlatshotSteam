#include "ControllerConfig.h"

void intro()
{
    Image* image = rosalila()->graphics->getTexture(assets_directory+"menu/rosalila.png");
    Image* image2 = rosalila()->graphics->getTexture(assets_directory+"menu/flatshot.png");
    int current_fade_in=0;

    /*
    rosalila()->graphics->notification_handler.notifications.push_back(
        new Notification(getLoadingImage(), rosalila()->graphics->screen_width/2-getLoadingImage()->getWidth()/2,
                            rosalila()->graphics->screen_height,
                            rosalila()->graphics->screen_height-getLoadingImage()->getHeight(),
                            999999));
*/
    int frames = 0;
    if(!rosalila()->api_integrator->isUsingApi())
    {
        rosalila()->graphics->notification_handler.interruptCurrentNotification();
    }
    while(true)
    {
        if(rosalila()->api_integrator->getState()!="loading" && frames > 180)
        {
            rosalila()->sound->playSound("Menu.confirm",1,0,0,0);
            rosalila()->graphics->notification_handler.interruptCurrentNotification();
            break;
        }
        if(rosalila()->receiver->isPressed("a") && rosalila()->api_integrator->getState()!="loading")
        {
            rosalila()->sound->playSound("Menu.right",0,0,0,0);
            rosalila()->graphics->notification_handler.interruptCurrentNotification();
            break;
        }

        if(rosalila()->receiver->isPressed("b"))
        {
            exit(0);
        }

        rosalila()->graphics->draw2DImage
        (   image,
            image->getWidth(),image->getHeight(),
            0,0,
            1.0,
            0.0,
            false,
            0,0,
            Color(current_fade_in,current_fade_in,current_fade_in,255),
            0,0,
            false,
            FlatShadow());

/*
        if(rosalila()->api_integrator->isUsingApi())
        {
          rosalila()->graphics->drawText(rosalila()->utility->toString(rosalila()->api_integrator->getLeaderboardDownloadPercentage())+"%", 20, 20, false, false);
        }
        */

        current_fade_in+=2;
        if(current_fade_in>255)
            current_fade_in=255;

        frames++;

        rosalila()->update();
    }

    int current_background_transparency=0;

    frames = 0;

    while(true)
    {
        if(frames > 180)
        {
            break;
        }
        if(rosalila()->receiver->isPressed("a"))
        {
            rosalila()->sound->playSound("Menu.right",0,0,0,0);
            break;
        }

        if(rosalila()->receiver->isPressed("b"))
        {
            exit(0);
        }

        rosalila()->graphics->draw2DImage
        (   image2,
            image2->getWidth(),image2->getHeight(),
            0,0,
            1.0,
            0.0,
            false,
            0,0,
            Color(255,255,255,current_background_transparency),
            0,0,
            false,
            FlatShadow());

        current_background_transparency+=2;
        if(current_background_transparency>255)
            current_background_transparency=255;

        frames++;

        rosalila()->update();
    }
}
