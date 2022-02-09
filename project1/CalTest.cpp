#include <iostream>
#include <string>
#include <stdexcept>
#include "Calendar.h"
using namespace std;
//this function test default constructor of calendar class
void test_default_ctor(Calendar *cal1){
    if (cal1->getNumRem() != 0) {  // test getNumRem()
        std::cout << "Default ctor failed to create an empty calendar" << std::endl;
        std::cout << "Reported that " << cal1->getNumRem() << " reminders exist" << std::endl;
    }
    if (cal1->toString() != "") {  // test toString()
        std::cout << "Default ctor should produce an empty calendar" << std::endl;
        std::cout << "toString returned the following reminders: " << cal1->toString() << std::endl;
    }

    size_t index=cal1->deleteRem();
    if (index!=0) {  // test deleteRem()
        std::cout << "Default ctor should produce an empty calendar" << std::endl;
        std::cout << "deleteRem returned the following reminders: " << cal1->deleteRem() << std::endl;
    }


}

//this function test adding a reminder object to calendar
void test_addRem(Calendar *cal1){

    Date d1("01/17/2022");
    Reminder rem1(d1, "First day of classes");

    size_t index = cal1->addRem(rem1);   // test addRem(); Calendar now has one Reminder


    if (index != 0) {
        std::cout << "addRem failed to return index 0 for first insertion" << std::endl;
        std::cout << "Returned index == " << index << std::endl;
    }

    if (cal1->getNumRem() != 1) {
        std::cout << "addRem/getNumRem failed after inserting one reminder" << std::endl;
        std::cout << "Reported that " << cal1->getNumRem() << " reminders exist"
                  << std::endl;
    }

    if (cal1->toString() != "On 01/17/2022: First day of classes\n") {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "toString returned the following reminders:\n" << cal1->toString() << std::endl;
    }

    if (cal1->displayRem(index) != "On 01/17/2022: First day of classes") {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders:\n"
                  << cal1->displayRem(index) << std::endl;
    }


}

//helper function which will add new Reminders in calendar and then verify if they're added or not,
//it also handles exceptions that could occur when invalid array index is accessed
void test_addRem(Calendar* cal1, std::string dateStr, std::string msg){

    Date date(dateStr);
    Reminder rem(date, msg);
    try{
        //adding now
        size_t loc = cal1->addRem(rem);
        //now we will test whether it is inserted or not using getRem function
        if(cal1->getRem(loc).getMsg().compare(rem.getMsg())!=0){
            std::cout<<"unable to find reminder in calendar"<<std::endl;
            std::cout<<"displayRem returned the following reminders:\n"<<
                     cal1->displayRem(loc)<<std::endl;
        }
    } catch (std::overflow_error &excpt) {
        std::cout << "Exception successfully thrown & caught:: " << excpt.what()
                  << std::endl;
    }

}

//this function test displays all reminders in calendar
void test_displayRem(Calendar* cal1, std::string testString){
    std::string reminders = cal1->toString();
    if(reminders.compare(testString)!=0){
        std::cout<<"Test failed: ";
        if(reminders.compare("")==0){
            std::cout<<"there are no reminders in calendar\n";
        }
        else std::cout<<"Calendar contains following reminders:\n"<<cal1->toString();
    }
}
//this function test displaying reminder at specific index
void test_displayRem(Calendar* cal1, size_t index, std::string testString){
    try {
        std::string reminders = cal1->displayRem(index);
        if(reminders.compare(testString)!=0){
            std::cout<<"Test failed: ";
            if(reminders.compare("")==0){
                std::cout<<"there are no reminders in calendar\n";
            }
            else std::cout<<"Calendar contains following reminders:\n"<<cal1->toString();
        }
    }
    catch (std::invalid_argument &excp) {
        std::cout<<excp.what()<<std::endl;
    }
}

//this function tests displayRem function when string is passed to it as parameter
void test_displayRem(Calendar *cal1, std::string strToCheck, std::string stringToCmp){
    if(cal1->displayRem(strToCheck).compare(stringToCmp)!=0){
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders:\n"
                  << cal1->toString() << std::endl;
    }

}
//this function tests displayRem function when Date is passed to it as parameter
void test_displayRem(Calendar *cal1, Date date, std::string toCmp){
    if(cal1->displayRem(date).compare(toCmp)!=0){
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders:\n"
                  << cal1->toString() << std::endl;
    }

}
//this function tests displayRem function when Date is passed to it as parameter
void test_displayRem(Calendar *cal1, Date date1, Date date2, std::string toCmp) {
    if(cal1->displayRem(date1, date2).compare(toCmp)!=0){
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders:\n"
                  << cal1->toString() << std::endl;
    }
}

