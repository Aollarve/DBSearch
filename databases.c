// Andres Ollarvez
// CSC 173
//  Copyright © 2017 Andres Ollarvez. All rights reserved.
//

#include "databases.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int hashId(int StudId) {
    return StudId % 1009; // from CH 8
}
int hashNId(char *Course) {
    int e = 0;
    while(*Course != '\0') {
        e+= *Course - '0';
        Course++;
    }
    
    return e % 1009;
}
void saveDB(schema db, char *fileName) {
    FILE *file;
    file = fopen(fileName, "w+"); //This will clear the file and make it ready to write
    
    
    
    if (file == NULL) {
        perror("Unable to open file");
        
    } else {
        
        int i;
        
        
        //To save the Table SNAP
        for (i = 0; i<1009; i++) {
            
            SNAP *tuple = *(db.SNAPTab+i);
            while (tuple) {
                fprintf(file, "SNAP \t %d \t %s \t %s \t %d\n", tuple->StudId, tuple->Name, tuple->Address, tuple->Phone);
                tuple = tuple->next;
            }
        }
    
        //To save the Table CSG
        for (i = 0; i<1009; i++) {
            
            CSG *tuple = *(db.CSGTab+i);
            while (tuple) {
                fprintf(file, "CSG \t %s \t %d \t %s\n",
                        tuple->Course, tuple->StudId, tuple->Grade);
                tuple = tuple->next;
            }
        }
        
        //To save the Table CDH
        for (i = 0; i<1009; i++) {
            
            CDH *tuple = *(db.CDHTab+i);
            while (tuple) {
                fprintf(file, "CDH \t %s \t %s \t %s\n", tuple->Course, tuple->Day, tuple->Hour);
                tuple = tuple->next;
            }
        }
        
        //To save the Table  CP
        for (i = 0; i<1009; i++) {
            
            CP *tuple = *(db.CPTab+i);
            while (tuple) {
                fprintf(file, "CP \t %s \t %s\n", tuple->Course, tuple->PreReq);
                tuple = tuple->next;
            }
        }
        
        //To save the Table CR
        for (i = 0; i<1009; i++) {
            
            CR *tuple = *(db.CRTab+i);
            while (tuple) {
                fprintf(file, "CR \t %s \t %s\n", tuple->Course, tuple->Room);
                tuple = tuple->next;
            }
        }
        
        
        fclose(file);
    }
}

schema *createDB() {
    schema *DB = malloc(sizeof(schema));
    
    
    DB ->SNAPTab = malloc(sizeof(SNAP *)*1009);
    for (unsigned int i = 0; i < 1009; i++) {
        
        *(DB->SNAPTab+i) = NULL;
    }
    
    
    DB ->CSGTab = malloc(sizeof(CSG *)*1009);
    for (unsigned int i = 0; i < 1009; i++) {
        
        *(DB->CSGTab+i) = NULL;
    }
    
    
    DB ->CDHTab = malloc(sizeof(CDH *)*1009);
    for (unsigned int i = 0; i < 1009; i++) {
        *(DB->CDHTab+i) = NULL;
    }
    
    DB ->CPTab = malloc(sizeof(CP *)*1009);
    for (unsigned int i = 0; i < 1009; i++) {
        
        *(DB->CPTab+i) = NULL;
    }
    
    DB ->CRTab =  malloc(sizeof(CR *)*1009);
    for (unsigned int i = 0; i < 61; i++) {
        
        *(DB->CRTab+i) = NULL;
    }
    
    return DB;
}



//For lookups
void lookup(schema data, char ***value, char *relation) {
    if (strcmp("SNAP", relation) == 0) { // If it is there
        SNAP *result = SNAPLookup(data, value);
        
        printf("%s", "Result:\n");
        if (!result) {
            printf("%s", "*No Result*\n");
        }
        while(result) {
            printf("Student ID: %d\n", result ->StudId);
            printf("Name: %s\n", result ->Name);
            printf("Address: %s\n", result ->Address);
            printf("Phone: %d\n", result -> Phone);
            
            
            result = result->next;
        }
        

    } else if (strcmp("CSG", relation) == 0) {
        
        CSG *result = CSGLookup(data, value);
        
        printf("%s", "Result:\n");
        if (!result) {
            printf("%s", "*No Result*\n");
        }
        while(result) {
            printf("Course: %s\n", result ->Course);
            printf("Student ID: %d\n", result ->StudId);
            printf("Grade: %s\n", result ->Grade);
            
            
            result = result->next;
        }
        
        
    } else if (strcmp("CDH", relation) == 0) {
        CDH *result = CDHLookup(data, value);
        
        printf("%s", "Result:\n");
        if (!result) {
           printf("%s", "*No Result*\n");
        }
        while(result) {
            printf("Course: %s\n", result ->Course);
            printf("Student ID: %s\n", result ->Day);
            printf("Grade: %s\n", result ->Hour);
            
            
            result = result ->next;
        }
        

    } else if (strcmp("CP", relation) == 0) {
        
        CP *result = CPLookup(data, value);
        
        printf("%s", "Result:\n");
        if (!result) {
            printf("%s", "*No Result*\n");
        }
        while(result) {
            printf("Course: %s\n", result ->Course);
            printf("Prerequisite: %s\n", result ->PreReq);
            
            result = result->next;
        }
        
        
    } else if (strcmp("CR", relation) == 0) {
        CR *result = CRLookup(data, value);
        
        printf("%s", "Results:");
        if (!result) {
            printf("%s", "*No Result*\n");
        }
        while(result) {
            printf("Course: %s\n", result ->Course);
            printf("Grade: %s\n", result ->Room);
            
            
            result  = result ->next;
        }
        
        
    } else {
        
        printf("Relation Not Identified: %s\n", relation);
    }
}

