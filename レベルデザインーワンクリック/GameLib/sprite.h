#ifndef INCLUDED_SPRITE
#define INCLUDED_SPRITE
//******************************************************************************
//
//
//      スプライト描画用クラス
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include <string>

#include <d3d11.h>
#include <DirectXMath.h>

#include "vector.h"
#include "resource_manager.h"

namespace GameLib
{

    //==========================================================================
    //
    //      Spriteクラス
    //
    //==========================================================================
    class Sprite
    {
        ID3D11VertexShader*         vertexShader;
        ID3D11PixelShader*          pixelShader;
        ID3D11InputLayout*          inputLayout;
        ID3D11Buffer*               buffer;
        ID3D11RasterizerState*      rasterizerState;

        ID3D11ShaderResourceView*   shaderResourceView;
        D3D11_TEXTURE2D_DESC        tex2dDesc;
        ID3D11SamplerState*         samplerState;
        ID3D11DepthStencilState*    depthStencilState;

    public:

        //--------------------------------------------------------------
        //  コンストラクタ
        //--------------------------------------------------------------
        Sprite(ID3D11Device*, const wchar_t*, int nBufSize = ( 4 ));

        //--------------------------------------------------------------
        //  デストラクタ
        //--------------------------------------------------------------
        ~Sprite();

        //--------------------------------------------------------------
        //  スプライト描画
        //--------------------------------------------------------------
        void render(ID3D11DeviceContext*, 
            const VECTOR2&, const VECTOR2&, 
            const VECTOR2&, const VECTOR2&,
            const VECTOR2&, float,
            const VECTOR4&
            ) const;

        //--------------------------------------------------------------
        //  スプライト描画
        //--------------------------------------------------------------
        void render(ID3D11DeviceContext*,
            float, float, float, float, 
            float, float, float, float,
            float, float, float,
            float, float, float, float
            ) const;

        //--------------------------------------------------------------
        //  テキスト描画
        //--------------------------------------------------------------
        float textout(ID3D11DeviceContext*, 
            std::string, const VECTOR2&,
            const VECTOR2&, const VECTOR4&, 
            bool world = ( false )) const;

        //--------------------------------------------------------------
        //  テキスト描画
        //--------------------------------------------------------------
        float textout(ID3D11DeviceContext*, 
            std::string, float, float,
            float, float,
            float, float, float, float, 
            bool world = ( false )) const;

        //--------------------------------------------------------------
        //  四角ポリゴン描画（頂点指定）
        //--------------------------------------------------------------
        void quad(ID3D11DeviceContext*, 
            const VECTOR2(&v)[4],
            const VECTOR2&, const VECTOR2&,
            const VECTOR4&
            ) const;

        //--------------------------------------------------------------
        //  四角ポリゴン描画（頂点指定）
        //--------------------------------------------------------------
        void quad(ID3D11DeviceContext*, 
            const VECTOR2(&v)[4],
            float, float, float, float,
            float, float, float, float
            ) const;

        void draw_triangle_strip(ID3D11DeviceContext*,
            const VECTOR3* pVertex, const VECTOR4* pColor, const VECTOR2* pUvs,
            int nVert, int nPolygon
            ) const;

        void draw_triangles_indexed(ID3D11DeviceContext*,
            const VECTOR3* pVertex, const VECTOR4* pColor, const VECTOR2* pUvs,
            short* pIndices, int nVert, int nPolygon
            ) const;

        void draw_triangle_fan_indexed(ID3D11DeviceContext*,
            const VECTOR3* pVertex, const VECTOR4* pColor, const VECTOR2* pUvs,
            short* pIndices, int nPolygon
            ) const;

        //--------------------------------------------------------------
        //  スプライトのサイズ取得
        //--------------------------------------------------------------
        bool getSize(int& w, int& h);

        //--------------------------------------------------------------
        //  構造体定義
        //--------------------------------------------------------------
        struct vertex { VECTOR3 position; VECTOR4 color; VECTOR2 texcoord; };
    };

    //==========================================================================
    //
    //      SpriteBatchクラス
    //
    //==========================================================================
    class SpriteBatch
    {
    private:
        ID3D11VertexShader*         vertexShader;
        ID3D11PixelShader*          pixelShader;
        ID3D11InputLayout*          inputLayout;
        ID3D11Buffer*               buffer;
        ID3D11RasterizerState*      rasterizerState;

        ID3D11ShaderResourceView*   shaderResourceView;
        D3D11_TEXTURE2D_DESC        tex2dDesc;
        ID3D11SamplerState*         samplerState;
        ID3D11DepthStencilState*    depthStencilState;

        size_t MAX_INSTANCES;

        //--------------------------------------------------------------
        //  構造体定義
        //--------------------------------------------------------------
        struct instance
        {
            DirectX::XMFLOAT4X4 ndcTransform;
            VECTOR4 texcoordTransform;
            VECTOR4 color;
        };
        ID3D11Buffer* instanceBuffer;

    public:

        //--------------------------------------------------------------
        //  構造体定義
        //--------------------------------------------------------------
        struct vertex
        {
            VECTOR3 position;
            VECTOR2 texcoord;
        };

        //--------------------------------------------------------------
        //  コンストラクタ
        //--------------------------------------------------------------
        SpriteBatch(ID3D11Device*, const wchar_t*, size_t);

        //--------------------------------------------------------------
        //  デストラクタ
        //--------------------------------------------------------------
        ~SpriteBatch();

        //--------------------------------------------------------------
        //  前処理
        //--------------------------------------------------------------
        void begin(ID3D11DeviceContext*);

        //--------------------------------------------------------------
        //  スプライトバッチ描画
        //--------------------------------------------------------------
        void render(
            const VECTOR2&, const VECTOR2&, 
            const VECTOR2&, const VECTOR2&,
            const VECTOR2&, float angle, 
            const VECTOR4&);

        //--------------------------------------------------------------
        //  テキスト描画
        //--------------------------------------------------------------
        float textout(
            std::string, const VECTOR2&,
            const VECTOR2&, const VECTOR4&, 
            bool world = ( false ));

        //--------------------------------------------------------------
        //  後処理
        //--------------------------------------------------------------
        void end(ID3D11DeviceContext*);

    private:

        D3D11_VIEWPORT viewport;

        UINT instanceCount = 0;
        instance* instances = nullptr;
    };

}

//******************************************************************************

#endif // !INCLUDED_SPRITE
