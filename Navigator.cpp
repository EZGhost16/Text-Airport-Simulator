/**********************************
 * File: Proj3.cpp
 * Project: CMSC 202 Project 3, Spring 2024
 * Author: Eden Zhang
 * Date: 3/18/2024
 * Section: 30/34
 * E-Mail: ezhang1@umbc.edu
 * 
 * Navigator.cpp file holds function bodies of Navigator.h
 * Handles main functions that manage routes and airports
 * Takes info from data file of airports and lets user do various things
 * Create routes, pick airports, remove airports, reverse routes, display routes with
 * all their info, etc.
 * 
*****************************************************/
#include "Navigator.h"

// Navigator
// Constructs Navigator object and sets the file name
Navigator::Navigator(string fileName)
{
    m_fileName = fileName;
}

// ~Navigator
// Destructor
Navigator::~Navigator()
{
    // Iterates through the airport vector and deletes all the objects
    for (vector<Airport*>::iterator it = m_airports.begin(); it != m_airports.end(); it++)
    {
        delete *it;
    }

    // Iterates through the route vector and deletes all the route linked lists
    for (vector<Route*>::iterator it = m_routes.begin(); it != m_routes.end(); it++)
    {
        delete *it;
    }

    m_airports.clear();
    m_routes.clear();
}

// Start
// Starts program by calling main functions
void Navigator::Start()
{
    ReadFile();
    MainMenu();
}

// DisplayAirports
// Goest through the airport vector and prints each element in a format
void Navigator::DisplayAirports()
{
    int num = 1;

    // Iterates through the airport vector and displayed each airport in numbered format
    for (vector<Airport*>::iterator it = m_airports.begin(); it != m_airports.end(); it++)
    {
        cout << num << ". " << *(*it) << endl;
        num++;
    }
}

// ReadFile
// File I/O, takes the data file, takes info line by line
// Puts it all in airport nodes and adds to the airport vector
void Navigator::ReadFile()
{
    int const NUMOFSECTS = 6; // The number of categories on each line
    char const DIVIDE = ',';  // Comma that is the main seperator for each category in a line
    string const BLANK = ""; // Needed to reset the airport variables
    // File I/O variables
    ifstream data;
    string line;
    int sectCounter = 0;
    // Counter to track how many airports loaded
    int airportsLoaded = 0;

    // Airport variables
    string code = BLANK;
    string name = BLANK;
    string city = BLANK;
    string country = BLANK;
    // These will be type casted into doubles
    string northstr = BLANK;
    string weststr = BLANK;

    data.open(m_fileName);

    // Makes sure the file is successfully opened
    if (data.is_open())
    {
        cout << "Opened File." << endl;
        // Takes each line and organizes 
        // the parts into their respective categories
        while (getline(data, line))
        {
            // Goes through each character in the line
            for (int i = 0; i < int(line.length()); i++)
            {
                switch (sectCounter % NUMOFSECTS)
                {
                    // Going through each category one by one in order
                    case 0:
                    // Once the loop hits a ',' it goes to the next category
                    if (line[i] == DIVIDE)
                    {
                        sectCounter++;
                    } else 
                    {
                        // Adds the character to the current category
                        code += line[i];
                    }
                    break;
                    case 1:
                    if (line[i] == DIVIDE)
                    {
                        sectCounter++;
                    } else 
                    {
                        name += line[i];
                    }
                    break;
                    case 2:
                    if (line[i] == DIVIDE)
                    {
                        sectCounter++;
                    } else 
                    {
                        city += line[i];
                    }
                    break;
                    case 3:
                    if (line[i] == DIVIDE)
                    {
                        sectCounter++;
                    } else 
                    {
                        country += line[i];
                    }
                    break;
                    case 4:
                    if (line[i] == DIVIDE)
                    {
                        sectCounter++;
                    } else 
                    {
                        northstr += line[i];
                    }
                    break;
                    case 5:
                    // Increases when it hits the end of the line
                    if (i == int(line.length()) - 1)
                    {
                        sectCounter++;
                    } else 
                    {
                        weststr += line[i];
                    }
                    break;
                }
            }

            // Takes all the info, creates an Airport node, adds it to airport vector
            double north = stod(northstr);
            double west = stod(weststr);
            m_airports.push_back(new Airport(code, name, city, country, north, west));
            airportsLoaded++;

            // Resets variables
            code = BLANK;
            name = BLANK;
            city = BLANK;
            country = BLANK;
            northstr = BLANK;
            weststr = BLANK;
        }
    } else 
    {
        cout << "Unable to open file." << endl;
    }

    data.close();
    cout << "Airports Loaded: " << airportsLoaded << endl;
}