SNAP *SNAPLookup(schema data, char ***value) {
    
    
    if (strcmp("*", *(*(value+1))) != 0) {
        //when there is an Student ID
        int val = hashNId(**(value+1));
        
        if (*(data.SNAPTab + val)) {
            
            SNAP *thisval = *(data.SNAPTab + val);
            SNAP *val2 = NULL;
            
            //check that the all information actually matches
            while(thisval) {
                if (SNAPcomp(*thisval, value) == 0) {
                    //If they are the same
                    SNAP *new = SNAPcreate(thisval->StudId, thisval->Name, thisval->Address, thisval->Phone);
                    
                    new ->next = val2;
                    val2 = new;
                }
                thisval = thisval->next;
            }
            
            return val2;
            
        } else {
            
            // Nothing found
            return NULL;
        }
    } else {
        //When there is no Student ID
        SNAP *val2 = NULL;
        
        for (int i = 0; i < 1009; i++) {
            SNAP *thisval = *(data.SNAPTab+i);
            
            //Check in each bucket
            while(thisval) {
                if (SNAPcomp(*thisval, value) == 0) {
                    //If they are equal
                    SNAP *new = SNAPcreate(thisval->StudId, thisval->Name, thisval->Address, thisval->Phone);
                    
                    new ->next = val2;
                    val2 = new;
                }
                
                thisval = thisval ->next;
            }
        }
        
        
        return val2;
    }
}

CSG *CSGLookup(schema data, char ***value) {
    
    if (strcmp("*", *(*(value+1))) != 0) {
        //when there is a Student ID
        int val = hashId(atoi(**(value+1)));
        
        if (*(data.CSGTab+val)) {
            
            CSG *thisval = *(data.CSGTab+val);
            CSG *val2 = NULL;
            
            //check that the all information actually matches
            while(thisval) {
                if (CSGcomp(*thisval, value) == 0) {
                    //IF they are equal
                    CSG *new = CSGcreate(thisval->Course, thisval->StudId, thisval->Grade);
                    
                    new ->next = val2;
                    val2 = new;
                }
                thisval = thisval ->next;
            }
            
            return val2;
        } else {
            //If nothing found
            return NULL;
        }
    } else {
        //There is no Student ID
        CSG *val2 = NULL;
        for (int i = 0; i < 1009; i++) {
            CSG *thisval = *(data.CSGTab+i);
            
            
            //Check in each bucket
            while(thisval) {
                if (CSGcomp(*thisval, value) == 0) {
                    //If they are equal
                    CSG *new = CSGcreate(thisval->Course, thisval->StudId, thisval->Grade);
                   
                    new ->next = val2;
                    val2 = new;
                }
                thisval = thisval ->next;
            }
            
        }
        return val2;
    }
}

CDH *CDHLookup(schema data, char ***value) {
    
    if (strcmp("*", *(*(value+0))) != 0) {
        //When there is a Student ID
        int val = hashNId(**(value+0));
        
        if (*(data.CDHTab+val)) {
            
            CDH *thisval = *(data.CDHTab+val);
            CDH *val2 = NULL;
            
            
            while(thisval) {
                if (CDHcomp(*thisval, value) == 0) {
                    //if they are equla
                    CDH *new = CDHcreate(thisval->Course, thisval->Day, thisval->Hour);
                    
                    new ->next = val2;
                    val2 = new;
                }
                
                thisval = thisval ->next;
            }
            
            return val2;
        } else {
            //if nothing found
            
            return NULL;
        }
    } else {
        //If there is No Student ID
        CDH *val2 = NULL;
        
        for (int i = 0; i < 1009; i++) {
            CDH *thisval = *(data.CDHTab+i);
            
            //check each bucket
            while(thisval) {
                if (CDHcomp(*thisval, value) == 0) {
                    //if they are eqaul
                    CDH *new = CDHcreate(thisval ->Course, thisval ->Day, thisval ->Hour);
                    new ->next = val2;
                    val2 = new;
                }
                
                thisval = thisval ->next;
            }
        }
        
        return val2;
    }
}


CP *CPLookup(schema data, char ***value) {
    
    if (strcmp("*", *(*(value+0))) != 0) {
        //If there is an Student ID
        int val = hashNId(**(value+0));
        
        if (*(data.CPTab+val)) {
            
            CP *thisval = *(data.CPTab+val);
            CP *val2 = NULL;
            
            while(thisval) {
                if (CPcomp(*thisval, value) == 0) {
                    //if they are equal
                    CP *new = CPcreate(thisval->Course, thisval->PreReq);
                    new ->next = val2;
                    val2 = new;
                }
                thisval = thisval ->next;
            }
            
            return val2;
            
        } else {
            //nothing found
            
            return NULL;
        }
    } else {
        //if there was no Student Id
        CP *val2 = NULL;
        
        
        for (int i = 0; i < 1009; i++) {
            CP *thisval = *(data.CPTab+i);
            //check each bucket
            while(thisval) {
                if (CPcomp(*thisval, value) == 0) {
                    //info match! insert to val2!
                    CP *new = CPcreate(thisval->Course, thisval->PreReq);
                    new ->next = val2;
                    val2 = new;
                }
                
                thisval = thisval ->next;
            }
        }
        
        
        return val2;
    }
}



