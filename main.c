// Andres Ollarvez
// CSC 173
//  Copyright © 2017 Andres Ollarvez. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "databases.h"

int main(int argc, char const *argv[]) {

    schema DB = *createDB(); // Create database schema
    
    //Read Tests
    printf("%s\n", "*LOAD*");
    printf("%s\n", "Load DB from \"bookDBs.txt\"...");
    DBFInsert(DB, "bookDBs.txt");
    
    
    //Test Lookups
    printf("*LOOKUP 1*\n");
    
    printf("Look up CSG entries with Class = \"CSC101\"\n");
    CSG *result = CSGLookup(DB, create("CSC101", "*", "*", "NA"));
    
    printf("Result:\n");
    if (!result) {
        printf("*No Result*\n");

    }
    
    while(result) {
        printf("Course: %s\n", result ->Course);
        printf("StudId: %d\n", result ->StudId);
        printf("Grade: %s\n", result ->Grade);
        printf("Next: %p\n", result ->next);
        
        result = result->next;
    }
    
    // Second test Look up
    
    printf("*LOOKUP 2*\n");
    
    printf("Look up CDH entries with hour = \"9AM\"\n");
    result = CSGLookup(DB, create("*", "*", "9AM", "NA"));
    
    printf("Result:\n");
    if (!result) {
        printf("*No Result*\n");
    }
    
    while(result) {
        printf("Course: %s\n", result ->Course);
        printf("StudId: %d\n", result ->StudId);
        printf("Grade: %s\n", result ->Grade);
        
        printf("Next: %p\n", result ->next);
        result = result->next;
    }
    
    //Save File Test
    printf("*SAVE*\n");
    printf("Save database to \"saveDB.txt\"");
    saveDB(DB, "saveDB.txt");

    
    //Test Delete
    printf("*DELETE*\n");
    printf("Deleting all classes that have CS101 as prerequisite\n");
    CSGDelete(DB, create("*", "CS101", "NA", "NA"));
    result = CSGLookup(DB, create("CS205", "*", "NA", "NA"));
    
    printf("Result:\n");
    if (!result) {
        printf("*No Result*\n");
    }
    
    while(result) {
        printf("Course: %s\n", result ->Course);
        printf("StudId: %d\n", result ->StudId);
        printf("Grade: %s\n", result ->Grade);
        printf("Next: %p\n", result ->next);
        
        result = result->next;
    }
    
    printf("*PART 2*\n");
    printf("What grade did L. Van Pelt get in CS101?\n");
    printf("L. Van Pelt got a(n) %s in CS101\n", whatGrade(DB, "L. Van Pelt", "CS101"));
    printf("In what room is L. Van Pelt at 9AM on Fridays?\n");
    printf("L. Van Pelt is in %s at 9AM on Fridays\n", whatRoom(DB, "L. Van Pelt", "9AM", "F"));
    
    //Test Unions
    printf("*UNION*\n");
    printf("Union CSG entries to additional CSG form (on another database)\n");
    
    schema DB2 = *createDB();
    DBFInsert(DB2, "CSG.txt");
    sunion(DB, DB2, "CSG");
    
    result = CSGLookup(DB, create("CS101", "*", "*", "NA"));
    printf("Result:\n");
    if (!result) {
        printf("*No Result*\n");
    }
    while(result) {
        printf("Course: %s\n", result ->Course);
        printf("StudId: %d\n", result ->StudId);
        printf("Grade: %s\n", result ->Grade);
        printf("Next: %p\n", result ->next);
        
        result = result->next;
    }
    
    //Test differnce
    printf("*DIFFERENCE*\n");
    printf("Difference between the main database and 2nd database\n");
    difference(DB, DB2, "CSG");
    
    result = CSGLookup(DB, create("CS101", "*", "*", "NA"));
    printf("Result:\n");
    if (!result) {
        printf("*No Result*\n");
    }
    
    while(result) {
        printf("Course: %s\n", result ->Course);
        printf("StudId: %d\n", result ->StudId);
        printf("Grade: %s\n", result ->Grade);
        printf("Next: %p\n", result ->next);
        
        result = result->next;
    }
    
    //Test intersection
    printf("*INTERSECT*\n");
    printf("Intersection between the main database and another database\n");
    
    DBFInsert(DB, "CSG.txt"); //Making some common tuples, Got this tip from internet
    
    intersect(DB, DB2, "CSG");
    result = CSGLookup(DB, create("CS101", "*", "*", "DC"));
    printf("Result:\n");
    if (!result) {
        printf("*No Result*\n");
    }
    while(result) {
        printf("Course: %s\n", result ->Course);
        printf("StudId: %d\n", result ->StudId);
        printf("Grade: %s\n", result ->Grade);
        printf("Next: %p\n", result ->next);
        
        result = result->next;
    }
    
    
    // I decided to use both examples from the book for these::
    
    //Test projection
    printf("*PROJECTION*\n");
    printf("Project entries in the CSG table whith course = CS101 onto StudentID\n");
    schema examples = *createDB(); // created table again
    DBFInsert(examples, "bookDBs.txt");
    CSGProject(CSGLookup(examples, create("CS101", "*", "*", "*")), "StudId");
    
    //Test Join
    printf("*JOIN*\n");
    printf("Join CR and CDH where the courses are the same");
    join(examples);
    
    return 0;
}