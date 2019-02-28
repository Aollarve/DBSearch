//
// Andres Ollarvez
// CSC 173
//  Copyright © 2017 Andres Ollarvez. All rights reserved.
//

#ifndef structs_h
#define structs_h

#include <stdio.h>
#include <stdlib.h>

// This is specifically made for each struct (SNAP, CSG, CDH, etc)

//SNAP = StudId, Name, Address, Phone
struct SNAP {
    int StudId;
    char *Name;
    char *Address;
    int Phone;
    struct SNAP *next;
};
typedef struct SNAP SNAP;


//CSG = Course, StudId, Grade
struct CSG {
    char *Course;
    int StudId;
    char *Grade;
    struct CSG *next;
};
typedef struct CSG CSG;

//CDH = Course, Day, Hour
struct CDH {
    char *Course;
    char *Day;
    char *Hour;
    struct CDH *next;
};
typedef struct CDH CDH;

//CP = Course, Prereq
struct CP {
    char *Course;
    char *PreReq;
    struct CP *next;
};
typedef struct CP CP;


//Course, Room
struct CR {
    char *Course;
    char *Room;
    struct CR *next;
};
typedef struct CR CR;


// Create functions (props)
SNAP *SNAPcreate(int, char *, char *, int);
CSG *CSGcreate(char *, int, char *);
CDH *CDHcreate(char *, char *, char *);
CP *CPcreate(char *, char *);
CR *CRcreate(char *, char *);

//Comparisons
int SNAPcomp(SNAP, char ***);
int CSGcomp(CSG, char ***);
int CDHcomp(CDH, char ***);
int CPcomp(CP, char ***);
int CRcomp(CR, char ***);


#endif /* structs_h */
