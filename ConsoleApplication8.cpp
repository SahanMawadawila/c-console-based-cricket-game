#include <iostream>
#include <cstdlib> 
#include<iomanip>
#include <ctime> 
#include <chrono>
#include<thread>
#include<cmath>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include<algorithm>
#include"Team.h"
#include"Umpire.h"


using namespace std;

class match {
    string time;
    string ground;
    teams* t1;
    teams* t2;
    Umpire* u1;
    Umpire* u2;
public:
    match(string Time, string Ground, teams* t3, teams* t4, Umpire* u3, Umpire* u4) {
        time = Time;
        ground = Ground;
        t1 = t3;
        t2 = t4;
        u1 = u3;
        u2 = u4;
    }
    void GetmatchDetails() {
        cout << "********* Welcome to the match between " << t1->name << " and " << t2->name << " at " << ground << " at " << time << " *********" << endl << endl;
        cout << u1->GetName() << " and " << u2->GetName() << " are the two umpires." << endl;
    }
};
class Captain :public player {
public:
    string team;

public:
    Captain(string Name, string Team) :player(Name) {
        team = Team;
    }

};

class toss {
private:
    char headOrTail;
    int HorT;
    char BatorFeild;
    string ToswonTeam;
public:
    string FlipCoin(Captain* c1, Captain* c2) {
        int randomNumber = rand() % 2;
        if (randomNumber == 1) {
            cout << "Captain " << c1->name << " will flip the coin. " << endl;
        }
        else {
            cout << "Captain " << c2->name << " will flip the coin. " << endl;
        }
        cout << "H or T? :";
        cin >> headOrTail;
        cout << ((headOrTail == 'H' || headOrTail == 'h') ? "Head is called" : "Tail is called");
        if (randomNumber == 1) {
            cout << " by captain " << c2->name << endl;
        }
        else {
            cout << " by captain " << c1->name << endl;
        }
        if (headOrTail == 'H' || headOrTail == 'h') {
            HorT = 0;
        }
        else {
            HorT = 1;
        }
        int randomNumber2 = rand() % 2;
        if (HorT == randomNumber2 && randomNumber == 1) {
            cout << "Team " << c2->team << " won the toss and elected to (B/F)? " << endl;
            ToswonTeam = c2->team;
        }
        else if (HorT != randomNumber2 && randomNumber == 1) {
            cout << "Team " << c1->team << " won the toss and elected to (B/F)? " << endl;
            ToswonTeam = c1->team;
        }
        else if (HorT == randomNumber2 && randomNumber != 1) {
            cout << "Team " << c1->team << " won the toss and elected to (B/F)? " << endl;
            ToswonTeam = c1->team;
        }
        else if (HorT != randomNumber2 && randomNumber != 1) {
            cout << "Team " << c2->team << " won the toss and elected to (B/F)? ";
            ToswonTeam = c2->team;
        }
        cin >> BatorFeild;
        cout << ((BatorFeild == 'B' || BatorFeild == 'b') ? "Bat first" : "Feild first") << endl << endl;
        return (ToswonTeam + " " + BatorFeild);
    }

};

//calculate total socre by a team
int scoreSum(teams team) {
    int sum = 0;
    player* temp = team.start;

    while (temp != NULL) {
        sum += temp->battingscore;
        temp = temp->right;
    }

    return sum+team.s.extraRuns;
}


// Function to calculate the total overs by the team
float OversSum(teams team) {
    float sum = 0;
    player* temp = team.start;

    while (temp != NULL) {
        sum += temp->noOfOvers;
        temp = temp->right;
    }

    return sum;
}

//convert to uppercase
string toUpperCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}


void printBattingScorecard(teams batting, teams bowling) {
    // Calculate total score and total wickets
    int totalScore = scoreSum(batting);
    cout << endl;
    cout << "------------------------------------------------------------------------------------------------" << endl;
    cout << "Batting Scorecard for Team: " << batting.name << setw(22) << "     Total: " << totalScore  << "/" << batting.s.totalWickets << "   " << "Overs: " << OversSum(bowling) << "   " << " Extra:" << batting.s.extraRuns << endl << endl;
    cout << left << setw(25) << "Name" << setw(15) << "Score" << setw(15) << "Balls Faced" << setw(15) << "Status" << setw(10) << "4s" << setw(10) << "6s" << setw(15) << "S/R" << endl;
    cout << "------------------------------------------------------------------------------------------------" << endl;

    player* temp = batting.start;
    while (temp != NULL) {
        cout << left << setw(25) << temp->name << setw(15) << temp->battingscore << setw(15) << temp->facedballs << setw(15);
        if (temp->isPlayed == 1)
            cout << "Not Played";
        else if (temp->isPlayed == 0)
            cout << "Not out";
        else if (temp->isPlayed == 2)
            cout << "Out";

        cout << setw(10) << temp->noOfFours << setw(10) << temp->noOfSixes << setw(15);
        if (temp->isPlayed == 1)
            cout << " - ";
        else if (temp->isPlayed == 0 && temp->facedballs == 0) {
            cout << "0";
        }
        else
            cout << left << fixed << setprecision(2) << (1.0 * temp->battingscore / temp->facedballs);
        cout << endl;
        temp = temp->right;
    }
}

