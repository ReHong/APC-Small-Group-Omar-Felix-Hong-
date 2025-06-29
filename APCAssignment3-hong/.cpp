#include "InstructorUI.h"
#include <iostream>

// Your existing callback lives elsewhere:
extern int callback(void*, int, char**, char**);

using namespace std;

void instructor_ui(sqlite3* db,
    Instructor& inst,
    char*& messageError)
{
    while (true)
    {
        cout << "\n=========== Instructor Menu ============\n"
            << "1. View my schedule\n"
            << "2. Print a course roster\n"
            << "3. Search my rosters for a student\n"
            << "0. Log out / Exit\n"
            << "Choice: ";

        int choice{};
        if (!(cin >> choice)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        if (choice == 0) break;

        string sql;
        switch (choice)
        {
        case 1: sql = inst.print_schedule();                   break;
        case 2: sql = inst.print_course_roster();              break;
        case 3: sql = inst.search_course_roster_for_student(); break;
        default: cout << "Invalid selection.\n"; continue;
        }

        int rc = sqlite3_exec(db, sql.c_str(),
            callback, nullptr, &messageError);

        if (rc != SQLITE_OK) {
            cerr << "SQL error: " << messageError << '\n';
            sqlite3_free(messageError);
        }
        else {
            cout << "-----------------------------------------\n(end of results)\n";
        }
    }
}
