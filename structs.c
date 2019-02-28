//
// Andres Ollarvez
// CSC 173
//  Copyright © 2017 Andres Ollarvez. All rights reserved.
//

#include "structs.h"
#include <string.h>

// Create functions (props)
SNAP *SNAPcreate(int StudId, char *Name, char *Address, int Phone) {
    SNAP *snap = malloc(sizeof(SNAP));
    snap-> StudId = StudId;
    snap-> Name = malloc(sizeof(char)*101);  // Copy each char into snap->Name
    strncpy(snap->Name, Name, 101); // 100 chars max
    snap-> Address = malloc(sizeof(char)*101); // Copy each char into snap->Address
    strncpy(snap->Address, Address, 101); // 100 chars max
    snap-> Phone = Phone;
    

    snap-> next = NULL;
    return snap;
}

CSG *CSGcreate(char *Course, int StudId, char *Grade) {
    CSG *csg = malloc(sizeof(CSG));
    csg-> Course = malloc(sizeof(char)*101); // 100 chars max
    strncpy(csg->Course, Course, 101); // Copy each char into csg->Course
    csg-> StudId = StudId;
    csg-> Grade = malloc(sizeof(char)*101); // Copy each char into csg->Grade
    strncpy(csg->Grade, Grade, 101); // 100 chars max
    
    
    csg-> next = NULL;
    return csg;
}

CDH *CDHcreate(char *Course, char *Day, char *Hour) {
    CDH *cdh = malloc(sizeof(CDH));
    cdh->Course = malloc(sizeof(char)*101); // 100 chars max
    strncpy(cdh->Course, Course, 101); // Copy each char into cdh->Course
    cdh->Day = malloc(sizeof(char)*101); // 100 chars max
    strncpy(cdh->Day, Day, 101); // Copy each char into cdh->Day
    cdh->Hour=malloc(sizeof(char)*101); // 100 chars max
    strncpy(cdh->Hour, Hour, 101); // Copy each char into cdh->Hour
    
    
    cdh->next = NULL;
    return cdh;
}


CP *CPcreate(char *Course, char *PreReq) {
    CP *cp = malloc(sizeof(CP));
    cp->Course = malloc(sizeof(char)*101); // 100 chars max
    strncpy(cp->Course, Course, 101);  // Copy each char into cp->Course
    cp->PreReq = malloc(sizeof(char)*101); // 100 chars max
    strncpy(cp->PreReq, PreReq, 101); // Copy each char into cp->PreReq
    
    
    cp->next = NULL;
    return cp;
}
CR *CRcreate(char *Course, char *Room) {
    CR *cr = malloc(sizeof(CP));
    cr->Course = malloc(sizeof(char)*101); // 100 chars max
    strncpy(cr->Course, Course, 101);  // Copy each char into cp->Course
    cr->Room = malloc(sizeof(char)*101); // 100 chars max
    strncpy(cr->Room, Room, 101); // Copy each char into cp->PreReq
    
    
    cr->next = NULL;
    return cr;
}

//Comparisons // Ask for help on this
int SNAPcomp(SNAP snap, char ***value) {
    if (((strcmp("*", *(*(value+0))) == 0)||
         (snap.StudId == atoi(*(*(value+0)))))
        &&
        ((strcmp("*", *(*(value+1))) == 0)||
         (strcmp(snap.Name, *(*(value+1))) == 0))
        &&
        ((strcmp("*", *(*(value+2))) == 0)||
         (strcmp(snap.Address, *(*(value+2))) == 0))
        &&
        ((strcmp("*", *(*(value+3))) == 0)||
         (snap.Phone == atoi(*(*(value+3)))))) {
            // If tuple exists
        return 0;
    } else {
        return 1;
    }
}

int CSGcomp(CSG csg, char ***value) {
    if (((strcmp("*", *(*(value+0))) == 0)||
         (strcmp(csg.Course, *(*(value+0))) == 0))
        &&
        ((strcmp("*", *(*(value+1))) == 0)||
         (csg.StudId == atoi(*(*(value+1)))))
        &&
        ((strcmp("*", *(*(value+2))) == 0)||
         (strcmp(csg.Grade, *(*(value+2))) == 0))) {
            // If Tuple exists
        return 0;
    } else {
        return 1;
    }
}

int CDHcomp(CDH cdh, char ***value) {
    if (((strcmp("*", *(*(value+0))) == 0)||
         (strcmp(cdh.Course, *(*(value+0))) == 0))
        &&
        ((strcmp("*", *(*(value+1))) == 0)||
         (strcmp(cdh.Day, *(*(value+1))) == 0))
        &&
        ((strcmp("*", *(*(value+2))) == 0)||
         (strcmp(cdh.Hour, *(*(value+2))) == 0))) {
             // IF tuple exists
        return 0;
    } else {
        return 1;
    }
}

int CPcomp(CP cp, char ***value) {
    if (((strcmp("*", *(*(value+0))) == 0)||
         (strcmp(cp.Course, *(*(value+0))) == 0))
        &&
        ((strcmp("*", *(*(value+1))) == 0)||
         (strcmp(cp.PreReq, *(*(value+1))) == 0))) {
            // IF tuple exists
        return 0;
    } else {
        return 1;
    }
}

int CRcomp(CR cr, char ***value) {
    if (((strcmp("*", *(*(value+0))) == 0)||
         (strcmp(cr.Course, *(*(value+0))) == 0))
        &&
        ((strcmp("*", *(*(value+1))) == 0)||
         (strcmp(cr.Room, *(*(value+1))) == 0))) {
                // IF tuple existx
        return 0;
    } else {
        return 1;
    }
}