// Function to print bowling team scorecard as a table
void printBowlingScorecard(teams team) {
    cout << endl;
    cout << "\nBowling Scorecard for Team:" << team.name << endl << endl;
    cout << left << setw(25) << "Name" << setw(15) << "Overs" << setw(15) << "Wickets" << setw(15) << "Runs" << setw(15) << "Economy" << endl;
    cout << "------------------------------------------------------------------------------------------------" << endl;

    player* temp = team.start;
    while (temp != NULL) {
        if (temp->isBowled) {
            cout << left << setw(25) << temp->name << setw(15) << fixed << setprecision(1) << temp->noOfOvers << setw(15) << temp->wickets << setw(15) << temp->bowlingscore << setw(15) << (temp->bowlingscore / temp->noOfOvers) << endl;

        }
        temp = temp->right;
    }
    cout << "------------------------------------------------------------------------------------------------" << endl;
}


//essentioal verables
string previousBowler = "";
string randomBowler = "";
//randombowler selector
player* randomBowlerSelecter(teams& team) {
    vector<string> bowlers;
    player* temp = team.start;
    while (temp != NULL) {
        //select players who can ball
        if (temp->bowlingSkill > 60 && temp->noOfOvers <= 3) {
            bowlers.push_back(temp->name);
        }
        temp = temp->right;
    }
    
    while (randomBowler == previousBowler) {
        int randomValue = rand() % (bowlers.size());
        randomBowler = bowlers[randomValue];

    }
    previousBowler = randomBowler;


    //search that object
    player* temp2 = team.start;
    while (randomBowler != temp2->name) {
        temp2 = temp2->right;
    }
    temp2->isBowled = true;
    return temp2;

}


void matchSummary(teams& batting, teams& bowling) {
    cout << endl << endl;
    cout <<"              ************ MATCH SUMMARY ************" << endl;
    cout << "-----------------------------------------------------------------------" << endl;

    // Print batting team summary
    cout << left << setw(20) << toUpperCase(batting.name) << setw(5) << right << OversSum(bowling) << " OVERS" << setw(30) << scoreSum(batting) << "/" << batting.s.totalWickets << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    batting.topScoreBatmens();
    cout << endl;
    bowling.topwicketBowlers();

    cout << endl << endl;

    // Print bowling team summary
    cout << "-----------------------------------------------------------------------" << endl;
    cout << left << setw(20) << toUpperCase(bowling.name) << setw(5) << right << OversSum(batting) << " OVERS" << setw(30) << scoreSum(bowling)  << "/" << bowling.s.totalWickets << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    bowling.topScoreBatmens();
    cout << endl;
    batting.topwicketBowlers();
}


