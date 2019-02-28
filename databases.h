// Andres Ollarvez
// CSC 173
//  Copyright © 2017 Andres Ollarvez. All rights reserved.
//

#ifndef databases_h
#define databases_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

typedef struct {
    SNAP **SNAPTab;
    CSG **CSGTab;
    CDH **CDHTab;
    CP **CPTab;
    CR **CRTab;
} schema;



//Prototypes to create the Functions
schema *createDB();

//
int hashId(int);
int hashNId(char *);
void saveDB(schema, char *);
//

//For lookups
void lookup(schema, char ***, char *);
SNAP *SNAPLookup(schema, char ***);
CSG *CSGLookup(schema, char ***);
CDH *CDHLookup(schema, char ***);
CP *CPLookup(schema, char ***);
CR *CRLookup(schema, char ***);


//For inserts
void SNAPInsert(schema, SNAP);
void CSGInsert(schema, CSG);
void CDHInsert(schema, CDH);
void CPInsert(schema, CP);
void CRInsert(schema, CR);
void DBFInsert(schema, char *);

//For deletes
void delete(schema, char ***, char *);
void SNAPDelete(schema, char ***);
void CSGDelete(schema, char ***);
void CDHDelete(schema, char ***);
void CPDelete(schema, char ***);
void CRDelete(schema, char ***);

char ***create(char *, char *, char *, char *);
// I was not sure about this one, but this creates a relation based on given info


// THE THREE OPERATIONS Union, Intersect,  Difference
void intersect(schema, schema, char *);
void sunion(schema, schema, char *); // union is already defined // s for schema
void difference(schema, schema, char *);


//For PART 2
char *whatGrade(schema, char *, char *); // This is specifically for “What grade did StudentName get in Course- Name?” in part 2
char *whatRoom(schema, char *, char *, char *);
// This is specifically for “Where is StudentName at Time on Day?” in part 2?"


// Relational Algebra
void SNAPProject(SNAP *, char *);
void CSGProject(CSG *, char *);
void CDHProject(CDH *, char *);
void CPProject(CP *, char *);
void CRProject(CR *, char *);
void join(schema);




#endif /* databases_h */