CR *CRLookup(schema data, char ***value) {
    

    if (strcmp("*", *(*(value+0))) != 0) {
        //If there was an Student ID
        int val = hashNId(**(value+0));
        
        if (*(data.CRTab+val)) {
            
            CR *thisval = *(data.CRTab+val);
            CR *val2 = NULL;
            
            
            while(thisval) {
                if (CRcomp(*thisval, value) == 0) {
                    //if they are equal
                    CR *new = CRcreate(thisval->Course, thisval->Room);
                    new ->next = val2;
                    val2 = new;
                }
                thisval = thisval ->next;
            }
            
            return val2;
        } else {
            //nothing found
            return NULL;
        }
    } else {
        //If there was no Student ID
        CR *val2 = NULL;
     
        for (int i = 0; i < 1009; i++) {
            CR *thisval = *(data.CRTab+i);
            
            //check each bucket
            while(thisval) {
                if (CRcomp(*thisval, value) == 0) {
                    //If they are equal
                    CR *new = CRcreate(thisval->Course, thisval->Room);
                    new->next = val2;
                    val2 = new;
                }
                
                thisval = thisval ->next;
            }
        }
        
        return val2;
    }
}


//For inserts
void SNAPInsert(schema data, SNAP snap) {
    
    int val = hashNId(snap.Name);
    
    if (*(data.SNAPTab+val)) {
        //if they match
        
        SNAP *temporal = *(data.SNAPTab+val);
        *(data.SNAPTab+val) = SNAPcreate(snap.StudId, snap.Name, snap.Address, snap.Phone);
        (*(data.SNAPTab+val))->next = temporal;
        
    } else {
        //if there is an empty slot
        
        *(data.SNAPTab+val) = SNAPcreate(snap.StudId, snap.Name, snap.Address, snap.Phone);
    }
}


void CSGInsert(schema data, CSG csg) {
    
    int val = hashId(csg.StudId);
    
    if (*(data.CSGTab+val)) {
        //if they match
        
        CSG *temporal = *(data.CSGTab+val);
        *(data.CSGTab+val) = CSGcreate(csg.Course, csg.StudId, csg.Grade);
        (*(data.CSGTab+val))->next = temporal;
        
    } else {
        //if there is an empty slot
        *(data.CSGTab+val) = CSGcreate(csg.Course, csg.StudId, csg.Grade);
    }
}

void CDHInsert(schema data, CDH cdh) {
    
    int val=hashNId(cdh.Course);
    
    if (*(data.CDHTab+val)) {
        //if they match
        
        CDH *temporal = *(data.CDHTab+val);
        *(data.CDHTab+val) = CDHcreate(cdh.Course, cdh.Day, cdh.Hour);
        (*(data.CDHTab+val))->next = temporal;
        
    } else {
        //if there is an empty slot
        *(data.CDHTab+val) = CDHcreate(cdh.Course, cdh.Day, cdh.Hour);
    }
}


void CPInsert(schema data, CP cp) {
    
    int val=hashNId(cp.Course);
    
    if (*(data.CPTab+val)) {
        //if they match
        
        CP *temporal = *(data.CPTab+val);
        *(data.CPTab+val) = CPcreate(cp.Course, cp.PreReq);
        (*(data.CPTab+val))->next = temporal;
        
    } else {
        //if there is an empty slot
        *(data.CPTab+val) = CPcreate(cp.Course, cp.PreReq);
    }
}


void CRInsert(schema data, CR cr) {
    
    int val=hashNId(cr.Course);
    
    if (*(data.CRTab+val)) {
        //if they match
        
        CR *temporal = *(data.CRTab+val);
        *(data.CRTab+val) = CRcreate(cr.Course, cr.Room);
        (*(data.CRTab+val))->next = temporal;
        
    } else {
        //if there is an empty slot
        *(data.CRTab+val) = CRcreate(cr.Course, cr.Room);
    }
}



//For deletes

void delete(schema data, char ***value, char *relation) {
        
    if (strcmp("SNAP", relation) == 0) {
        SNAPDelete(data, value);
        
    } else if (strcmp("CDH", relation) == 0) {
        CDHDelete(data, value);
        
    } else if (strcmp("CSG", relation) == 0) {
        CSGDelete(data, value);
        
    } else if (strcmp("CP", relation) == 0) {
        CPDelete(data, value);
        
    } else if (strcmp("CR", relation) == 0) {
        CRDelete(data, value);
        
    } else {
        printf("Relation Not Identified: %s\n", relation);
        
    }
}

void SNAPDelete(schema data, char ***value) {
    
    if (strcmp("*", *(*(value+1))) != 0) {
        //If there is an Student ID
        int val = hashNId(**(value+1));
        
        if (*(data.SNAPTab+val)) {
            //if there is a match
            SNAP *thisval = *(data.SNAPTab+val);
            SNAP *prev = *(data.SNAPTab+val);
            
            while(thisval) {
                if (SNAPcomp(*thisval, value) == 0) {
                    //if they are equal
                    
                    SNAP *deleted = thisval;
                    
                    
                    if (prev == *(data.SNAPTab+val)) {
                        *(data.SNAPTab+val) = thisval->next;
                        
                    } else {
                        prev->next = thisval->next;
                        
                    }
                    
                    
                    
                    thisval = thisval ->next;
                    
                    free(deleted ->Name);
                    free(deleted ->Address);
                    // No phone due to the fact that itis int
                    free(deleted);
                    
                } else {
                    
                    if (thisval != *(data.SNAPTab+val)) {
                       prev = prev ->next;
                    }
                    
                    thisval = thisval ->next;
                }
            }
        }
        
    } else {
        //if there is no student id
        
        
        for (int i = 0; i < 1009; i++) {
            
            SNAP *thisval = *(data.SNAPTab+i);
            SNAP *prev = *(data.SNAPTab+i);
            
            
            //check each bucket
            while(thisval) {
                
                if (SNAPcomp(*thisval, value) == 0) {
                    //if they are equal
                    
                    SNAP *deleted = thisval;
                    
                    
                    if (prev == *(data.SNAPTab+i)) {
                        *(data.SNAPTab+i) = thisval ->next;
                        
                    } else {
                        prev->next = thisval ->next;
                        
                    }
                    
                    
                    thisval = thisval->next;
                    
                    free(deleted ->Name);
                    free(deleted ->Address);
                    // No phoen due to the fact that it is an int
                    free(deleted);
                    
                } else {
                    
                    if (thisval != *(data.SNAPTab+i)) {
                        prev = prev ->next;
                    }
                    
                    thisval = thisval ->next;
                }
            }
        }
    }
}




