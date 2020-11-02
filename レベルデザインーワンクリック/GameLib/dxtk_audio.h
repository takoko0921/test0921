#ifndef INCLUDED_DXTK_AUDIO
#define	INCLUDED_DXTK_AUDIO
//******************************************************************************
//
//
//		DirectXTKAudio
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "./DirectXTK-master/Inc/Audio.h"

namespace GameLib
{
    const int MUSIC_FILE_MAX = 32;
    const int WAVE_FILE_MAX = 128;
    const int WAVE_SOUND_MAX = 8;   // 最大8音同時再生OK

    namespace audio
    {
        //======================================================================
        //
        //      DXTKAudioクラス
        //
        //======================================================================
        class DXTKAudio
        {
        public:

            //--------------------------------------------------------------
            //  コンストラクタ
            //--------------------------------------------------------------
            DXTKAudio();

            //--------------------------------------------------------------
            //  デストラクタ
            //--------------------------------------------------------------
            ~DXTKAudio();

        public:

            //--------------------------------------------------------------
            //  オーディオエンジンのリセット
            //--------------------------------------------------------------
            bool reset();

            //--------------------------------------------------------------
            //  音楽読込
            //--------------------------------------------------------------
            //  int trackNo                     トラック番号 (0 ~ 31)
            //  const wchar_t* waveFileName     音楽ファイルのパス
            //  float volume                    ボリューム (0.0f ~ 1.0f)
            //--------------------------------------------------------------
            void musicLoad(int, const wchar_t*, float volume = ( 0.5f ));

            //--------------------------------------------------------------
            //  音楽解放
            //--------------------------------------------------------------
            //  int trackNo                     トラック番号 (0 ~ 31)
            //--------------------------------------------------------------
            void musicUnload(int);

            //--------------------------------------------------------------
            //  音楽再生
            //--------------------------------------------------------------
            //  int trackNo                     トラック番号 (0 ~ 31)
            //  bool isLoop                     ループ再生するかどうか
            //--------------------------------------------------------------
            void musicPlay(int, bool isLoop = ( false ));

            //--------------------------------------------------------------
            //  音楽停止
            //--------------------------------------------------------------
            //  int trackNo                     トラック番号 (0 ~ 31)
            //--------------------------------------------------------------
            void musicStop(int);

            //--------------------------------------------------------------
            //  音楽一時停止
            //--------------------------------------------------------------
            //  int trackNo                     トラック番号 (0 ~ 31)
            //--------------------------------------------------------------
            void musicPause(int);

            //--------------------------------------------------------------
            //  音楽再開（一時停止からの）
            //--------------------------------------------------------------
            //  int trackNo                     トラック番号 (0 ~ 31)
            //--------------------------------------------------------------
            void musicResume(int);

            //--------------------------------------------------------------
            //  音楽ボリューム設定
            //--------------------------------------------------------------
            //  int trackNo                     トラック番号 (0 ~ 31)
            //  float volume                    ボリューム (0.0f ~ 1.0f)
            //--------------------------------------------------------------
            void musicSetVolume(int, float);

            //--------------------------------------------------------------
            //  SoundStateの取得
            //  int trackNo                     トラック番号 (0 ~ 31)
            //--------------------------------------------------------------
            DirectX::SoundState musicGetState(int);

            //--------------------------------------------------------------
            //  ループの有無の取得
            //  int trackNo                     トラック番号 (0 ~ 31)
            //--------------------------------------------------------------
            bool musicIsLooped(int);

            //--------------------------------------------------------------
            //  panの設定
            //  int trackNo                     トラック番号 (0 ~ 31)
            //  float pan                       pan (-1.0f ~ 1.0f)
            //--------------------------------------------------------------
            void musicSetPan(int, float);

            //--------------------------------------------------------------
            //  pitchの設定
            //  int trackNo                     トラック番号 (0 ~ 31)
            //  float pitch                     pitch (-1.0f ~ 1.0f)
            //--------------------------------------------------------------
            void musicSetPitch(int, float);

            //--------------------------------------------------------------
            //  フォーマットの取得
            //  int trackNo                     トラック番号 (0 ~ 31)
            //--------------------------------------------------------------
            const WAVEFORMATEX* musicGetFormat(int);

            //--------------------------------------------------------------
            //  音楽が使用中かどうか
            //  int trackNo                     トラック番号 (0 ~ 31)
            //--------------------------------------------------------------
            bool musicIsInUse(int);




            //--------------------------------------------------------------
            //  効果音の読込
            //--------------------------------------------------------------
            //  const wchar_t* xwbFileName      xwbファイルのパス
            //  float volume                    ボリューム (0.0f ~ 1.0f)
            //--------------------------------------------------------------
            void soundLoad(const wchar_t*, float volume = ( 0.5f ));

            //--------------------------------------------------------------
            //  効果音の再生
            //--------------------------------------------------------------
            //  int trackNo                     トラック番号 (0 ~ 127)
            //--------------------------------------------------------------
            void soundPlay(int);

            //--------------------------------------------------------------
            //  効果音のボリューム設定
            //--------------------------------------------------------------
            //  int trackNo                     トラック番号 (0 ~ 127)
            //  float volume                    ボリューム (0.0f ~ 1.0f)
            //--------------------------------------------------------------
            void soundSetVolume(int, float);

            bool isAudioDevicePresent() { return audioEngine->IsAudioDevicePresent(); }
            bool isCriticalError() { return audioEngine->IsCriticalError(); }

        private:
            //音楽用
            std::unique_ptr<DirectX::AudioEngine>			audioEngine;
            std::unique_ptr<DirectX::SoundEffect>			music[GameLib::MUSIC_FILE_MAX];
            std::unique_ptr<DirectX::SoundEffectInstance>	musicInst[GameLib::MUSIC_FILE_MAX];
            float											musicVolume[GameLib::MUSIC_FILE_MAX];

            //サウンド用
            std::unique_ptr<DirectX::WaveBank>				waveBank;
            std::unique_ptr<DirectX::SoundEffectInstance>	soundInst[GameLib::WAVE_FILE_MAX][WAVE_SOUND_MAX];//最大8音を同時再生可能
            float											soundVolume[GameLib::WAVE_FILE_MAX];
        };
    }
}

//******************************************************************************

#endif // !INCLUDED_DXTK_AUDIO