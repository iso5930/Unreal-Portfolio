// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class HUNTER_API HT_Quest
{
public:
	enum QUEST_STATE
	{
		QUEST_STATE_LOCK,
		QUEST_STATE_OPEN,
		QUEST_STATE_ACCEPT,
		QUEST_STATE_COMPLETE,
		QUEST_STATE_CLEAR,
		QUEST_STATE_END
	};

	enum QUEST_TYPE
	{
		QUEST_TYPE_GATHER,
		QUEST_TYPE_HUNTING,
		QUEST_TYPE_TALK,
		QUEST_TYPE_END
	};

private:
	FString Quest_Name;
	int Quest_Num;

private:
	bool IsPrecede; //���� ����Ʈ�ΰ�..?
	int PrecedeQuestNum; //�ִٸ� ����ΰ�.

	int QuestLevel; //����Ʈ ����.

public:
	QUEST_STATE QusetState = QUEST_STATE::QUEST_STATE_LOCK;
	QUEST_TYPE QuestType = QUEST_TYPE::QUEST_TYPE_END;

public:
	HT_Quest();
	~HT_Quest();
};