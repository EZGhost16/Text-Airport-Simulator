/**********************************
 * File: Proj3.cpp
 * Project: CMSC 202 Project 3, Spring 2024
 * Author: Eden Zhang
 * Date: 3/18/2024
 * Section: 30/34
 * E-Mail: ezhang1@umbc.edu
 * 
 * Airport.cpp file with the function bodies of Airport.h
 * Handles making the Airport Nodes and its associated destructor, 
 * getter, and setter functions.
 * 
*****************************************************/
#include "Airport.h"

// Airport
// Default constructor for airport node
Airport::Airport()
{
    // NOTE: Check if this is correct ??
    m_name = "New Airport";
    m_north = 0;
    m_west = 0;
    m_city = "New Location";
    m_next = nullptr;
}

// Airport
// Main constructor of new nodes with all the set info
Airport::Airport(string code, string name, string city, string country, double north, double west)
{
    m_code = code;
    m_name = name;
    m_city = city;
    m_country = country;
    m_north = north;
    m_west = west;
    m_next = nullptr;
}

// ~Airport
// Empty destructor
Airport::~Airport() 
{

}

// GetCode
// Getter function for airport code
string Airport::GetCode()
{
    return m_code;
}

// GetName
// Getter function for airport name
string Airport::GetName()
{
    return m_name;
}

// GetNext
// Getter function for airport next
Airport* Airport::GetNext()
{
    return m_next;
}

// GetNorth
// Getter function for airport north coord
double Airport::GetNorth()
{
    return m_north;
}

// GetWest
// Getter function for airport west coord
double Airport::GetWest()
{
    return m_west;
}

// GetCity
// Getter function for airport city
string Airport::GetCity()
{
    return m_city;
}

// GetCountry
// Getter function for airport country
string Airport::GetCountry()
{
    return m_country;
}

// SetNext
// Setter function for airport next
void Airport::SetNext(Airport* next)
{
    m_next = next;
}
