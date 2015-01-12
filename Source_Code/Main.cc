#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include "helper.h"
#include "Floor.h"
#include "Chamber.h"
#include "Entity.h"
#include "Character.h"
#include "Item.h"
#include "Tile.h"
#include "Hero.h"
using namespace std;

string ActionMsg = "";

// GetRace() prompts the user for a valid input on the race they would like to choose
string GetRace(){
    //Race is the place holder that cin will be reads to
    char race = '\0';
    //result is the acutal out put of the race string
    string result = "";
    //Print message
    cout<< "Pick your Hero!" <<endl;
    cout<< "(S)hade!" <<endl;
    cout<< "(D)row" <<endl;
    cout<< "(V)ampire" <<endl;
    cout<< "(T)roll" <<endl;
    cout<< "(G)oblin" <<endl;
    cout<< "or (q)uit" << endl;
    //If no input is valid
    while(result == ""){
        cin >> race;
        switch(race){
        	case 'S': 
                result = "Shade";
                break;
        	case 'D': 
                result = "Drow";
                break;
        	case 'V': 
                result = "Vampire";
                break;
        	case 'T': 
                result = "Troll";
                break;
        	case 'G': 
                result = "Goblin";
                break;
            case 'q': 
                result = "quit";
        	    break;
        	default:
        		continue;
        }
        //break;
    }
    //Possible results: "Shade", "Drow", "Vampire", "Troll", "Goblin", "quit"
    return result;
}

//DircToInt(string command) maps direction command("no", "ne"...) to a corresponding
//direction-indicating integer. 
int DircToInt(string command) {
    // Abbreviations for directions
    string Abbr[8] = {"no", "ne", "ea", "se", "so", "sw", "we", "nw"};
    // dirc represents direction
    // index of Abbr is the integer direction we want to return:
    /*
    7 0 1
    6 X 2
    5 4 3
    where X is the Tile being analyzed.
    */
    // if none of the direction abbreviations match the command,
    // direction is prompted until a valid direction is read in
	while (true) {
		for (int dirc = 0; dirc < 8; ++dirc) {
		    if (command == Abbr[dirc]) {
			return dirc;
		    }
		}
		command = "";
		cin >> command;
	    if (cin.eof()) //break;
	    if (cin.fail()){
		cin.ignore();
            continue;
        }
    } // while
}

// DircToInt(string command) maps direction-indicating integer to its
// corresponding string. It is called to populate the ActionMsg.
std::string DircToStr(int dirc) {
	string directions[8] = {"North", "Northeast", "East", "Southeast", "South", "Southwest", "West", "Northwest"};
	for (int i = 0; i < 8; ++i) {
		if (i == dirc) {
			return directions[dirc];
		}
	}
	return "";
}

// NextTurn(fl) is called every time player makes a move.
bool NextTurn(Floor* fl) {
    #ifdef DEBUG
        cout << "---NextTurn() Called." <<endl;
    #endif
    fl->MoveEnemy();
    #ifdef DEBUG
        cout << "---All enemies Moved!!!" <<endl;
    #endif
    fl->DrawInterface();
    #ifdef DEBUG
        cout << "---New interface composed." <<endl;
    #endif
   
    if (fl->CheckEndGame()) {
        #ifdef DEBUG
            cout << "---GAME OVER!!!" <<endl;
        #endif
        return false;
    }else{
        return true;  
    } 
}


