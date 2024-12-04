

#include "C:\Users\mblac\Code\Code_C++\2420FinalProject\ConsoleApplication1\Player.h" //These will probably have to be modified
#include "C:\Users\mblac\Code\Code_C++\2420FinalProject\ConsoleApplication1\Rooms.h" //In order to run on your computer
#include "C:\Users\mblac\Code\Code_C++\2420FinalProject\ConsoleApplication1\BinaryTree.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <stack>  // Include the stack header

using namespace std;

unordered_map<int, string> load_items() {
    unordered_map<int, string> temp_dictionary;

    vector<string> items = {
    "Potion of Strength",
    "Smoke Bomb",
    "Puzzle Hint Scroll",
    "Health Elixir",
    "Combat Charm",
    "Trap Disarming Kit",
    "Lockpick",
    "Torch",
    "Map Fragment",
    "Strength Charm",
    "Silent Cloak",
    "Antidote",
    "Magic Mirror",
    "Energy Crystal",
    "Enchanted Key"
    };

    int index = 1;
    for (const auto& item : items) {
        temp_dictionary[index] = item;
        index++;
    }

    return temp_dictionary;
}

Graph load_graph() {
    Graph temp_graph(40);
    temp_graph.generateMazeGraph(40, 0, 15);
    return temp_graph;
}


Player load_player() {
    Player temp_player(0,0,0);
    int totalPoints = 25;

    // Get input from the user for strength, intelligence, and agility
    cout << "Enter strength (max " << totalPoints << " points): ";
    cin >> temp_player.strength;

    totalPoints -= temp_player.strength;

    cout << "Enter intelligence (max " << totalPoints << " points): ";
    cin >> temp_player.intelligence;

    totalPoints -= temp_player.intelligence;

    cout << "Enter agility (max " << totalPoints << " points): ";
    cin >> temp_player.agility;

    // Ensure the total points don't exceed 25
    while (temp_player.strength + temp_player.intelligence + temp_player.agility > 25) {
        temp_player.strength = 0;
        temp_player.agility = 0;
        temp_player.intelligence = 0;
        int totalPoints = 25;

        cout << "Total points exceed 25. Please re-enter values." << endl;
        cout << "Enter strength (max " << totalPoints << " points): ";
        cin >> temp_player.strength;
        totalPoints -= temp_player.strength;


        cout << "Enter intelligence (max " << totalPoints << " points): ";
        cin >> temp_player.intelligence;
        totalPoints -= temp_player.intelligence;


        cout << "Enter agility (max " << totalPoints << " points): ";
        cin >> temp_player.agility;
        totalPoints -= temp_player.strength;

    }

    // Load Items (randomly generated)
    srand(time(0)); // Seed the random number generator
    temp_player.addItemToInventory(rand() % 15 + 1);
    temp_player.addItemToInventory(rand() % 15 + 1);
    cout << "Now welcome to the maze. Get from room 0 to room 15 to leave.\n";
    return temp_player;
}

BinaryTree load_tree() {
    BinaryTree temp_tree;

    temp_tree.insert("Locked Iron Door", 27, 1, 8);
    temp_tree.insert("Bottomless Pit", 13, 2, 7);
    temp_tree.insert("Enchanted Riddle Wall", 38, 3, 9);
    temp_tree.insert("Sleeping Dragon", 17, 2, 6);
    temp_tree.insert("Poisonous Gas Trap", 3, 3, 5);
    temp_tree.insert("Magic Barrier", 22, 3, 10);
    temp_tree.insert("Heavy Boulder Blocking Path", 10, 1, 10);
    temp_tree.insert("Narrow Cliff Walkway", 35, 2, 8);
    temp_tree.insert("Ancient Puzzle Gate", 5, 3, 7);
    temp_tree.insert("Guarded Treasure Room", 40, 2, 9);
    temp_tree.insert("Swamp of Sluggishness", 2, 1, 6);
    temp_tree.insert("Spike Floor Trap", 19, 2, 7);
    temp_tree.insert("Labyrinth of Shadows", 31, 3, 6);
    temp_tree.insert("Haunted Mirror Maze", 25, 3, 8);
    temp_tree.insert("Raging River Crossing", 16, 1, 7);
    temp_tree.insert("Enchanted Forest of Confusion", 9, 3, 5);
    temp_tree.insert("Treacherous Mud Pit", 33, 2, 5);
    temp_tree.insert("Cursed Idol", 29, 3, 9);
    temp_tree.insert("Fiery Gates", 4, 2, 6);
    temp_tree.insert("Frozen Lake", 8, 1, 9);

    return temp_tree;
}



