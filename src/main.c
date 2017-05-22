#include <string.h>

#include "cal_functions.h"

int main(void) {	

  // Declare vars
  int ch, quit = 0;
  char tabItem[10];
  int todaysYear = 2017,
     todaysMonth = 05,
       todaysDay = 21;

  // Initial values
  sprintf(tabItem, "calendar");
  int selectionYear = todaysYear,
     selectionMonth = todaysMonth,
       selectionDay = todaysDay;

  // Begin curses session
  initializeCurses();

  // Construct calendar layout
  makeCalendar(selectionYear, selectionMonth, selectionDay, tabItem); // (YYYY, MM, DD)

  // Input loop until quit
  while ( quit == 0 ) {

    ch = wgetch(stdscr); // Keyboard key input

    // Calendar window key input
    if ( strcmp(tabItem, "calendar") == 0 ) {

      switch ( ch ) {
        case 'q' : quit = 1; break; // Quit

        case '?' : // Return to current date
          if ( selectionYear != todaysYear || selectionMonth != todaysMonth ) { clear(); refresh(); }
          selectionYear = todaysYear, selectionMonth = todaysMonth, selectionDay = todaysDay;
          break;

        case 'h' : // Help box
          drawHelpBox(); clear(); refresh();
          break;

        case '\t' : // Switch to notepad window
          sprintf(tabItem, "notepad");
          break;

        case KEY_LEFT : // Go back one day, including month and year if needed
          if ( selectionDay == 1 ) {
            if ( selectionMonth == 1 ) {
              selectionYear = selectionYear-1;
              selectionMonth = 12;
              selectionDay = 31;
            } else {
              selectionMonth = selectionMonth-1;
              selectionDay = getNumDaysInMonth(selectionYear, selectionMonth);
            }
            clear(); refresh();
          } else {
            selectionDay = selectionDay - 1;
          }
          break;

        case KEY_RIGHT : // Go back one day, including month and year if needed
          if ( selectionDay == getNumDaysInMonth(selectionYear, selectionMonth) ) {
            if ( selectionMonth == 12 ) {
              selectionYear = selectionYear+1;
              selectionMonth = 1;
              selectionDay = 1;
            } else {
              selectionMonth = selectionMonth+1;
              selectionDay = 1;
            }
            clear(); refresh();
          } else {
            selectionDay = selectionDay + 1;
          }
          break;

        case KEY_UP : // Go back one week, including month and year if needed
          if ( selectionDay-7 < 1 ) {
            if ( selectionMonth == 1 ) {
              selectionYear = selectionYear-1;
              selectionMonth = 12;
              selectionDay = 31 + selectionDay - 7;
            } else {
              selectionMonth = selectionMonth-1;
              selectionDay = getNumDaysInMonth(selectionYear, selectionMonth) + selectionDay - 7;
            }
            clear(); refresh();
          } else {
            selectionDay = selectionDay-7;
          }
          break;

          case KEY_DOWN : // Go forward one week, including month and year if needed
            if ( selectionDay+7 > getNumDaysInMonth(selectionYear, selectionMonth) ) {
              if ( selectionMonth == 12 ) {
                selectionYear = selectionYear+1;
                selectionMonth = 1;
                selectionDay = selectionDay + 7 - 31;
              } else {
                selectionMonth = selectionMonth+1;
                selectionDay = selectionDay + 7 - getNumDaysInMonth(selectionYear, selectionMonth-1);
              }
              clear(); refresh();
            } else {
            selectionDay = selectionDay+7;
          }
          break;

        case KEY_SLEFT : // Go back one month, including year if needed
          if ( selectionMonth == 1 ) {
            selectionYear = selectionYear-1;
            selectionMonth = 12;
          } else {
            selectionMonth = selectionMonth-1;
          }
          clear(); refresh();
          if ( selectionDay > getNumDaysInMonth(selectionYear, selectionMonth) ) { selectionDay = getNumDaysInMonth(selectionYear, selectionMonth); }
          break;

        case KEY_SRIGHT : // Go forward one month, including year if needed
          if ( selectionMonth == 12 ) {
            selectionYear = selectionYear+1;
            selectionMonth = 1;
          } else {
            selectionMonth = selectionMonth+1;
          }
          clear(); refresh();
          if ( selectionDay > getNumDaysInMonth(selectionYear, selectionMonth) ) { selectionDay = getNumDaysInMonth(selectionYear, selectionMonth); }
          break;

        case KEY_SR : // Go back one year, including year if needed
          selectionYear = selectionYear-1;
          clear(); refresh();
          if ( selectionDay > getNumDaysInMonth(selectionYear, selectionMonth) ) { selectionDay = getNumDaysInMonth(selectionYear, selectionMonth); }
          break;

        case KEY_SF : // Go forward one year, including year if needed
          selectionYear = selectionYear+1;
          clear(); refresh();
          if ( selectionDay > getNumDaysInMonth(selectionYear, selectionMonth) ) { selectionDay = getNumDaysInMonth(selectionYear, selectionMonth); }
          break;
      }
    } else {

      switch ( ch ) {

        case 'q' : quit = 1; break; // Quit

        case '?' : // Return to current date
          if ( selectionYear != todaysYear || selectionMonth != todaysMonth ) { clear(); refresh(); }
          selectionYear = todaysYear, selectionMonth = todaysMonth, selectionDay = todaysDay;
          break;

        case 'h' : // Help box
          drawHelpBox(); clear(); refresh();
          break;

        case '\t' : // Switch to notepad window
          sprintf(tabItem, "calendar");
          break;

        case 10: // Enter
          editNotepad();
          break;
      }
    }

  makeCalendar(selectionYear, selectionMonth, selectionDay, tabItem);
  }

  // End curses session
  terminateCurses();

  return 0;
}
