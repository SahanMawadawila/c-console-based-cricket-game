#pragma once
#include<iostream>

using namespace std;

class player {
public:
    string name;
    int battingscore;
    int bowlingscore;
    int wickets;
    int battingSkill;
    int bowlingSkill;
    int facedballs;
    int deliveredballs;
    float noOfOvers;
    int noOfFours;
    int noOfSixes;
    player* left;
    player* right;
    bool isBat;
    bool isOnCrease;
    int isPlayed;
    bool isBowled;
public:
    player(string Name) {
        name = Name;
    }
    player(string Name, int BattingSkill, int BowlingSkill) {
        name = Name;
        battingSkill = BattingSkill;
        bowlingSkill = BowlingSkill;
        wickets = 0;
        battingscore = 0;
        bowlingscore = 0;
        facedballs = 0;
        deliveredballs = 0;
        left = NULL;
        right = NULL;
        isBat = false;
        isBowled = false;
        isOnCrease = false;
        isPlayed = 1;
        noOfOvers = 0;
        noOfFours = 0;
        noOfSixes = 0;
        noOfOvers = 0;
    }
    void increaseBattingScore(int value) {
        battingscore += value;
    }
    void increaseBowlingScore(int value) {
        bowlingscore += value;
    }

    void increaseWickets(int value) {
        wickets += value;
    }
    void increaseFacedBalls(int value) {
        facedballs += value;
    }
    void increaseDeliverdBalls(int value) {
        deliveredballs += value;
    }

    void increaseOvers(float value) {
        noOfOvers += value;
    }
    
};

