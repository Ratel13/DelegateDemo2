/*
 * GameLayer.h
 *
 *  Created on: 2014年7月29日
 *      Author: tubuntu
 */

#ifndef GAMELAYER_H_
#define GAMELAYER_H_
#include "cocos2d.h"

USING_NS_CC;
//游戏进行的状态枚举类
typedef enum _game_status {
	GAME_STATUS_READY = 1,
	GAME_STATUS_START,
	GAME_STATUS_OVER
} GameStatus;

/**
 * 抽象的委托类，有三个虚函数，继承这个委托类的子类需要实现
 * 这三个虚函数，以便控制游戏开始，运行，结束的判断
 */
class StatusDelegate {
public:
	/**
	* When the game start, this method will be called
	*/
	virtual void onGameStart() = 0;
	/**
	* During paying, after the score changed, this method will be called
	*/
	virtual void onGamePlaying() = 0;
	/**
	* When game is over, this method will be called
	*/
	virtual void onGameEnd() = 0;
};

const int MENU_START = 10001;

class GameLayer : public Layer {
public:
	GameLayer();
	~GameLayer();
	virtual bool init();
	CREATE_FUNC(GameLayer);	//实现注册委托类的宏，delegator作为成员变量，可以调用委托类中的各个函数

	//覆写父类的onEnter函数，记得带override
	virtual void onEnter() 	//实现注册委托类的宏，delegator作为成员变量，可以调用委托类中的各个函数override;
	//实现注册委托类的宏，delegator作为成员变量，可以调用委托类中的各个函数
	CC_SYNTHESIZE(StatusDelegate*,delegator,Delegator);
private:
	void showStartButton();//显示开始按钮
	void menuStartCallback(Ref* pSender);//开始按钮回调函数
	void createSquares();//创建红色方块
	void moveFinished(Ref* pSender);//方块移动结束函数
private:
	Sprite* square;
	Size visibleSize;
	Point origin;

	GameStatus gameStatus;
};


#endif /* GAMELAYER_H_ */
