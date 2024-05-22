/**********************************
 * File: Proj3.cpp
 * Project: CMSC 202 Project 3, Spring 2024
 * Author: Eden Zhang
 * Date: 3/18/2024
 * Section: 30/34
 * E-Mail: ezhang1@umbc.edu
 * 
 * Route.cpp file that holds function bodies of Route.h
 * Handles linked list functions of Route with destructor,
 * inserting airports, reversing routes, calculating distance, etc.
 * 
*****************************************************/
#include "Route.h"

// Route
// Default constructor for linked list
Route::Route()
{
    m_name = "Test";
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

// SetName
// Sets name of route
void Route::SetName(string name)
{
    m_name = name;
}

// ~Route
// Destructur, cleans up the nodes and linked lists, resetting
Route::~Route()
{
    Airport *curr = m_head;

    // Loops through the route and deletes everything
    while (curr != nullptr)
    {
        m_head = curr;
        curr = curr->GetNext();
        delete m_head;
    }

    // Resets info
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

// InsertEnd
// Inserts a new airport at the end of the route
void Route::InsertEnd(string code, string name, string city, string country, double north, double west)
{
    Airport *temp = new Airport(code, name, city, country, north, west);

    // Checks to make sure this addition isn't the first one
    if (m_size == 0)
    {
        // If it is the first one, then simply adds it as the first, or front
        m_head = temp;
        m_tail = temp;
        m_size++;
    } else 
    {
        // If there are already two airports in, 
        // then goes through the process of adding it at the end
        temp->SetNext(nullptr);
        m_tail->SetNext(temp);
        m_tail = temp;
        m_size++;
    }
}

// RemoveAirport
// Iterates to the airport location in route and removes it
// Maintaining connections of route
void Route::RemoveAirport(int airport)
{
    // If we need to traverse the route, then we need to track the current number
    // of airports in order to match it with the one the user wants
    int indexTracker = 1;
    
    cout << airport << endl;
    // Check if list is empty
    if (m_size == 0)
    {
        cout << "No Airports in Routes." << endl;

    } else if (airport == 1)
    {
        // Front removal
        Airport *curr = m_head;
        m_head = m_head->GetNext();
        delete curr;
        curr = nullptr;
        m_size--;

    } else if (airport == m_size)
    {
        // Tracking the current and previous airports as we traverse the route
        Airport *curr = m_head;
        Airport *prev = m_head;

        while (curr != nullptr)
        {
            // When the airport is found
            if (airport == indexTracker)
            {
                // Makes the previous airport the new last
                prev->SetNext(nullptr);
                m_tail->SetNext(prev);
                m_tail = prev;

                // Gets rid of the last airport
                delete curr;
                curr = nullptr;
            } else 
            {
                // Continues traversing until the end
                prev = curr;
                curr = curr->GetNext();
                indexTracker++;
            }
        }

        m_size--;
    } else 
    {
        // Tracking the current and previous airports as we traverse the route
        Airport *curr = m_head;
        Airport *prev = m_head;

        while (curr != nullptr)
        {
            // Moves through the route
            prev = curr;
            curr = curr->GetNext();
            indexTracker++;

            // Once airport is found, removes it while maintaining the linked list connections
            if (airport == indexTracker)
            {
                prev->SetNext(curr->GetNext());
                delete curr;
            }
        }

        m_size--;
    }
}

// GetName
// Getter function for name of route
string Route::GetName()
{
    return m_name;
}

// UpdateName
// Updates the name of route with front and end format
// Needed for any changes to route and initial creation
string Route::UpdateName()
{
    // Sets up the start and end names
    string start = m_head->GetName();
    string end = m_tail->GetName();

    // Forms and sets the whole name in format
    string newName = start + " to " + end;
    SetName(newName);
    return newName;
}

// GetSize
// Getter function for how many airports in route
int Route::GetSize()
{
    return m_size;
}

// ReverseRoute
// Goes through the route and 
// reverses the connections of the route
// Front becomes end, and vice versa
void Route::ReverseRoute()
{
    Airport *curr = m_head;
    Airport *prev = nullptr;
    Airport *next = nullptr;

    // Traversing the list and reversing it
    while (curr != nullptr)
    {
        next = curr->GetNext();
        curr->SetNext(prev);
        prev = curr;
        curr = next;
    }

    // Adjusting the front and end pointers
    m_tail = m_head;
    m_head = prev;
}

// GetData
// Finds an airport at the given index in route
Airport* Route::GetData(int index)
{
    int indexTracker = 1;
    Airport *curr = m_head;

    // Loops through the list and checks if the 
    // current index matches the target index
    while (curr != nullptr)
    {   
        // When airport is found
        if (index == indexTracker)
        {
            return curr;
        }

        // Traverses
        curr = curr->GetNext();
        indexTracker++;
    }

    return curr;
}

// DisplayRoute
// Displays the route's airports
void Route::DisplayRoute()
{
    // For formatting purposes
    int numLabel = 1;

    // Checks if the route is empty
    if (m_size == 0)
    {
        cout << "The Route is empty." << endl;
    } else 
    {
        Airport *temp = m_head;
        // Traverses the route linked list
        while (temp != nullptr)
        {
            // Displays all the info in proper format
            cout << numLabel << ". " << temp->GetCode() << ", " << temp->GetName() << ", " << temp->GetCity() << 
            ", " << temp->GetCountry() << " (N" << temp->GetNorth() << " W" << temp->GetWest() << ")" << endl;

            // Moves to the next airport
            temp = temp->GetNext();
            numLabel++;
        }
    }
}
