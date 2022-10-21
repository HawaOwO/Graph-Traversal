#include <iostream>
#include "Graph.h"
using namespace std;
void initializeGraph(Graph&);
void MainMenu();
bool checkStrong(Graph&, int);
int main()
{
    // Five vertices
    int vertices = 5;

    // Declaring main graph and graph with all weights
    Graph g(vertices);
    int weights[5][5] = {{0, 8202, 7625, 10136, 9906},
                         {8202, 0, 13603, 2803, 3826},
                         {7625, 13603, 0, 12836, 17143},
                         {10136, 2803, 12836, 0, 5536},
                         {9906, 3826, 17143, 5536, 0}};

    // Initializing
    initializeGraph(g);

    int choice = 0;


    do {
        MainMenu();
        cin >> choice;
        // Validation for choice
        while (choice < 1 || choice > 9) {
            cout << "Invalid input." << endl;
            cout << "Re-enter your choice." << endl;
            cin >> choice;
        }

        if (choice != 9) {
            if (choice == 1) {
                g.toString();
                cin.get();
                cin.get();
            }

            else if (choice == 2) {
                while (!checkStrong(g, vertices)) {  // Repeat until the graph is strongly connected, if already strongly connected, exit while loop
                    char selection;
                    cout << "\nThe graph is not strong connected " << endl;
                    cout << "Would you like to make it strong? (Y/y or N/n)" << endl; // Ask whether the user wants to make the graph to be strongly connected.
                    cin >> selection;
                    if (selection == 'Y' || selection == 'y') {
                        g.generateRandomEdge(weights);  // If yes, generate random edge
                        g.toString();  // Display graph
                    }
                    else if(selection =='n'||selection =='N')
                    {
                        cout<<"\nThe graph is not strongly connected and you decide not to make it one\n";
                        break;
                    }
                }
                if (checkStrong(g, vertices))
                {
                    cout << "\nGraph is strongly connected now, Press enter to continue !!" << endl; // If the graph is originally strong connected, display this and the graph
                    g.toString(); // Display graph
                }
                cin.get();
                cin.get();
            }

            else if (choice == 3) {
                while (!g.DFS()) {
                    char selection;
                    cout << "\nThe graph does not contain cycles " << endl;
                    cout << "Would you like to make it to have cycles? (Y/y or N/n)" << endl;
                    cin >> selection;
                    if (selection == 'Y' || selection == 'y') {
                        g.generateRandomEdge(weights);
                    }
                    else if (selection == 'N' || selection == 'n') {
                        cout << "\nYou have decided to not make any cycles.";
                    }
                    else {
                        break;
                    }
                    break;
                }
                cin.get();
                cin.get();
            }

            else if (choice == 4) {
                int origin = 0, destination = 0;

                cout << "\nPlease enter your departure point" << endl;
                cin >> origin;
                cout << "\nPlease enter your arrival point" << endl;
                cin >> destination;

                g.dijkstraDist(weights, origin, destination);

                if(!g.isReachable(origin, destination))
                {
                    while (!g.isReachable(origin, destination)) {  // Repeat until the graph is strongly connected, if already strongly connected, exit while loop
                        char selection;
                        cout << "\nWould you like to randomly added a new edge? (Y/y or N/n)" << endl; // Ask whether the user wants to make the graph to be strongly connected.
                        cin >> selection;
                        if (selection == 'Y' || selection == 'y') {
                            g.generateRandomEdge(weights);  // If yes, generate random edge
                            g.toString();  // Display graph
                        }
                        else if(selection =='n'||selection =='N')
                        {
                            break;
                        }
                    }

                    if (g.isReachable(origin, destination))
                    {
                        cout << "\nThe path between " << origin << " and " << destination << " is now existed." << endl; // If the graph is originally strong connected, display this and the graph
                        g.toString(); // Display graph
                        g.dijkstraDist(weights, origin, destination);
                    }
                }
                cin.get();
                cin.get();
            }

            else if (choice == 5) {
                int mst = g.kruskalMST(weights);
                cout << endl << "Weight of MST is " << mst << endl;

                cin.get();
                cin.get();
            }

            else if (choice == 6) {
                char selection;
                cout << "Would you like to reset the graph? (Y/y or N/n)" << endl;
                cin >> selection;
                if (selection == 'Y' || selection == 'y') {
                    g.reset(5);
                    cout << "\nThe graph has been reset";
                    initializeGraph(g);
                }
                cin.get();
                cin.get();
            }

            else if (choice == 7) {
                g.toString();

                int v1, v2;
                cout << "\nPlease specify the first vertex" << endl;
                cin >> v1;
                cout << "\nPlease specify the second vertex" << endl;
                cin >> v2;
                if (g.isAvailable(v1, v2)) {
                    cout << "\nThe edge already exists" << endl;
                }
                else {
                    g.addEdge(v1, v2, weights[v1][v2]);
                    cout << "\nNew edge added" << endl;
                    cout << "\nThis the new graph:\n";
                    g.toString(); // Display graph
                }
                cin.get();
                cin.get();
            }

            else if (choice == 8) {
                g.toString();

                int v1, v2;
                cout << "\nPlease specify the first vertex" << endl;
                cin >> v1;
                cout << "\nPlease specify the second vertex" << endl;
                cin >> v2;
                if (g.isAvailable(v1, v2)) {
                    g.removeEdge(v1, v2);
                    cout << "\nEdge removed" << endl;
                }
                else {
                    cout << "\nNo edge exists" << endl;
                }
                cin.get();
                cin.get();
            }
        }
    } while (choice != 9);
}


void initializeGraph(Graph& g) {
    g.addEdge(0, 1, 8202);
    g.addEdge(1, 2, 13603);
    g.addEdge(2, 3, 12836);
    g.addEdge(3, 4, 5536);
    g.addEdge(0, 4, 9906);
}


void MainMenu() {
    system("CLS");
    cout << "***********************************Graph Traversal********************************************" << endl;
    cout << "\nThe cities represented by integer 0 to 4";
    cout << "\n[0]\tTunis, Tunisia";
    cout << "\n[1]\tAtlanta, USA";
    cout << "\n[2]\tDhaka, Bangladesh";
    cout << "\n[3]\tLas Vegas, USA";
    cout << "\n[4]\tQuito, Ecuador";
    cout << "\n\nMain Menu: " << endl;
    cout << "Please select your choice: " << endl;
    cout << "1. Display graph" << endl;
    cout << "2: Check Strongly Connected" << endl;
    cout << "3: Check Cycle Detection" << endl;
    cout << "4: Find Shortest Path" << endl;
    cout << "5: Find Minimum Spanning Tree" << endl; // deyan punya baru
    cout << "6: Reset Graph" << endl;
    cout << "7: Add Edge" << endl;
    cout << "8: Remove Edge" << endl;
    cout << "9: Exit" << endl;
    cout << "\nYour choice: ";
}

bool checkStrong(Graph& g, int V) {
    Graph inverse(V); // Object for inverse graph

    if (g.isSC()) { // Check whether the graph is strongly connected
        inverse.getTranspose(g);   // Get the transpose of the graph
        if (inverse.isSC()) { // Check whether the transposed graph is strongly connected
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}