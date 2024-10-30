/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"
#include "BlockSprite.h"

USING_NS_CC;
#define PTM_RATIO 32.0

class HelloWorld : public cocos2d::Layer
{
public:
    typedef struct {
        int blockmax;
        int blockscore;
        int remaining_block;
    } level_t;
    level_t levels[21] = {
        {  5,   10,   60 },
        {  6,   25,  120 },
        {  7,   50,  180 },
        {  8,   75,  240 },
        {  9,  100,  300 },
        { 10,  125,  360 },
        { 11,  150,  420 },
        { 12,  175,  480 },
        { 13,  200,  540 },
        { 14,  225,  600 },
        { 15,  250,  660 },
        { 16,  275,  720 },
        { 17,  300,  780 },
        { 18,  350,  840 },
        { 19,  500,  900 },
        { 20,  750,  960 },
        { 21, 1000, 1020 },
        { 22, 1250, 1080 },
        { 23, 1500, 1140 },
        { 24, 2000, 1200 },
        { 25, 2250, 1260 },
    };
    enum {
        kPlaying,
        kPause,
        kGameOver,
    };
    HelloWorld();
    ~HelloWorld();

    static cocos2d::Scene* createScene();

    virtual bool init();
    // Layer::draw メソッドをオーバーライド
    virtual void draw(Renderer* renderer, const Mat4& transform, uint32_t flags) override;

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    // 物理演算初期化用メソッド
    void initPhysics();
    virtual void update(float dt);
    /** Touch listener */
    void enableTouchEvent(bool enabled);
    CC_SYNTHESIZE(EventListenerTouchOneByOne*, _touchListener, TouchListener);
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    virtual void onTouchCancelled(Touch* touch, Event* event);

    void DropTsum(Vec2 location, bool autoDrop);
    void autoDropTsum();
    bool destroyCollideBlocks();
    void checkCollisionBlocks();
    int checkCollisionTarget(BlockSprite* target);
    void checkGameOver(); 
protected:
    void onDraw(const Mat4& transform, uint32_t flags);
    GLESDebugDraw* _debugDraw;
    CustomCommand _customCmd;

    bool _isAutoDroping;
    float _ResolutionScale;
    float _scaledTsumSize;
    SpriteBatchNode* _batchNode;

    CC_SYNTHESIZE(std::vector<BlockSprite*>, _nextDropTsums, NextDropTsums);

    void initNextTsum();
    int chooseNextTsumNumber();
    void block_delete_callback(Node* sender, b2Body* b, Sprite* eff);
    void autoDropTsumCallback(float randomX);
    void autoDropEndCallback();
    void createScore(Node* rootNode, int score);

private:
    b2World* _world;
    int _state;
    CC_SYNTHESIZE(int, _level, Level);
    CC_SYNTHESIZE(int, _totalScore, TotalScore);
    CC_SYNTHESIZE(int, _score, Score);
    CC_SYNTHESIZE(int, _eraseCount, EraseCount);
    CC_SYNTHESIZE(int, _highScore, HighScore);
    CC_SYNTHESIZE(Node*, _scoreNode, ScoreNode);
    CC_SYNTHESIZE(Node*, _levelNode, LevelNode);
    CC_SYNTHESIZE(Node*, _remainingNode, RemainingNode);
    CC_SYNTHESIZE(Size, _visibleSize, VisibleSize);
    CC_SYNTHESIZE(Size, _winSize, WinSize);
};

#endif // __HELLOWORLD_SCENE_H__
