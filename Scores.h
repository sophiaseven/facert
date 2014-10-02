//
//  Scores.h
//  Sophia Hannah
//
//

#ifndef FaceGame_Scores_h
#define FaceGame_Scores_h

//#include "cocos2d.h"
//
//using namespace cocos2d;

#include <list>
#include <string>


class ScoreData{
public:
    ScoreData(std::string name, int score = 0)
    {
        this->name = name;
        this->score = score;
    }
    std::string name;
    int score;
};


class Score{
public:
    Score(int maxSize);
    ~Score();
    static Score * sharedInstance(int maxSize = 10);
    static void deleteInstance();
    
private:
    
    struct ScoreDataCompare {
        bool operator() (const ScoreData * first, const ScoreData * second) const {
            // Return true if first should go before second
            if(first->score >= second->score)
                return true;
            else
                return false;
        }
    };
    
    int m_maxSize;
    std::list<ScoreData*> * m_traning;
    std::list<ScoreData*> * m_matching;

    ScoreData* is_in(std::list<ScoreData*> *scoreList, const std::string playName);
    
public:
    
    std::list<ScoreData*> * traning() {return m_traning;}
    std::list<ScoreData*> * matching() {return m_matching;}
    
    //Under the length of score's list is 10, when score large than existence value , just can save;
    void updateTraningScore(const std::string playName, const int score);
    void updateMatchingScore(const std::string playName, const int score);
    
    void loadTraningScoreFromProfile();
    void loadMatchingScoreFromProfile();
    
    void storeTraningScoreToProfile();
    void storeMatchingScoreToProfile();
    
};

#endif