// InsertNewRoute
// Special cases, makes new route with stuff, at least 2 airports
// Added to m_routes
void Navigator::InsertNewRoute()
{
    // Creates a Route object to have info be added in
    Route *newRoute = new Route();
    int user = 0;

    // Loop until the user exits with -1
    while (user != -1)
    {
        // Displays the Airports and asks the user for an airport
        DisplayAirports();
        cout << "Enter the number of the airport to add to your Route: (-1 to end)" << endl;
        cin >> user;

        // Bound checking
        while ((user != -1 && user < 1) || user > int(m_airports.size()))
        {
            cout << "Please pick an airport from the list." << endl;
            cin >> user;
        }
        
        // Makes sure the code doesn't try to insert a -2 airport when user tries exiting
        if (user != -1)
        {
            // Takes the user's chosen airport and inserts it into the route accordingly
            Airport *air = m_airports.at(user - 1);

            newRoute->InsertEnd(air->GetCode(), air->GetName(), 
            air->GetCity(), air->GetCountry(), air->GetNorth(), air->GetWest());
        }

        // Checking that the user isn't trying to make a singular or empty route
        if (user == -1 && newRoute->GetSize() < 2)
        {
            cout << "Your Route must have at least 2 airports." << endl;
            user = 0;
        }
    }

    // Sets the Routes name and adds it to the routes list
    newRoute->UpdateName();
    m_routes.push_back(newRoute);

    cout << "Done Building a New Route named " << newRoute->GetName() << endl;
}

// MainMenu
// Main function for user to pick action
void Navigator::MainMenu()
{
    int user = -1;

    // Keeps going until the user picks 5 to exit
    while (user != 5)
    {
        // Menu displayed
        cout << "What would you like to do?:" << endl;
        cout << "1. Create New Route" << endl;
        cout << "2. Display Route" << endl;
        cout << "3. Remove Airport From Route" << endl;
        cout << "4. Reverse Route" << endl;
        cout << "5. Exit" << endl;

        cin >> user;

        // Switch statement to pick the appropriate action
        switch (user)
        {
            case 1:
            InsertNewRoute();
            break;
            case 2:
            DisplayRoute();
            break;
            case 3:
            RemoveAirportFromRoute();
            break;
            case 4:
            ReverseRoute();
            break;
            case 5:
            cout << "Routes removed from memory." << endl;
            cout << "Deleting Airports." << endl;
            cout << "Deleting Routes." << endl;
            break;
        }
    }
}

// ChooseRoute
// User picks a route and iterates to the index of route in vector
int Navigator::ChooseRoute()
{
    // Initialized
    int user = -1;

    // Initial ask
    cin >> user;

    // Bound checking
    while (user <= 0 || user > int(m_routes.size()))
    {
        cout << "Please choose a Route from the list." << endl;
        cin >> user;
    }

    // Returns in index
    return (user - 1);
}

