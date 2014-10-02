//
//  Scores.cpp
//  Sophia Hannah
//
//

#include "Scores.h"
#include "cocos2d.h"
#include "CCUserDefault.h"

#define TRAING_NUM "traing_num"
#define MATCHING_NUM "matching_num"

#define TRAING_PLAYER "training_player%d"
#define TRAING_SCORE "training_score%d"

#define MATCHING_PLAYER "matching_player%d"
#define MATCHING_SCORE "matching_score%d"

using namespace cocos2d;

static Score * m_instance = NULL;

Score* Score::sharedInstance(int maxSize)
{
    if(m_instance == NULL)
        m_instance = new Score(maxSize);
    return m_instance;
}

void Score::deleteInstance()
{
    if(m_instance)
        delete m_instance;
    m_instance = NULL;
}

Score::Score(int maxSize)
{
    m_maxSize = maxSize;
    m_traning = new std::list<ScoreData*>();
    m_matching = new std::list<ScoreData*>();
}

Score::~Score()
{
    delete m_traning;
    delete m_matching;
}

void Score::updateTraningScore(const std::string playname, const int score)
{
    ScoreData* scoreData = is_in(m_traning, playname);
    if(scoreData)
    {
        scoreData->score = score;
    }
    else
    {
        scoreData = new ScoreData(playname, score);
        m_traning->push_back(scoreData);
    }
    m_traning->sort(ScoreDataCompare());
    if(m_traning->size() > m_maxSize)
        m_traning->resize(m_maxSize);
}

void Score::updateMatchingScore(const std::string playname, const int score)
{
    ScoreData* scoreData = is_in(m_matching, playname);
    if(scoreData)
    {
        scoreData->score = score;
    }
    else
    {
        scoreData = new ScoreData(playname, score);
        m_matching->push_back(scoreData);
    }
    m_matching->sort(ScoreDataCompare());
    if(m_matching->size() > m_maxSize)
        m_matching->resize(m_maxSize);
}

ScoreData* Score::is_in(std::list<ScoreData*> *scoreList, const std::string playName)
{
    std::list<ScoreData*>::iterator it;
    ScoreData * pScoreData = NULL;
    it = scoreList->begin();
    while(it != scoreList->end())
    {
        if(((ScoreData*)*it)->name.compare(playName) == 0)
        {
            pScoreData = (ScoreData*)*it;
            break;
        }
        it ++;
    }
    return pScoreData;
}

void Score::loadTraningScoreFromProfile()
{
    char buf[100] = {0};
    sprintf(buf, TRAING_NUM);
    int number = CCUserDefault::sharedUserDefault()->getIntegerForKey(buf);
    while (number > 0) {
        memset(buf, sizeof(char) * 100, 0x0);
        sprintf(buf, TRAING_PLAYER, number);
        std::string playerName = CCUserDefault::sharedUserDefault()->getStringForKey(buf);
        memset(buf, sizeof(char) * 100, 0x0);
        sprintf(buf, TRAING_SCORE, number);
        int playerScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(buf);
        ScoreData* pScoreData = new ScoreData(playerName, playerScore);
        m_traning->push_front(pScoreData);
//        std::cout << pScoreData->name << " " << pScoreData->score << std::endl;
        number --;
    }
}
void Score::loadMatchingScoreFromProfile()
{
    char buf[100] = {0};
    sprintf(buf, MATCHING_NUM);
    int number = CCUserDefault::sharedUserDefault()->getIntegerForKey(buf);
    while (number > 0) {
        memset(buf, sizeof(char) * 100, 0x0);
        sprintf(buf, MATCHING_PLAYER, number);
        std::string playerName = CCUserDefault::sharedUserDefault()->getStringForKey(buf);
        memset(buf, sizeof(char) * 100, 0x0);
        sprintf(buf, MATCHING_SCORE, number);
        int playerScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(buf);
        ScoreData* pScoreData = new ScoreData(playerName, playerScore);
        m_matching->push_front(pScoreData);
//        std::cout << pScoreData->name << " " << pScoreData->score << std::endl;
        number --;
    }
}

void Score::storeTraningScoreToProfile()
{
    int number = m_traning->size();
    if(number == 0)
        return;
    char buf[100] = {0};
    sprintf(buf, TRAING_NUM);
    CCUserDefault::sharedUserDefault()->setIntegerForKey(buf, number);
    number = 1;
    for(std::list<ScoreData*>::iterator it = m_traning->begin(); it != m_traning->end(); it++)
    {
        ScoreData* pScoreData = (ScoreData*)*it;
        memset(buf, sizeof(char) * 100, 0x0);
        sprintf(buf, TRAING_PLAYER, number);
        CCUserDefault::sharedUserDefault()->setStringForKey(buf, pScoreData->name);
        memset(buf, sizeof(char) * 100, 0x0);
        sprintf(buf, TRAING_SCORE, number);
        CCUserDefault::sharedUserDefault()->setIntegerForKey(buf, pScoreData->score);
//        std::cout << pScoreData->name << " " << pScoreData->score << std::endl;
        number ++;
    }
    CCUserDefault::sharedUserDefault()->flush();
}
void Score::storeMatchingScoreToProfile()
{
    int number = m_matching->size();
    if(number == 0)
        return;
    char buf[100] = {0};
    sprintf(buf, MATCHING_NUM);
    CCUserDefault::sharedUserDefault()->setIntegerForKey(buf, number);
    number = 1;
    for(std::list<ScoreData*>::iterator it = m_matching->begin(); it != m_matching->end(); it++)
    {
        ScoreData* pScoreData = (ScoreData*)*it;
        memset(buf, sizeof(char) * 100, 0x0);
        sprintf(buf, MATCHING_PLAYER, number);
        CCUserDefault::sharedUserDefault()->setStringForKey(buf, pScoreData->name);
        memset(buf, sizeof(char) * 100, 0x0);
        sprintf(buf, MATCHING_SCORE, number);
        CCUserDefault::sharedUserDefault()->setIntegerForKey(buf, pScoreData->score);
//        std::cout << pScoreData->name << " " << pScoreData->score << std::endl;
        number ++;
    }
    CCUserDefault::sharedUserDefault()->flush();
}

