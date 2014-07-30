/*
 * GameLayer.cpp
 *
 *  Created on: 2014年7月29日
 *      Author: tubuntu
 */
#include "GameLayer.h"

USING_NS_CC;

GameLayer::GameLayer(){
}
GameLayer::~GameLayer() {
}

bool GameLayer::init() {
	if(!Layer::init()) {
		return false;
	}
	this->gameStatus = GAME_STATUS_READY;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	//调用显示开始按钮
	this->showStartButton();

	return true;
}

void GameLayer::onEnter() {
	Layer::onEnter();
	//TODO
}
/**
 * 显示开始按钮，并为按钮注册回调函数
 */
void GameLayer::showStartButton() {
	Sprite* startBtn = Sprite::createWithSpriteFrameName("play.png");
	Sprite* startBtnActive = Sprite::createWithSpriteFrameName("play.png");
	startBtn->setScale(0.6f);//缩放
	startBtnActive->setScale(0.6f);//缩放
	startBtnActive->setPositionY(4);//使button向上移动4个单位
	//将上述精灵作为菜单进行添加
	auto menuStartItem = MenuItemSprite::create(startBtn,startBtnActive,NULL,
			CC_CALLBACK_1(GameLayer::menuStartCallback,this));
	auto menuStart = Menu::create(menuStartItem,NULL);
	menuStart->setPosition(Vec2(this->visibleSize.width/2, this->visibleSize.height/2));
	menuStart->setTag(MENU_START);
	this->addChild(menuStart,10);

}
/**
 * 按下开始菜单后的回调函数，主要是调用委托类中的onGameStart函数来实现游戏的开始
 * 同时移除开始按钮并创建游戏主界面中的红色小方块
 */
void GameLayer::menuStartCallback(Ref* pSender) {
	if(this->gameStatus == GAME_STATUS_OVER) {
		return ;
	}
	if(this->gameStatus == GAME_STATUS_READY) {
		log("start");
		//委托StatusLayer中的onGameStart函数来执行游戏开始逻辑
		this->delegator->onGameStart();
		this->getChildByTag(MENU_START)->runAction(FadeOut::create(0.4f));
		this->removeChildByTag(MENU_START,true);
		this->gameStatus = GAME_STATUS_START;
		this->createSquares();//创建红色小方块
	} else if(this->gameStatus  == GAME_STATUS_START) {
		//TODO
	}
}
/**
 * 创建红色小方块，并在移动5s后游戏结束
 */
void GameLayer::createSquares(){
	//添加方块精灵
	square = Sprite::createWithSpriteFrameName("whitebird.png");
	square->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	square->setColor(Color3B::RED);
	this->addChild(square);
	//游戏开始，5秒后游戏结束
	auto move = MoveTo::create(5.0f,Vec2(square->getPositionX(),origin.y));
	//移动结束后回调函数
	auto moveDone = CallFuncN::create(CC_CALLBACK_1(GameLayer::moveFinished,this));
	auto sequence = Sequence::createWithTwoActions(move,moveDone);
	square->runAction(sequence);
}
/**
 * 移动结束后的回调函数，也就是游戏结束，
 * 其中可以开到delegator->onGameEnd的运用
 * 这个是直接使用委托类的onGameEnd来控制游戏结束
 * 是不是瞬间感觉这个类清晰了许多，
 */
void GameLayer::moveFinished(Ref* pSender) {
	//委托StatusLayer中的onGameEnd函数执行游戏结束的逻辑
	this->delegator->onGameEnd();
	this->removeChild(square,true);
}
