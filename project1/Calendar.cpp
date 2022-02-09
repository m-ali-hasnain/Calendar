

#include <string>
#include <stdexcept>
#include <cassert>
#include "Calendar.h"


// Default Constructor
// Create an empty Calendar (one with zero Reminders)

Calendar::Calendar(){
    numRem = 0;
}

// getNumRem
// Return the total number of Reminders in the Calendar
size_t Calendar::getNumRem() const {
    return numRem;
}



//addRem(const Reminder &r)
//
//Purpose: add/insert a reminder in the array of reminder objects
//Parameters: Reminder r - the reminder to be added
//Returns: size_t - the index position of the inserted reminder
//
//Behavior:
//1. In case of the array being empty: insert as the first element
//2. In case the array is full: throw an overflow_error exception
//3. In case of a non-empty array with space available: insert Reminder in sorted
//      order, shifting other items up to make space
//4. In case of already existing Reminder with same date: insert new reminder
//      before (ahead of) the existing one.
//5. Return the index of the inserted reminder, using zero-based indexing
//6. Operates in linear time.
size_t Calendar::addRem(const Reminder &r) {

    //first element case
    if(numRem==0){
        remArr[numRem] = r;

        numRem+=1;
        return 0;
    }

    //second case, when index is out of bounds
    else if(numRem >= MAX_REM){
        throw (std::overflow_error("array index out of bounds"));
    }

    //third and fourth case, when we have to do insertion in order and same date reminders
    else{
        size_t si;
        for(si=0; si<=numRem-1; si++){
            //case for insertion as last available index, that is when new reminder is of date which is largest among all
            if(r>remArr[si]){
                continue;
            }

            //case for remiders of same date and choronological insertion
            else if(r.equals(remArr[si]) || r<remArr[si]){
                int endingBounds = si;
                int startingBounds = numRem-1;
                while(startingBounds >= endingBounds){
                    remArr[startingBounds+1] = remArr[startingBounds];
                    startingBounds =  startingBounds - 1;
                }
                si = startingBounds+1;
                remArr[si] = r;
                numRem+=1;
                return  si;
            }

        }

        remArr[si] = r;
        numRem+=1;
        return  si;
    }


}

//
//getRem(size_t index)
//
//Purpose: returns the reminder at the specified index in the Calendar, throw
//   exception if index is bad
//Parameters: size_t index - the index of the desired reminder; using zero-based
//   indexing
//Returns: Reminder - the reminder at the specified index
//
//Behavior:
//1. If the index is invalid, throw an std::invalid_argument exception
//2. Otherwise, return the reminder at the specified index
Reminder Calendar::getRem(size_t index) const {
//    if index is invaild we sill simply throw exception
    if(index<0 || index >= MAX_REM || index >= numRem){
        throw (std::invalid_argument("array index out of bounds"));
    }

    //else we will return element at that index
    else  return remArr[index];
}



//toString()
//
//Purpose: Return a string representation of the Calendar; ie, a string of all
//   reminders
//Parameters: None
//Return: string containing all the reminders in sorted order with each reminder
//   followed immediately by a newline character. Returns an empty string if the
//   Calendar is empty
std::string Calendar::toString() const {
    if(numRem == 0){
        return ""; //if calendar is empty
    }
    else{
//        now we will loop on our array and returns reminder strings
        std::string result;
        for(size_t i=0; i<=numRem-1; i++){
            result+=remArr[i].toString()+"\n";
        }
        return result;
    }
}


//displayRem(size_t index)
//
//Purpose: Return a string of the reminder at a particular index in the Calendar
//Parameters: size_t index
//Return: string containing the reminder
//
//Behavior:
//1. Returns string containing the reminder at the given index (no newline
//      character added)
//2. Follows 0-indexing
//3. If array is empty or the index is invalid, returns an empty string
std::string Calendar::displayRem(size_t index) const {
    //If array is empty or the index is invalid, returns an empty string
   if(numRem==0 || (index < 0 || index >= MAX_REM)){
       return "";
   }

   //else we will simply return message at that position
   else return remArr[index].toString();
}