void CSGDelete(schema data, char ***value) {
    
    if (strcmp("*", *(*(value+1))) != 0) {
        // If there is a Student id
        int val = hashId(atoi(**(value+1)));
        
        if (*(data.CSGTab+val)) {
            
            CSG *prev = *(data.CSGTab+val);
            CSG *thisval = *(data.CSGTab+val);
            
            
            while(thisval) {
                
                if (CSGcomp(*thisval, value) == 0) {
                    //if they are equal
                    
                    CSG *deleted = thisval;
                    
                    
                    if (prev == *(data.CSGTab+val)) {
                        *(data.CSGTab+val) = thisval ->next;
                        
                    } else {
                        prev->next = thisval ->next;
                        
                    }
                    
                    
                    
                    thisval = thisval ->next;
                    free(deleted ->Course);
                    free(deleted -> Grade);
                    free(deleted);
                    
                } else {
                    if (thisval != *(data.CSGTab+val)) {
                        prev = prev ->next;
                    }
                    
                    thisval = thisval ->next;
                }
            }
        }
    } else {
        //if there is no student Id
        
        for (int i = 0; i < 1009; i++) {
            
            CSG *thisval = *(data.CSGTab+i);
            CSG *prev = *(data.CSGTab+i);
            
            // check each bucket
            while(thisval) {
                
            
                if (CSGcomp(*thisval, value) == 0) {
                    //If they are equal
                    
                    
                    CSG *deleted = thisval;
                    
                    if (prev == *(data.CSGTab+i)) {
                        *(data.CSGTab+i) = thisval->next;
                        
                    } else {
                        prev->next = thisval->next;
                        
                    }
                    
                    thisval = thisval->next;
                    free(deleted->Course);
                    free(deleted->Grade);
                    free(deleted);
                    
                } else {
                    
                    if (thisval != *(data.CSGTab+i)) {
                        prev = prev->next;
                    }
                    
                    thisval = thisval->next;
                }
            }
        }
    }
}

void CDHDelete(schema data, char ***value) {
    
    
    if (strcmp("*", *(*(value+0))) != 0) {
        //if there is an Student Id
        int val = hashNId(**(value+0));
        
        if (*(data.CDHTab+val)) {
            //if ther eis a match
            
            CDH *thisval = *(data.CDHTab+val);
            CDH *prev = *(data.CDHTab+val);
            
            
            while(thisval) {
                
                
                if (CDHcomp(*thisval, value) == 0) {
                    //if they are equal
                    
                    CDH *deleted = thisval;
                    
                    
                    
                    if (prev == *(data.CDHTab+val)) {
                        *(data.CDHTab+val) = thisval ->next;
                        
                    } else {
                        prev->next = thisval ->next;
                        
                    }
                    
                    
                    thisval = thisval ->next;
                    free(deleted ->Course);
                    free(deleted ->Day);
                    free(deleted ->Hour);
                    free(deleted);
                    
                } else {
                    
                    if (thisval != *(data.CDHTab+val)) {
                        prev = prev ->next;
                    }
                    
                    thisval = thisval ->next;
                }
            }
        }
    } else {
        //if there is no Student id
        
        for (int i = 0; i < 1009; i++) {
            
            CDH *thisval = *(data.CDHTab+i);
            CDH *prev = *(data.CDHTab+i);
            
            
            //check each bucket
            while(thisval) {
                
                if (CDHcomp(*thisval, value) == 0) {
                    //if they are equal
                    
                    CDH *deleted = thisval;
                    
                    
                    if (prev == *(data.CDHTab+i)) {
                        *(data.CDHTab+i) = thisval ->next;
                        
                    } else {
                        
                        prev->next = thisval ->next;
                    }
                    
                    
                    thisval = thisval ->next;
                    free(deleted ->Course);
                    free(deleted ->Day);
                    free(deleted ->Hour);
                    free(deleted);
                    
                } else {
                    
                    if (thisval != *(data.CDHTab+i)) {
                        prev = prev ->next;
                    }
                    
                    thisval = thisval ->next;
                }
            }
        }
    }
}