int main() {
    Graph roomgraph(40);
    roomgraph = load_graph();
    //roomgraph.printGraph();

    Player playercharacter;
    playercharacter = load_player();

    BinaryTree challengetree;
    challengetree = load_tree();

    unordered_map<int, string> items = load_items();

    bool win_condition = false;
    int currentroom = 0;

    // Stack to keep track of the rooms visited (path history)
    stack<int> visitedRooms;
    visitedRooms.push(currentroom);  // Start from room 0

    while (!win_condition) {
        system("cls");


        cout << "You are currently in room " << currentroom << ".\n";
        int challenge_number = challengetree.FindNearestChallenge(currentroom);
        cout << "While here, you must traverse the " << challengetree.getChallengeName(challenge_number) << endl;
        int challengestatyouneed = challengetree.getChallengeStat(challenge_number) + 1;
        string challengetype = challengetree.getChallengeType(challenge_number);
        cout << "To do so you will have to pass a " << challengetype << " trial, and you need a value of " << challengestatyouneed << " in " << challengetype << " to pass it." << endl;
        int challengestatyouhave = 0;
        if (challengetype == "Strength") {
            challengestatyouhave = playercharacter.strength;
        }
        else if (challengetype == "Agility") {
            challengestatyouhave = playercharacter.agility;
        }
        else if (challengetype == "Intelligence") {
            challengestatyouhave = playercharacter.intelligence;
        }

        bool passroom = false;
        if (challengestatyouhave > challengestatyouneed) {
            passroom = true;
        }

        if (passroom) {
            cout << "Congrats! You passed the challenge! You lose no health." << endl;
            if (rand() % 3 + 1 == 1) {
                int random_treasure = rand() % 14 + 1;
                cout << "You also found a treasure! You got a " << items[random_treasure] << ".\n";
                playercharacter.addItemToInventory(random_treasure);
                challengetree.NodeDeletion(challenge_number);
            }
        }
        else {
            playercharacter.health = playercharacter.health - (challengestatyouneed-challengestatyouhave);
            cout << "You didn't beat the challenge, you lost "<< challengestatyouneed - challengestatyouhave << " health. That means you only have " << playercharacter.health << " health left." << endl;
        }

        cout << "You are now ready to move onto the next room!" << endl;
        cout << "Here are your options of rooms you can go to: ";

        vector<int> room_options = roomgraph.getConnectedRooms(currentroom);

        // Remove rooms already visited from the room options
        vector<int> available_rooms;
        while (!room_options.empty()) {
            int next_room = room_options.back();
            room_options.pop_back();
            if (find(visitedRooms._Get_container().begin(), visitedRooms._Get_container().end(), next_room) == visitedRooms._Get_container().end()) {
                available_rooms.push_back(next_room);
            }
        }

        // Show available rooms to go to
        for (int i = 0; i < available_rooms.size(); i++) {
            cout << available_rooms[i] << " ";
        }
        cout << "\nEnter what room you would like to go to: ";
        cin >> currentroom;

        // If player chooses a valid room, push it to stack
        if (find(available_rooms.begin(), available_rooms.end(), currentroom) != available_rooms.end()) {
            visitedRooms.push(currentroom);  // Track the visited room
        }
        else {
            cout << "Invalid room selection. Please choose a valid room.\n";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Press any key to continue...";
        cin.get();
        if (currentroom == 15) {
            cout << "You won the maze! Well done!\n";
            return 0;
        }
        if (playercharacter.health <= 0) {
            cout << "Your character died, the game is over\n";
            cout << "A winning path from start to finish was: ";
            for (int i = 0; i < roomgraph.winningPath.size(); i++) {
                cout << roomgraph.winningPath[i];
            }
            return 0;
        }
    }
    cout << "You made it through the maze! You won!\n";
    return 0;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
