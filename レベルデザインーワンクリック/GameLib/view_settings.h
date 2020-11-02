#ifndef INCLUDED_VIEW_SETTINGS
#define INCLUDED_VIEW_SETTINGS
//******************************************************************************
//
//
//      ViewSettings
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "vector.h"

namespace GameLib
{
    //==========================================================================
    //
    //      ViewSettings�N���X
    //
    //==========================================================================
    class ViewSettings
    {
    private:
        float   scaleFactor;    // ��ʂɕ`�悳���C���[�W�̃X�P�[��
        VECTOR2 vCenter;        // ��ʂ̒��S���W
        VECTOR2 vLeftTop;       // ��ʍ���̍��W
        VECTOR2 vLeftBottom;    // ��ʍ����̍��W

    public:
        ViewSettings();
        ~ViewSettings();

        void initialize();

        void setScaleFactor(float s);
        void setViewCenter(VECTOR2);
        void setViewLeftTop(VECTOR2);
        void setViewLeftBottom(VECTOR2);
        void setViewByPosition(VECTOR2, VECTOR2);

        float getScaleFactor() { return scaleFactor; }
        VECTOR2 getViewCenter() { return vCenter; }
        VECTOR2 getViewLeftTop() { return vLeftTop; }
        VECTOR2 getViewLeftBottom() { return vLeftBottom; }

        VECTOR2 worldToScreen(const VECTOR2&);
        VECTOR3 worldToScreen(const VECTOR3&);
        VECTOR2 screenToWorld(VECTOR2);
    };
}

//******************************************************************************

#endif // !INCLUDED_VIEW_SETTINGS