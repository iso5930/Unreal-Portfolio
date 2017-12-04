// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
/**
 * 
 */
class HUNTER_API HT_QuestMgr
{
private:
	TArray<class HT_Quest*> QuestList[5];

public:
	HT_QuestMgr();
	~HT_QuestMgr();
};