//this function tests findRem function when date is passed as parameter
void test_findRem(Calendar *cal1, Date d, int testIndex){
    if(cal1->findRem(d)!=testIndex){
        std::cout<<"no such remainder found at "<<testIndex<<std::endl;
        std::cout << "displayRem returned the following reminders:\n"
                  << cal1->displayRem(d) << std::endl;
    }
}

//this function tests findRem function when date is passed as parameter
void test_findRem(Calendar *cal1, std::string str, int testIndex){
    if(cal1->findRem(str)!=testIndex){
        std::cout<<"no such remainder found at "<<testIndex<<std::endl;
        std::cout << "displayRem returned the following reminders:\n"
                  << cal1->displayRem(str) << std::endl;
    }
}

//this helper function checks if a reminder exists earlier than today's date, if so it returns true else false
bool exists(Calendar* cal1){
    //iterating on reminders array and checking dates
    //initializing today's date
    Date currDate;
    for(size_t i=0; i < cal1->getNumRem(); i++){
        if(!cal1->getRem(i).getDate().equals(currDate)){
            return true;
        }
    }
    return false;
}

//this function will test delRem() function which will delete all dates earlier than today
void test_delRem(Calendar* cal1){
    size_t deleted = cal1->deleteRem();
    if(exists(cal1)){
        std::cout<<"Failed to delete all reminders earlier than today's date\n";
        std::cout<<"Total deleted: "<<deleted<<std::endl;
    }
}


//this function will test delRem() function which will delete all reminders whose message matched with msg passed
void test_delRem(Calendar* cal1, std::string msg, size_t testDeleteCounts){
    size_t deleted = cal1->deleteRem(msg);
    if(deleted != testDeleteCounts){
        std::cout<<"Failed to delete all reminders that matched with message\n";
        std::cout<<"Total deleted: "<<deleted<<std::endl;
    }
}

//this function will test delRem() function which will delete all reminders matched with reminder passed as parameter
void test_delRem(Calendar* cal1, Reminder rem, size_t testDeleteCounts){
    size_t deleted = cal1->deleteRem(rem);
    if(deleted != testDeleteCounts){
        std::cout<<"Failed to delete all reminders that matched reminder passed as parameter\n";
        std::cout<<"Total deleted: "<<deleted<<std::endl;
    }
}

//this function will test delRem() function which will delete all reminders matched with Date passed as parameter
void test_delRem(Calendar* cal1, Date date, size_t testDeleteCounts){
    size_t deleted = cal1->deleteRem(date);
    if(deleted != testDeleteCounts){
        std::cout<<"Failed to delete all reminders that matched with date passed as parameter\n";
        std::cout<<"Total deleted: "<<deleted<<std::endl;
    }
}

//this function will test delRem() function which will delete all reminders between the 2 dates passed as parameters
void test_delRem(Calendar* cal1, Date date1, Date date2, size_t testDeleteCounts){
    size_t deleted = cal1->deleteRem(date1, date2);
    if(deleted != testDeleteCounts){
        std::cout<<"Failed to delete all reminders between "<<date1.toString()<<" "<<date2.toString()<<std::endl;
        std::cout<<"Total deleted: "<<deleted<<std::endl;
    }
}

void test_delRem(Calendar *cal1, size_t index, size_t testIndex){
    if(cal1->deleteRem(index)!=testIndex){
        cout<<"Test Case: DelRem(size_t index) failed\n";
    }
}
//this method test total reminders
void test_totalRemindersInCalendar(Calendar* cal1, size_t test_totalReminders){
    if(cal1->getNumRem() != test_totalReminders){
        std::cout<<"Failed. There are "<<cal1->getNumRem()<<" reminders in calendar\n";
    }
}


//this method test getRem exception
void test_getRem(Calendar* cal1, size_t index){
    try {
        Reminder rem = cal1->getRem(index);
        std::cout<<rem.toString()<<std::endl;
    }
    catch (std::invalid_argument &excpt) {
        std::cout << "Exception successfully thrown & caught:: " << excpt.what()
                  << std::endl;
    }
}

