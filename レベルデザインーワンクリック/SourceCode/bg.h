#ifndef INCLUDED_BG
#define INCLUDED_BG

//******************************************************************************
//
//
//      bg.h
//
//
//******************************************************************************

//==============================================================================
//
//      BGクラス
//
//==============================================================================

class BG
{
public:
    //------< 定数 >------------------------------------------------------------
    static const int CHIP_NUM_X = 30;                       // マップの横方向のチップ数
    static const int CHIP_NUM_Y = 20;                       // マップの縦方向のチップ数
    static const int CHIP_SIZE = 32;                        // %演算子を使用するためint型を使用する
    static const int CHIP_NUM_PER_LINE = 8;                 // マップチップの1列が8個
    static const int CHIP_LINE_NUM = 4;                     // マップチップが４行

    static constexpr float WIDTH = static_cast<float>(CHIP_NUM_X * CHIP_SIZE);  // マップの幅（ドット）
    static constexpr float HEIGHT = static_cast<float>(CHIP_NUM_Y * CHIP_SIZE); // マップの高さ（ドット）
    static constexpr float SCROLL_MERGIN_X = 120.f;         // この数値より画面端に近づいたらスクロールする（横）
    static constexpr float SCROLL_MERGIN_Y = 80.f;          // この数値より画面端に近づいたらスクロールする（縦）
    static constexpr float ADJUST_Y = 0.125f;               // あたり判定での位置調整用（縦）
    static constexpr float ADJUST_X = 0.0125f;              // あたり判定での位置調整用（横）

    // 地形（Terrain）の属性
    enum TR_ATTR
    {
        TR_NONE = -1,   // -1:何もなし
        ALL_BLOCK,      //  0:四方ブロック
        UPPER_BLOCK,    //  1:上だけブロック
        HASHIGO,        //  2:はしご
		NEEDLE,
    };

    // 背景（Back）の属性
    enum BG_ATTR
    {
        BG_NONE = -1,   // -1:何もなし
        NORMAL,         //  0:普通（特に何もなし）
        WATER,          //  1:水中（抵抗を受ける）
		
    };

	int stage = 2;

private:
    // 地形チップテクスチャの各部分の属性を定義する
    const TR_ATTR terrainAttr[CHIP_LINE_NUM][CHIP_NUM_PER_LINE] = {
        { ALL_BLOCK,   ALL_BLOCK,   ALL_BLOCK,   ALL_BLOCK,    NEEDLE,		 NEEDLE,		NEEDLE,	   NEEDLE,},
        { UPPER_BLOCK, UPPER_BLOCK, UPPER_BLOCK, UPPER_BLOCK,TR_NONE, ALL_BLOCK, ALL_BLOCK, ALL_BLOCK,	 },
        { HASHIGO,     HASHIGO,     TR_NONE,     TR_NONE,     TR_NONE,   TR_NONE,   TR_NONE,   TR_NONE,  },
		 { HASHIGO,     HASHIGO,     TR_NONE,     TR_NONE,     TR_NONE,   TR_NONE,   TR_NONE,   TR_NONE,  },
    };

    // 背景チップテクスチャの各部分の属性を定義する
    const BG_ATTR bgAttr[CHIP_LINE_NUM][CHIP_NUM_PER_LINE] = {
        { NORMAL,      NORMAL,      NORMAL,      NORMAL,      NORMAL,    NORMAL,    BG_NONE,   BG_NONE, },
        { WATER,       WATER,       WATER,       WATER,       BG_NONE,   BG_NONE,   BG_NONE,   BG_NONE, },
        { BG_NONE,     BG_NONE,     BG_NONE,     BG_NONE,     BG_NONE,   BG_NONE,   BG_NONE,   BG_NONE, },
        { BG_NONE,     BG_NONE,     BG_NONE,     BG_NONE,     BG_NONE,   BG_NONE,   BG_NONE,   BG_NONE, },
    };

    //------< 変数 >------------------------------------------------------------
    VECTOR2 scroll;                                         // 現在表示されている左上の地点の座標

    char back[CHIP_NUM_Y][CHIP_NUM_X];                      // 背景データ
    char terrain[CHIP_NUM_Y][CHIP_NUM_X];                   // 地形データ

public:
    BG();
    ~BG();

    // 初期化
    void init();

    // 更新
    void update();

    // 描画
    void drawBack();                                        // 背景描画
    void drawTerrain();                                     // 地形描画

    // スクロール位置取得
    float getScrollX() { return scroll.x; }
    float getScrollY() { return scroll.y; }
    const VECTOR2& getScrollPos() { return scroll; }

    // 当たり判定
    // 下方向
    bool isFloor(float, float, float);          // 床にめり込んでいるか
    void mapHoseiDown(OBJ2D*);                  // 下方向補正処理

    // 上方向
    bool isCeiling(float, float, float);        // 天井にあたっているか
    void mapHoseiUp(OBJ2D*);                    // 上方向補正処理

    // 横方向
    bool isWall(float, float, float);           // 横方向に壁にめり込んでいるか
    void mapHoseiRight(OBJ2D*);                 // 右方向補正処理
    void mapHoseiLeft(OBJ2D*);                  // 左方向補正処理


	//はりに対する処理
	bool BG::isNeedle(float x, float y, float width,float height);

	char(*getTerrain())[BG::CHIP_NUM_X]{ return terrain; }
private:
    // クリア
    void clear();

    // マップデータのロード
    bool loadMapData(const char[CHIP_NUM_Y][CHIP_NUM_X], char[CHIP_NUM_Y][CHIP_NUM_X]);

    // BG、Terrain共通の描画関数
    void draw(int, char[CHIP_NUM_Y][CHIP_NUM_X]);  // 描画処理（スムーズなスクロール）

    // マップスクロール用
    void scrollMap();

    bool isHitDown(float, float);
    bool isHitAll(float, float);
    bool isUpperQuater(float);
    TR_ATTR getTerrainAttr(float, float);
    int getData(char[CHIP_NUM_Y][BG::CHIP_NUM_X], float, float);
};

//******************************************************************************

#endif // ! INCLUDED_BG