void simulateBatting(teams& batting, teams& bowling, int breakingLoop, bool isSecondBattingTeam) {

    int noOfBalls = 0;
    player* currentBowler = randomBowlerSelecter(bowling);
    player* currentBatsman = batting.start;
    currentBatsman->isBat = true; currentBatsman->isOnCrease = true, currentBatsman->isPlayed = 0;
    currentBatsman->right->isBat = true; currentBatsman->right->isOnCrease = true; currentBatsman->right->isPlayed = 0;


    while (noOfBalls < 120 && batting.s.totalWickets < 10 && batting.s.totalScore < breakingLoop) {

        // Generate a random value between 0 and 99
        int randomBowl = rand() % 100;
        int totalBowlingSkill = (randomBowl + currentBowler->bowlingSkill) / 2;
        if (currentBatsman->battingSkill < totalBowlingSkill) {   // Out of ball, leave
            currentBatsman->increaseFacedBalls(1);
            cout << currentBowler->name << " to " << currentBatsman->name;
            //direct out
            if (totalBowlingSkill > currentBatsman->battingSkill * 1.04) {
                //
                cout << " OUT!.." << endl;
                batting.s.totalWickets++;
                currentBatsman->isPlayed = 2;
                currentBatsman->isOnCrease = false;
                while (currentBatsman->isBat == true && batting.s.totalWickets < 10) {
                    currentBatsman = currentBatsman->right;
                }
                currentBatsman->isBat = true;
                if (batting.s.totalWickets != 10) {
                    currentBatsman->isPlayed = 0;
                }
                currentBatsman->isOnCrease = true;
                currentBowler->increaseWickets(1);
            }
            //LBW
            else if (totalBowlingSkill > currentBatsman->battingSkill * 1.02) {
                cout << " LBW ";
                //getting random number
                int umpirescall = rand() % 2;
                if (umpirescall == 1) {
                    cout << " PITCHING IN LINE, IMPACT IN LINE..OUT!.." << endl;
                    batting.s.totalWickets++;
                    currentBatsman->isPlayed = 2;
                    currentBatsman->isOnCrease = false;
                    while (currentBatsman->isBat == true && batting.s.totalWickets < 10) {
                        currentBatsman = currentBatsman->right;
                    }
                    currentBatsman->isBat = true;
                    if (batting.s.totalWickets != 10) {
                        currentBatsman->isPlayed = 0;
                    }
                    currentBatsman->isOnCrease = true;
                    currentBowler->increaseWickets(1);
                }
                else {
                    cout << " PITCHING OUTSIDE OFF..NOT OUT.." << endl;
                }


            }
            else {
                cout << " OH!..What a delivery.Very close to the bat. No score." << endl;
            }


        }
        else {
            currentBatsman->increaseFacedBalls(1);
            cout << currentBowler->name << " to " << currentBatsman->name;
            //leave the ball
            if (totalBowlingSkill > currentBatsman->battingSkill * 0.83) {
                cout << " Straight to the fielder.. No score." << endl;
            }
            //one run
            else if (totalBowlingSkill > currentBatsman->battingSkill * 0.73) {
                currentBatsman->increaseBattingScore(1);
                currentBowler->increaseBowlingScore(1);
                cout << " One run." << endl;
                //batmens exchanging
                player* x = currentBatsman;
                player* y = batting.start;
                while (y->isOnCrease == false || y == x) {
                    y = y->right;
                }
                currentBatsman = y;

            }
            //2 runs
            else if (totalBowlingSkill > currentBatsman->battingSkill * 0.63) {
                currentBatsman->increaseBattingScore(2);
                currentBowler->increaseBowlingScore(2);
                cout << " 2 Runs.." << endl;
            }
            //3 runs
            else if (totalBowlingSkill > currentBatsman->battingSkill * 0.58) {
                currentBatsman->increaseBattingScore(3);
                currentBowler->increaseBowlingScore(3);
                cout << " 3 Runs.." << endl;
                //batmens exchanging
                player* x = currentBatsman;
                player* y = batting.start;
                while (y->isOnCrease == false || y == x) {
                    y = y->right;
                }
                currentBatsman = y;
            }
            //4 runs
            else if (totalBowlingSkill > currentBatsman->battingSkill * 0.53) {
                currentBatsman->increaseBattingScore(4);
                currentBowler->increaseBowlingScore(4);
                currentBatsman->noOfFours++;
                cout << " WOW.. FOUR!.. " << endl;
            }
            //6 runs
            else if (totalBowlingSkill > currentBatsman->battingSkill * 0.46) {
                currentBatsman->increaseBattingScore(6);
                currentBowler->increaseBowlingScore(6);
                currentBatsman->noOfSixes++;
                cout << " ABSOLUTELY MAGNIFICENT..SIX!.." << endl;
            }
            //wides
            else if (totalBowlingSkill > currentBatsman->battingSkill * 0.43) {
                cout << " WIDE BALL.." << endl;
                currentBatsman->increaseFacedBalls(-1);
                currentBowler->increaseDeliverdBalls(-1);
                currentBowler->increaseBowlingScore(1);
                batting.s.extraRuns++;
                noOfBalls--;
            }
            //noball
            else {
                cout << " NO BALL.." << endl;
                currentBatsman->increaseFacedBalls(-1);
                currentBowler->increaseDeliverdBalls(-1);
                currentBowler->increaseBowlingScore(1);
                batting.s.extraRuns++;
                noOfBalls--;
            }
        }

        noOfBalls++;
        currentBowler->increaseDeliverdBalls(1);
        //if its 10 wickets down
        if (batting.s.totalWickets == 10 && currentBowler->deliveredballs != 6) {
            currentBowler->increaseOvers(currentBowler->deliveredballs / 10.0);
        }
        //changing over
        if (currentBowler->deliveredballs == 6) {
            currentBowler->increaseOvers(1);
            currentBowler->deliveredballs = 0;
            currentBowler = randomBowlerSelecter(bowling);

            cout << endl;
            //batmens changing
            player* x = currentBatsman;
            player* y = batting.start;
            while (y->isOnCrease == false || y == x) {
                y = y->right;
            }
            currentBatsman = y;
        }

        batting.s.totalScore = scoreSum(batting);
        // Pause for 1 second (100 milliseconds)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    //last over update
    if (batting.s.totalScore >= breakingLoop && currentBowler->deliveredballs != 6) {
        currentBowler->increaseOvers(currentBowler->deliveredballs / 10.0);
    }
    // Calculate and display batting scorecard for Team India
    printBattingScorecard(batting, bowling);

    // Calculate and display bowling scorecard for Team Sri Lanka (starting from player 6)
    printBowlingScorecard(bowling);
    //
    //
    if(isSecondBattingTeam)
    matchSummary(bowling, batting);

    if (scoreSum(batting) >= breakingLoop) {
        cout << endl;
        cout << "-----------------------------------------------------------------------" << endl;
        cout << batting.name << " won by " << (10 - batting.s.totalWickets) << " Wickets." << endl;
        cout << "-----------------------------------------------------------------------" << endl;
    }

    if (isSecondBattingTeam && batting.s.totalScore < breakingLoop) {
        cout << endl;
        cout << "-----------------------------------------------------------------------" << endl;
        cout << bowling.name << " won by " << (scoreSum(bowling) - scoreSum(batting)) << " runs." << endl;
        cout << "-----------------------------------------------------------------------" << endl;
    }

}


// line to array
void stringToArray(string str, string* arr) {
    istringstream iss(str);
    string word;
    int i = 0;
    while (iss >> word)
    {

        arr[i] = word;
        i++;
    }
}

// A function to put elements of wordsOfALine array to NULL
void setArrayToNull(string* ptr, int x)
{
    for (int i = 0; i < x; i++)
    {
        ptr[i] = "";
    }
}



int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(0)));
    ifstream File;
    string fileLine;
    const int size = 10;
    string arr[size];

    if (argc < 2) {
        cerr << "Error: No input file name is provided" << endl;
        return -1;
    }

    File.open(argv[1], ios::in);

    //variables
    bool isTeamone = true;
    bool isFirstUmpire = true;
    string time;
    string ground;
    string captain1;
    string captain2;

    //objects
    teams team1("NULL");
    teams team2("NULL");
    Umpire u1("NULL");
    Umpire u2("NULL");

    while (getline(File, fileLine)) {
        stringToArray(fileLine, arr);
        try {
            if (arr[0] == "Team" && isTeamone) {
                team1.changeName((arr[1]));
                isTeamone = false;
            }
            else if (arr[0] == "Team" && !isTeamone) {
                team2.changeName((arr[1]));
                isTeamone = true;
            }
            else if (arr[0] == "Player:" && !isTeamone) {
                team1.insertPlayer(arr[1] + " " + arr[2], stoi(arr[3]), stoi(arr[4]));
                if (arr[5] == "(c)") {
                    captain1 = arr[1] + " " + arr[2];
                }
            }
            else if (arr[0] == "Player:" && isTeamone) {
                team2.insertPlayer(arr[1] + " " + arr[2], stoi(arr[3]), stoi(arr[4]));
                if (arr[5] == "(c)") {
                    captain2 = arr[1] + " " + arr[2];
                }
            }
            else if (arr[0] == "Umpire:" && isFirstUmpire) {
                u1.chageName(arr[1] + " " + arr[2]);
                isFirstUmpire = false;
            }
            else if (arr[0] == "Umpire:" && !isFirstUmpire)
            {
                u2.chageName(arr[1] + " " + arr[2]);
            }
            else if (arr[0] == "Ground:") {
                ground = arr[1] + " " + arr[2];
            }
            else if (arr[0] == "Time:") {
                time = arr[1];
            }
            setArrayToNull(arr, 10);
        }
        catch (const std::invalid_argument& e) {
            // Handle the exception here
            std::cerr << "Error: " << e.what() << " in line: " << fileLine << std::endl;
            return 0;
        }
    }

    //match object
    match m(time, ground, &team1, &team2, &u1, &u2);
    m.GetmatchDetails();

    //captain Objects
    Captain c1(captain1, team1.name);
    Captain c2(captain2, team2.name);

    //toss object
    toss t;
    string tosWonTeam = t.FlipCoin(&c1, &c2);
    stringToArray(tosWonTeam, arr);
    if (team1.name == arr[0] && (arr[1] == "B" || arr[1] == "b") || team2.name == arr[0] && (arr[1] == "F" || arr[1] == "f")) {
        simulateBatting(team1, team2, 1000000, false);
        cout << " Press Enter to continue the game...." << endl;
        cin.ignore();
        cin.get();
        cout << endl;
        int targetScore = scoreSum(team1) + 1;
        simulateBatting(team2, team1, targetScore, true);
    }
    else if (team2.name == arr[0] && (arr[1] == "B" || arr[1] == "b") || team1.name == arr[0] && (arr[1] == "F" || arr[1] == "f"))
    {
        simulateBatting(team2, team1, 1000000, false);
        cout << " Press Enter to continue the game...." << endl;
        cin.ignore();
        cin.get();
        cout << endl;
        int targetScore = scoreSum(team2) + 1;
        simulateBatting(team1, team2, targetScore, true);
    }

  
    File.close(); // Close the file when done


    return 0;
}