int main() {


    Calendar cal1;

    //testing default constructor
    test_default_ctor(&cal1);

    //test adding a reminder object to calendar, this method is just for testing initial object at 0 index
    test_addRem(&cal1);

    //testing displayRem function when called with string as a parameter
    test_displayRem(&cal1, "First day of classes", "On 01/17/2022: First day of classes\n");

    //testing displayRem function when called with date object passed as a parameter
    test_displayRem(&cal1, Date("01/17/2022"), "On 01/17/2022: First day of classes\n");
    //lets test adding new Reminder

    test_addRem(&cal1, "01/20/2022", "Starting C++ assignment");
    test_addRem(&cal1, "01/31/2022", "Assignment due");
    test_addRem(&cal1, "01/22/2022", "Basketball Practice");

    //std::cout<<cal1.displayRem(Date("01/20/2022"), Date("01/22/2022"));
    //lets test display_rem function when passed with 2 date parameters
    test_displayRem(&cal1, Date("01/20/2022"), Date("01/22/2022"), "On 01/20/2022: Starting C++ assignment\n"
                                                                   "On 01/22/2022: Basketball Practice\n");

    //test findRem function by passing date and test index as parameter
    test_findRem(&cal1, Date("01/22/2022"), 2);

    //test findRem function by passing string and test index as parameter
    test_findRem(&cal1, "Basketball Practice", 2);

    //test delRem function by deleting all reminders earlier than today
    test_delRem(&cal1);

    //adding some more reminders for testing
    test_addRem(&cal1, "01/20/2022", "Friend's Birthday");
    test_addRem(&cal1, "01/22/2022", "Family Dinner");
    test_addRem(&cal1, "01/31/2022", "Meeting with Josh");

    //deleting reminder with message Family Dinner
    test_delRem(&cal1, "Family Dinner", 1);

    //test, reminders should be only 2 now
    test_totalRemindersInCalendar(&cal1, 2);

    //lets delete reminder with Date "01/31/2022"
    test_delRem(&cal1, Date("01/31/2022"), 1);

    //test, reminders should be only 1 now
    test_totalRemindersInCalendar(&cal1, 1);

    //now delete reminder by passing reminder object

    Date d("01/20/2022");
    Reminder r(d,"Friend's Birthday");
    test_delRem(&cal1, r, 1);

    //test, reminders should be only 0 now
    test_totalRemindersInCalendar(&cal1, 0);


    //adding few calendars
    //adding some more reminders for testing
    test_addRem(&cal1, "01/31/2022", "Friend's Birthday");
    test_addRem(&cal1, "01/22/2022", "Family Dinner");
    test_addRem(&cal1, "01/22/2022", "Meeting with Josh");

    //test, reminders should be only 3 now
    test_totalRemindersInCalendar(&cal1, 3);

    //deleting all reminders that lie in range 01/22/2022 to 01/31/2022, deleted counts should be 3
    test_delRem(&cal1, Date("01/22/2022"), Date("01/31/2022"), 3);

    //test, reminders should be only 0 now
    test_totalRemindersInCalendar(&cal1, 0);

    //testing displayRem when calendar is empty
    test_displayRem(&cal1, 41, "");

    //testing displayRem when there is nothing in calendar
    test_displayRem(&cal1, "");

    //now lets test addRem function when we will add reminder at invalid index
    for(int i=0; i<=50; i++){
        test_addRem(&cal1, "02/01/2022", "reminder found");
    }

    //this will test displayRem at specific index
    test_displayRem(&cal1, 10, "On 02/01/2022: reminder found");


    //testing find rem on non-existing dates
    Date d1("01/31/2022");
    test_findRem(&cal1, d1, -1);

    //testing find rem on non-existing messages
    test_findRem(&cal1, "java assignment submission", -1);

    //lets delete all reminders
    cal1.deleteRem(Date("02/01/2022"));


    //------------------------------------------testing left over cases here---------------------------

    //Failed to test displayRem(size_t) on a non-empty Calendar with parameter out of range.
    test_displayRem(&cal1, 100, "");

    //Failed to test displayRem(string) such that no matching reminders were found
    test_displayRem(&cal1, "");

    //Failed to test displayRem(string) such that more than one matching reminders were found
    test_addRem(&cal1, "02/06/2022", "Adding test cases");
    test_addRem(&cal1, "02/07/2022", "Adding test cases");
    test_displayRem(&cal1, "Adding test cases", "On 02/06/2022: Adding test cases\nOn 02/07/2022: Adding test cases\n");

    //Failed to test displayRem(Date, Date) function with the first Date parameter being a later date than the second Date parameter
        //lets add few more reminders

    test_addRem(&cal1, "02/04/2022", "reminder 4");
    test_addRem(&cal1, "02/05/2022", "reminder 5");

    test_displayRem(&cal1, Date("02/06/2022"),  Date("02/04/2022"), "On 02/04/2022: reminder 4\n"
                                                                    "On 02/05/2022: reminder 5\n"
                                                                    "On 02/06/2022: Adding test cases\n");

    //Failed to test displayRem(Date, Date) function with the smaller Date parameter being larger than all dates in the calendar
    test_displayRem(&cal1, Date("02/10/2022"), Date("02/07/2022"),
            "On 02/07/2022: Adding test cases\n");

    //Failed to test displayRem(Date, Date) function with the larger Date parameter being smaller than all dates in the calendar
    test_displayRem(&cal1, Date("02/04/2022"), Date("02/01/2022"),
                    "On 02/04/2022: reminder 4\n");


    //Failed to test displayRem(Date, Date) function with the range of Dates spanning from the middle of the calendar all the way to the end
    test_addRem(&cal1, "02/16/2022", "Reminder16");
    test_addRem(&cal1, "02/27/2022", "Reminder27");

    test_displayRem(&cal1, Date("02/16/2022"), Date("02/27/2022"),
                    "On 02/16/2022: Reminder16\nOn 02/27/2022: Reminder27\n");

    //Failed to test displayRem(Date, Date) function with the range of Dates spanning from the start of the calendar to somewhere in the middle
    //lets add reminder of date somewhere middle
    test_addRem(&cal1, "02/15/2022", "MiddleReminder");
    test_displayRem(&cal1, Date("02/07/2022"), Date("02/15/2022"),
                    "On 02/07/2022: Adding test cases\nOn 02/15/2022: MiddleReminder\n");

    //Failed to test deleteRem(size_t) function with a parameter index larger than a valid index for the calendar
    test_delRem(&cal1, 8, 0);

    //Failed to test deleteRem(size_t) function such that shifting down of reminders was required
    test_delRem(&cal1, "MiddleReminder", 1);
    test_totalRemindersInCalendar(&cal1, 6);
    test_displayRem(&cal1, 4, "On 02/16/2022: Reminder16");
    //Failed to test deleteRem(string) function such that no matches were found/deleted
    test_delRem(&cal1, "i am learning java", 0);
    //Failed to test deleteRem(Date, Date) function with the two date parameters out of order(the first one being later than the second one)
    test_delRem(&cal1, Date("02/27/2022"), Date("02/04/2022"), 6);

    //Failed to test deleteRem(Date, Date) function such that no reminders in the calendar get deleted
    test_delRem(&cal1, Reminder(Date("02/01/2022"),"hello"), 0);
    //Failed to test deleteRem(Reminder) on an empty calendar
    test_delRem(&cal1, Reminder(Date("02/01/2022"),"hello"), 0);
    //Failed to test deleteRem(Reminder) where the Reminder is not found in the calendar
    test_delRem(&cal1, Reminder(Date("02/01/2022"),"hello"), 0);


    //Failed to test deleteRem(string) function on an empty calendar
    test_delRem(&cal1, "this may be existing reminder", 0);
    //Failed to test deleteRem(Date, Date) function on an empty calendar
    test_delRem(&cal1, Date("02/01/2022"), Date("02/03/2022"), 0);
    //Failed to test deleteRem(Reminder) where the Reminder exists more than once in the calendar
        //lets add few
        test_addRem(&cal1, "02/15/2022", "Reminder15");
        test_addRem(&cal1, "02/18/2022", "Reminder18");
        test_addRem(&cal1, "02/16/2022", "Reminder16");
        test_addRem(&cal1, "02/16/2022", "Reminder16");

        test_delRem(&cal1, Reminder(Date("02/16/2022"),"Reminder16"), 2);

        //left over should be 2 now
        test_totalRemindersInCalendar(&cal1, 2);
        //Failed to test deleteRem() function w/o params such that all dates in the calendar are equal or later than current date(ie, nothing will be deleted)
        if(cal1.deleteRem()!=0){
            cout<<"Test case for deleting all reminders of date later than today's date is failed\n";
        }

        //total reminders should be 2 now
        test_totalRemindersInCalendar(&cal1, 2);
        
}