// main takes in command line arguments for floor layout input file
// and the random seed.
int main(int argc, char *argv[]){
    //cout << Action ;
    cout << "Welcome to Chamber Crawl 3000!" << endl;   
    //Assign random seed
    if (! argv[2]) {
        srand(time(NULL));
        //srand(0);
    } else {
        // if second command line argument was entered.
        istringstream tempcast(argv[2]);
        int i = 0;
        tempcast >> i;
        srand(i);
    }
    //Command will read in the actual command 
    string Command = "";
    //Builds the floor
    Floor* fl = new Floor;
    //Call the GetRace() helper funciton. It will prompt the player
    //to enter a race char.
    string race = GetRace();
    Hero* Player = 0;
    if (race == "quit") {
        cout << "Goodbye!" << endl;
    } else {
        //Return a Hero* pointing to a subclass(Shade, Vam...) denpending on 
        //input race.
        Player = fl->MakeHero(race);
    }
    //If Player is not null anymore.
    if (Player) {
        if (! argv[1]) {
            //If there is no floor layout printed, ask for input.
            cout << "Please enter the board layout." << endl;
    	    iostream layout(NULL);
	    iostream layout2(NULL);
    	    while (true) {
    	        string line;
    	        getline(cin,line);
    	        layout << line;
		layout2 << line;
                if (cin.fail()) {
                    if(cin.eof()){
                        break;    
                    }else{
                        cout << "Invalid input" << endl;
                        cin.clear();
                        cin.ignore();
                    }
    	        }
    	    }
            //If EOF is encountered, construct the level basing on design.
            fl->ConstructLevel(layout, layout, Player);
        } else {
            // if command line argument was entered:
            cout << "Reading in from file " << argv[1] << endl;    
            // converts command line arg to file stream
            ifstream init (argv[1]);
        	init >> std::noskipws; // don't skip whitespace
	        ifstream init2 (argv[1]);
	        init2 >> std::noskipws;
            //Create tiles using the stream, connect them to their coresponding 
            //neighbours, and spawn the hero, connect it to a tile, 
            fl->ConstructLevel(init, init2, Player);
        } // if
    }
    string command = "";
    // set to false when game ends
    bool keep_prompting = true;
    bool quit = false;
    bool restart = false;
    bool first_read = true;
    bool spawned = true; // switches on player spawn msg

    while(Player && keep_prompting){
        string line = "";
        string command = "";
    if (spawned) {
	ActionMsg = "Player has spawned. ";
	spawned = false;
    }
        cout<< "Action: " << ActionMsg <<endl;
    ActionMsg = "";
        cout<< "Commands:" <<endl;
        cout<< "Move (no)rth, (so)uth, (ea)st, (we)st, ne, nw, se, sw" <<endl;
        cout<< "u <direction>: use potion in direction" <<endl;
        cout<< "a <direction>: attack in direction" <<endl;
        cout<< "(r)estart" <<endl;
        cout<< "or (q)uit" << endl;
        //get a line of input
        //Get player command
    if (first_read) {
		cin.ignore();
		first_read = false;
    }
        getline(cin, line);
        if (cin.eof()) //break;
        if (cin.fail()){
            cin.ignore();
            continue;
        }
        //iss the stream version of line.
        istringstream iss(line);
        iss >> command;
	    int dirc = -1; // assume input is invalid
	    bool try_atk = false;
	    bool try_use = false;
        //check what is the command
        switch(command[0]){

        //*************QUIT*********************
            case 'q': //quit
                cout << "Goodbye!" << endl;
		        quit = true;
                break;

        //*************RESART*********************
            case 'r': 
                cout << "Level is restarting..." << endl;
                race = GetRace();
                cout << "Race obtained!" << endl;
                if (race == "quit") {
                    cout << "Goodbye!" << endl;
                    quit = true;
                    break;
                } else {
                    cout << "Clearing level..." << endl;
                    fl->ClearLevel();
                    delete Player;
                    Player = NULL;
                    cout << "About to make hero..." << endl;
                    Player = fl->MakeHero(race);
                    cout << "Populating chamber..." << endl;
                    fl->PopulateChamber();
                    cout << "Chamber repopulated!" << endl;
                    restart = true;
                    fl->DrawInterface();
                }
                #ifdef DEBUG
                    cout<<"breaking switch statement..."<<endl;
                #endif
	    spawned = true; // turns on ActionMsg
                break;

        //*************MOVE AROUND*********************
            case 'n':
    	    case 'e':
            case 'w':
            case 's':
			dirc = DircToInt(command); // movement direction		
                if (Player->GetTile()->GetNeighbour(dirc)->GetDisplay() == '\\'){
                    #ifdef DEBUGSTAIRS
                        cout << "STAIRS REACHED" << endl;
                    #endif
                    fl->NextLevel();
                    ActionMsg += "WOOHOO! You have reached the next floor.";
                    #ifdef DEBUGSTAIRS
                        cout << "---fl->NextLeve() Called!!!" <<endl;
                    #endif
                    break; // we assume the player has moved to stairs already; floor has regenerated player position.
                }
	   	    if (Player->MoveMe(dirc)){
                //Move success
                string TempMsg = ActionMsg;
            	ActionMsg = "PC moves " + DircToStr(dirc);
                Player-> SeePotion();
                ActionMsg = ActionMsg + TempMsg; 
            }else{
                //Move Towards invalid postion
                cout<< "---MOVE FAILED!"<<endl;
                continue;
            }
            break;
        //*************USE ITEM*********************
        case 'u':
		    iss >> command; 
			dirc = DircToInt(command); // movement direction
            try_use = Player->AttemptToUse(dirc);
            if (!try_use) {
		    ActionMsg = "There is no potion in direction " + DircToStr(dirc) + ". Please try another command.";
            }
            break;
        //*************ATTACK*********************
        case 'a':
		    iss >> command;
		    dirc = DircToInt(command);
		    try_atk = Player->AttemptToHit(dirc);
            if (!try_atk) {
                ActionMsg = "Cannot attack in direction " + DircToStr(dirc);
            }
            break;
        default:
		    cout << "Invalid command" << endl;
            continue;
         } // switch: takes action based on command
        if (!quit && !restart) {
            keep_prompting = NextTurn(fl);
        } else if (restart) {
            restart = false;
        } else if (quit) {
            keep_prompting = false;
        }
        
    } // while prompt loop
    delete fl;
}