//displayRem(const string& str)
//
//Purpose: Return a string of all reminders whose message matches the provided string
//Parameters: string str - the string we are supposed to check for match
//Return: string containing all the matching reminders, in sorted order, each reminder
//   followed immediately by a newline character.
//
//Behavior:
//1. Finds any reminders having its message same as the provided string (in a case
//    sensitive manner)
//2. If no match is found, returns an empty string
//3. If matches are found, append them on the return string in sorted order each
//    followed by a newline character.
std::string Calendar::displayRem(const std::string &str) const {
    std::string result = "";

    //we will loop and find all reminders having same message as parameter and then we will concat it in result string
    //finally we will return
    for(size_t i=0; i<=numRem-1; i++){
        if(remArr[i].getMsg().compare(str)==0){
            result+=remArr[i].toString()+"\n";
        }
    }
    return result;
}


//displayRem(const Date& d)
//
//Purpose: Return a string of all reminders for a given date
//Parameters: Date d - the date we are supposed to check for match
//Return: string containing all the matching reminders, in sorted order, each reminder
//        followed immediately by a newline character.
//
//Behavior:
//1. Finds any reminders on the provided date
//2. If no match is found, returns an empty string
//3. If matches are found, append them on the return string in sorted order each
//     followed by a newline character.
//
//Note: see addRem() for the definition of sorted order of Reminders with the
//  same date.
std::string Calendar::displayRem(const Date &d) const    // searches reminders by date
{
    //we will loop and find all reminders having same date as parameter and then we will concat it in result string
    //finally we will return
    std::string result = "";
    for(size_t i=0; i<=numRem-1; i++){
        if(remArr[i].equals(d)){
            result+=remArr[i].toString()+"\n";
        }
    }
    return result;
}


//displayRem(const Date& d1, const Date& d2)
//
//Purpose: Displays reminders in a range of two given dates
//Parameters: Date d1, Date d2 (the range of Dates)
//Return: string containing all the matching reminders, in sorted order, each reminder
//   followed immediately by a newline character.
//
//Behavior:
//1. If the Calendar contains no dates in the given range, return an empty string
//2. Create a string containing all the reminders, in sorted order, which are later
//    than or equal to the smaller of the two dates and are earlier than or equal to
//    the larger of the two dates, with each reminder followed immediately by a
//    newline character.
std::string Calendar::displayRem(const Date &d1, const Date &d2) const {
    std::string result = "";

    //we will loop and find all reminders between range of dates provided as parameter and then we will concat it in result string
    //finally we will return
    //first of all finding smaller and larger date
    Date smallerDate, largerDate;
    if(d1 < d2){
        smallerDate.setDate(d1);
        largerDate.setDate(d2);
    }
    else{
        smallerDate.setDate(d2);
        largerDate.setDate(d1);
    }



    for(size_t i=0; i<=numRem-1; i++){
        if((remArr[i]>smallerDate || remArr[i].equals(smallerDate)) &&( remArr[i]<=largerDate || remArr[i].equals(largerDate))){
            result+=remArr[i].toString()+"\n";
        }
    }
    return result;
}


//findRem(const Date& d)
//
//Purpose: Find first reminder for the given date and return its index
//Parameters: Date d, the date to search for
//Return: int value containing the index of the first reminder with the specified date,
//        or -1 if no reminders with that date exist
int Calendar::findRem(const Date &d) const {
//    //we will loop and find first reminder having same date as parameter and then we will return index
    for(size_t i=0; i<=numRem-1; i++){
        if(remArr[i].equals(d)){
            return i;
        }
    }
    return -1;
}


//findRem(const std::string& str)
//
//Purpose: Find first reminder with the given message and return its index
//Parameters: string str, the message to search for
//Return: int value containing the index of the first reminder with the specified
//        message, or -1 if no reminders with that message exist
int Calendar::findRem(const std::string &str) const {
    //we will loop and find first reminder having same message as parameter and then we will return index

    for(size_t i=0; i<=numRem-1; i++){
        if(remArr[i].getMsg().compare(str)==0){
            return i;
        }
    }
    return -1;
}


void Calendar::shiftLeft(size_t si, size_t li) {
    while(si<=li){
        remArr[si-1] = remArr[si];
        si+=1;
    }
}

// deleteRem()
//
//Purpose: Deletes all reminders earlier than today's date
//Parameters: None
//Return: the number of reminders deleted (a size_t value)
//
//Behavior:
//1) Reminders are shifted down in the array to fill any vacated entries.
//
//Implementation Notes:
//1) The default constructor of the Date class initializes a Date object to today's
//   date.
size_t Calendar::deleteRem() {
    Date currentDate; //initializing currentDate
    int deletedReminders = 0; //represents deletedCounts
    //now we will loop on reminders array and delete reminder earlier than today's date
    for(int i=0; i<=(int)(numRem-1); i++){
        if(remArr[i]<currentDate){
            deleteRem(i);
            deletedReminders+=1;
            //reset i to where it was
            i-=1;
        }
    }
    return deletedReminders;
}


