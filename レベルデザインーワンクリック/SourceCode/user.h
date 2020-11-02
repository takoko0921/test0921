#ifndef INCLUDED_USER
#define INCLUDED_USER

//******************************************************************************
//
//
//      ユーザー（ユーティリティー）
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include <sstream>
#include <bitset>

//------< inline function >-----------------------------------------------------

//--------------------------------------------------------------
//  strBit16    整数を2進数（16bit）のstringに変換する
//--------------------------------------------------------------
//  　引数：const int n     変換する整数
//  戻り値：std::string     数値を2進数に変換したもの(string)
//--------------------------------------------------------------
inline std::string strBit16(const int n)
{
    std::stringstream ss;
    ss << static_cast<std::bitset<16>>(n);
    return ss.str();
}

//--------------------------------------------------------------
//  値を範囲内に収める関数
//--------------------------------------------------------------
//    引数：const float& v  入力する数値
//        ：const float& lo 最小値
//        ：const float& hi 最大値
//  戻り値：const float&    範囲内に収まった数値
//--------------------------------------------------------------
inline const float& clamp(const float& v, const float& lo, const float& hi)
{
    assert(hi >= lo);
    return (std::max)((std::min)(v, hi), lo);
}

//--------------------------------------------------------------
//  値をラップアラウンド（範囲を繰り返す）させる
//--------------------------------------------------------------
//  const int v  範囲を繰り返させたい値
//  const int lo 下限値
//  const int hi 上限値（loより大きい値でなければならない）
//--------------------------------------------------------------
//  戻り値：int    vをloからhiまでの範囲でラップアラウンドさせた数値
//--------------------------------------------------------------
inline int wrap(const int v, const int lo, const int hi)
{
    assert(hi > lo);
    const int n = (v - lo) % (hi - lo); // 負数の剰余はc++11から使用可になった
    return n >= 0 ? (n + lo) : (n + hi);
}

// float版
inline float wrap(const float v, const float lo, const float hi)
{
    assert(hi > lo);
    const float n = std::fmod(v - lo, hi - lo);
    return n >= 0 ? (n + lo) : (n + hi);
}

#endif // !INCLUDED_USER