void CPDelete(schema data, char ***value) {
    
    if (strcmp("*", *(*(value+0))) != 0) {
        //if there is an Student ID
        int val = hashNId(**(value+0));
        
        
        if (*(data.CPTab+val)) {
            //if there is a match
            
            CP *thisval = *(data.CPTab+val);
            CP *prev = *(data.CPTab+val);
            
            
            while(thisval) {
                
                if (CPcomp(*thisval, value) == 0) {
                    // if they are equal
                    
                    CP *deleted = thisval;
                    
                    
                    if (prev == *(data.CPTab+val)) {
                        *(data.CPTab+val) = thisval ->next;
                        
                    } else {
                        
                        prev->next = thisval ->next;
                    }
                    
                    thisval = thisval ->next;
                    free(deleted ->Course);
                    free(deleted ->PreReq);
                    free(deleted);
                    
                } else {
                    
                    if (thisval != *(data.CPTab+val)) {
                        prev = prev->next;
                    }
                    
                    thisval = thisval->next;
                }
            }
        }
    } else {
        //IF there is no student id
        
        for (int i = 0; i < 1009; i++) {
            
            CP *thisval = *(data.CPTab+i);
            CP *prev = *(data.CPTab+i);
            
            
            //check each bucket
            while(thisval) {
                
                
                if (CPcomp(*thisval, value) == 0) {
                    //if they are equal
                    
                    CP *deleted = thisval;
                    
                    
                    if (prev == *(data.CPTab+i)) {
                        *(data.CPTab+i) = thisval ->next;
                        
                    } else {
                        
                        prev->next = thisval ->next;
                    }
                    
                    thisval = thisval ->next;
                    free(deleted ->Course);
                    free(deleted ->PreReq);
                    free(deleted);
                    
                } else {
                    
                    if (thisval != *(data.CPTab+i)) {
                        prev = prev ->next;
                    }
                    
                    thisval = thisval ->next;
                }
            }
        }
    }
}


void CRDelete(schema data, char ***value) {
    
    
    if (strcmp("*", *(*(value+0))) != 0) {
        //If there is a Student Id
        
        int val = hashNId(**(value+0));
        
        
        if (*(data.CRTab+val)) {
            //if there is a match
            
            CR *thisval = *(data.CRTab+val);
            CR *prev = *(data.CRTab+val);
            
        
            
            while(thisval) {
                
                if (CRcomp(*thisval, value) == 0) {
                    //if they are equal
                    
                    CR *deleted = thisval;
                    
                    
                    if (prev == *(data.CRTab+val)) {
                        *(data.CRTab+val) = thisval ->next;
                        
                    } else {
                        prev->next = thisval ->next;
                        
                    }
                    
                    thisval = thisval ->next;
                    free(deleted ->Course);
                    free(deleted ->Room);
                    free(deleted);
                    
                } else {
                    
                    if (thisval != *(data.CRTab+val)) {
                        prev = prev->next;
                        
                    }
                    
                    thisval = thisval->next;
                }
            }
        }
        
    } else {
        //if there is no Student Id
        
        for (int i = 0; i < 1009; i++) {
            
            CR *thisval = *(data.CRTab+i);
            CR *prev = *(data.CRTab+i);
            
            while(thisval) {
                
                if (CRcomp(*thisval, value) == 0) {
                    //if they are equal
                    
                    CR *deleted = thisval;
                    
                    
                    if (prev == *(data.CRTab+i)) {
                        *(data.CRTab+i) = thisval ->next;
                        
                    } else {
                        prev->next = thisval ->next;
                        
                    }
                    
                    thisval = thisval ->next;
                    free(deleted ->Course);
                    free(deleted ->Room);
                    free(deleted);
                    
                } else {
                    
                    if (thisval != *(data.CRTab+i)) {
                        prev = prev->next;
                        
                    }
                    
                    thisval = thisval->next;
                }
            }
        }
    }
}


char ***create(char *att1, char *att2, char *att3, char *att4) { // For each attribute
    
    
    // So first we obtain the information within each attribute
    char ***value = malloc(sizeof(char **)*4);
    *(value+0) = malloc(sizeof(char *));
    *(value+1) = malloc(sizeof(char *));
    *(value+2) = malloc(sizeof(char *));
    *(value+3) = malloc(sizeof(char *));
    
    // then we obtain each single character within each single part of the attributes
    **(value+0) = malloc(sizeof(char)*100);
    **(value+1) = malloc(sizeof(char)*100);
    **(value+2) = malloc(sizeof(char)*100);
    **(value+3) = malloc(sizeof(char)*100);
    
    // then we copy the whole string
    strncpy(**(value+0), att1, 100);
    strncpy(**(value+1), att2, 100);
    strncpy(**(value+2), att3, 100);
    strncpy(**(value+3), att4, 100);
    

    
    return value;
}


// THE THREE OPERATIONS Union, Intersect,  Difference
void intersect(schema, schema, char *);
void sunion(schema, schema, char *); // Union already existant // s for schema
void difference(schema, schema, char *);