// deleteRem(size_t index)
//
//Purpose: Deletes reminder object at a provided index position
//Parameters: size_t index
//Return: the number of reminders deleted (a size_t value)
//
//Notes:
//1) Reminders are shifted down in the array to fill any vacated entries.
//2) If the index is invalid, no deletions will be performed and zero is returned
size_t Calendar::deleteRem(size_t index) {
    if(index<0 || index>=MAX_REM || index >=numRem){
        return 0;
    }
    else{
        shiftLeft(index+1, numRem-1);
        numRem-=1;
        return 1;
    }
}


// deleteRem(const string& str)
//
//Purpose: Delete all reminders whose message matches a given string
//Parameters: string str (whose match we want to find, case sensitive)
//Return: number of reminders deleted (size_t value)
//
//Notes:
//1) Reminders are shifted down in the array to fill any vacated entries.
size_t Calendar::deleteRem(const std::string &str) {
    int deletedReminders = 0; //represents deletedCounts
    //now we will loop on reminders array and delete reminder earlier than today's date
    for(int i=0; i<=(int)(numRem-1); i++){
        if(remArr[i].getMsg().compare(str)==0){
           deleteRem(i);
           deletedReminders+=1;
           //reset i to where it was
           i-=1;
        }
    }
    return deletedReminders;
}


// deleteRem(const Reminder& rem)
//
//Purpose: Delete all occurrences of the given reminder
//Parameters: Reminder rem
//Return: number of reminders deleted (size_t value)
//
//Notes:
//1) Reminders are shifted down in the array to fill any vacated entries.
size_t Calendar::deleteRem(const Reminder &rem) {
    int deletedReminders = 0; //represents deletedCounts
    //now we will loop on reminders array and delete reminder earlier than today's date
    for(int i=0; i<=(int)(numRem-1); i++){
        if(remArr[i].operator==(rem)){
            deleteRem(i);
            deletedReminders+=1;
            //reset i to where it was
            i-=1;

        }
    }
    return deletedReminders;
}


// deleteRem(const Date& d)
//
//Purpose: Deletes all reminders on a particular date
//Parameters: Date d
//Return: number of reminders deleted (size_t value)
//
//Notes:
//1) Reminders are shifted down in the array to fill any vacated entries.
size_t Calendar::deleteRem(const Date &d) {
    int deletedReminders = 0; //represents deletedCounts
    //now we will loop on reminders array and delete reminder earlier than today's date
    for(int i=0; i<=(int)(numRem-1); i++){
        if(remArr[i].equals(d)){
            deleteRem(i);
            deletedReminders+=1;
            //reset i to where it was
            i-=1;
        }
    }
    return deletedReminders;
}


// deleteRem(const Date& d1, const Date& d2)
//
//Purpose: Deletes all reminders between a range of two given dates
//Parameters: Date d1, Date d2 (the range of Dates)
//Return: number of reminders deleted (size_t value)
//
//Behavior:
//1. If the Calendar contains no dates in the given range, perform no deletions &
//      return zero
//2. Delete all Reminders which are later than or equal to the smaller of the two
//      dates and are earlier than or equal to the larger of the two dates. Return the
//      number deleted.
//3. Reminders are shifted down in the array to fill any vacated entries.
size_t Calendar::deleteRem(const Date &d1, const Date &d2) {
    Date smallerDate, largerDate;
    if(d1 < d2){
        smallerDate.setDate(d1);
        largerDate.setDate(d2);
    }
   else{
        smallerDate.setDate(d2);
        largerDate.setDate(d1);
   }


    int deletedReminders = 0; //represents deletedCounts
    //now we will loop on reminders array and delete reminder earlier than today's date
    for(int i=0; i<=(int)(numRem-1); i++){
        if((remArr[i]<largerDate || remArr[i].equals(largerDate))&&
        (remArr[i]>smallerDate || remArr[i].equals(smallerDate))){
            deleteRem(i);
            deletedReminders+=1;
            //reset i to where it was
            i-=1;

        }
    }
    return deletedReminders;

}


