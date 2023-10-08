#pragma once
#include<iostream>
#include"Player.h"
#include"ScoreCard.h"
#include<algorithm>
#include<string>
#include<vector>
#include<iomanip>

using namespace std;


class teams {
public:
    string name;
    player* start = NULL;
    //player* bowlingStart = NULL;
    Scorecard s;
public:
    teams(string name1) :name(name1) {}
    void insertPlayer(string Name, int BattingSkill, int BowlingSkill);
    void changeName(string Name);
    void topScoreBatmens() {
        player* temp = start;
        vector<int> players;
        while (temp != NULL) {
            if (temp->battingscore != 0) {
                players.push_back(temp->battingscore);
            }
            temp = temp->right;
        }
        // Sort the vector in descending order
        sort(players.rbegin(), players.rend());

        vector<int> top3;
        // Get the top 3 elements
        if (players.size() >= 3) {
            top3 = vector<int>(players.begin(), players.begin() + 3);
        }
        else {
            top3 = vector<int>(players.begin(), players.end());
        }

        //
        vector<int> uniqueTop3;

        if (top3.size() > 0) {
            uniqueTop3.push_back(top3[0]); // Add the first element

            for (size_t i = 1; i < top3.size(); ++i) {
                bool isDuplicate = false;

                // Check if the current element is a duplicate
                for (size_t j = 0; j < i; ++j) {
                    if (top3[i] == top3[j]) {
                        isDuplicate = true;
                        break;
                    }
                }

                // If it's not a duplicate, add it to the uniqueTop3 vector
                if (!isDuplicate) {
                    uniqueTop3.push_back(top3[i]);
                }
            }
        }

        // Print the top 3 elements
        temp = start; // Reset temp to the beginning
        for (int score : uniqueTop3) {
            while (temp != NULL) {
                if (score == temp->battingscore) {
                    string name = temp->name;
                    if (temp->isPlayed == 0) {
                        name=name + "*";
                    }
                    cout << left << setw(25) << name;
                    cout << temp->battingscore << "(" << temp->facedballs << ")" << endl;
                }
                temp = temp->right;
            }
            temp = start; // Reset temp for the next iteration
        }
    }

    void topwicketBowlers() {
        player* temp = start;
        vector<int> players;
        while (temp != NULL) {
            if (temp->wickets!=0) {
                players.push_back(temp->wickets);
            }
            temp = temp->right;
        }
        // Sort the vector in descending order
        sort(players.rbegin(), players.rend());

        vector<int> top3;
        // Get the top 3 elements
        if (players.size() >= 3) {
            top3 = vector<int>(players.begin(), players.begin() + 3);
        }
        else {
            top3 = vector<int>(players.begin(), players.end());
        }


        //
        vector<int> uniqueTop3;

        if (top3.size() > 0) {
            uniqueTop3.push_back(top3[0]); // Add the first element

            for (size_t i = 1; i < top3.size(); ++i) {
                bool isDuplicate = false;

                // Check if the current element is a duplicate
                for (size_t j = 0; j < i; ++j) {
                    if (top3[i] == top3[j]) {
                        isDuplicate = true;
                        break;
                    }
                }

                // If it's not a duplicate, add it to the uniqueTop3 vector
                if (!isDuplicate) {
                    uniqueTop3.push_back(top3[i]);
                }
            }
        }

        // Print the top 3 elements
        temp = start; // Reset temp to the beginning
        for (int score : uniqueTop3) {
            while (temp != NULL) {
                if (score == temp->wickets) {
                    cout << left << setw(25) << temp->name << temp->wickets << "-" << temp->bowlingscore;
                    cout<<right<<setw(20)<< temp->noOfOvers << endl;
                }
                temp = temp->right;
            }
            temp = start; // Reset temp for the next iteration
        }
    }

    
    
};

void teams::changeName(string Name) {
    name = Name;
}

void teams::insertPlayer(string Name, int BattingSkill, int BowlingSkill) {
    player* newNode = new player(Name, BattingSkill, BowlingSkill);

    if (start == NULL) {
        start = newNode;
        return;
    }

    player* lastNode = start;
    while (lastNode->right != NULL)
        lastNode = lastNode->right;
    newNode->left = lastNode;
    lastNode->right = newNode;
}