void intersect(schema data1, schema data2, char *relation) {
    
    
    if (strcmp("CSG", relation) == 0) {
        
        for (int i = 0; i < 1009; i++) {
            
            CSG *thisval1 = *(data1.CSGTab+i);
            
            
            //check each bucket
            while(thisval1) {
                
                char buf[6];
                
                sprintf(buf,"%d", thisval1 ->StudId);
                CSG *lookup = CSGLookup(data2, create(thisval1->Course, buf, thisval1->Grade, "*"));
                
                if (!lookup) {
                    
                    CSGDelete(data1, create(thisval1->Course, buf, thisval1->Grade, "*"));
                }
                
                thisval1 = thisval1 ->next;
            }
        }
        
    } else if (strcmp("SNAP", relation) == 0) {
        
        for (int i = 0; i < 1009; i++) {
            
            SNAP *thisval1 = *(data1.SNAPTab+i);
            
            // check each bucket
            while(thisval1) {
                
                char buf1[6];
                sprintf(buf1,"%d", thisval1->StudId);
                
                char buf2[8];
                sprintf(buf2,"%d", thisval1->Phone);
                
                SNAP *lookup = SNAPLookup(data2, create(buf1, thisval1->Name, thisval1->Address, buf2));
                
                if (!lookup) {
                    SNAPDelete(data1, create(buf1, thisval1->Name, thisval1->Address, buf2));
                }
                
                thisval1 = thisval1 ->next;
            }
        }
        
    } else if (strcmp("CP", relation) == 0) {
        
        for (int i = 0; i < 1009; i++) {
            
            CP *thisval1 = *(data1.CPTab+i);
            
            //check each bucket
            while(thisval1) {
                
                CP *lookup = CPLookup(data2, create(thisval1->Course, thisval1->PreReq, "*", "*"));
                
                if (!lookup) {
                    CPDelete(data1, create(thisval1->Course, thisval1->PreReq, "*", "*"));
                }
                
                thisval1 = thisval1 ->next;
            }
        }
        
    } else if (strcmp("CDH", relation) == 0) {
        
        for (int i = 0; i < 1009; i++) {
            
            CDH *thisval1 = *(data1.CDHTab+i);
            
            //check each bucket
            while(thisval1) {
                
                CDH *lookup = CDHLookup(data2, create(thisval1->Course, thisval1->Day, thisval1->Hour, "*"));
                
                if (!lookup) {
                    CDHDelete(data1, create(thisval1->Course, thisval1->Day, thisval1->Hour, "*"));
                    
                }
                
                thisval1 = thisval1 ->next;
                
            }
        }
        
    } else if (strcmp("CR", relation) == 0) {
        
        for (int i = 0; i < 1009; i++) {
            
            CR *thisval1 = *(data1.CRTab+i);
            
            //check each bucket
            while(thisval1) {
                
                CR *lookup = CRLookup(data2, create(thisval1->Course, thisval1->Room, "*", "*"));
                
                if (!lookup) {
                    CRDelete(data1, create(thisval1->Course, thisval1->Room, "*", "*"));
                    
                }
            
                thisval1 = thisval1 ->next;
                
            }
        }
        
    } else {
        
        printf("Relation Not Identified: %s\n", relation);
    }
}



void sunion(schema data1, schema data2, char *relation) {
    
    if (strcmp("CSG", relation) == 0) {
        
        
        for (int i = 0; i < 1009; i++) {
            
            CSG *thisval2 = *(data2.CSGTab+i);
            
            
            //check each bucket
            while(thisval2) {
                
                CSG *thisval1 = *(data1.CSGTab+i);
                
                if (thisval1) {
                    //if there is a match
                    
                    int flag = 1; // -
                    
                    while (thisval1) {
                        
                        char buf[6];
                        sprintf(buf,"%d",thisval2->StudId);
                        
                        if (CSGcomp((*thisval1), create(thisval2->Course, buf, thisval2->Grade, "*")) == 0) {
                            
                            flag = 0; //
                        }
                        
                        thisval1 = thisval1 ->next;
                    }
                    if (flag == 1) {
                        CSG *temporal = *(data1.CSGTab+i);
                        
                        *(data1.CSGTab+i) = CSGcreate(thisval2->Course, thisval2->StudId, thisval2->Grade);
                        
                        (*(data1.CSGTab+i)) ->next = temporal;
                    }
                    
                } else {
                    
                    *(data1.CSGTab+i) = CSGcreate(thisval2->Course, thisval2->StudId, thisval2->Grade);
                    
                }
                
                thisval2 = thisval2 ->next;
            }
        }
        
    } else if (strcmp("SNAP", relation) == 0) {
        
        
        for (int i = 0; i < 1009; i++) {
            
            SNAP *thisval2 = *(data2.SNAPTab+i);
            
            // check each bucket
            while(thisval2) {
                
                SNAP *thisval1 = *(data1.SNAPTab+i);
                
                if (thisval1) {
                    
                    int flag = 1; ///
                    
                    while (thisval1) {
                        
                        char buf1[6];
                        sprintf(buf1,"%d", thisval2 ->StudId);
                        
                        char buf2[8];
                        sprintf(buf2,"%d",thisval2 ->Phone);
                        
                        if (SNAPcomp((*thisval1), create(buf1, thisval2->Name, thisval2->Address, buf2)) == 0) {
                            
                            flag = 0; //
                        }
                        
                        thisval1 = thisval1 ->next;
                    }
                    if (flag == 1) {
                        
                        SNAP *temporal = *(data1.SNAPTab+i);
                        
                        *(data1.SNAPTab+i) = SNAPcreate(thisval2->StudId, thisval2->Name, thisval2->Address, thisval2->Phone);
                        
                        (*(data1.SNAPTab+i))->next = temporal;
                        
                    }
                    
                } else {
                    
                    *(data1.SNAPTab+i) = SNAPcreate(thisval2->StudId, thisval2->Name, thisval2->Address, thisval2->Phone);
                    
                }
                
                thisval2 = thisval2 ->next;
                
            }
        }
        
    } else if (strcmp("CP", relation) == 0) {
        
        
        for (int i = 0; i < 1009; i++) {
            
            CP *thisval2 = *(data2.CPTab+i);
            
            // check each bucket
            while(thisval2) {
                
                CP *thisval1 = *(data1.CPTab+i);
                
                if (thisval1) {
                
                    int flag = 1; //
                    
                    while (thisval1) {
                        
                        if (CPcomp((*thisval1), create(thisval2->Course, thisval2->PreReq, "*", "*")) == 0) {
                            
                            flag = 0;
                        }
                        
                        thisval1 = thisval1 ->next;
                    }
                    
                    if (flag == 1) {
                        
                        CP *temporal = *(data1.CPTab+i);
                        
                        *(data1.CPTab+i) = CPcreate(thisval2->Course, thisval2->PreReq);
                        
                        (*(data1.CPTab+i)) ->next = temporal;
                    }
                    
                } else {
                    
                    
                    *(data1.CPTab+i) = CPcreate(thisval2->Course, thisval2->PreReq);
                    
                }
                
                thisval2 = thisval2 ->next;
                
            }
        }
        
    } else if (strcmp("CDH", relation) == 0) {
        
        
        for (int i = 0; i < 1009; i++) {
            
            CDH *thisval2 = *(data2.CDHTab+i);
            
            // check each bucket
            while(thisval2) {
                
                CDH *thisval1 = *(data1.CDHTab+i);
                
                if (thisval1) {
                
                    int flag = 1; //
                    
                    while (thisval1) {
                        
                        if (CDHcomp((*thisval1), create(thisval2->Course, thisval2->Day, thisval2->Hour, "*")) == 0) {
                            
                            flag = 0; //
                            
                        }
                        
                        thisval1 = thisval1 ->next;
                        
                    }
                    if (flag == 1) {
                        
                        CDH *temporal = *(data1.CDHTab+i);
                        
                        *(data1.CDHTab+i) = CDHcreate(thisval2->Course, thisval2->Day, thisval2->Hour);
                        
                        (*(data1.CDHTab+i))->next = temporal;
                        
                    }
                    
                } else {
                    
                    *(data1.CDHTab+i) = CDHcreate(thisval2->Course, thisval2->Day, thisval2->Hour);
                    
                }
                
                thisval2 = thisval2 ->next;
                
            }
            
        }
        
    } else if (strcmp("CR", relation) == 0) {
        
        
        for (int i = 0; i < 1009; i++) {
            
            CR *thisval2 = *(data2.CRTab+i);
            
            // check each bucket
            while(thisval2) {
                
                CR *thisval1 = *(data1.CRTab+i);
                
                if (thisval1) {
                    
                    int flag = 1; //
                    while (thisval1) {
                        
                        if (CRcomp((*thisval1), create(thisval2->Course, thisval2->Room, "*", "*")) == 0) {
                            
                            flag = 0; //
                        }
                        
                        thisval1 = thisval1 ->next;
                        
                    }
                    if (flag == 1) {
                        
                        CR *temporal = *(data1.CRTab+i);
                        
                        *(data1.CRTab+i) = CRcreate(thisval2->Course, thisval2->Room);
                        
                        (*(data1.CRTab+i))->next = temporal;
                        
                    }
                    
                } else {
                    
                    *(data1.CRTab+i) = CRcreate(thisval2->Course, thisval2->Room);
                    
                }
                
                thisval2 = thisval2 ->next;
                
            }
        }
        
    } else {
        
        printf("Relation Not Identified: %s\n", relation);
        
    }
}