// DisplayRoute
// Prints chosen route with airports and total distance in miles
void Navigator::DisplayRoute()
{
    int listNum = 1;

    // Checks that m_routes is populated
    if (int(m_routes.size()) == 0)
    {
        cout << "No Routes to display." << endl;
    } else 
    {
        // Loops through m_routes and displays each route
        for (vector<Route*>::iterator it = m_routes.begin(); it != m_routes.end(); it++)
        {
            // Prints out each route with number formatting
            cout << listNum << ". " << (*it)->GetName() << endl;
            listNum++;
        }

        // Grabs the chosen route and puts it in a usable route object
        int user = ChooseRoute();
        Route *useRoute = m_routes.at(user);

        // Displays Airports in the route and the total distance of route
        cout << useRoute->GetName() << endl;
        useRoute->DisplayRoute();
        cout << "The total miles of this route is " << RouteDistance(useRoute) << " miles." << endl;
    }
}

// RemoveAirportFromRoute
// Removes an airport from Route of user's choice
// Cannot remove less than 2 airports
void Navigator::RemoveAirportFromRoute()
{
    int const LIMIT = 2;  // The least amount of airports allowed in a route
    int listNum = 1;
    int airportIndex = 0;

    // Checks that m_routes is populated
    if (int(m_routes.size()) == 0)
    {
        cout << "No Routes to display." << endl;
    } else 
    {
        // Loops through m_routes and displays each route
        for (vector<Route*>::iterator it = m_routes.begin(); it != m_routes.end(); it++)
        {
            cout << listNum << ". " << (*it)->GetName() << endl;
            listNum++;
        }

        // Grabs the chosen route and puts it in a usable route object
        int user = ChooseRoute();
        Route *useRoute = m_routes.at(user);

        // Checks that the user isn't trying to make a route with less than 2 nodes
        if (useRoute->GetSize() == LIMIT)
        {
            cout << "You cannot have a route with less than 2 airports." << endl;
        } else 
        {
            // Displays Airports in the route
            cout << useRoute->GetName() << endl;
            useRoute->DisplayRoute();

            // Asks the user for what airport they want to remove now
            cout << "Which airport would you like to remove?" << endl;
            cin >> airportIndex;

            // Bound checking
            while (airportIndex <= 0 || airportIndex > useRoute->GetSize())
            {
                cout << "Please pick an airport in the route." << endl;
                cin >> airportIndex;
            }

            // Removes airport of index and updates the name if end or front changes
            useRoute->RemoveAirport(airportIndex);
            useRoute->UpdateName();

            // Displays the Route airports again
            cout << useRoute->GetName() << endl;
            useRoute->DisplayRoute();

            cout << "Route named " << useRoute->GetName() << " updated." << endl;
        }
    }
}

// RouteDistance
// Calculates the total distance of the route in miles
double Navigator::RouteDistance(Route* route)
{
    double totalDistance = 0;
    double currDistance = 0;
    Airport *curr;
    Airport *next;

    // Loops through the route using GetSize()
    for (int i = 1; i < route->GetSize(); i++)
    {
        // When the loop reaches the end, then finished
        if (i == route->GetSize())
        {
            // Stops from overflowing
            return totalDistance;
        } else
        {
            // Gets the airport info
            curr = route->GetData(i);
            next = route->GetData(i + 1);
            currDistance = CalcDistance(curr->GetNorth(), curr->GetWest(), next->GetNorth(), next->GetWest());
            totalDistance += currDistance;
        }
    }

    return totalDistance;
}

// ReverseRoute
// Reverses the route
void Navigator::ReverseRoute()
{
    int listNum = 1;

    // Checks that the m_routes vector is populated
    if (int(m_routes.size()) == 0)
    {
        cout << "No Routes available to reverse." << endl;
    } else
    {
        // Loops through m_routes and displays each route
        for (vector<Route*>::iterator it = m_routes.begin(); it != m_routes.end(); it++)
        {
            cout << listNum << ". " << (*it)->GetName() << endl;
            listNum++;
        }

        // Sets up the selected Route
        int user = ChooseRoute();
        Route *useRoute = m_routes.at(user);

        // Reverses Route and Updates the name
        useRoute->ReverseRoute();
        useRoute->UpdateName();

        // Feedback to show it was done
        cout << "Done reversing Route " << useRoute->GetName() << endl;
    }
}
