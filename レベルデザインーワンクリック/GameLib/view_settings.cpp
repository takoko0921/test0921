//******************************************************************************
//
//
//      ViewSettings
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "view_settings.h"
#include "vector.h"
#include "game_lib.h"

//******************************************************************************
//
//      ViewSettings
//
//******************************************************************************

namespace GameLib
{
    //--------------------------------------------------------------
    //  �R���X�g���N�^
    //--------------------------------------------------------------
    ViewSettings::ViewSettings()
    {
        initialize();
    }

    //--------------------------------------------------------------
    //  �f�X�g���N�^
    //--------------------------------------------------------------
    ViewSettings::~ViewSettings()
    {
    }

    //--------------------------------------------------------------
    //  �����ݒ�
    //--------------------------------------------------------------
    void ViewSettings::initialize()
    {
        scaleFactor = 1.0f;
        setViewLeftTop(VECTOR2(0, 0));
    }

    //--------------------------------------------------------------
    //  �X�P�[����ݒ�
    //--------------------------------------------------------------
    void ViewSettings::setScaleFactor(float s)
    {
        scaleFactor = s;
    }

    //--------------------------------------------------------------
    //  ��ʒ����̃��[���h���W��ݒ�
    //--------------------------------------------------------------
    void ViewSettings::setViewCenter(VECTOR2 c)
    {
        vCenter = c;
#ifdef GAMELIB_PLUS_UP
        vLeftTop = vCenter + VECTOR2(-system::SCREEN_WIDTH / 2, system::SCREEN_HEIGHT / 2) / scaleFactor;
        vLeftBottom = vCenter + VECTOR2(-system::SCREEN_WIDTH / 2, -system::SCREEN_HEIGHT / 2) / scaleFactor;
#else
        vLeftTop = vCenter + VECTOR2(-system::SCREEN_WIDTH / 2, -system::SCREEN_HEIGHT / 2) / scaleFactor;
        vLeftBottom = vCenter + VECTOR2(-system::SCREEN_WIDTH / 2, system::SCREEN_HEIGHT / 2) / scaleFactor;
#endif
    }

    //--------------------------------------------------------------
    //  ��ʍ���̃��[���h���W��ݒ�
    //--------------------------------------------------------------
    void ViewSettings::setViewLeftTop(VECTOR2 lt)
    {
        vLeftTop = lt;
#ifdef GAMELIB_PLUS_UP
        vCenter = vLeftTop + VECTOR2(system::SCREEN_WIDTH / 2, -system::SCREEN_HEIGHT / 2) / scaleFactor;
        vLeftBottom = vLeftTop + VECTOR2(0, -system::SCREEN_HEIGHT) / scaleFactor;
#else
        vCenter = vLeftTop + VECTOR2(system::SCREEN_WIDTH / 2, system::SCREEN_HEIGHT / 2) / scaleFactor;
        vLeftBottom = vLeftTop + VECTOR2(0, system::SCREEN_HEIGHT) / scaleFactor;
#endif
    }

    //--------------------------------------------------------------
    //  ��ʍ����̃��[���h���W��ݒ�
    //--------------------------------------------------------------
    void ViewSettings::setViewLeftBottom(VECTOR2 lb)
    {
        vLeftBottom = lb;
#ifdef GAMELIB_PLUS_UP
        vCenter = vLeftBottom + VECTOR2(system::SCREEN_WIDTH / 2, system::SCREEN_HEIGHT / 2) / scaleFactor;
        vLeftTop = vLeftBottom + VECTOR2(0, system::SCREEN_HEIGHT) / scaleFactor;
#else
        vCenter = vLeftBottom - VECTOR2(system::SCREEN_WIDTH / 2, system::SCREEN_HEIGHT / 2) / scaleFactor;
        vLeftTop = vLeftBottom - VECTOR2(0, system::SCREEN_HEIGHT) / scaleFactor;
#endif
    }

    //--------------------------------------------------------------
    //  ��ʓ��̔C�ӂ̍��W�̃��[���h���W��ݒ�
    //--------------------------------------------------------------
    void ViewSettings::setViewByPosition(VECTOR2 screenPos, VECTOR2 worldPos)
    {
#ifdef GAMELIB_PLUS_UP
        screenPos.y = system::SCREEN_HEIGHT - screenPos.y;
        VECTOR2 lb = worldPos - screenPos / scaleFactor;
        setViewLeftBottom(lb);
#else
        VECTOR2 lt = worldPos - screenPos / scaleFactor;
        setViewLeftTop(lt);
#endif
    }

    //--------------------------------------------------------------
    //  ���[���h���W���X�N���[�����W�ɕϊ�
    //--------------------------------------------------------------
    VECTOR2 ViewSettings::worldToScreen(const VECTOR2& wPos)
    {
#ifdef GAMELIB_PLUS_UP
        return (wPos - vLeftBottom) * scaleFactor;
#else
        return (wPos - vLeftTop) * scaleFactor;
#endif
    }

    VECTOR3 ViewSettings::worldToScreen(const VECTOR3& wPos)
    {
#ifdef GAMELIB_PLUS_UP
        return (wPos - vLeftBottom) * scaleFactor;
#else
        return (wPos - vLeftTop) * scaleFactor;
#endif
    }

    //--------------------------------------------------------------
    //  �X�N���[�����W�����[���h���W�ɕϊ�
    //--------------------------------------------------------------
    VECTOR2 ViewSettings::screenToWorld(VECTOR2 sPos)
    {
#ifdef GAMELIB_PLUS_UP
        sPos.y = system::SCREEN_HEIGHT - sPos.y;
        return vLeftBottom + sPos / scaleFactor;
#else
        return vLeftTop + sPos / scaleFactor;
#endif
    }

}