void difference(schema data1, schema data2, char *relation) {
    
    if (strcmp("CSG", relation) == 0) {
        
        for (int i = 0; i < 1009; i++) {
            
            CSG *thisval2 = *(data2.CSGTab+i);
            
            // check each bucket
            while(thisval2) {
                
                char buf[6];
                sprintf(buf,"%d",thisval2 ->StudId);
                
                CSGDelete(data1, create(thisval2->Course, buf, thisval2->Grade, "*"));
                
                thisval2 = thisval2 ->next;
                
            }
        }
        
    } else if (strcmp("SNAP", relation) == 0) {
        
        for (int i = 0; i < 1009; i++) {
            
            SNAP *thisval2 = *(data2.SNAPTab+i);
            
            // check each bucket
            while(thisval2) {
                
                char buf1[6];
                sprintf(buf1,"%d", thisval2 ->StudId);
                
                char buf2[8];
                sprintf(buf2,"%d", thisval2 ->Phone);
                
                SNAPDelete(data1, create(buf1, thisval2->Name, thisval2->Address, buf2));
                
                thisval2 = thisval2 ->next;
                
            }
        }
        
    } else if (strcmp("CP", relation) == 0) {
        
        for (int i = 0; i < 1009; i++) {
            
            CP *thisval2 = *(data2.CPTab+i);
            
            //check each bucket
            while(thisval2) {
                
                CPDelete(data1, create(thisval2->Course, thisval2->PreReq, "*", "*"));
                
                thisval2 = thisval2 ->next;
                
            }
        }
        
    } else if (strcmp("CDH", relation) == 0) {
    
        for (int i = 0; i < 1009; i++) {
            
            CDH *thisval2 = *(data2.CDHTab+i);
            
            //check each bucket
            while(thisval2) {
                
                CDHDelete(data1, create(thisval2->Course, thisval2->Day, thisval2->Hour, "*"));
                
                thisval2 = thisval2 ->next;
            }
        }
        
    } else if (strcmp("CR", relation) == 0) {
        
        for (int i = 0; i < 1009; i++) {
            
            CR *thisval2 = *(data2.CRTab+i);
            
            //check each bucket
            while(thisval2) {
                
                CRDelete(data1, create(thisval2->Course, thisval2->Room, "*", "*"));
                
                thisval2 = thisval2 ->next;
            }
        }
    
    } else {
        
        printf("Relation Not Identified: %s\n", relation);
        
    }

}



//For PART 2
char *whatGrade(schema, char *, char *); // This is specifically for “What grade did StudentName get in Course- Name?” in part 2

