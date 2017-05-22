#include <stdio.h>
#include <time.h>
#include <math.h>

#include "cal_ncurses.h"

// Get month duration in days
int getNumDaysInMonth(int selectionYear, int selectionMonth) {

  int the_numDaysInMonth;
  switch ( selectionMonth ) {
    case 1 : the_numDaysInMonth = 31; break;
    case 2 :
      if ( selectionYear%4 == 0 ) {
        the_numDaysInMonth = 29;
      } else {
        the_numDaysInMonth = 28;
      }
      break;
    case 3 : the_numDaysInMonth = 31; break;
    case 4 : the_numDaysInMonth = 30; break;
    case 5 : the_numDaysInMonth = 31; break;
    case 6 : the_numDaysInMonth = 30; break;
    case 7 : the_numDaysInMonth = 31; break;
    case 8 : the_numDaysInMonth = 31; break;
    case 9 : the_numDaysInMonth = 30; break;
    case 10 : the_numDaysInMonth = 31; break;
    case 11 : the_numDaysInMonth = 30; break;
    case 12 : the_numDaysInMonth = 31; break;
  }
  return the_numDaysInMonth;
}

// Get month name from monthNum
void assignMonthName(char* the_monthName, int selectionMonth) {

  //char the_monthName[9];
  switch ( selectionMonth ) {
    case 1 : sprintf(the_monthName,   "January"); break;
    case 2 : sprintf(the_monthName,  "February"); break;
    case 3 : sprintf(the_monthName,     "March"); break;
    case 4 : sprintf(the_monthName,     "April"); break;
    case 5 : sprintf(the_monthName,       "May"); break;
    case 6 : sprintf(the_monthName,      "June"); break;
    case 7 : sprintf(the_monthName,      "July"); break;
    case 8 : sprintf(the_monthName,    "August"); break;
    case 9 : sprintf(the_monthName, "September"); break;
    case 10 : sprintf(the_monthName,  "October"); break;
    case 11 : sprintf(the_monthName, "November"); break;
    case 12 : sprintf(the_monthName, "December"); break;
}}

// Use Doomsday Rule to determine day-of-week
// Sun - 0, Mon - 1, Tue - 2,  Wed - 3,  Thu - 4, Fri - 5, Sat - 6
int getFirstDayOfMonth(int selectionYear, int selectionMonth) {

  // Obtain doomday value
  int doomsdayYear = selectionYear - 1000*(selectionYear/1000); // last two numbers of year
  int doomsdayAnchor = 2; // 2000-2099
  int doomsday = (doomsdayAnchor + (doomsdayYear/12) + (doomsdayYear%12) + ((doomsdayYear%12)/4))%7; // algorithm

  // Obtain dayOfYear index for selectionMonth
  int monthOfYear, dayOfYear = 1;
  for ( monthOfYear = 1; monthOfYear < selectionMonth; monthOfYear++ ) {
    dayOfYear = dayOfYear + getNumDaysInMonth(selectionYear, monthOfYear);
  }

  // January 3rd is doomsday, apply leap year condition
  int dayOfWeek;
  if ( doomsdayYear%4 == 0 ) {
      dayOfWeek = ((dayOfYear-4)%7 + doomsday)%7;
  } else {
      dayOfWeek = ((dayOfYear-3)%7 + doomsday)%7;
  }

  // Days of week (0-6)
  return dayOfWeek;
}

// Check system time for 
int checkForCurrentDate(int selectionYear, int selectionMonth, int gridDate) {

  // Get current date parameters
  int currentYear, currentMonth, currentDay;
  time_t t = time(NULL);
  struct tm tm_now = *localtime(&t);
  currentYear = tm_now.tm_year+1900; // year since 1900
  currentMonth = tm_now.tm_mon+1; // zero-indexed month number
  currentDay = tm_now.tm_mday; // day of month

  if ( selectionYear == currentYear &&
      selectionMonth == currentMonth &&
            gridDate == currentDay ) { return 1; } else { return 0; }
}

// (Re)Draw calendar grid with known time period and date
void makeCalendar(int selectionYear, int selectionMonth, int selectionDay, char* tabItem) {

  // Obtain current month parameters
  char selectionMonthName[10]; assignMonthName(selectionMonthName, selectionMonth);
  int numDaysInMonth = getNumDaysInMonth(selectionYear, selectionMonth); // [28, 31]
  int firstDayOfMonth = getFirstDayOfMonth(selectionYear, selectionMonth); // 0-6 Sun through Sat

  // Draw top header bar, bottom status bar, and notepad frame
  drawCalendarHeader(selectionYear, selectionMonthName);
  drawCalendarStatusBar();
  drawCalendarNotepad(tabItem);

  // Declare vars and parameters
  int day_i, week_i;

  for ( week_i = 1; week_i < 7; week_i++ ) { // For each week (rows)
  for ( day_i = 1; day_i < 8; day_i++ ) { // For each day during the week (columns)

    // Maximum range to allow space for status box (up to a Monday the 31st, if necessary)
    if ( week_i == 6 && day_i > 2 ) { return; }

    // Obtain day number from indices
    int gridDate = 7*(week_i-1) + day_i - firstDayOfMonth; // [0, {28, 29, 30, 31})
    if ( gridDate > 0 && gridDate <= numDaysInMonth ) {

      // Position day in monthly grid
      int dayBoxHeight = 6, dayBoxWidth = 12, dayBoxYOffset = 5, dayBoxXOffset = 1;
      int dayBoxYPos = dayBoxYOffset+(week_i-1)*dayBoxHeight,
          dayBoxXPos = dayBoxXOffset+(day_i-1)*dayBoxWidth;

      //if os.path.isfile(attemptFileName):
      //  window_dayFrame.addstr(2,0,"   +++++  \n   +@@@+  \n   +++++  ",curses.color_pair(5))
      // Use red border (if unselected) and red number on today's date
      //if ( gridDate == int(sysDay) && currentMonth == sysMonth && currentYear == sysYear) {
      //  window_dayFrame.addstr(1,9,str(gridDate),curses.color_pair(2))
      //  window_dayFrame.attrset(curses.color_pair(2))
      //} else {
      //}

      // Drawing characteristics for event
      int eventSelection = 0,
            eventCurrent = checkForCurrentDate(selectionYear, selectionMonth, gridDate);
      // Blue border if selected
      if ( gridDate == selectionDay ) { eventSelection = 1; }

      // Create window
      drawCalendarDayBox(dayBoxYPos, dayBoxXPos, gridDate, tabItem, eventSelection, eventCurrent);
    }
  }}
}
