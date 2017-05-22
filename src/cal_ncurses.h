#include <string.h>
#include <ncurses.h>

// Configure and initialize curses screen
void initializeCurses() {

  initscr(); // Initialize curses
  noecho();  // Disable key echoing
  refresh(); // Apply curses screen
  curs_set(0); // No cursor blink
  keypad(stdscr, 1);

  // Initialize color and define schemes
  start_color(); // Also default white on black
  init_pair(1, COLOR_WHITE, COLOR_BLACK); // white default
  init_pair(2, COLOR_RED,   COLOR_BLACK); // red current date
  init_pair(3, COLOR_BLUE,  COLOR_BLACK); // blue selection date
  init_pair(4, COLOR_CYAN,  COLOR_BLACK); // cyan highlight date
}

// Safely end curses screen
void terminateCurses() {

  echo(); // Re-enble key echoing
  endwin(); // End curses session
}

// Draw top month/days-of-week bar
void drawCalendarHeader(int yearNum, char* the_monthName) {

  int headerHeight = 5, headerWidth = 84, headerYPos = 0, headerXPos = 1;
  WINDOW* window_header = newwin(headerHeight, headerWidth, headerYPos, headerXPos);
  box(window_header, 0, 0);
  char text_headerMonthYear[15]; sprintf(text_headerMonthYear, "%s %d", the_monthName, yearNum);
  mvwaddstr(window_header, 1, 30, text_headerMonthYear);
  mvwaddstr(window_header, 3, 4, "Sun          Mon         Tue         Wed         Thu         Fri         Sat");
  wrefresh(window_header);
}

// Draw bottom status information box
void drawCalendarStatusBar() {

    // TODO: add status ID functionality
    int statusBarHeight = 6, statusBarWidth = 60, statusBarYPos = 35, statusBarXPos = 25;
    WINDOW* window_statusBar = newwin(statusBarHeight, statusBarWidth, statusBarYPos, statusBarXPos);
    box(window_statusBar, 0, 0);
    mvwaddstr(window_statusBar, 1, 1, "Type \'h\' for help.");
    wrefresh(window_statusBar);
}

// Draw notepad on right
void drawCalendarNotepad(char* tabItem) {

    // Create notepad window (with color if selected)
    int notepadHeight = 41, notepadWidth = 58, notepadYPos = 0, notepadXPos = 86;
    WINDOW* window_notepad = newwin(notepadHeight, notepadWidth, notepadYPos, notepadXPos);
    if ( strcmp(tabItem, "notepad") == 0 ) { wattron(window_notepad, COLOR_PAIR(3)); }
    box(window_notepad, 0, 0);
    wrefresh(window_notepad);
}

// Draw (week_i, day_i)'s day box within arrangement of month's days
void drawCalendarDayBox(int dayBoxYPos, int dayBoxXPos, int gridDate, char* tabItem, int eventSelection, int eventCurrent) {

  // dayBox graphic parameters
  int dayBoxHeight = 6, dayBoxWidth = 12, dayBoxYOffset = 5, dayBoxXOffset = 1;
  int dayBoxStrYPos = 1, dayBoxStrXPos = 8;

  // Draw dayBox in grid
  WINDOW* window_dayBox = newwin(dayBoxHeight, dayBoxWidth, dayBoxYPos, dayBoxXPos);

  // grid date int to str
  char text_gridDate[3]; snprintf(text_gridDate, 3, "%d", gridDate);
  mvwaddstr(window_dayBox, dayBoxStrYPos, dayBoxStrXPos, text_gridDate);

  // Enable drawing attributes
  if ( eventCurrent == 1 ) { wattron(window_dayBox, COLOR_PAIR(2)); }
  if ( eventSelection == 1 && strcmp(tabItem, "calendar") == 0 ) { wattron(window_dayBox, COLOR_PAIR(3)); }
  else if ( eventSelection == 1 && strcmp(tabItem, "notepad") == 0 ) { wattron(window_dayBox, COLOR_PAIR(4)); }

  // Refresh screen with newly drawn box
  box(window_dayBox, 0, 0);
  wrefresh(window_dayBox);
}

// Draw help and command info box
void drawHelpBox() {

  WINDOW* window_helpBox = newwin(25, 70, 9, 30);
  mvwaddstr(window_helpBox,  2, 8, "Commands");
  mvwaddstr(window_helpBox,  4, 4, "q - Quit");
  mvwaddstr(window_helpBox,  5, 4, "h - Open this help menu");
  mvwaddstr(window_helpBox,  6, 4, "? - Return to today's date");
  mvwaddstr(window_helpBox,  7, 2, "TAB - Switch between calendar/notepad");
  mvwaddstr(window_helpBox, 10, 2, "Calendar window");
  mvwaddstr(window_helpBox, 11, 4, "            left, right - Navigate days");
  mvwaddstr(window_helpBox, 12, 4, "               up, down - Navigate weeks");
  mvwaddstr(window_helpBox, 13, 4, "shift+left, shift+right - Navigate months");
  mvwaddstr(window_helpBox, 14, 4, "   shift+up, shift+down - Navigate years");
  mvwaddstr(window_helpBox, 17, 2, "Notepad window");
  mvwaddstr(window_helpBox, 18, 4, "                  ENTER - Edit notepad (todo)");
  mvwaddstr(window_helpBox, 21, 2, "Hit any key to continue...");
  box(window_helpBox, 0, 0);
  wrefresh(window_helpBox);
  wgetch(stdscr);
}

// Edit mode of selected day's notepad
void editNotepad() {

  // Create notepad window
  int notepadTextHeight = 39, notepadTextWidth = 56, notepadTextYPos = 1, notepadTextXPos = 87;
  WINDOW* window_notepadText = newwin(notepadTextHeight, notepadTextWidth, notepadTextYPos, notepadTextXPos);
  box(window_notepadText, 0, 0);
  wrefresh(window_notepadText);
  int endIt = getch();
}