char *whatGrade(schema data, char *studentName, char *courseName) {
    
    SNAP *student = SNAPLookup(data, create("*", studentName, "*", "*"));
    
    
    //I am assuming that no student has the same name // Couldn't find other way to do it
    if (student) {
        
        char buffer[6];
        sprintf(buffer,"%d",student -> StudId);
        
        CSG *Grade = CSGLookup(data, create(courseName, buffer, "*", "*"));
        
        if (Grade) {
            return Grade->Grade;
            
        } else {
            printf("%s is not in %s.\n", studentName, courseName);
            return NULL;
            
        }
        
    } else {
        
        printf("Student: %s is not on the table.\n", studentName);
        return NULL;
    }
}

char *whatRoom(schema data, char *studentName, char *Hour, char *Day) {
    
    SNAP *student = SNAPLookup(data, create("*", studentName, "*", "*"));
    
    
    if (student) {
        
        CDH *Courses = CDHLookup(data, create("*", Day, Hour, "*"));
        
        if (Courses) {
            
            char buf[6]; //
            sprintf(buf,"%d",student->StudId);
            
            CSG *studentCourses = CSGLookup(data, create("*", buf, "*", "*"));
            
            CDH *DayHourCourses = Courses;
            
            while (studentCourses) {
                
                while (DayHourCourses) {
                    
                    if (strcmp(studentCourses->Course, DayHourCourses->Course) == 0) {
                        
                        CR *Room = CRLookup(data, create(studentCourses->Course, "*", "*", "*"));
                        return Room->Room;
                        
                    }
                    
                    DayHourCourses = DayHourCourses ->next;
                }
                
                studentCourses = studentCourses ->next;
                DayHourCourses = Courses;
            }
            
            //when there is no matches
            printf("%s is not in any class at %s on %s\n", studentName, Hour, Day);
            return NULL;
            
        } else {
            
            printf("There are no courses at %s on %s.\n", Hour, Day);
            return NULL;
            
        }
        
    } else {
        
        printf("Student: %s is not in the table.\n", studentName);
        return NULL;
        
    }
}


// Relational Algebra
void SNAPProject(SNAP *, char *);
void CSGProject(CSG *, char *);
void CDHProject(CDH *, char *);
void CPProject(CP *, char *);
void CRProject(CR *, char *);
void join(schema);

void SNAPProject(SNAP *snap, char *attribute) {
    
    printf("%s:\n", attribute);
    
    if (strcmp("StudId", attribute) == 0) {
        while(snap) {
            printf("%d\n", snap ->StudId);
            snap = snap ->next;
            
        }
        
    } else if (strcmp("Name", attribute) == 0) {
        while(snap) {
            printf("%s\n", snap ->Name);
            snap = snap ->next;
            
        }
        
    } else if (strcmp("Address", attribute) == 0) {
        while(snap) {
            printf("%s\n", snap ->Address);
            snap = snap ->next;
            
        }
        
    } else if (strcmp("Phone", attribute) == 0) {
        while(snap) {
            printf("%d\n", snap ->Phone);
            snap = snap ->next;
            
        }
        
    } else {
        printf("Attribute Not Identified: %s\n", attribute);
       
        
    }
}


void CSGProject(CSG *csg, char *attribute) {

    printf("%s:\n", attribute);
    
    if (strcmp("Course", attribute) == 0) {
        while(csg) {
            printf("%s\n", csg ->Course);
            csg = csg ->next;
            
        }
        
    } else if (strcmp("StudId", attribute) == 0) {
        while(csg) {
            printf("%d\n", csg ->StudId);
            csg = csg ->next;
            
        }
        
    } else if (strcmp("Grade", attribute) == 0) {
        while(csg) {
            printf("%s\n", csg ->Grade);
            csg = csg ->next;
            
        }
        
    } else {
        printf("Attribute Not Identified: %s\n", attribute);
        
    }
    
}


void CDHProject(CDH *cdh, char *attribute) {
    
    printf("%s:\n", attribute);
    if (strcmp("Course", attribute) == 0) {
        while(cdh) {
            printf("%s\n", cdh ->Course);
            cdh = cdh ->next;
            
        }
        
    } else if (strcmp("Day", attribute) == 0) {
        while(cdh) {
            printf("%s\n", cdh ->Day);
            cdh = cdh ->next;
            
        }
        
    } else if (strcmp("Hour", attribute) == 0) {
        while(cdh) {
            printf("%s\n", cdh ->Hour);
            cdh = cdh ->next;
            
        }
        
    } else {
        printf("Attribute Not Identified: %s\n", attribute);
        
    }
}

void CPProject(CP *cp, char *attribute) {
    
    printf("%s:\n", attribute);
    
    if (strcmp("Course", attribute) == 0) {
        while(cp) {
            printf("%s\n", cp ->Course);
            cp = cp ->next;
            
        }
        
    } else if (strcmp("PreReq", attribute) == 0) {
        while(cp) {
            printf("%s\n", cp ->PreReq);
            cp = cp ->next;
            
        }
        
    } else {
        
        printf("Attribute Not Identified: %s\n", attribute);
        
    }
}

void CRProject(CR *cr, char *attribute) {
    
    printf("%s:\n", attribute);
    
    if (strcmp("Course", attribute) == 0) {
        while(cr) {
            printf("%s\n", cr ->Course);
            cr = cr ->next;
            
        }
        
    } else if (strcmp("Room", attribute) == 0) {
        while(cr) {
            printf("%s\n", cr->Room);
            cr = cr->next;
            
        }
    } else {
        
        printf("Attribute Not Identified: %s\n", attribute);
        
    }
}

// DONE DONE!!!
