/*++

Copyright (c) 1990-2003  Microsoft Corporation
All rights reserved


Abstract:

    Routines to facilitate printing of EMF jobs.

--*/

#include "local.h"
#include "stddef.h"
#include <windef.h>
#include "emf.h"


#include <winppi.h>

#define EMF_DUP_NONE 0
#define EMF_DUP_VERT 1
#define EMF_DUP_HORZ 2

#define EMF_DEGREE_90   0x0001
#define EMF_DEGREE_270  0x0002
#define EMF_DEGREE_SWAP 0x8000

//
// IS_DMSIZE_VALID returns TRUE if the size of the devmode is atleast as much as to 
// be able to access field x in it without AV. It is assumed that the devmode is 
// atleast the size pdm->dmSize 
//
#define IS_DMSIZE_VALID(pdm,x)  ( ( (pdm)->dmSize >= (FIELD_OFFSET(DEVMODEW, x ) + sizeof((pdm)->x )))? TRUE:FALSE)


//
// function pointer to PrintOneSideReverseEMF. Used for booklet, reverse printing 
//
typedef BOOL (*PFPRINTONESIDEREVERSEEMF)(HANDLE, \
                                         HDC,    \
                                         PEMF_ATTRIBUTE_INFO, \
                                         PPAGE_NUMBER, \
                                         BOOL, \
                                         DWORD, \
                                         LPDEVMODE);


#define MAX_NUP         16 //Max is 16-up
#define MAX_NUP_OPTIONS 8  //4 options for page arrangements * 2 (for Portrait, Landscape).
                           //the portrait and landscape used only for 2-up and 6-up.

DWORD      dwIndexIntoUpdateRect[MAX_NUP] = {           //npps=Number of Pages Per Side
                                            0xFFFFFFFF, //npps=1  //Nothing to do.
                                            0,          //npps=2
                                            0xFFFFFFFF, //npps=3  //Invalid Option
                                            1,          //npps=4
                                            0xFFFFFFFF, //npps=5  //Invalid Option
                                            2,          //npps=6
                                            0xFFFFFFFF, //npps=7  //Invalid Option
                                            0xFFFFFFFF, //npps=8  //Invalid Option
                                            3,          //npps=9
                                            0xFFFFFFFF, //npps=10  //Invalid Option
                                            0xFFFFFFFF, //npps=11  //Invalid Option
                                            0xFFFFFFFF, //npps=12  //Invalid Option
                                            0xFFFFFFFF, //npps=13  //Invalid Option
                                            0xFFFFFFFF, //npps=14  //Invalid Option
                                            0xFFFFFFFF, //npps=15  //Invalid Option
                                            4           //npps=16
                                        };

//
// The update factors for the different nup options. These factors when multiplied
// with the horizontal and vertical resolutions give the coordinates for the rectangle
// where the EMF page is to be played.
//
// Note: You see two sets of matrices here. One form part of the 
// gUpdateRect[][MAX_NUP_OPTIONS][MAX_NUP] array, other are named like URect21, URect21R etc.
// The reason we have both of them is as follows. The gUpdateRect have been added after
// Windows Server 2003 and it incorproates the URect21, URect21R and also allows for
// various n-up options. But I am afraid to remove URect21, URect21R etc because it
// might cause regression. So for simple n-up, i.e. right then down, I am using the old
// method, while for the newer n-ups, I'll use the gUpdateRect 3D array.
//
UpdateRect gUpdateRect[][MAX_NUP_OPTIONS][MAX_NUP] =  
            {
                {
                    { //2-up, right then down.  gUpdateRect[0][0]
                        {0.5, 1, 0, 1}, 
                        {0, 0.5, 0, 1}
                    },
                    { //2-up, down then right. Same as right then down. gUpdateRect[0][1]
                        {0.5, 1, 0, 1}, 
                        {0, 0.5, 0, 1}
                    },
                    { //2-up, left then down. gUpdateRect[0][2]
                        { 0, 0.5, 0, 1},
                        {0.5, 1,  0, 1}
                    },
                    { //2-up, down then left. Same as left then down. gUpdateRect[0][3]
                        { 0, 0.5, 0, 1},
                        {0.5, 1,  0, 1}
                    },

                    { //Landscape. 2-up, right then down.  gUpdateRect[0][4]
                        {0, 1, 0, 0.5},
                        {0, 1, 0.5, 1}
                    },
                    { //Landscape. 2-up, down then right. Same as right then down. gUpdateRect[0][5]
                        {0, 1, 0, 0.5},
                        {0, 1, 0.5, 1}
                    },
                    { //Landscape. 2-up, left then down. gUpdateRect[0][6]
                        {0, 1, 0.5,   1},
                        {0, 1,   0, 0.5}
                    },
                    { //Landscape. 2-up, down then left. Same as left then down. gUpdateRect[0][7]
                        {0, 1, 0.5, 1},
                        {0, 1, 0, 0.5}
                    }
                },
                {
                    { //4-up, right then down = gUpdateRect[1][0] 
                        {   0, 0.5,   0, 0.5 },    //1
                        {   0, 0.5, 0.5,   1 },    //2
                        { 0.5,   1,   0, 0.5 },    //3
                        { 0.5,   1, 0.5,   1 }     //4
                    },
                    { //4-up, down then right = gUpdateRect[1][1] 
                        {   0, 0.5,   0, 0.5 },
                        { 0.5,   1,   0, 0.5 },
                        {   0, 0.5, 0.5,   1 },
                        { 0.5,   1, 0.5,   1 }
                    },
                    { //4-up, left then down = gUpdateRect[1][2]
                        {  0, 0.5, 0.5,   1 },
                        {  0, 0.5,   0, 0.5 },
                        {0.5,   1, 0.5,   1 },
                        {0.5,   1,   0, 0.5 }
                    },
                    { //4-up, down then left  = gUpdateRect[1][3]
                        {   0, 0.5, 0.5,   1 },     //2
                        { 0.5,   1, 0.5,   1 },     //4
                        {   0, 0.5,   0, 0.5 },     //1
                        { 0.5,   1,   0, 0.5 }      //3
                    }
                },
                {
                    { //6-up. Right then down. = gUpdateRect[2][0]
                        { 2.0/3.0,       1,   0, 0.5 },     //1
                        { 1.0/3.0, 2.0/3.0,   0, 0.5 },     //2
                        {       0, 1.0/3.0,   0, 0.5 },     //3
                        { 2.0/3.0,       1, 0.5,   1 },     //4
                        { 1.0/3.0, 2.0/3.0, 0.5,   1 },     //5
                        {       0, 1.0/3.0, 0.5,   1 }      //6
                    },
                    { //6-up. Down then Right = Top To Bottom, Left To Right. = gUpdateRect[2][1]
                        { 2.0/3.0,       1,   0, 0.5 },     //1
                        {       0, 1.0/3.0,   0, 0.5 },     //3
                        { 1.0/3.0, 2.0/3.0, 0.5,   1 },     //5
                        { 1.0/3.0, 2.0/3.0,   0, 0.5 },     //2
                        { 2.0/3.0,       1, 0.5,   1 },     //4
                        {       0, 1.0/3.0, 0.5,   1 }      //6
                    },
                    { //Portrait 6-up. Left then down = Right To Left, Top To Bottom. = gUpdateRect[2][2]
                        {       0, 1.0/3.0,   0, 0.5 },     //3
                        { 1.0/3.0, 2.0/3.0,   0, 0.5 },     //2
                        { 2.0/3.0,       1,   0, 0.5 },     //1
                        {       0, 1.0/3.0, 0.5,   1 },     //6
                        { 1.0/3.0, 2.0/3.0, 0.5,   1 },     //5
                        { 2.0/3.0,       1, 0.5,   1 }      //4
                    },
                    { //Portrait 6-up Down then left = Top To Bottom, Right To Left = gUpdateRect[2][3]
                        {       0, 1.0/3.0,   0, 0.5 },     //3
                        {       0, 1.0/3.0, 0.5,   1 },     //6
                        { 1.0/3.0, 2.0/3.0,   0, 0.5 },     //2
                        { 1.0/3.0, 2.0/3.0, 0.5,   1 },     //5
                        { 2.0/3.0,       1,   0, 0.5 },     //1
                        { 2.0/3.0,       1, 0.5,   1 }      //4
                    },
                    { //Landscape 6-up. Right then down. = gUpdateRect[2][4]
                        { 0.5,   1,       0, 1.0/3.0 },     //1
                        {   0, 0.5,       0, 1.0/3.0 },     //2
                        { 0.5,   1, 1.0/3.0, 2.0/3.0 },     //3
                        {   0, 0.5, 1.0/3.0, 2.0/3.0 },     //4
                        { 0.5,   1, 2.0/3.0,       1 },     //5
                        {   0, 0.5, 2.0/3.0,       1 }      //6
                    },
                    { //Landscape 6-up. Down then Right = Top To Bottom, Left To Right. = gUpdateRect[2][5]
                        { 0.5,   1,       0, 1.0/3.0 },
                        { 0.5,   1, 1.0/3.0, 2.0/3.0 },
                        { 0.5,   1, 2.0/3.0,       1 },
                        {   0, 0.5,       0, 1.0/3.0 },
                        {   0, 0.5, 1.0/3.0, 2.0/3.0 },
                        {   0, 0.5, 2.0/3.0,       1 }
                    },
                    { //Landscape 6-up. Left then down = Right To Left, Top To Bottom. = gUpdateRect[2][6]
                        {   0, 0.5,       0, 1.0/3.0 },
                        { 0.5,   1,       0, 1.0/3.0 },
                        {   0, 0.5, 1.0/3.0, 2.0/3.0 },
                        { 0.5,   1, 1.0/3.0, 2.0/3.0 },
                        {   0, 0.5, 2.0/3.0,       1 },
                        { 0.5,   1, 2.0/3.0,       1 }
                    } ,
                    { //Landscape 6-up Down then left = Top To Bottom, Right To Left = gUpdateRect[2][7]
                        {   0, 0.5,       0, 1.0/3.0 },     //2
                        {   0, 0.5, 1.0/3.0, 2.0/3.0 },     //4
                        {   0, 0.5, 2.0/3.0,       1 },     //6
                        { 0.5,   1,       0, 1.0/3.0 },     //1
                        { 0.5,   1, 1.0/3.0, 2.0/3.0 },     //3
                        { 0.5,   1, 2.0/3.0,       1 }      //5
                    }
                },
                {
                    { //9-up. Right then down = Left to Right. Top To Bottom = gUpdateRect[3][0]
                        {       0, 1.0/3.0,       0, 1.0/3.0 },
                        {       0, 1.0/3.0, 1.0/3.0, 2.0/3.0 },
                        {       0, 1.0/3.0, 2.0/3.0,       1 },
                        { 1.0/3.0, 2.0/3.0,       0, 1.0/3.0 },
                        { 1.0/3.0, 2.0/3.0, 1.0/3.0, 2.0/3.0 },
                        { 1.0/3.0, 2.0/3.0, 2.0/3.0,       1 },
                        { 2.0/3.0,       1,       0, 1.0/3.0 },
                        { 2.0/3.0,       1, 1.0/3.0, 2.0/3.0 },
                        { 2.0/3.0,       1, 2.0/3.0,       1 }
                    },
                    { //9-up Down then right. Top to Bottom, Left To Right = gUpdateRect[3][1]
                        {       0, 1.0/3.0,       0, 1.0/3.0 },    //1
                        { 1.0/3.0, 2.0/3.0,       0, 1.0/3.0 },    //4
                        { 2.0/3.0,       1,       0, 1.0/3.0 },    //7
                        {       0, 1.0/3.0, 1.0/3.0, 2.0/3.0 },    //2
                        { 1.0/3.0, 2.0/3.0, 1.0/3.0, 2.0/3.0 },    //5
                        { 2.0/3.0,       1, 1.0/3.0, 2.0/3.0 },    //8
                        {       0, 1.0/3.0, 2.0/3.0,       1 },    //3
                        { 1.0/3.0, 2.0/3.0, 2.0/3.0,       1 },    //6
                        { 2.0/3.0,       1, 2.0/3.0,       1 }     //9
                    },
                    { //9-up. Left then down = Right To Left, Top To Bottom = gUpdateRect[3][2]
                        {       0, 1.0/3.0, 2.0/3.0,       1 },       //3
                        {       0, 1.0/3.0, 1.0/3.0, 2.0/3.0 },       //2
                        {       0, 1.0/3.0,       0, 1.0/3.0 },       //1
                        { 1.0/3.0, 2.0/3.0, 2.0/3.0,       1 },       //6
                        { 1.0/3.0, 2.0/3.0, 1.0/3.0, 2.0/3.0 },       //5
                        { 1.0/3.0, 2.0/3.0,       0, 1.0/3.0 },       //4
                        { 2.0/3.0,       1, 2.0/3.0,       1 },       //9
                        { 2.0/3.0,       1, 1.0/3.0, 2.0/3.0 },       //8
                        { 2.0/3.0,       1,       0, 1.0/3.0 }        //7
                    },

                    { //9-up. Down then left = Top To Bottom, Right To Left = gUpdateRect[3][3]
                        {       0, 1.0/3.0, 2.0/3.0,       1 },       //3
                        { 1.0/3.0, 2.0/3.0, 2.0/3.0,       1 },       //6
                        { 2.0/3.0,       1, 2.0/3.0,       1 },       //9
                        {       0, 1.0/3.0, 1.0/3.0, 2.0/3.0 },       //2
                        { 1.0/3.0, 2.0/3.0, 1.0/3.0, 2.0/3.0 },       //5 
                        { 2.0/3.0,       1, 1.0/3.0, 2.0/3.0 },       //8
                        {       0, 1.0/3.0,       0, 1.0/3.0 },       //1
                        { 1.0/3.0, 2.0/3.0,       0, 1.0/3.0 },       //4
                        { 2.0/3.0,       1,       0, 1.0/3.0 }        //7
                    }
                },
                {
                    { //16-up. Right then down = gUpdateRect[4][0]
                        {    0, 0.25,    0, 0.25 },
                        {    0, 0.25, 0.25,  0.5 },
                        {    0, 0.25,  0.5, 0.75 },
                        {    0, 0.25, 0.75,    1 },
                        { 0.25,  0.5,    0, 0.25 },
                        { 0.25,  0.5, 0.25,  0.5 },
                        { 0.25,  0.5,  0.5, 0.75 },
                        { 0.25,  0.5, 0.75,    1 },
                        {  0.5, 0.75,    0, 0.25 },
                        {  0.5, 0.75, 0.25,  0.5 },
                        {  0.5, 0.75,  0.5, 0.75 },
                        {  0.5, 0.75, 0.75,    1 },
                        { 0.75,    1,    0, 0.25 },
                        { 0.75,    1, 0.25,  0.5 },
                        { 0.75,    1,  0.5, 0.75 },
                        { 0.75,    1, 0.75,    1 }
                    },
                    { //16-up. Down then right = Top To Bottom, Left To Right = gUpdateRect[4][1]
                        {    0, 0.25,    0, 0.25 },     //1
                        { 0.25,  0.5,    0, 0.25 },     //5
                        {  0.5, 0.75,    0, 0.25 },     //9
                        { 0.75,    1,    0, 0.25 },     //13
                        {    0, 0.25, 0.25,  0.5 },     //2
                        { 0.25,  0.5, 0.25,  0.5 },     //6
                        {  0.5, 0.75, 0.25,  0.5 },     //10
                        { 0.75,    1, 0.25,  0.5 },     //14
                        {    0, 0.25,  0.5, 0.75 },     //3
                        { 0.25,  0.5,  0.5, 0.75 },     //7
                        {  0.5, 0.75,  0.5, 0.75 },     //11
                        { 0.75,    1,  0.5, 0.75 },     //15
                        {    0, 0.25, 0.75,    1 },     //4
                        { 0.25,  0.5, 0.75,    1 },     //8
                        {  0.5, 0.75, 0.75,    1 },     //12
                        { 0.75,    1, 0.75,    1 }      //16
                    },        
                    { //16-up. Left Then down. Righ To Left. Top to Bottom = gUpdateRect[4][2]
                        {    0, 0.25, 0.75,    1 },     //4
                        {    0, 0.25,  0.5, 0.75 },     //3
                        {    0, 0.25, 0.25,  0.5 },     //2
                        {    0, 0.25,    0, 0.25 },     //1
                        { 0.25,  0.5, 0.75,    1 },     //8
                        { 0.25,  0.5,  0.5, 0.75 },     //7
                        { 0.25,  0.5, 0.25,  0.5 },     //6
                        { 0.25,  0.5,    0, 0.25 },     //5
                        {  0.5, 0.75, 0.75,    1 },     //12
                        {  0.5, 0.75,  0.5, 0.75 },     //11
                        {  0.5, 0.75, 0.25,  0.5 },     //10
                        {  0.5, 0.75,    0, 0.25 },     //9
                        { 0.75,    1, 0.75,    1 },     //16
                        { 0.75,    1,  0.5, 0.75 },     //15
                        { 0.75,    1, 0.25,  0.5 },     //14
                        { 0.75,    1,    0, 0.25 }      //13
                    },
                    { //16-up. Down then left = Top To Bottom, Right To Left = gUpdateRect[4][3]
                        {    0, 0.25, 0.75,    1 },     //4
                        { 0.25,  0.5, 0.75,    1 },     //8
                        {  0.5, 0.75, 0.75,    1 },     //12
                        { 0.75,    1, 0.75,    1 },     //16
                        {    0, 0.25,  0.5, 0.75 },     //3
                        { 0.25,  0.5,  0.5, 0.75 },     //7
                        {  0.5, 0.75,  0.5, 0.75 },     //11
                        { 0.75,    1,  0.5, 0.75 },     //15
                        {    0, 0.25, 0.25,  0.5 },     //2
                        { 0.25,  0.5, 0.25,  0.5 },     //6
                        {  0.5, 0.75, 0.25,  0.5 },     //10
                        { 0.75,    1, 0.25,  0.5 },     //14
                        {    0, 0.25,    0, 0.25 },     //1
                        { 0.25,  0.5,    0, 0.25 },     //5
                        {  0.5, 0.75,    0, 0.25 },     //9
                        { 0.75,    1,    0, 0.25 }      //13
                   }

        
                 }
            };

UpdateRect URect21[] = {{0, 0.5, 0, 1},
                        {0.5, 1, 0, 1}};

UpdateRect URect21R[] = {{0.5, 1, 0, 1},
                         {0, 0.5, 0, 1}};

UpdateRect URect21RRToL[] = {
                               { 0, 0.5, 0, 1},
                               {0.5, 1,  0, 1}
                            };

UpdateRect URect22[] = {{0, 1, 0, 0.5},
                        {0, 1, 0.5, 1}};

UpdateRect URect4[] = {{0, 0.5, 0, 0.5},
                       {0, 0.5, 0.5, 1},
                       {0.5, 1, 0, 0.5},
                       {0.5, 1, 0.5, 1}};


UpdateRect URect4TtoB[] =   {                   //Top To Bottom, Left To Right.
                            {0, 0.5, 0, 0.5},
                            {0.5, 1, 0, 0.5},
                            {0, 0.5, 0.5, 1},
                            {0.5, 1, 0.5, 1}
                        };

UpdateRect URect4RToL[] = {                     //Right To Left, Top To Bottom
                            {  0, 0.5, 0.5,   1 },
                            {  0, 0.5,   0, 0.5 },
                            {0.5,   1, 0.5,   1 },
                            {0.5,   1,   0, 0.5 }
                          };

UpdateRect URect4TToBRToL[] = {     //Top To Bottom, Right to Left.
                                {   0, 0.5, 0.5,   1 },
                                { 0.5,   1, 0.5,   1 },
                                {   0, 0.5,   0, 0.5 },
                                { 0.5,   1,   0, 0.5 }
                              };

UpdateRect URect61[] = {{0, 1.0/3.0, 0, 0.5},
                        {0, 1.0/3.0, 0.5, 1},
                        {1.0/3.0, 2.0/3.0, 0, 0.5},
                        {1.0/3.0, 2.0/3.0, 0.5, 1},
                        {2.0/3.0, 1, 0, 0.5},
                        {2.0/3.0, 1, 0.5, 1}};

UpdateRect URect61R[] = {{2.0/3.0, 1, 0, 0.5},
                         {1.0/3.0, 2.0/3.0, 0, 0.5},
                         {0, 1.0/3.0, 0, 0.5},
                         {2.0/3.0, 1, 0.5, 1},
                         {1.0/3.0, 2.0/3.0, 0.5, 1},
                         {0, 1.0/3.0, 0.5, 1}};

UpdateRect URect61RTtoB[] = {           //Top To Bottom, Left To Right.
                                { 2.0/3.0,       1,   0, 0.5 },      //1
                                {       0, 1.0/3.0,   0, 0.5 },      //3
                                { 1.0/3.0, 2.0/3.0, 0.5,   1 },      //5
                                { 1.0/3.0, 2.0/3.0,   0, 0.5 },      //2
                                { 2.0/3.0,       1, 0.5,   1 },      //4 
                                {       0, 1.0/3.0, 0.5,   1 },      //6
                            };

UpdateRect URect61RRToL[] = {   //Right To Left, Top To Bottom
                                {       0, 1.0/3.0,   0, 0.5 },     //3
                                { 1.0/3.0, 2.0/3.0,   0, 0.5 },     //2
                                { 2.0/3.0,       1,   0, 0.5 },     //1
                                {       0, 1.0/3.0, 0.5,   1 },     //6
                                { 1.0/3.0, 2.0/3.0, 0.5,   1 },     //5
                                { 2.0/3.0,       1, 0.5,   1 }      //4
                            };

UpdateRect URect61RTToBRToL[] = {       //Top To Bottom, Right To Left
                                { 1.0/3.0, 2.0/3.0, 0.5,   1 },     //5
                                {       0, 1.0/3.0,   0, 0.5 },     //3
                                { 2.0/3.0,       1,   0, 0.5 },     //1
                                {       0, 1.0/3.0, 0.5,   1 },     //6
                                { 2.0/3.0,       1, 0.5,   1 },     //4
                                { 1.0/3.0, 2.0/3.0,   0, 0.5 }      //2
                                };


UpdateRect URect62[]  = {{0, 0.5, 0, 1.0/3.0},
                         {0, 0.5, 1.0/3.0, 2.0/3.0},
                         {0, 0.5, 2.0/3.0, 1},
                         {0.5, 1, 0, 1.0/3.0},
                         {0.5, 1, 1.0/3.0, 2.0/3.0},
                         {0.5, 1, 2.0/3.0, 1}};

UpdateRect URect62R[] = {{0.5, 1, 0, 1.0/3.0},
                         {0, 0.5, 0, 1.0/3.0},
                         {0.5, 1, 1.0/3.0, 2.0/3.0},
                         {0, 0.5, 1.0/3.0, 2.0/3.0},
                         {0.5, 1, 2.0/3.0, 1},
                         {0, 0.5, 2.0/3.0, 1}};

UpdateRect URect62RTToB[] = { //Top To Bottom, Left To Right.
                                {0.5, 1, 0, 1.0/3.0},
                                {0.5, 1, 1.0/3.0, 2.0/3.0},
                                {0.5, 1, 2.0/3.0, 1},
                                {0, 0.5, 0, 1.0/3.0},
                                {0, 0.5, 1.0/3.0, 2.0/3.0},
                                {0, 0.5, 2.0/3.0, 1}
                            };

UpdateRect URect62RRToL[] = { //Right To Left, Top To Bottom
                                { 0,  0.5,    0,    1.0/3.0},
                                {0.5,  1,     0,    1.0/3.0},
                                { 0,  0.5, 1.0/3.0, 2.0/3.0},
                                {0.5,  1,  1.0/3.0, 2.0/3.0},
                                { 0,  0.5, 2.0/3.0,    1   },
                                {0.5,  1,  2.0/3.0,    1   }
                            };

UpdateRect URect62RTToBRToL[] = { //Top To Bottom, Right To Left
                                    {  0, 0.5, 2.0/3.0,       1},
                                    {  0, 0.5,       0, 1.0/3.0},
                                    {  0, 0.5, 1.0/3.0, 2.0/3.0},
                                    {0.5,   1, 1.0/3.0, 2.0/3.0},
                                    {0.5,   1, 2.0/3.0,       1},
                                    {0.5,   1,       0, 1.0/3.0}
                                };

UpdateRect URect9[] = {{0, 1.0/3.0, 0, 1.0/3.0},
                       {0, 1.0/3.0, 1.0/3.0, 2.0/3.0},
                       {0, 1.0/3.0, 2.0/3.0, 1},
                       {1.0/3.0, 2.0/3.0, 0, 1.0/3.0},
                       {1.0/3.0, 2.0/3.0, 1.0/3.0, 2.0/3.0},
                       {1.0/3.0, 2.0/3.0, 2.0/3.0, 1},
                       {2.0/3.0, 1, 0, 1.0/3.0},
                       {2.0/3.0, 1, 1.0/3.0, 2.0/3.0},
                       {2.0/3.0, 1, 2.0/3.0, 1}};

UpdateRect URect9TToB[] = { // Top to Bottom, Left To Right
                            {      0, 1.0/3.0,       0, 1.0/3.0},    //1
                            {1.0/3.0, 2.0/3.0,       0, 1.0/3.0},    //4
                            {2.0/3.0,       1,       0, 1.0/3.0},    //7
                            {      0, 1.0/3.0, 1.0/3.0, 2.0/3.0},    //2
                            {1.0/3.0, 2.0/3.0, 1.0/3.0, 2.0/3.0},    //5
                            {2.0/3.0,       1, 1.0/3.0, 2.0/3.0},    //8
                            {      0, 1.0/3.0, 2.0/3.0,       1},    //3
                            {1.0/3.0, 2.0/3.0, 2.0/3.0,       1},    //6
                            {2.0/3.0,       1, 2.0/3.0,       1}     //9
                          };

UpdateRect URect9RToL[] = {     //Right To Left, Top To Bottom
                            {      0, 1.0/3.0, 2.0/3.0,       1},       //3
                            {      0, 1.0/3.0, 1.0/3.0, 2.0/3.0},       //2
                            {      0, 1.0/3.0,       0, 1.0/3.0},       //1
                            {1.0/3.0, 2.0/3.0, 2.0/3.0,       1},       //6
                            {1.0/3.0, 2.0/3.0, 1.0/3.0, 2.0/3.0},       //5
                            {1.0/3.0, 2.0/3.0,       0, 1.0/3.0},       //4
                            {2.0/3.0,       1, 2.0/3.0,       1},       //9
                            {2.0/3.0,       1, 1.0/3.0, 2.0/3.0},       //8
                            {2.0/3.0,       1,       0, 1.0/3.0}        //7
                          };

UpdateRect URect9TToBRToL[] = {     //Top To Bottom, Right To Left
                                {2.0/3.0, 1, 0, 1.0/3.0},               //7
                                {1.0/3.0, 2.0/3.0, 0, 1.0/3.0},         //4
                                {0, 1.0/3.0, 0, 1.0/3.0},               //1
                                {2.0/3.0, 1, 1.0/3.0, 2.0/3.0},         //8
                                {1.0/3.0, 2.0/3.0, 1.0/3.0, 2.0/3.0},   //5 
                                {0, 1.0/3.0, 1.0/3.0, 2.0/3.0},         //2
                                {2.0/3.0, 1, 2.0/3.0, 1},               //9
                                {1.0/3.0, 2.0/3.0, 2.0/3.0, 1},         //6
                                {0, 1.0/3.0, 2.0/3.0, 1}                //3
                              };

UpdateRect URect16[] = {{0, 0.25, 0, 0.25},
                        {0, 0.25, 0.25, 0.5},
                        {0, 0.25, 0.5, 0.75},
                        {0, 0.25, 0.75, 1},
                        {0.25, 0.5, 0, 0.25},
                        {0.25, 0.5, 0.25, 0.5},
                        {0.25, 0.5, 0.5, 0.75},
                        {0.25, 0.5, 0.75, 1},
                        {0.5, 0.75, 0, 0.25},
                        {0.5, 0.75, 0.25, 0.5},
                        {0.5, 0.75, 0.5, 0.75},
                        {0.5, 0.75, 0.75, 1},
                        {0.75, 1, 0, 0.25},
                        {0.75, 1, 0.25, 0.5},
                        {0.75, 1, 0.5, 0.75},
                        {0.75, 1, 0.75, 1}};

UpdateRect URect16TToB[] = {            //Top To Bottom, Left To Right
                            {    0, 0.25,    0, 0.25 },     //1
                            { 0.25,  0.5,    0, 0.25 },     //5
                            {  0.5, 0.75,    0, 0.25 },     //9
                            { 0.75,    1,    0, 0.25 },     //13
                            {    0, 0.25, 0.25,  0.5 },     //2
                            { 0.25,  0.5, 0.25,  0.5 },     //6
                            {  0.5, 0.75, 0.25,  0.5 },     //10
                            { 0.75,    1, 0.25,  0.5 },     //14
                            {    0, 0.25,  0.5, 0.75 },     //3
                            { 0.25,  0.5,  0.5, 0.75 },     //7
                            {  0.5, 0.75,  0.5, 0.75 },     //11
                            { 0.75,    1,  0.5, 0.75 },     //15
                            {    0, 0.25, 0.75,    1 },     //4
                            { 0.25,  0.5, 0.75,    1 },     //8
                            {  0.5, 0.75, 0.75,    1 },     //12
                            { 0.75,    1, 0.75,    1 }      //16
                           };        


UpdateRect URect16RToL[] = {
                            {    0, 0.25, 0.75,    1 },     //4
                            {    0, 0.25,  0.5, 0.75 },     //3
                            {    0, 0.25, 0.25,  0.5 },     //2
                            {    0, 0.25,    0, 0.25 },     //1
                            { 0.25,  0.5, 0.75,    1 },     //8
                            { 0.25,  0.5,  0.5, 0.75 },     //7
                            { 0.25,  0.5, 0.25,  0.5 },     //6
                            { 0.25,  0.5,    0, 0.25 },     //5
                            {  0.5, 0.75, 0.75,    1 },     //12
                            {  0.5, 0.75,  0.5, 0.75 },     //11
                            {  0.5, 0.75, 0.25,  0.5 },     //10
                            {  0.5, 0.75,    0, 0.25 },     //9
                            { 0.75,    1, 0.75,    1 },     //16
                            { 0.75,    1,  0.5, 0.75 },     //15
                            { 0.75,    1, 0.25,  0.5 },     //14
                            { 0.75,    1,    0, 0.25 }      //13
                           };

UpdateRect URect16TToBRToL[] = {            //Top To Bottom, Right To Left
                                { 0.75,    1,    0, 0.25 },     //13
                                {  0.5, 0.75,    0, 0.25 },     //9
                                { 0.25,  0.5,    0, 0.25 },     //5
                                {    0, 0.25,    0, 0.25 },     //1
                                { 0.75,    1, 0.25,  0.5 },     //14
                                {  0.5, 0.75, 0.25,  0.5 },     //10
                                { 0.25,  0.5, 0.25,  0.5 },     //6
                                {    0, 0.25, 0.25,  0.5 },     //2
                                { 0.75,    1,  0.5, 0.75 },     //15
                                {  0.5, 0.75,  0.5, 0.75 },     //11
                                { 0.25,  0.5,  0.5, 0.75 },     //7
                                {    0, 0.25,  0.5, 0.75 },     //3
                                { 0.75,    1, 0.75,    1 },     //16
                                {  0.5, 0.75, 0.75,    1 },     //12
                                { 0.25,  0.5, 0.75,    1 },     //8
                                {    0, 0.25, 0.75,    1 }      //4
                               };


//
// Local function declaration
//
BOOL GdiGetDevmodeForPagePvt(
    IN  HANDLE              hSpoolHandle,
    IN  DWORD               dwPageNumber,
    OUT PDEVMODEW           *ppCurrDM,
    OUT PDEVMODEW           *ppLastDM
  );

BOOL BIsDevmodeOfLeastAcceptableSize(
    IN PDEVMODE pdm) ;


BOOL
ValidNumberForNUp(
    DWORD  dwPages)

/*++
Function Description: Checks if the number of pages printed on a single side is Valid.

Parameters: dwPages - Number of pages printed on a single side

Return Values: TRUE if (dwPages = 1|2|4|6|9|16)
               FALSE otherwise.
--*/

{

    return ((dwPages == 1) || (dwPages == 2) || (dwPages == 4) ||
            (dwPages == 6) || (dwPages == 9) || (dwPages == 16));
}

BOOL
GetPageCoordinatesForNUp(
    HDC                    hPrinterDC,
    PEMF_ATTRIBUTE_INFO    pEMFAttr,
    RECT                  *rectDocument,
    RECT                  *rectBorder,
    UINT                   uCurrentPageNumber,
    LPBOOL                 pbRotate
    )

/*++
Function Description: GetPageCoordinatesForNUp computes the rectangle on the Page where the
                      EMF file is to be played. It also determines if the picture is to
                      rotated.

Parameters:  hPrinterDC           - Printer Device Context
             pEMFAttr             - Attributes like n-up, n-up Border flags. Assumed to be valid.
             *rectDocument        - pointer to RECT where the coordinates to play the
                                     page will be returned.
             *rectBorder          - pointer to RECT where the page borders are to drawn.
             uCurrentPageNumber   - 1 based page number on the side.
             pbRotate             - pointer to BOOL which indicates if the picture must be
                                    rotated.

Return Values:  NONE.
--*/

{

    UpdateRect   *URect;
    LONG          lXPrintPage,lYPrintPage,lXPhyPage,lYPhyPage,lXFrame,lYFrame,ltemp,ldX,ldY;
    LONG          lXNewPhyPage,lYNewPhyPage,lXOffset,lYOffset,lNumRowCol,lRowIndex,lColIndex;
    double        dXleft,dXright,dYtop,dYbottom;
    LONG          xResolution = pEMFAttr->lXResolution;
    LONG          yResolution = pEMFAttr->lYResolution;

    DWORD         dwTotalNumberOfPages = pEMFAttr->dwNumberOfPagesPerSide; //total pages on 1 side.
    DWORD         dwNupBorderFlags     = pEMFAttr->dwNupBorderFlags;
    ENupDirection eNupDirection       = pEMFAttr->eNupDirection;

    // Get the 0-based array index for the current page

    uCurrentPageNumber = uCurrentPageNumber - 1;

    if (dwTotalNumberOfPages==1 || xResolution==yResolution)
    {
        xResolution = yResolution = 1;
    }

    rectDocument->top = rectDocument->bottom = lYPrintPage = (pEMFAttr->lYPrintArea - 1) * xResolution;
    rectDocument->left = rectDocument->right = lXPrintPage = (pEMFAttr->lXPrintArea - 1) * yResolution;

    lXPhyPage = GetDeviceCaps(hPrinterDC, PHYSICALWIDTH)  * yResolution;
    lYPhyPage = GetDeviceCaps(hPrinterDC, PHYSICALHEIGHT) * xResolution;

    //
    // Down in the code, we are dividing by these values, which can lead
    // to divide-by-zero errors.
    //
    if ( 0 == xResolution ||
         0 == yResolution ||
         0 == lXPhyPage   ||
         0 == lYPhyPage )
    {
        return FALSE;
    }

    *pbRotate = FALSE;

    //
    // Select the array containing the update factors
    // For n-up = 1 or if nupdirection is simple right then down, then look 
    // at the named matrices, if not, look get from the gUpdateRect using the 
    // BGetCoordinatesForNupFromArray function. For full reason, look at the comments
    // before gUpdateRect is declared.
    // kRightThenDown has value 0
    //

    if ( 1 == dwTotalNumberOfPages || eNupDirection == kRightThenDown )
    {
        switch (dwTotalNumberOfPages) {

        case 1: rectDocument->top = rectDocument->left = 0;
                rectDocument->right += 1;
                rectDocument->bottom += 1;
                return TRUE;

        case 2: if (lXPrintPage > lYPrintPage) {  // cut vertically
                    URect = URect22;
                } else {                          // cut horizontally
                    URect = URect21;
                }
                break;


        case 4: URect = URect4;
                break;

        case 6: if (lXPrintPage > lYPrintPage) {  // cut vertically twice
                    URect = URect62;
                } else {                          // cut horizontally twice
                    URect = URect61;
                }
                break;

        case 9: URect = URect9;
                break;

        case 16: URect = URect16;
                 break;

        default: // Should Not Occur.
                 return FALSE;
        } // end of switch
    }
    else
    {
        //
        // URect is actually a pointer to UpdateRect i.e. it points to array of
        // UpdateRect structures. So &URect is address of the pointer. 
        //
        BGetPageCoordinatesForNUpFromArray(pEMFAttr, &URect, (lXPrintPage > lYPrintPage)); 
     
    }

    //
    // We need to divide the page into appropriate sized rectangles.
    // So lets update the frame values.
    //
    switch (dwTotalNumberOfPages) {

        case 2: if (lXPrintPage > lYPrintPage) {  // cut vertically
                    lXFrame = (LONG) (lXPrintPage / 2.0);
                    lYFrame = lYPrintPage;
                } else {                          // cut horizontally
                    lYFrame = (LONG) (lYPrintPage / 2.0);
                    lXFrame = lXPrintPage;
                }
                break;


        case 4: lXFrame = (LONG) (lXPrintPage / 2.0);
                lYFrame = (LONG) (lYPrintPage / 2.0);
                break;

        case 6: if (lXPrintPage > lYPrintPage) {  // cut vertically twice
                    lXFrame = (LONG) (lXPrintPage / 3.0);
                    lYFrame = (LONG) (lYPrintPage / 2.0);
                } else {                          // cut horizontally twice
                    lYFrame = (LONG) (lYPrintPage / 3.0);
                    lXFrame = (LONG) (lXPrintPage / 2.0);
                }
                break;

        case 9: lXFrame = (LONG) (lXPrintPage / 3.0);
                lYFrame = (LONG) (lYPrintPage / 3.0);
                break;

        case 16: lXFrame = (LONG) (lXPrintPage / 4.0);
                 lYFrame = (LONG) (lYPrintPage / 4.0);
                 break;

        default: // Should Not Occur.
                 return FALSE;
    } 

    // Set the flag if the picture has to be rotated
    *pbRotate = !((lXPhyPage >= lYPhyPage) && (lXFrame >= lYFrame)) &&
                !((lXPhyPage < lYPhyPage) && (lXFrame < lYFrame));


    //
    // If the picture is to be rotated, modify the rectangle selected.
    // Again, do it only for traditional n-up
    // kRightThenDown has value 0
    //
    if ( eNupDirection == kRightThenDown )
    {

        if ((dwTotalNumberOfPages == 2) || (dwTotalNumberOfPages == 6)) {

           if (*pbRotate) {
              switch (dwTotalNumberOfPages) {
    
              case 2: if (lXPrintPage <= lYPrintPage) {
                          URect = URect21R;
                      } // URect22 = URect22R
                      break;

              case 6: if (lXPrintPage <= lYPrintPage) {
                          URect = URect61R;
                      } else {
                          URect = URect62R;
                      }
                      break;
              }
           }

        } else {
    
           if (*pbRotate) {
    
              // get the number of rows/columns. switch is faster than sqrt.
              switch (dwTotalNumberOfPages) {
    
              case 4: lNumRowCol = 2;
                      break;
              case 9: lNumRowCol = 3;
                      break;
              case 16: lNumRowCol = 4;
                      break;
              }
    
              lRowIndex  = (LONG) (uCurrentPageNumber / lNumRowCol);
              lColIndex  = (LONG) (uCurrentPageNumber % lNumRowCol);

              uCurrentPageNumber = (lNumRowCol - 1 - lColIndex) * lNumRowCol + lRowIndex;
           }

        }
    } //if eNupDirection

    // Update the Page Coordinates.

    rectDocument->top    = (LONG) (rectDocument->top    * URect[uCurrentPageNumber].top);
    rectDocument->bottom = (LONG) (rectDocument->bottom * URect[uCurrentPageNumber].bottom);
    rectDocument->left   = (LONG) (rectDocument->left   * URect[uCurrentPageNumber].left);
    rectDocument->right  = (LONG) (rectDocument->right  * URect[uCurrentPageNumber].right);

    // If the page border has to drawn, return the corresponding coordinates in rectBorder.

    if (dwNupBorderFlags == BORDER_PRINT) {
        rectBorder->top    = rectDocument->top/xResolution;
        rectBorder->bottom = rectDocument->bottom/xResolution - 1;
        rectBorder->left   = rectDocument->left/yResolution;
        rectBorder->right  = rectDocument->right/yResolution - 1;
    }

    if (*pbRotate) {
        ltemp = lXFrame; lXFrame = lYFrame; lYFrame = ltemp;
    }

    // Get the new size of the rectangle to keep the X/Y ratio constant.
    if ( ((LONG) (lYFrame*((lXPhyPage*1.0)/lYPhyPage))) >= lXFrame) {
         ldX = 0;
         ldY = lYFrame - ((LONG) (lXFrame*((lYPhyPage*1.0)/lXPhyPage)));
    } else {
         ldY = 0;
         ldX = lXFrame - ((LONG) (lYFrame*((lXPhyPage*1.0)/lYPhyPage)));
    }

    // Adjust the position of the rectangle.

    if (*pbRotate) {
        if (ldX) {
            rectDocument->bottom -= (LONG) (ldX / 2.0);
            rectDocument->top    += (LONG) (ldX / 2.0);
        } else {
           rectDocument->right   -= (LONG) (ldY / 2.0);
           rectDocument->left    += (LONG) (ldY / 2.0);
        }
    } else {
        if (ldX) {
           rectDocument->left    += (LONG) (ldX / 2.0);
           rectDocument->right   -= (LONG) (ldX / 2.0);
        } else {
           rectDocument->top     += (LONG) (ldY / 2.0);
           rectDocument->bottom  -= (LONG) (ldY / 2.0);
        }
    }

    // Adjust to get the Printable Area on the rectangle

    lXOffset = GetDeviceCaps(hPrinterDC, PHYSICALOFFSETX) * yResolution;
    lYOffset = GetDeviceCaps(hPrinterDC, PHYSICALOFFSETY) * xResolution;

    dXleft = ( lXOffset * 1.0) / lXPhyPage;
    dYtop  = ( lYOffset * 1.0) / lYPhyPage;
    dXright =  ((lXPhyPage - (lXOffset + lXPrintPage)) * 1.0) / lXPhyPage;
    dYbottom = ((lYPhyPage - (lYOffset + lYPrintPage)) * 1.0) / lYPhyPage;

    lXNewPhyPage = rectDocument->right  - rectDocument->left;
    lYNewPhyPage = rectDocument->bottom - rectDocument->top;

    if (*pbRotate) {

       ltemp = lXNewPhyPage; lXNewPhyPage = lYNewPhyPage; lYNewPhyPage = ltemp;

       rectDocument->left   += (LONG) (dYtop    * lYNewPhyPage);
       rectDocument->right  -= (LONG) (dYbottom * lYNewPhyPage);
       rectDocument->top    += (LONG) (dXright  * lXNewPhyPage);
       rectDocument->bottom -= (LONG) (dXleft   * lXNewPhyPage);

    } else {

       rectDocument->left   += (LONG) (dXleft   * lXNewPhyPage);
       rectDocument->right  -= (LONG) (dXright  * lXNewPhyPage);
       rectDocument->top    += (LONG) (dYtop    * lYNewPhyPage);
       rectDocument->bottom -= (LONG) (dYbottom * lYNewPhyPage);
    }

    if (xResolution!=yResolution)
    {
        rectDocument->left   = rectDocument->left   / yResolution;
        rectDocument->right  = rectDocument->right  / yResolution;
        rectDocument->top    = rectDocument->top    / xResolution;
        rectDocument->bottom = rectDocument->bottom / xResolution;
    }

    return TRUE;
}

BOOL
PlayEMFPage(
    HANDLE                hSpoolHandle,
    HDC                   hPrinterDC,
    HANDLE                hEMF,
    PEMF_ATTRIBUTE_INFO   pEMFAttr,
    DWORD                 dwPageNumber,
    DWORD                 dwPageIndex,
    DWORD                 dwAngle)

/*++
Function Description: PlayEMFPage plays the EMF in the appropriate rectangle. It performs
                      the required scaling, rotation and translation.

Parameters:   hSpoolHandle           -- handle the spool file handle
              hPrinterDC             -- handle to the printer device context
              hEMF                   -- handle to the contents of the page in the spool file
              pEMFAttr               -- Attributes like n-up, Border Flags etc. Assumed nonnull.
              dwPageNumber           -- page number in the document
              dwPageIndex            -- page number in the side. (1 based)
              dwAngle                -- angle for rotation (if neccesary)

Return Values:  TRUE if successful
                FALSE otherwise
--*/
{
   BOOL         bReturn = FALSE, bRotate;
   RECT         rectDocument, rectPrinter, rectBorder = {-1, -1, -1, -1};
   RECT         *prectClip = NULL;
   XFORM        TransXForm = {1, 0, 0, 1, 0, 0}, RotateXForm = {0, -1, 1, 0, 0, 0};
   HPEN         hPen;
   HANDLE       hFormEMF;
   DWORD        dwPageType,dwFormPage;
   DWORD        dwNumberOfPagesPerSide = pEMFAttr->dwNumberOfPagesPerSide;

   // Compute the rectangle for one page.
   if ( FALSE == GetPageCoordinatesForNUp(hPrinterDC,
                            pEMFAttr,
                            &rectDocument,
                            &rectBorder,
                            dwPageIndex,
                            &bRotate) )
    {
        goto CleanUp;
    }

   // If swap flag is set, reverse rotate flag
   //
   if (dwAngle & EMF_DEGREE_SWAP)
       bRotate = !bRotate;

   if (dwAngle & EMF_DEGREE_270) {
       RotateXForm.eM12 = 1;
       RotateXForm.eM21 = -1;
   }   // EMF_DEGREE_90 case is the initialization

   if (bRotate) {

       rectPrinter.top = 0;
       rectPrinter.bottom = rectDocument.right - rectDocument.left;
       rectPrinter.left = 0;
       rectPrinter.right = rectDocument.bottom - rectDocument.top;

       // Set the translation matrix
       if (dwAngle & EMF_DEGREE_270) {
           TransXForm.eDx = (float) rectDocument.right;
           TransXForm.eDy = (float) rectDocument.top;
       } else {
           // EMF_DEGREE_90
           TransXForm.eDx = (float) rectDocument.left;
           TransXForm.eDy = (float) rectDocument.bottom;
       }

       // Set the transformation matrix
       if (!SetWorldTransform(hPrinterDC, &RotateXForm) ||
           !ModifyWorldTransform(hPrinterDC, &TransXForm, MWT_RIGHTMULTIPLY)) {

            ODS(("Setting transformation matrix failed\n"));
            goto CleanUp;
       }
   }

   // Add clipping for Nup
   if (dwNumberOfPagesPerSide != 1) {

       prectClip = &rectDocument;
   }

   // Print the page.
   if (bRotate) {
       GdiPlayPageEMF(hSpoolHandle, hEMF, &rectPrinter, &rectBorder, prectClip);

   } else {
       GdiPlayPageEMF(hSpoolHandle, hEMF, &rectDocument, &rectBorder, prectClip);
   }

   bReturn = TRUE;

CleanUp:

   if (!ModifyWorldTransform(hPrinterDC, NULL, MWT_IDENTITY)) {

       ODS(("Setting Identity Transformation failed\n"));
       bReturn = FALSE;
   }

   return bReturn;
}

BOOL
SetDrvCopies(
    HDC          hPrinterDC,
    LPDEVMODEW   pDevmode,
    DWORD        dwNumberOfCopies)

/*++
Function Description: SetDrvCopies sets the dmCopies field in pDevmode and resets
                      hPrinterDC with this devmode

Parameters: hPrinterDC             -- handle to the printer device context
            pDevmode               -- pointer to devmode
            dwNumberOfCopies       -- value for dmCopies

Return Values:  TRUE if successful
                FALSE otherwise
--*/

{
    BOOL     bReturn;
    DWORD    dmFields;

    if ((pDevmode->dmFields & DM_COPIES) &&
        (pDevmode->dmCopies == (short) dwNumberOfCopies)) {

         return TRUE;
    }

    // Save the old fields structure
    dmFields = pDevmode->dmFields;
    pDevmode->dmFields |= DM_COPIES;
    pDevmode->dmCopies = (short) dwNumberOfCopies;

    if (!ResetDC(hPrinterDC, pDevmode))  {
        bReturn = FALSE;
    } else {
        bReturn = TRUE;
    }
    // Restore the fields structure
    pDevmode->dmFields = dmFields;

    if (!SetGraphicsMode(hPrinterDC,GM_ADVANCED)) {
        ODS(("Setting graphics mode failed\n"));
        bReturn = FALSE;
    }

    return bReturn;
}

BOOL
DifferentDevmodes(
    LPDEVMODE    pDevmode1,
    LPDEVMODE    pDevmode2
    )

/*++
Function Description: Compares the devmodes for differences other than dmTTOption

Parameters:  pDevmode1    -   devmode 1
             pDevmode2    -   devmode 2

Return Values: TRUE if different ; FALSE otherwise
--*/

{
    DWORD   dwSize1, dwSize2, dwTTOffset, dwSpecOffset, dwLogOffset;

    // Same pointers are the same devmode
    if (pDevmode1 == pDevmode2) {
        return FALSE;
    }

    // Check for Null devmodes
    if (!pDevmode1 || !pDevmode2) {
        return TRUE;
    }

    dwSize1 = pDevmode1->dmSize + pDevmode1->dmDriverExtra;
    dwSize2 = pDevmode2->dmSize + pDevmode2->dmDriverExtra;

    // Compare devmode sizes
    if (dwSize1 != dwSize2) {
        return TRUE;
    }

    dwTTOffset = FIELD_OFFSET(DEVMODE, dmTTOption);
    dwSpecOffset = FIELD_OFFSET(DEVMODE, dmSpecVersion);
    dwLogOffset = FIELD_OFFSET(DEVMODE, dmLogPixels);

    if (wcscmp(pDevmode1->dmDeviceName,
               pDevmode2->dmDeviceName)) {
        // device names are different
        return TRUE;
    }

    if (dwTTOffset < dwSpecOffset ||
        dwSize1 < dwLogOffset) {

        // incorrent devmode offsets
        return TRUE;
    }

    if (memcmp((LPBYTE) pDevmode1 + dwSpecOffset,
               (LPBYTE) pDevmode2 + dwSpecOffset,
               dwTTOffset - dwSpecOffset)) {
        // Front half is different
        return TRUE;
    }

    // Ignore the dmTTOption setting.

    if ((pDevmode1->dmCollate != pDevmode2->dmCollate) ||
        wcscmp(pDevmode1->dmFormName, pDevmode2->dmFormName)) {

        // form name or collate option is different
        return TRUE;
    }

    if (memcmp((LPBYTE) pDevmode1 + dwLogOffset,
               (LPBYTE) pDevmode2 + dwLogOffset,
               dwSize1 - dwLogOffset)) {
        // Back half is different
        return TRUE;
    }

    return FALSE;
}


BOOL
ResetDCForNewDevmode(
    HANDLE                hSpoolHandle,
    HDC                   hPrinterDC,
    PEMF_ATTRIBUTE_INFO   pEMFAttr,
    DWORD                 dwPageNumber,
    BOOL                  bInsidePage,
    DWORD                 dwOptimization,
    LPBOOL                pbNewDevmode,
    LPDEVMODE             pDevmode,
    LPDEVMODE            *ppCurrentDevmode
    )

/*++
Function Description: Determines if the devmode for the page is different from the
                      current devmode for the printer dc and resets the dc if necessary.
                      The parameters allow dmTTOption to be ignored in devmode comparison.

Parameters: hSpoolHandle         -  spool file handle
            hPrinterDC           -  printer dc
            pEMFAttr             -  Job Attributes
            dwPageNumber         -  page number before which we search for the devmode
            bInsidePage          -  flag to ignore changes in TT options and call EndPage
                                       before ResetDC
            dwOptimization       -  optimization flags
            pbNewDevmode         -  pointer to flag to indicate if ResetDC was called
            pDevmode             -  The devmode active when this function called. 
            ppCurrentDevmode     -  The devmode that should be active after exiting from this func.

Return Values: TRUE if successful; FALSE otherwise
--*/

{
    BOOL           bReturn = FALSE;
    LPDEVMODE      pLastDM, pCurrDM;

    // Initialize OUT parameters
    *pbNewDevmode = FALSE;

    // Get the devmode just before the page
    if (!GdiGetDevmodeForPagePvt(hSpoolHandle,
                                 dwPageNumber,
                                 &pCurrDM,
                                 &pLastDM)) {

        ODS(("GdiGetDevmodeForPagePvt failed\n"));
        return bReturn;
    }

    // Save pointer to current devmode
    if (ppCurrentDevmode)
        *ppCurrentDevmode = pCurrDM;

    // Check if the devmodes are different
    if (pLastDM != pCurrDM) {

        // If the pointers are different the devmodes are always different
        if (!bInsidePage ||
            DifferentDevmodes(pLastDM, pCurrDM)) {

            *pbNewDevmode = TRUE;
        }
    }

    // Call ResetDC on the hPrinterDC if necessary
    if (*pbNewDevmode) {

        if (bInsidePage &&
            !GdiEndPageEMF(hSpoolHandle, dwOptimization)) {

            ODS(("EndPage failed\n"));
            return bReturn;
        }

        if (pCurrDM) {
            pCurrDM->dmPrintQuality = pDevmode->dmPrintQuality;
            pCurrDM->dmYResolution = pDevmode->dmYResolution;
            pCurrDM->dmCopies = pDevmode->dmCopies;


            if ( IS_DMSIZE_VALID ( pCurrDM, dmCollate ) )
            {
                if ( IS_DMSIZE_VALID ( pDevmode, dmCollate ) )
                {
                    pCurrDM->dmCollate = pDevmode->dmCollate;
                }
                else
                {
                    pCurrDM->dmCollate = DMCOLLATE_FALSE;
                }
                
            }
        }

        // Ignore the return values of ResetDC and SetGraphicsMode
        GdiResetDCEMF(hSpoolHandle, pCurrDM);
        SetGraphicsMode(hPrinterDC, GM_ADVANCED);


        //
        // Also if new devmode indicates orientation has changed, then we need to change
        // a few things in EMFAttr. e.g. The printable area is different in landscape
        // and portrait mode.
        //
        if ( pCurrDM && (pCurrDM->dmOrientation != pDevmode->dmOrientation) )
        {
            BUpdateAttributes(hPrinterDC, pEMFAttr);
        }

    }

    bReturn = TRUE;

    return bReturn;
}

DWORD
PrintOneSideForwardEMF(
    HANDLE                  hSpoolHandle,
    HDC                     hPrinterDC,
    PEMF_ATTRIBUTE_INFO     pEMFAttr,
    BOOL                    bDuplex,
    DWORD                   dwOptimization,
    DWORD                   dwPageNumber,
    LPBOOL                  pbComplete,
    LPDEVMODE               pDevmode)

/*++
Function Description: PrintOneSideForwardEMF plays the next physical page in the same order
                      as the spool file.

Parameters: hSpoolHandle              -- handle the spool file handle
            hPrinterDC                -- handle to the printer device context
            pEMFAttr                  --
            bDuplex                   -- flag to indicate duplex printing
            dwOptimization            -- optimization flags
            dwPageNumber              -- pointer to the starting page number
            pbComplete                -- pointer to the flag to indicate completion
            pDevmode                  -- devmode with resolution settings

Return Values:  Last Page Number if successful
                0 on job completion (pbReturn set to TRUE) and
                  on failure (pbReturn remains FALSE)
--*/

{
    DWORD              dwPageIndex, dwPageType;
    DWORD              dwReturn = 0;
    LPDEVMODEW         pCurrDM;
    HANDLE             hEMF = NULL;
    DWORD              dwSides;
    BOOL               bNewDevmode;
    DWORD              cPagesToPlay;
    DWORD              dwAngle;
    INT                dmOrientation = pDevmode->dmOrientation;
    DWORD              dwNumberOfPagesPerSide    = pEMFAttr->dwNumberOfPagesPerSide;
    DWORD              dwDrvNumberOfPagesPerSide = pEMFAttr->dwDrvNumberOfPagesPerSide;
    DWORD              dwJobNumberOfCopies       = pEMFAttr->dwJobNumberOfCopies;


    // set the number of sides on this page;
    dwSides = bDuplex ? 2 : 1;
    *pbComplete = FALSE;

    for ( ; dwSides && !*pbComplete ; --dwSides) {

       // loop for a single side
       for (dwPageIndex = 1;
            dwPageIndex <= dwNumberOfPagesPerSide;
            ++dwPageIndex, ++dwPageNumber) {

            if (!(hEMF = GdiGetPageHandle(hSpoolHandle,
                                          dwPageNumber,
                                          &dwPageType))) {

                if (GetLastError() == ERROR_NO_MORE_ITEMS) {
                     // End of the print job
                     *pbComplete = TRUE;
                     break;
                }

                ODS(("GdiGetPageHandle failed\nPrinter %ws\n", pDevmode->dmDeviceName));
                goto CleanUp;
            }
            dwAngle = EMF_DEGREE_90;
            if (dwPageIndex == 1)
            {
                // Process new devmodes in the spool file that appear before this page
                if (!ResetDCForNewDevmode(hSpoolHandle,
                                      hPrinterDC,
                                      pEMFAttr,
                                      dwPageNumber,
                                      (dwPageIndex != 1),
                                      dwOptimization,
                                      &bNewDevmode,
                                      pDevmode,
                                      &pCurrDM)) {

                    goto CleanUp;
                }
                if (pCurrDM)
                    dmOrientation = pCurrDM->dmOrientation;
            }
            // in case of orientation switch we need to keep track of what
            // we started with and what it is now
            else if (dwNumberOfPagesPerSide > 1)
            {
                if (GdiGetDevmodeForPagePvt(hSpoolHandle,
                                            dwPageNumber,
                                            &pCurrDM,
                                            NULL))
                {
                    if (pCurrDM && pCurrDM->dmOrientation != dmOrientation)
                    {
                        dwAngle = EMF_DEGREE_SWAP | EMF_DEGREE_90;
                        BUpdateAttributes(hPrinterDC, pEMFAttr);
                    }
                }
            }
            // Call StartPage for each new page
            if ((dwPageIndex == 1) &&
                !GdiStartPageEMF(hSpoolHandle)) {

                ODS(("StartPage failed\nPrinter %ws\n", pDevmode->dmDeviceName));
                goto CleanUp;
            }

            if (!PlayEMFPage(hSpoolHandle,
                             hPrinterDC,
                             hEMF,
                             pEMFAttr,
                             dwPageNumber,
                             dwPageIndex,
                             dwAngle)) {

                ODS(("PlayEMFPage failed\nPrinter %ws\n", pDevmode->dmDeviceName));
                goto CleanUp;
            }
       }

       //
       // Explaination of the scinario set for the conditions on
       // dwPageIndex1 , pbComplete and bDuplex.
       // N.B. we are naming them cond.1 and cond.2
       //     dwPageIndex!=1    pbComplete   bDuplex    Condition
       //           0               0           0       None
       //           0               0           1       None
       //           0               1           0       None
       //           0               1           1       Cond2 on Second Side i.e. dwsides==1
       //           1               0           0       Cond1
       //           1               0           1       Cond1
       //           1               1           0       Cond1
       //           1               1           1       Cond1 & Cond2 on First Side i.e. dwsides==2
       //


       // cond.1
       if (dwPageIndex != 1) {

           // Call EndPage if we played any pages
           if (!GdiEndPageEMF(hSpoolHandle, dwOptimization)) {

               ODS(("EndPage failed\n"));
               *pbComplete = FALSE;
               goto CleanUp;
           }
       }

       // cond.2
       // play empty page on the back of duplex
       if (*pbComplete && bDuplex && dwDrvNumberOfPagesPerSide==1) {

           ODS(("PCL or PS with no N-up\n"));

           //
           // Checking dwsides against 2 or 1.
           // depends on whether it is n-up or not.
           //
           if (((dwPageIndex!=1)?(dwSides==2):(dwSides==1))) {

               if (!GdiStartPageEMF(hSpoolHandle) ||
                   !GdiEndPageEMF(hSpoolHandle, dwOptimization)) {

                   ODS(("EndPage failed\n"));
                   *pbComplete = FALSE;
                   goto CleanUp;
               }
           }
        }
    }

    if (*pbComplete &&
        dwNumberOfPagesPerSide==1 &&
        dwDrvNumberOfPagesPerSide!=1 &&
        dwJobNumberOfCopies!=1)
    {
        cPagesToPlay = dwDrvNumberOfPagesPerSide * (bDuplex ? 2 : 1);
        if ((dwPageNumber-1) % cPagesToPlay)
        {
            //
            // Number of pages played on last physical page
            //
            cPagesToPlay = cPagesToPlay - ((dwPageNumber-1) % cPagesToPlay);

            ODS(("\nPS with N-up!\nMust fill in %u pages\n", cPagesToPlay));

            for (;cPagesToPlay;cPagesToPlay--)
            {
                if (!GdiStartPageEMF(hSpoolHandle) || !GdiEndPageEMF(hSpoolHandle, dwOptimization))
                {
                    ODS(("EndPage failed\n"));
                    goto CleanUp;
                }
            }
        }
    }

    if (!(*pbComplete)) dwReturn = dwPageNumber;

CleanUp:

    return dwReturn;
}

BOOL
PrintForwardEMF(
    HANDLE                  hSpoolHandle,
    HDC                     hPrinterDC,
    PEMF_ATTRIBUTE_INFO     pEMFAttr,
    BOOL                    bDuplex,
    DWORD                   dwOptimization,
    LPDEVMODEW              pDevmode,
    PPRINTPROCESSORDATA pData)

/*++
Function Description: PrintForwardEMF plays the EMF files in the order in which they
                      were spooled.

Parameters: hSpoolHandle              -- handle the spool file handle
            hPrinterDC                -- handle to the printer device context
            pEMFAttr                  -- 
            bDuplex                   -- flag for duplex printing
            dwOptimization            -- optimization flags
            pDevmode                  -- pointer to devmode for changing the copy count
            pData                     -- needed for status and the handle of the event: pause, resume etc.

Return Values:  TRUE if successful
                FALSE otherwise
--*/

{
    DWORD              dwLastPageNumber = 1,dwPageNumber,dwPageIndex,dwRemainingCopies;
    BOOL               bReturn = FALSE;

    BOOL               bCollate                   = pEMFAttr->bCollate;
    DWORD              dwJobNumberOfCopies        = pEMFAttr->dwJobNumberOfCopies;
    DWORD              dwDrvNumberOfCopies        = pEMFAttr->dwDrvNumberOfCopies;
    

    // Keep printing as long as the spool file contains EMF handles.
    while (dwLastPageNumber) {

        //
        // If the print processor is paused, wait for it to be resumed
        //
        if (pData->fsStatus & PRINTPROCESSOR_PAUSED) {
            WaitForSingleObject(pData->semPaused, INFINITE);
        }

        dwPageNumber = dwLastPageNumber;

        if (bCollate) {

           dwLastPageNumber = PrintOneSideForwardEMF(hSpoolHandle,
                                                     hPrinterDC,
                                                     pEMFAttr,
                                                     bDuplex,
                                                     dwOptimization,
                                                     dwPageNumber,
                                                     &bReturn,
                                                     pDevmode);
        } else {

           dwRemainingCopies = dwJobNumberOfCopies;

           while (dwRemainingCopies) {

               if (dwRemainingCopies <= dwDrvNumberOfCopies) {
                  SetDrvCopies(hPrinterDC, pDevmode, dwRemainingCopies);
                  dwRemainingCopies = 0;
               } else {
                  SetDrvCopies(hPrinterDC, pDevmode, dwDrvNumberOfCopies);
                  dwRemainingCopies -= dwDrvNumberOfCopies;
               }

               if (!(dwLastPageNumber =  PrintOneSideForwardEMF(hSpoolHandle,
                                                                hPrinterDC,
                                                                pEMFAttr,
                                                                bDuplex,
                                                                dwOptimization,
                                                                dwPageNumber,
                                                                &bReturn,
                                                                pDevmode)) &&
                   !bReturn) {

                    goto CleanUp;
               }
           }
        }
    }

CleanUp:

    return bReturn;
}

BOOL
PrintOneSideReverseForDriverEMF(
    HANDLE                hSpoolHandle,
    HDC                   hPrinterDC,
    PEMF_ATTRIBUTE_INFO   pEMFAttr,
    PPAGE_NUMBER          pHead,
    BOOL                  bDuplex,
    DWORD                 dwOptimization,
    LPDEVMODE             pDevmode)

/*++
Function Description: PrintOneSideReverseForDriverEMF plays the EMF pages on the next
                      physical page, in the reverse order for the driver which does the
                      Nup transformations.

Parameters: hSpoolHandle           -- handle the spool file handle
            hPrinterDC             -- handle to the printer device context
            pEMFAttr               -- 
            pHead                  -- Linked list of page numbers
            bDuplex                -- flag to indicate duplex printing
            dwOptimization         -- optimization flags
            pDevmode               -- devmode with resolution settings

Return Values:  TRUE if successful
                FALSE otherwise
--*/
{
    DWORD       dwPageIndex, dwPageType, dwSides;
    BOOL        bReturn = FALSE, bNewDevmode,BeSmart;
    LPDEVMODEW  pCurrDM;
    HANDLE      hEMF = NULL;
    DWORD       dwLimit;
    DWORD       dwNumPagePerSide = 1; //Temporary value holder.
    DWORD       dwPageNumber;         // page number to start the side

    DWORD       dwDrvNumberOfPagesPerSide = pEMFAttr->dwDrvNumberOfPagesPerSide;
    DWORD       dwTotalNumberOfPages      = pEMFAttr->dwTotalNumberOfPages;
    PPAGE_NUMBER pHeadLogical             = pHead;


    dwSides = bDuplex ? 2 : 1;

    if ( !pHead )
    {
        ODS(("pHead is NULL.\n"));
        return FALSE;
    }

    //
    // If the document will fit on one physical page, then this variable will prevent
    // the printer from playing extra pages just to fill in one phisical page
    // The exception is when the pages fit on a single phisical page, but they must
    // be collated. Then because of design, the printer will also draw borders for the
    // empty pages which are played so that the page gets ejected.
    //
    BeSmart =  (dwTotalNumberOfPages<=dwDrvNumberOfPagesPerSide) &&
               IS_DMSIZE_VALID(pDevmode, dmCollate) && 
               (pDevmode->dmCollate != DMCOLLATE_TRUE);

    for (; dwSides && pHead; --dwSides, pHead = pHead->pNextSide) {

        pHeadLogical = pHead;
        dwPageNumber = pHeadLogical->dwPageNumber;

        // This loop may play some empty pages in the last side, since the
        // driver is doing nup and it does not keep count of the page numbers
        //
        dwPageIndex=BeSmart?dwPageNumber:1;
        dwLimit    =BeSmart?dwTotalNumberOfPages:dwDrvNumberOfPagesPerSide;

        for (;(dwPageIndex<=dwLimit && pHeadLogical); ++dwPageIndex, pHeadLogical = pHeadLogical->pNextLogPage) {
 
            //
            // if dwPageNumber is 0 or 0xFFFFFFFF, it means empty page.
            //
            dwPageNumber = pHeadLogical->dwPageNumber;
            if ( dwPageNumber == 0 )
            {
                dwPageNumber = 0xFFFFFFFF; //big number
            }

             if (BeSmart || dwPageNumber <= dwTotalNumberOfPages) {

                 if (!(hEMF = GdiGetPageHandle(hSpoolHandle,
                                               dwPageNumber,
                                               &dwPageType))) {
                     ODS(("GdiGetPageHandle failed\nPrinter %ws\n", pDevmode->dmDeviceName));
                     goto CleanUp;
                 }

                 // Process new devmodes in the spoolfile
                 if (!ResetDCForNewDevmode(hSpoolHandle,
                                           hPrinterDC,
                                           pEMFAttr,
                                           dwPageNumber,
                                           FALSE,
                                           dwOptimization,
                                           &bNewDevmode,
                                           pDevmode,
                                           NULL)) {
                 }
             }

             if (!GdiStartPageEMF(hSpoolHandle)) {
                 ODS(("StartPage failed\nPrinter %ws\n", pDevmode->dmDeviceName));
                 goto CleanUp;
             }

             if (BeSmart || dwPageNumber <= dwTotalNumberOfPages) {

                //
                // I need to print with numpageperside=1.
                // But pEMFAttr->dwNumberOfPagesPerSide may be any value.
                // So i store its current value, replace it by 1,
                // and then restore the value.
                //
                dwNumPagePerSide = pEMFAttr->dwNumberOfPagesPerSide;
                pEMFAttr->dwNumberOfPagesPerSide = 1;


                if (!PlayEMFPage(hSpoolHandle,
                                  hPrinterDC,
                                  hEMF,
                                  pEMFAttr,
                                  dwPageNumber,
                                  1,
                                  EMF_DEGREE_90)) {

                     ODS(("PlayEMFPage failed\n"));
                     pEMFAttr->dwNumberOfPagesPerSide = dwNumPagePerSide;
                     goto CleanUp;
                 }
                pEMFAttr->dwNumberOfPagesPerSide = dwNumPagePerSide;
             }

             if (!GdiEndPageEMF(hSpoolHandle, dwOptimization)) {
                 ODS(("EndPage failed\nPrinter %ws\n", pDevmode->dmDeviceName));
                 goto CleanUp;
             }
        }

        if ( pHeadLogical == NULL && dwPageIndex<=dwLimit && dwDrvNumberOfPagesPerSide > 1)
        {
            //
            // Suppose the n-up is 4 (dwLimit is 4) and the n-up is done by the device ( dwDrvNumberOfPagesPerSide > 1)
            // i.e. device needs 4 pages to finish printing a side and eject paper.
            // Suppose pHeadLogical list has only 2 pages (i.e. the pHeadLogical is now NULL after 
            // going thru above loop). 
            // So we need to send the printer 2 empty pages (logical pages)
            //
            BPlayEmptyPages(hSpoolHandle, pEMFAttr, (dwLimit-dwPageIndex+1), dwOptimization);
        }

    }

    bReturn = TRUE;

CleanUp:

    return bReturn;
}



BOOL
PrintEMFInPredeterminedOrder(
    HANDLE                  hSpoolHandle,
    HDC                     hPrinterDC,
    PEMF_ATTRIBUTE_INFO     pEMFAttr,
    PPAGE_NUMBER            pHead,
    BOOL                    bDuplex,
    BOOL                    bOdd,
    DWORD                   dwOptimization,
    LPDEVMODEW              pDevmode,
    PPRINTPROCESSORDATA     pData)

/*++
Function Description: PrintEMFInPredeterminedOrder plays the EMF pages in the order dictated by pHead.

Parameters: hSpoolHandle           -- handle the spool file handle
            hPrinterDC             -- handle to the printer device context
            pEMFAttr               -- Job Attributes
            pHead                  -- pointer to a linked list containing the starting
                                       page numbers for each of the sides
            bDuplex                -- flag to indicate duplex printing
            bOdd                   -- flag to indicate odd number of sides to print
            dwOptimization         -- optimization flags
            pDevmode               -- pointer to devmode for changing the copy count
            pData                  -- needed for status and the handle of the event: pause, resume etc.

Return Values:  TRUE if successful
                FALSE otherwise
--*/

{
    DWORD         dwPageIndex,dwPageNumber,dwRemainingCopies;
    BOOL          bReturn = FALSE;

    /*++
            dwJobNumberOfCopies    -- number of copies of the job to be printed
            dwDrvNumberOfCopies    -- number of copies that the driver can print
            bCollate               -- flag for collating the copies
    --*/

    DWORD   dwDrvNumberOfCopies        = pEMFAttr->dwDrvNumberOfCopies;
    DWORD   dwJobNumberOfCopies        = pEMFAttr->dwJobNumberOfCopies;
    BOOL    bCollate                   = pEMFAttr->bCollate;
    DWORD   dwNumberOfPagesPerSide     = pEMFAttr->dwNumberOfPagesPerSide;
    DWORD   dwDrvNumberOfPagesPerSide  = pEMFAttr->dwDrvNumberOfPagesPerSide;
    PFPRINTONESIDEREVERSEEMF   pfPrintOneSideReverseEMF = NULL;

    if (!pHead) {
        ODS(("pHead is NULL.\n"));
        bReturn = FALSE;
        goto CleanUp;
    }

    //
    // This function is called for Booklet, Reverse Printing in which printer does
    // n-up, and reverse printing in which print processor simulates n-up. So lets
    // select which of the cases it is called for, and setup the appropriate functions.
    //
    if ( pEMFAttr->bBookletPrint )
    {
        pfPrintOneSideReverseEMF = PrintOneSideBookletEMF;
    }
    else if (dwDrvNumberOfPagesPerSide != 1 || dwNumberOfPagesPerSide == 1) 
    {
        //
        // If the printer can handle n-up
        //
        pfPrintOneSideReverseEMF = PrintOneSideReverseForDriverEMF;
        dwNumberOfPagesPerSide   = dwDrvNumberOfPagesPerSide;
    }
    else
    {
        pfPrintOneSideReverseEMF = PrintOneSideReverseEMF;
    }


    // play the sides in reverse order
    while (pHead) {
        //
        // If the print processor is paused, wait for it to be resumed
        //
        if (pData->fsStatus & PRINTPROCESSOR_PAUSED) {
            WaitForSingleObject(pData->semPaused, INFINITE);
        }

        // set the page number
        dwPageNumber = pHead->dwPageNumber;

        if (bCollate) {

           if (!pfPrintOneSideReverseEMF(hSpoolHandle,
                                         hPrinterDC,
                                         pEMFAttr,
                                         pHead,
                                         bDuplex,
                                         dwOptimization,
                                         pDevmode)) {
               goto CleanUp;
           }

        } else {

           dwRemainingCopies = dwJobNumberOfCopies;

           while (dwRemainingCopies) {

               if (dwRemainingCopies <= dwDrvNumberOfCopies) {
                  SetDrvCopies(hPrinterDC, pDevmode, dwRemainingCopies);
                  dwRemainingCopies = 0;
               } else {
                  SetDrvCopies(hPrinterDC, pDevmode, dwDrvNumberOfCopies);
                  dwRemainingCopies -= dwDrvNumberOfCopies;
               }

               if (!pfPrintOneSideReverseEMF(hSpoolHandle,
                                             hPrinterDC,
                                             pEMFAttr,
                                             pHead,
                                             bDuplex,
                                             dwOptimization,
                                             pDevmode)) {
                   goto CleanUp;
               }
           }
        }

        //
        // go to the next node(page) in the linked list. For duplex printing
        // we go ahead 2 nodes. 
        //
        pHead = pHead->pNextSide;
        if (bDuplex && pHead) {
            pHead = pHead->pNextSide;
        }
    } //while pHead

    bReturn = TRUE;

CleanUp:

    return bReturn;
}

BOOL
PrintOneSideReverseEMF(
    HANDLE                hSpoolHandle,
    HDC                   hPrinterDC,
    PEMF_ATTRIBUTE_INFO   pEMFAttr,
    PPAGE_NUMBER          pHead,
    BOOL                  bDuplex,
    DWORD                 dwOptimization,
    LPDEVMODE             pDevmode)

/*++
Function Description: PrintOneSideReverseEMF plays the EMF pages for the next physical page.

Parameters: hSpoolHandle           -- handle the spool file handle
            hPrinterDC             -- handle to the printer device context
            pEMFAttr               -- Job Attributes
            pHead                  -- List of pages in the order in which they have to be printed.
            bDuplex                -- flag to indicate duplex printing
            dwOptimization         -- optimization flags
            pDevmode               -- devmode with resolution settings

Return Values:  TRUE if successful
                FALSE otherwise
--*/
{
    DWORD         dwPageNumber, dwPageIndex, dwPageType;
    DWORD         dwStartPage1, dwEndPage1, dwStartPage2, dwEndPage2;

    BOOL          bReturn = FALSE, bNewDevmode;
    LPDEVMODEW    pCurrDM = NULL;
    HANDLE        hEMF    = NULL;
    DWORD         dwEndPage, dwStartPage, dwSides, dwAngle;
    INT           dmOrientation = pDevmode->dmOrientation;

    DWORD         dwNumberOfPagesPerSide = pEMFAttr->dwNumberOfPagesPerSide;
    DWORD         dwTotalNumberOfPages   = pEMFAttr->dwTotalNumberOfPages;
    PPAGE_NUMBER  pHeadLogical           = pHead;

    if ( !pHead )
    {
        return TRUE;
    }

    dwSides = bDuplex ? 2 : 1;

    //
    // For each side, print all the logical pages.
    //
    for (;  dwSides;  --dwSides, pHead = pHead->pNextSide) {

        pHeadLogical = pHead;
        dwPageNumber = pHeadLogical->dwPageNumber;

        if ( NULL == pHeadLogical )
        {
            ODS(("Unexpected end of ReversePrintList %ws\n", pDevmode->dmDeviceName));
            goto CleanUp;
        }

        for (dwPageIndex = 1;
              ( (pHeadLogical != NULL) && (dwPageIndex <= dwNumberOfPagesPerSide));
              pHeadLogical = pHeadLogical->pNextLogPage, ++dwPageIndex) 
        {

            dwPageNumber = pHeadLogical->dwPageNumber;
    
            if ( dwPageNumber == 0 )
            {
                dwPageNumber = 0xFFFFFFFF; //some big number.
            }

            //
            // Get PageHandle only if the page number is less than or equal to
            // total number of pages. A bigger  page number indicates
            // empty/non-existent page for which there can be no handle.
            //
            if (dwPageNumber <= dwTotalNumberOfPages )
            {
                if (!(hEMF = GdiGetPageHandle(hSpoolHandle,
                                                 dwPageNumber,
                                                 &dwPageType))) {

                    ODS(("GdiGetPageHandle failed\nPrinter %ws\n", pDevmode->dmDeviceName));
                    goto CleanUp;
                }
            }

            dwAngle = EMF_DEGREE_90;
            if (dwPageIndex == 1) 
            {

                //
                // We now need to give a ResetDC call. ResetDC should be given
                // at most once on begining of each side. If side is empty, no
                // ResetDC is done. If side is half filled (e.g. n-up = 2 but
                // only one page has to be printed), then we do ResetDC for
                // first available valid page.
                //
                DWORD dwPageNumberForResetDC = 0xFFFFFFFF;
                PPAGE_NUMBER pHeadMoving  = NULL; //moves thru the list.

                if ( dwPageNumber <= dwTotalNumberOfPages )
                {
                    dwPageNumberForResetDC = dwPageNumber;
                }
                else
                {
                    
                    //
                    // Go to first non-empty logical page. 
                    // Note: Empty page means a blank page generated by print processor.
                    //
                    for ( pHeadMoving = pHeadLogical; pHeadMoving; pHeadMoving = pHeadMoving->pNextLogPage )
                    {
                        dwPageNumberForResetDC = pHeadMoving->dwPageNumber;
                        if ( dwPageNumberForResetDC > 0 && dwPageNumberForResetDC <= dwTotalNumberOfPages )
                        {
                            break; //Valid page number found.
                        }
                    } //for

                }

                if ( dwPageNumberForResetDC > 0 && dwPageNumberForResetDC <= dwTotalNumberOfPages )
                {


                    // Process devmodes in the spool file 
                    if (!ResetDCForNewDevmode(hSpoolHandle,
                                                 hPrinterDC,
                                                 pEMFAttr,
                                                 dwPageNumberForResetDC,
                                                 FALSE,
                                                 dwOptimization,
                                                 &bNewDevmode,
                                                 pDevmode,
                                                 &pCurrDM) ) 
                    {
                        goto CleanUp;
                    }
                }

                //
                // Lets do a startPage. This has to be done even if side is empty.
                //
                if ( !GdiStartPageEMF(hSpoolHandle)) {

                    ODS(("StartPage failed\nPrinter %ws\n", pDevmode->dmDeviceName));
                    goto CleanUp;
                }

                if (pCurrDM)
                    dmOrientation = pCurrDM->dmOrientation;
            }

            else if (dwNumberOfPagesPerSide > 1 && dwPageNumber <= dwTotalNumberOfPages)
            {
                // in case of orientation switch we need to keep track of what
                // we started with and what it is now
                if (GdiGetDevmodeForPagePvt(hSpoolHandle,
                                            dwPageNumber,
                                            &pCurrDM,
                                            NULL))
                {
                    if (pCurrDM && pCurrDM->dmOrientation != dmOrientation)
                    {
                        dwAngle = EMF_DEGREE_SWAP | EMF_DEGREE_90;
                        BUpdateAttributes(hPrinterDC, pEMFAttr);
                    }
                }
            }

            if ( dwPageNumber <= dwTotalNumberOfPages )
            {
                if (!PlayEMFPage(hSpoolHandle,
                                    hPrinterDC,
                                    hEMF,
                                    pEMFAttr,
                                    dwPageNumber,
                                    dwPageIndex,
                                    dwAngle)) {

                    ODS(("PlayEMFPage failed\nPrinter %ws\n", pDevmode->dmDeviceName));
                    goto CleanUp;
                }
            }
         }


        //
        // All pages on the side have been printed. If some sheets are blank
        // a StartPageEMF was sent but PlayEMFPage was not done.
        //
        if (!GdiEndPageEMF(hSpoolHandle, dwOptimization)) {
            ODS(("EndPage failed\nPrinter %ws\n", pDevmode->dmDeviceName));
            goto CleanUp;
        }

    } //for dwSides

    bReturn = TRUE;

CleanUp:

    return bReturn;
}


BOOL
PrintOneSideBookletEMF(
    HANDLE                hSpoolHandle,
    HDC                   hPrinterDC,
    PEMF_ATTRIBUTE_INFO   pEMFAttr,
    PPAGE_NUMBER          pHead,
    BOOL                  bDuplex,
    DWORD                 dwOptimization,
    LPDEVMODE             pDevmode)

/*++
Function Description: PrintOneSideBookletEMF prints one page of the booklet job.

Parameters: hSpoolHandle           -- handle the spool file handle
            hPrinterDC             -- handle to the printer device context
            pEMFAttr               -- Job Attributes
            pHead                  -- List of pages in the order in which they have to be printed.
            bDuplex                -- Whether duplex is supported in hardware
            dwOptimization         -- optimization flags
            pDevmode               -- devmode with resolution settings

Return Values:  TRUE if successful
                FALSE otherwise
--*/

{
    DWORD       dwPageIndex, dwAngle = 0, dwPageType, dwPageNumber;
    HANDLE      hEMF = NULL;
    LPDEVMODEW  pCurrDM;
    BOOL        bReturn = FALSE ,bNewDevmode;
    INT         dmOrientation;


    DWORD       dwSides;
    PPAGE_NUMBER pHeadLogical, pHeadMoving; 
    
    DWORD       dwNumberOfPagesPerSide    = pEMFAttr->dwNumberOfPagesPerSide;
    DWORD       dwDrvNumberOfPagesPerSide = pEMFAttr->dwDrvNumberOfPagesPerSide;
    DWORD       dwTotalNumberOfPages      = pEMFAttr->dwTotalNumberOfPages;
    BOOL        bReverseOrderPrinting     = pEMFAttr->bReverseOrderPrinting;
    DWORD       dwDuplexMode              = pEMFAttr->dwDuplexMode;
    BOOL        bDeviceNup                = dwDrvNumberOfPagesPerSide > 1 ? TRUE: FALSE; //hware supported nup
    DWORD       dwLimit                   = min(dwTotalNumberOfPages,dwDrvNumberOfPagesPerSide);


    if ( !pHead )
    {
        return TRUE;
    }

    //
    // There are 2 n-up options here. One is when the printer supports it
    // (dwDrvNumberOfPagesPerSide > 1) and the other is when print processor
    // simulates it (dwNumberOfPagesPerSide > 1). If both of them are
    // present, then it is an unexpected case. For the time being, I'll let
    // the printer n-up be superior.
    //
    if ( dwDrvNumberOfPagesPerSide > 1 ) //cud also hvae used bDeviceNup
    {
        if ( dwNumberOfPagesPerSide > 1)
        {
            ODS(("PrintOneSideBookletEMF... Both printer hardware n-up and simulated n-up present\n"));
        }
        dwNumberOfPagesPerSide           = dwDrvNumberOfPagesPerSide;
    }



    dwSides = bDuplex ? 2 : 1;


    //
    // Lets reset the devmode for the page number that is 
    // first in the pHead list. Note that sometimes,
    // this page number is larger than dwTotalNumberOfPages 
    // (to indicate an empty page).
    // Therefore, we need to keep moving pHead to next node
    // till we get a valid dwPageNumber
    //
    for ( pHeadMoving = pHead; pHeadMoving ; pHeadMoving = pHeadMoving->pNextSide) 
    {
        for ( pHeadLogical = pHeadMoving; pHeadLogical; pHeadLogical = pHeadLogical->pNextLogPage )
        {
            dwPageNumber = pHeadLogical->dwPageNumber;
            if ( dwPageNumber > 0 && dwPageNumber <= dwTotalNumberOfPages )
            {
                break; //Valid page number found.
            }
        }
        if ( pHeadLogical != NULL )
        {
            break;
        }
    }

    if ( pHeadMoving == NULL )
    {
        ODS (("pHeadMoving is NULL.\n"));
        return FALSE;
    }

    // Process devmodes in the spool file
    if (!ResetDCForNewDevmode(hSpoolHandle,
                              hPrinterDC,
                              pEMFAttr,
                              dwPageNumber,
                              FALSE,
                              dwOptimization,
                              &bNewDevmode,
                              pDevmode,
                              &pCurrDM)) {
        goto CleanUp;
    }
    if (pCurrDM)
        dmOrientation = pCurrDM->dmOrientation;
    else
        dmOrientation = pDevmode->dmOrientation;

    for (;  dwSides;  --dwSides, pHead = pHead->pNextSide) 
    {
        pHeadLogical = pHead;
        dwPageNumber = pHeadLogical->dwPageNumber;

        for (dwPageIndex = 1;
              ( (pHeadLogical != NULL) && (dwPageIndex <= dwNumberOfPagesPerSide));
              pHeadLogical = pHeadLogical->pNextLogPage, ++dwPageIndex) 
        {

            dwPageNumber = pHeadLogical->dwPageNumber;
            if ( dwPageNumber == 0 )
            {
                dwPageNumber = 0xFFFFFFFF; //some big number.
            }

            if (dwPageNumber <= dwTotalNumberOfPages) 
            {


                if (!(hEMF = GdiGetPageHandle(hSpoolHandle,
                                              dwPageNumber,
                                              &dwPageType))) 
                {
                     ODS(("GdiGetPageHandle failed\nPrinter %ws\n", pDevmode->dmDeviceName));
                     goto CleanUp;
                }
            }
            if (dwPageIndex == 1 || bDeviceNup) 
            {

                if (!GdiStartPageEMF(hSpoolHandle)) 
                {
                     ODS(("StartPage failed\nPrinter %ws\n", pDevmode->dmDeviceName));
                    goto CleanUp;
                }
            }

            //
            // Simulating n-up in print processor. Does not support 
            // device n-up.
            //
            if (dwPageNumber <= dwTotalNumberOfPages) 
            {
                dwAngle = 0; //reset it for every page.
            
                //
                // in case of orientation switch we need to keep track of what
                // we started with and what it is now
                //
                if (GdiGetDevmodeForPagePvt(hSpoolHandle,
                                            dwPageNumber,
                                            &pCurrDM,
                                            NULL))
                {
                    if (pCurrDM && pCurrDM->dmOrientation != dmOrientation)
                    {
                        dwAngle |= EMF_DEGREE_SWAP;
                        BUpdateAttributes(hPrinterDC, pEMFAttr);
                    }
                }

                //
                // For flip on long edge, the reverse side has to be rotated 180 degree
                // w.r.t. the 1st side
                //
                if ( (dwSides == 1) && (dwDuplexMode == EMF_DUP_VERT) )
                {
                    dwAngle |= EMF_DEGREE_270;
                    if ( bDeviceNup && (pDevmode->dmOrientation == DMORIENT_LANDSCAPE) )
                    {
                        dwAngle |= EMF_DEGREE_SWAP;
                    }

                } 
                else 
                { 
                    // EMF_DUP_HORZ or 1st side
                    dwAngle |= EMF_DEGREE_90;
                }

                if (!PlayEMFPage(hSpoolHandle,
                                  hPrinterDC,
                                  hEMF,
                                  pEMFAttr,
                                  dwPageNumber,
                                  dwPageIndex,
                                  dwAngle)) {

                     ODS(("PlayEMFPage failed\nPrinter %ws\n", pDevmode->dmDeviceName));
                     goto CleanUp;
                }
            }

            if (dwPageIndex == dwNumberOfPagesPerSide || bDeviceNup) {

                if (!GdiEndPageEMF(hSpoolHandle, dwOptimization)) {
                     ODS(("EndPage failed\nPrinter %ws\n", pDevmode->dmDeviceName));
                     goto CleanUp;
                }
            }

            if ( bDeviceNup && pHeadLogical == NULL && dwPageIndex<=dwLimit )
            {
                //
                // Suppose the n-up is 4 (dwLimit is 4) and the n-up is done by the device 
                // ( dwDrvNumberOfPagesPerSide > 1)
                // i.e. device needs 4 pages to finish printing a side and eject paper.
                // Suppose pHeadLogical list has only 2 pages (i.e. the pHeadLogical is now NULL after
                // going thru above loop).
                // So we need to send the printer 2 empty pages (logical pages)
                //
                BPlayEmptyPages(hSpoolHandle, pEMFAttr, (dwLimit-dwPageIndex+1), dwOptimization);
            }
       }
    }

    bReturn = TRUE;

CleanUp:

    return bReturn;
}


BOOL
PrintBookletEMF(
    HANDLE                hSpoolHandle,
    HDC                   hPrinterDC,
    PEMF_ATTRIBUTE_INFO   pEMFAttr,
    PPAGE_NUMBER          pHead,
    BOOL                  bDuplex,
    DWORD                 dwOptimization,
    LPDEVMODEW            pDevmode,
    PPRINTPROCESSORDATA   pData)

/*++
Function Description: PrintBookletEMF prints the job in 2-up in booklet form.

Parameters: hSpoolHandle           -- handle the spool file handle
            hPrinterDC             -- handle to the printer device context
            pEMFAttr               -- Job Attributes
            pHead                  -- List of pages in the order in which they have to be printed.
            bDuplex                -- 
            dwOptimization         -- optimization flags
            pDevmode               -- pointer to devmode for changing the copy count
            pData                  -- needed for status and the handle of the event: pause, resume etc.

Return Values:  TRUE if successful
                FALSE otherwise
--*/

{
    BOOL              bReturn = FALSE;
    DWORD             dwTotalPrintPages, dwNumberOfPhyPages, dwRemainingCopies, dwIndex;
    DWORD             dwTotalNumberOfPages = pEMFAttr->dwTotalNumberOfPages;
    BOOL              bCollate             = pEMFAttr->bCollate;
    DWORD             dwJobNumberOfCopies  = pEMFAttr->dwJobNumberOfCopies;
    DWORD             dwDrvNumberOfCopies  = pEMFAttr->dwDrvNumberOfCopies;

    if (!pHead) {
        bReturn = TRUE;
        goto CleanUp;
    }

    while (pHead)
    {

         //
         // If the print processor is paused, wait for it to be resumed
         //
         if (pData->fsStatus & PRINTPROCESSOR_PAUSED) {
                WaitForSingleObject(pData->semPaused, INFINITE);
         }

         if (bCollate) {

            if (!PrintOneSideBookletEMF(hSpoolHandle,
                                        hPrinterDC,
                                        pEMFAttr,
                                        pHead,
                                        bDuplex,
                                        dwOptimization,
                                        pDevmode)) {
                 goto CleanUp;
            }

         } else {

            dwRemainingCopies = dwJobNumberOfCopies;

            while (dwRemainingCopies) {

                if (dwRemainingCopies <= dwDrvNumberOfCopies) {
                   SetDrvCopies(hPrinterDC, pDevmode, dwRemainingCopies);
                   dwRemainingCopies = 0;
                } else {
                   SetDrvCopies(hPrinterDC, pDevmode, dwDrvNumberOfCopies);
                   dwRemainingCopies -= dwDrvNumberOfCopies;
                }

                if (!PrintOneSideBookletEMF(hSpoolHandle,
                                            hPrinterDC,
                                            pEMFAttr,
                                            pHead,
                                            bDuplex,
                                            dwOptimization,
                                            pDevmode)) {
                     goto CleanUp;
                }
            }
        }

        pHead = pHead->pNextSide;

        //
        // go to the next page for duplex printing
        //
        if (bDuplex && pHead) {
            pHead = pHead->pNextSide;
        }

    }

    bReturn = TRUE;

CleanUp:

    return bReturn;
}

BOOL
PrintEMFSingleCopy(
    HANDLE                hSpoolHandle,
    HDC                   hPrinterDC,
    PEMF_ATTRIBUTE_INFO   pEMFAttr,
    PPAGE_NUMBER          pHead,
    BOOL                  bOdd,
    DWORD                 dwOptimization,
    LPDEVMODEW            pDevmode,
    PPRINTPROCESSORDATA   pData)

/*++
Function Description: PrintEMFSingleCopy plays one copy of the job on hPrinterDC.

Parameters: hSpoolHandle           -- handle the spool file handle
            hPrinterDC             -- handle to the printer device context
            pEMFAttr               -- Job Attributes
            pHead                  -- pointer to a linked list containing the starting
                                       page numbers for each of the sides
                                      (valid for booklet,reverse printing) 
            bOdd                   -- flag to indicate odd number of sides to print
            dwOptimization         -- optimization flags
            pDevmode               -- pointer to devmode for changing the copy count
            pData                  -- needed for status and the handle of the event: pause, resume etc.

Return Values:  TRUE if successful
                FALSE otherwise
--*/

{
    /*++
            dwDrvNumberOfPagesPerSide -- number of pages the driver will print per side
            dwNumberOfPagesPerSide -- number of pages to be printed per side by the print
                                       processor
            dwTotalNumberOfPages   -- number of pages in the document
            bCollate               -- flag for collating the copies
            bBookletPrint          -- flag for booklet printing
            dwDuplexMode           -- duplex printing mode (none|horz|vert)
    --*/
    BOOL  bReverseOrderPrinting      = pEMFAttr->bReverseOrderPrinting;
    BOOL  bBookletPrint              = pEMFAttr->bBookletPrint;
    DWORD dwDuplexMode               = pEMFAttr->dwDuplexMode;

    BOOL  bDuplex = (dwDuplexMode != EMF_DUP_NONE);


    if (bBookletPrint || bReverseOrderPrinting) {

          // Reverse printing and nup
          return PrintEMFInPredeterminedOrder(hSpoolHandle,
                                 hPrinterDC,
                                 pEMFAttr,
                                 pHead,
                                 bDuplex,
                                 bOdd,
                                 dwOptimization,
                                 pDevmode,
                                 pData);
    } else {

       // Normal printing
       return PrintForwardEMF(hSpoolHandle,
                              hPrinterDC,
                              pEMFAttr,
                              bDuplex,
                              dwOptimization,
                              pDevmode,
                              pData);
    }
}

BOOL
GetStartPageListBooklet(
    HANDLE                 hSpoolHandle,
    PEMF_ATTRIBUTE_INFO    pEMFAttr,
    PPAGE_NUMBER          *ppMemoryHead,
    PPAGE_NUMBER          *ppPageListHead,
    BOOL                   bCheckForDevmode,
    LPBOOL                 pbOdd)

/*++
Function Description: GetStartPageListBooklet generates an ordered list of page numbers which
                      should appear on each side of the job. This takes
                      into consideration the ResetDC calls that may appear before the
                      end of the page. The list generated by GetStartPageListBooklet is used
                      to play the job in BookletMode. 

Parameters: hSpoolHandle           -- handle the spool file handle
            ppPageListHead         -- pointer to a pointer to a linked list containing the
                                       starting page numbers for each of the sides
            ppMemoryHead           -- pointer to pointer to memory that has to be releazed by 
                                      calling function after it is done processing the pages in
                                      ppPageListHead
            pbOdd                  -- pointer to flag indicating odd number of pages to
                                       print

Return Values:  TRUE if successful
                FALSE otherwise
--*/

{
    DWORD        dwPageIndex,dwPageNumber=1,dwPageType;
    PPAGE_NUMBER pMemoryHead   = NULL;
    PPAGE_NUMBER pHeadMoving   = NULL;
    PPAGE_NUMBER pHeadPrevious = NULL, pHeadNext = NULL;
    BOOL         bReturn       = FALSE;
    BOOL         bCheckDevmode;
    DWORD        dwTotalSheets;
    DWORD        dwMaxLogicalPages; // = dwTotalSheets * 4.
    DWORD        dwTempPageNumber;


    DWORD        dwTotalNumberOfPages  = pEMFAttr->dwTotalNumberOfPages;
    EBookletMode eBookletMode          = pEMFAttr->eBookletMode;
    BOOL         bReverseOrderPrinting = pEMFAttr->bReverseOrderPrinting; 
    DWORD        dwDuplexMode          = pEMFAttr->dwDuplexMode;
    ULONG        ulNodeNumber          = 0;


    //
    // Total number of pages in the job should have been initialized properly.
    // Also ppHead should be valid.
    //
    if ( dwTotalNumberOfPages == 0          || 
         dwTotalNumberOfPages == 0xFFFFFFFF ||
         ppMemoryHead         == NULL       ||
         ppPageListHead       == NULL   )
    {
        ODS(("Parameters to GetStartPageListBooklet are not proper.\n"));
        return FALSE;
    }

    //
    // 1) Booklet printing needs some special page ordering.
    // 2) The n-up is always 2. 
    // 3) There are 2 n-up options. One is when the printer supports it 
    // (dwDrvNumberOfPagesPerSide) and the other is when print processor
    // simulates it (dwNumberOfPagesPerSide). If both of them are 
    // present, then it is an unexpected case. For the time being, I'll let
    // the printer n-up be superior.
    //

    //
    // Assume dwTotalSheets is the minimum number of sheets required for doing booklet
    // We print 2 logical pages on each side and we print on
    // both sides. i.e. on a single sheet of paper we print 4 logical
    // pages. So let dwMaxLogicalPages = dwTotalSheets*4.
    // Not all the dwMaxLogicalPages need to be printed (e.g a book can have 3 pages,
    // the 4th page is just empty page).
    // So we need a linked list with dwMaxLogicalPages nodes. 
    //
    // The book can be left edge binding (for latin and most other languages)
    // or right edge binding (for hebrew).
    //

    dwTotalSheets = dwTotalNumberOfPages/4;
    if ( dwTotalSheets * 4 != dwTotalNumberOfPages )
    {
        dwTotalSheets++;
    }
    dwMaxLogicalPages = dwTotalSheets*4;

    //
    // AllocSplMem initializes the memory to 0.
    //
    if (!(pMemoryHead = (PPAGE_NUMBER)AllocSplMem( dwMaxLogicalPages * sizeof(PAGE_NUMBER)))) {
        ODS(("GetStartPageListBooklet - Run out of memory"));
        goto CleanUp;
    }

    //
    // Now lets start populating the linked list.
    // For booklet printing of 11 pages, we need 3 sheets. The ordering is
    // (Assuming left edge binding)
    // blank (page 12), 1 - first sheet
    // 11, 2              - back of 1st sheet
    // 10,3               - second sheet
    // 9 ,4               - back of 2nd sheet
    // 8 ,5               - third sheet
    // 7, 6               - back of 3rd sheet.
    // 
    // The following loop arranges page numbers. The arrangement can be visualized
    // as follows. (for left edge binding, job with 7 pages, to be printed on 2 sheets).
    // pages 8,1 on 1st side 1st sheet
    // pages 7,2 on reverse side of 1st sheet.
    // pages 6,3 on 1st side of 2nd sheet.
    // pages 5,4 on reverse side of 2nd sheet.
    //
    //                  -----------------------------------(pNextSide)
    //                  |
    //                  |
    // *ppPageListHead  |
    //        |         |
    //       \/        \/
    //        8 --> 7  --->6 ----> 5
    //        |     |      |       |  <---- (pNextLogicalPage)
    //       \/    \/      \/      \/
    //        1     2      3       4
    //

    *ppPageListHead = pHeadMoving = pMemoryHead;

    if ( eBookletMode == kNoBooklet ||
         eBookletMode == kBookletLeftEdge)
    {

        for ( ulNodeNumber = 0 ; ulNodeNumber < dwMaxLogicalPages/2; ulNodeNumber++)
        {
            pHeadMoving->dwPageNumber = dwMaxLogicalPages - ulNodeNumber;
            pHeadMoving->pNextLogPage = pHeadMoving + 1;
            pHeadMoving->pNextSide    = pHeadMoving + 2;
            pHeadMoving++; 

            pHeadMoving->dwPageNumber = ulNodeNumber+1;
            pHeadMoving->pNextSide = NULL;
            pHeadMoving->pNextLogPage = NULL;
            pHeadMoving++; 
        }
        (pHeadMoving-2)->pNextSide = NULL;
    }
    else if ( eBookletMode == kBookletRightEdge ) //Right Edge binding.
    {
        for ( ulNodeNumber = 0 ; ulNodeNumber < dwMaxLogicalPages/2; ulNodeNumber++)
        {
            pHeadMoving->dwPageNumber = ulNodeNumber+1;
            pHeadMoving->pNextLogPage = pHeadMoving + 1; 
            pHeadMoving->pNextSide    = pHeadMoving + 2;
            pHeadMoving++;

            pHeadMoving->dwPageNumber = dwMaxLogicalPages - ulNodeNumber;
            pHeadMoving->pNextSide    = NULL;
            pHeadMoving->pNextLogPage = NULL; 
            pHeadMoving++;
        }
        (pHeadMoving-2)->pNextSide = NULL;
    }


    //
    // The above list is arranged for out-to-in printing, so to make it work for
    // in-to-out, we'll need to reverse it. There is no option in the UI for
    // in-to-out or out-to-in. So let's re-use the forward/reverse printing option.
    //

    if ( bReverseOrderPrinting )
    {
        //
        // Go through the linked list above and start reversing the pointers.
        // After this loop is done, the list will look like 
        // (for a 7 page job with kBookletLeftEdge )
        //                  -----------------------------------(pNextSide)
        //                  |
        //                  | 
        // *ppPageListHead  | 
        //        |         | 
        //       \/        \/ 
        //        5 --> 6  --->7 ----> 8 
        //        |     |      |       |  <---- (pNextLogicalPage)
        //       \/    \/      \/      \/ 
        //        4     3      2       1  
        //
        pHeadMoving = *ppPageListHead; 
        pHeadPrevious = NULL;
        for ( ;pHeadMoving != NULL; )
        {
            pHeadNext = pHeadMoving->pNextSide;
            pHeadMoving->pNextSide = pHeadPrevious;
            pHeadPrevious = pHeadMoving;
            pHeadMoving = pHeadNext;
        }
        *ppPageListHead = pHeadPrevious;        
    }


    if ( dwDuplexMode == EMF_DUP_HORZ ) //Flip on Short Edge.
    {
        //
        // The pages need to be re-arranged as follows.
        // If the pages are not flipped, the printout is not proper.
        // The sheet that has the first page should not be flipped.
        // For Forward printing, the *ppPageListHead points to the first 
        // logical page. So we start switching from *ppPageListHead->pNextSide
        // For Reverse Printing, *ppPageListHead points to the last sheet.'
        // The first sheet has the logical page number 1. There are even 
        // logical pages (numofsheets * 4) and therefore there are even sides
        // ( (numofsheets * 4)/2). The last side has page number 1. This side
        // cannot be switched. So we have to start switching right from 
        // *ppPageListHead.
        // 
        pHeadMoving = *ppPageListHead;
        if ( !bReverseOrderPrinting )
        {
        
            //                  -----------------------------------(pNextSide)
            //                  |
            //                  |
            // *ppPageListHead  |
            //        |         |
            //       \/        \/
            //        8 --> 2  --->6 ----> 4
            //        |     |      |       |  <---- (pNextLogicalPage)
            //       \/    \/      \/      \/
            //        1     7      3       5
            // Note pages 2,7 have been flipped, and so have 4,5
            //
            while ( pHeadMoving && pHeadMoving->pNextSide )
            {
                pHeadMoving                 = pHeadMoving->pNextSide;
                if ( pHeadMoving->pNextLogPage )
                {
                    dwTempPageNumber            = pHeadMoving->dwPageNumber;
                    pHeadMoving->dwPageNumber   = pHeadMoving->pNextLogPage->dwPageNumber;
                    pHeadMoving->pNextLogPage->dwPageNumber = dwTempPageNumber;
                }
                
                pHeadMoving = pHeadMoving->pNextSide;
            }
        }
        else
        {

            //                  -----------------------------------(pNextSide)
            //                  |
            //                  |
            // *ppPageListHead  |
            //        |         |
            //       \/        \/
            //        4 --> 6  --->2 ----> 8
            //        |     |      |       |  <---- (pNextLogicalPage)
            //       \/    \/      \/      \/
            //        5     3      7       1
            // Note pages 2,7 have been flipped, and so have 4,5
            //
            while ( pHeadMoving )
            {
                if ( pHeadMoving->pNextLogPage )
                {
                    dwTempPageNumber            = pHeadMoving->dwPageNumber;
                    pHeadMoving->dwPageNumber   = pHeadMoving->pNextLogPage->dwPageNumber;
                    pHeadMoving->pNextLogPage->dwPageNumber = dwTempPageNumber;
                }

                if ( pHeadMoving ->pNextSide )
                {
                    pHeadMoving = pHeadMoving->pNextSide->pNextSide;
                }
            } //end of while
        }
    }


    bReturn = TRUE;

CleanUp:

    if ( bReturn == FALSE )
    {
        if ( pMemoryHead == NULL )
        {
            FreeSplMem (pMemoryHead);
            *ppMemoryHead   = NULL;
            *ppPageListHead = NULL;
        }
    }

    return bReturn;
}

BOOL
GetStartPageListReverseOrder(
    HANDLE                 hSpoolHandle,
    PEMF_ATTRIBUTE_INFO    pEMFAttr,
    PPAGE_NUMBER          *ppMemoryHead,
    PPAGE_NUMBER          *ppPageListHead,
    BOOL                   bCheckForDevmode,
    LPBOOL                 pbOdd)

/*++
Function Description: 
    GetStartPageListReverseOrder generates a list of the page numbers which
    should appear on the start of each side of the job. This takes
    into consideration the ResetDC calls that may appear before the
    end of the page. The list generated by GetStartPageListReverseOrder is used
    to play the job in reverse order.

Parameters: 
    hSpoolHandle           -- handle the spool file handle
    ppHead                 -- pointer to a pointer to a linked list containing the
                               starting page numbers for each of the sides
    dwTotalNumberOfPages   -- number of pages in the document
    dwNumberOfPagesPerSide -- number of pages to be printed per side by the print
                              processor
    pbOdd                  -- pointer to flag indicating odd number of pages to
                              print

Return Values:  TRUE if successful
                FALSE otherwise
--*/

{


    DWORD        dwPageIndex,dwPageNumber=1,dwPageType;
    LPDEVMODEW   pCurrDM, pLastDM = NULL;
    PPAGE_NUMBER pHeadMoving  = NULL; //moves thru the list.
    PPAGE_NUMBER pHeadNewSide = NULL; //ptr keeps track of new sides.
    PPAGE_NUMBER pNewLogicalPage = NULL; //ptr keeps track of next logical page on each side.
    BOOL         bReturn = FALSE;
    BOOL         bCheckDevmode = FALSE;
    DWORD        dwTotalNumberOfPages      = pEMFAttr->dwTotalNumberOfPages;
    DWORD        dwNumberOfPagesPerSide    = pEMFAttr->dwNumberOfPagesPerSide;
    DWORD        dwDrvNumberOfPagesPerSide = pEMFAttr->dwDrvNumberOfPagesPerSide;
    DWORD        dwDuplexMode              = pEMFAttr->dwDuplexMode;
    ULONG        ulNumNodes = 0;
    DWORD        dwMaxLogicalPagesPerSheet = 1;
    DWORD        dwTotalSheets = 0;
    DWORD        dwMaxLogicalPages = 0; 

    //
    // This function assumes that dwTotalNumberOfPages is set to a valid
    // value. 
    //
    if ( dwTotalNumberOfPages == 0 ||
         dwTotalNumberOfPages == 0xFFFFFFFF ||
         ppMemoryHead         == NULL       ||
         ppPageListHead       == NULL    )
    {
        return FALSE;
    }

    *ppMemoryHead = NULL;
    *ppPageListHead = NULL;

    //
    // There are 2 n-up options here. One is when the printer supports it 
    // (dwDrvNumberOfPagesPerSide) and the other is when print processor
    // simulates it (dwNumberOfPagesPerSide). If both of them are 
    // present, then it is an unexpected case. For the time being, I'll let
    // the printer n-up be superior.
    //
    if ( dwDrvNumberOfPagesPerSide > 1 )
    {
        if ( dwNumberOfPagesPerSide > 1)
        {
            ODS(("GetStartPageListReverseOrder..Both printer hardware n-up and simulated n-up present\n"));
        }
        dwNumberOfPagesPerSide           = dwDrvNumberOfPagesPerSide;
    }

    bCheckDevmode = bCheckForDevmode && (dwNumberOfPagesPerSide != 1);

    //
    // First see how many sheets of paper will be required. Some examples are.
    // Cond. Id       Condition.              Sheets required.
    // --------     ---------------         -------------------
    // 1.          5 pg, 1-up, no duplex        5
    // 2.          5 pg, 2-up, no duplex        3
    // 3.          5 pg, 2-up, duplex           2
    // 4.          7 pg, 4-up, duplex           1
    //
    // If dwDuplexMode is not zero, i.e. duplex is on, then we can fit double pages per sheet of paper.

    dwMaxLogicalPagesPerSheet = dwNumberOfPagesPerSide * ( (dwDuplexMode == EMF_DUP_NONE) ?1:2);
    dwTotalSheets = dwTotalNumberOfPages/dwMaxLogicalPagesPerSheet;
    if ( dwTotalSheets * dwMaxLogicalPagesPerSheet != dwTotalNumberOfPages )
    {
        dwTotalSheets++;
    }
    dwMaxLogicalPages = dwTotalSheets * dwMaxLogicalPagesPerSheet;

    //
    // allocate the memory for all logical pages. AllocSplMem also zero inits it.
    //
    if (!(pHeadMoving = (PPAGE_NUMBER)AllocSplMem( dwMaxLogicalPages * sizeof(PAGE_NUMBER) )))    
    {
        ODS(("GetStartPageListBooklet - Run out of memory"));
        goto CleanUp;
    }

    *ppMemoryHead     = pHeadMoving;
    pHeadMoving += (dwMaxLogicalPages - 1) ; //Go to the last block.
    pHeadNewSide = NULL;

    //
    // The following loop will arrange pages as below.
    // Assuming 
    //      1) 5 pages with 2-up 
    //      2) DifferentDevmodes() always fails.
    //
    //
    //                  ------------------pNextSide
    //                  |
    //                  |
    //                  \/
    //     7 -->  5  -->  3  -->  1
    //     |      |       |       |  <-- pNextLogicalPage
    //     |      |       |       |
    //     \/     \/      \/      \/
    //     8      6       4       2
    //
    // Pages 7,8,6 are marked but they should be treated as empty pages.
    // since maximum pages are 5.
    //



    //
    // While loop advances a side of the sheet.
    //
    while (dwPageNumber <= dwMaxLogicalPages && pHeadMoving >= *ppMemoryHead) {

        //
        // For loop fills in information for each page in the side.
        //
       for (dwPageIndex = 1;
            (dwPageIndex <= dwNumberOfPagesPerSide) && (dwPageNumber <= dwMaxLogicalPages);
            ++dwPageIndex, ++dwPageNumber) 
       {

            if (bCheckDevmode && (dwPageNumber <= dwTotalNumberOfPages) ) 
            {

                // Check if the devmode has changed requiring a new page
                 if (!GdiGetDevmodeForPagePvt(hSpoolHandle, dwPageNumber,
                                               &pCurrDM, NULL)) {
                     ODS(("Get devmodes failed\n"));
                     goto CleanUp;
                 }

                 if (dwPageIndex == 1) {
                     // Save the Devmode for the first page on a side
                     pLastDM = pCurrDM;
    
                 } else {
                     // If the Devmode changes in a side, start a new page
                        if (DifferentDevmodes(pCurrDM, pLastDM)) {
    
                            dwPageIndex = 1;
                            pLastDM = pCurrDM;
                        }
                }
            } //if (bCheckDevmode)

            // Create a node for the start of a side
            if (dwPageIndex == 1) 
            {

                //
                // A new side starts here. i.e. this page has to
                // be printed on a new side.
                //

                pHeadMoving->dwFlags      = NEW_PHYSICAL_SIDE; 
                pHeadMoving->pNextSide    = pHeadNewSide;
                pHeadNewSide              = pHeadMoving;
                ulNumNodes++;

                // flip the bOdd flag
                *pbOdd = !*pbOdd;
            }
            else
            {
                //
                // This is a new logical page to be printed
                // on the same side as the previous logical page.
                //
                (pHeadMoving+1)->pNextLogPage = pHeadMoving;
            }

            //
            // Note page number here can exceed max pages in the document (dwTotalNumberOfPages).
            // The max. page possible here is dwMaxLogicalPages which can be 
            // greater than dwTotalNumberOfPages. e.g. in cond 2 above, dwTotalNumberOfPages = 5
            // but dwMaxLogicalPages = 6. 
            //
            pHeadMoving->dwPageNumber = dwPageNumber; 
    
            pHeadMoving--;
        } //end of for.

     } //end of while

    *ppPageListHead = pHeadNewSide;

    bReturn = TRUE;

CleanUp:

    return bReturn;
}


BOOL
CopyDevmode(
    PPRINTPROCESSORDATA pData,
    LPDEVMODEW *pDevmode)

/*++
Function Description: Copies the devmode in pData or the default devmode into pDevmode.

Parameters:   pData           - Data structure for the print job
              pDevmode        - pointer to devmode

Return Value:  TRUE  if successful
               FALSE otherwise
--*/

{
    HANDLE           hDrvPrinter = NULL;
    BOOL             bReturn = FALSE;
    fnWinSpoolDrv    fnList;
    LONG             lNeeded;
    HMODULE          hWinSpoolDrv = NULL;

    if (pData->pDevmode) {

        lNeeded = pData->pDevmode->dmSize +  pData->pDevmode->dmDriverExtra;

        if (*pDevmode = (LPDEVMODEW) AllocSplMem(lNeeded)) {
            memcpy(*pDevmode, pData->pDevmode, lNeeded);
        } else {
            goto CleanUp;
        }

    } else {
        // Get the default devmode

        ZeroMemory ( &fnList, sizeof (fnWinSpoolDrv) );

        //
        // Get the pointers to the client side functions. 
        //

        if (!(hWinSpoolDrv = LoadLibrary(TEXT("winspool.drv")))) 
        {
           // Could not load the client side of the spooler
           goto CleanUp;
        }

        fnList.pfnOpenPrinter        = (BOOL (*)(LPTSTR, LPHANDLE, LPPRINTER_DEFAULTS))
                                            GetProcAddress( hWinSpoolDrv,"OpenPrinterW" );

        fnList.pfnClosePrinter       = (BOOL (*)(HANDLE))
                                            GetProcAddress( hWinSpoolDrv,"ClosePrinter" );


        fnList.pfnDocumentProperties = (LONG (*)(HWND, HANDLE, LPWSTR, PDEVMODE, PDEVMODE, DWORD))
                                             GetProcAddress( hWinSpoolDrv,"DocumentPropertiesW" );

        if ( NULL == fnList.pfnOpenPrinter   ||
             NULL == fnList.pfnClosePrinter  ||
             NULL == fnList.pfnDocumentProperties )
        {
            goto CleanUp;
        }

        // Get a client side printer handle to pass to the driver
        if (!(* (fnList.pfnOpenPrinter))(pData->pPrinterName, &hDrvPrinter, NULL)) {
            ODS(("Open printer failed\nPrinter %ws\n", pData->pPrinterName));
            goto CleanUp;
        }

        lNeeded = (* (fnList.pfnDocumentProperties))(NULL,
                                                     hDrvPrinter,
                                                     pData->pPrinterName,
                                                     NULL,
                                                     NULL,
                                                     0);

        if (lNeeded <= 0  ||
            !(*pDevmode = (LPDEVMODEW) AllocSplMem(lNeeded)) ||
            (* (fnList.pfnDocumentProperties))(NULL,
                                               hDrvPrinter,
                                               pData->pPrinterName,
                                               *pDevmode,
                                               NULL,
                                               DM_OUT_BUFFER) < 0) {

             if (*pDevmode) {
                FreeSplMem(*pDevmode);
                *pDevmode = NULL;
             }

             ODS(("DocumentProperties failed\nPrinter %ws\n",pData->pPrinterName));
             goto CleanUp;
        }
    }

    bReturn = TRUE;

CleanUp:

    if (hDrvPrinter) {
        (* (fnList.pfnClosePrinter))(hDrvPrinter);
    }

    if ( hWinSpoolDrv )
    {
        FreeLibrary (hWinSpoolDrv);
        hWinSpoolDrv = NULL;
    }

    return bReturn;
}

BOOL
PrintEMFJob(
    PPRINTPROCESSORDATA pData,
    LPWSTR pDocumentName)

/*++
Function Description: Prints out a job with EMF data type.

Parameters:   pData           - Data structure for this job
              pDocumentName   - Name of this document

Return Value:  TRUE  if successful
               FALSE if failed - GetLastError() will return reason.
--*/

{
    HANDLE             hSpoolHandle = NULL;
    DWORD              LastError = ERROR_SUCCESS;
    HDC                hPrinterDC = NULL;

    BOOL               bReverseOrderPrinting, bReturn = FALSE, bSetWorldXform = TRUE;
    BOOL               bCollate, bDuplex, bBookletPrint, bStartDoc = FALSE, bOdd = FALSE;
    BOOL               bUpdateAttributes = FALSE;
    SHORT              dmCollate,dmCopies;

    DWORD              dwJobNumberOfPagesPerSide,dwDrvNumberOfCopies;
    DWORD              dwDrvNumberOfPagesPerSide;
    DWORD              dwJobNumberOfCopies, dwRemainingCopies;
    DWORD              dwTotalNumberOfPages, dwNupBorderFlags, dwPoster, dwDuplexMode, dwNumberOfPagesPerSide;
    DWORD              dwJobOrder, dwDrvOrder, dwOptimization;

    DOCINFOW           DocInfo;
    XFORM              OldXForm;
    PPAGE_NUMBER       pMemoryHead = NULL, pPageListHead = NULL;
    ATTRIBUTE_INFO_3   AttributeInfo;
    LPDEVMODEW         pDevmode = NULL, pFirstDM = NULL, pCopyDM;
    EMF_ATTRIBUTE_INFO EMFAttr;
    ENupDirection      eNupDirection  = kRightThenDown; //Default.
    EBookletMode       eBookletMode   = kNoBooklet;
    DWORD              dwMultiPartJob = 0;


    memset(&EMFAttr, 0, sizeof(EMF_ATTRIBUTE_INFO));
    EMFAttr.dwTotalNumberOfPages = 0xFFFFFFFF; //since this attribute is not always 
                                               //valid, 0xfffffff means uninitialized.
    EMFAttr.dwSignature  = EMF_ATTRIBUTE_INFO_SIGNATURE;


    // Copy the devmode into pDevMode
    if (!CopyDevmode(pData, &pDevmode)) {

        ODS(("CopyDevmode failed\nPrinter %ws\nDocument %ws\nJobID %u\n", pData->pDevmode->dmDeviceName, pData->pDocument, pData->JobId));
        goto CleanUp;
    }

    if ( ! BIsDevmodeOfLeastAcceptableSize (pDevmode) )
    {
        ODS(("Devmode not big enough. Failing job.\nPrinter %ws\nDocument %ws\nJobID %u\n", pData->pDevmode->dmDeviceName, pData->pDocument, pData->JobId));
        goto CleanUp;
    }

    // Update resolution before CreateDC for monochrome optimization
    if (!GetJobAttributes(pData->pPrinterName,
                          pDevmode,
                          &AttributeInfo)) {
        ODS(("GetJobAttributes failed\nPrinter %ws\nDocument %ws\nJobID %u\n", pData->pDevmode->dmDeviceName, pData->pDocument, pData->JobId));
        goto CleanUp;
    } else {
        if (AttributeInfo.dwColorOptimization) 
        {
            if (pDevmode->dmPrintQuality != AttributeInfo.dmPrintQuality ||
                pDevmode->dmYResolution != AttributeInfo.dmYResolution)
            {
                pDevmode->dmPrintQuality =  AttributeInfo.dmPrintQuality;
                pDevmode->dmYResolution =  AttributeInfo.dmYResolution;
                bUpdateAttributes = TRUE;
            }
        }
        if (pDevmode->dmFields & DM_COLLATE)
            dmCollate = pDevmode->dmCollate;
        else
            dmCollate = DMCOLLATE_FALSE;

        if (pDevmode->dmFields & DM_COPIES)
            dmCopies = pDevmode->dmCopies;
        else
            dmCopies = 0;
    }

    // Get spool file handle and printer device context from GDI
    __try {

        hSpoolHandle = GdiGetSpoolFileHandle(pData->pPrinterName,
                                             pDevmode,
                                             pDocumentName);
        if (hSpoolHandle) {
            hPrinterDC = GdiGetDC(hSpoolHandle);
        }

    } __except (EXCEPTION_EXECUTE_HANDLER) {

        ODS(("PrintEMFJob gave an exceptionPrinter %ws\nDocument %ws\nJobID %u\n", pData->pDevmode->dmDeviceName, pData->pDocument, pData->JobId));
        goto CleanUp;
    }

    if (!hPrinterDC || !hSpoolHandle) {
        goto CleanUp;
    }


    EMFAttr.lXResolution = GetDeviceCaps(hPrinterDC, LOGPIXELSX); //dpi in x direction.
    EMFAttr.lYResolution = GetDeviceCaps(hPrinterDC, LOGPIXELSY); //dpi in y direction.
    EMFAttr.lXPrintArea  = GetDeviceCaps(hPrinterDC, DESKTOPHORZRES);//numpixels in printable area in x direction.
    EMFAttr.lYPrintArea  = GetDeviceCaps(hPrinterDC, DESKTOPVERTRES);//numpixels in printable area in y direction


    //
    // Use the first devmode in the spool file to update the copy count
    // and the collate setting
    //
    if (GdiGetDevmodeForPagePvt(hSpoolHandle, 1, &pFirstDM, NULL) &&
        pFirstDM) {

        if (pFirstDM->dmFields & DM_COPIES) {
            pDevmode->dmFields |= DM_COPIES;
            pDevmode->dmCopies = pFirstDM->dmCopies;
        }
        if ( (pFirstDM->dmFields & DM_COLLATE) && 
             IS_DMSIZE_VALID ( pDevmode, dmCollate) )
        {
            pDevmode->dmFields |= DM_COLLATE;
            pDevmode->dmCollate = pFirstDM->dmCollate;
        }
    }

    // The number of copies of the print job is the product of the number of copies set
    // from the driver UI (present in the devmode) and the number of copies in pData struct
    dwJobNumberOfCopies = (pDevmode->dmFields & DM_COPIES) ? pData->Copies*pDevmode->dmCopies
                                                           : pData->Copies;
    pDevmode->dmCopies = (short) dwJobNumberOfCopies;
    pDevmode->dmFields |=  DM_COPIES;

    // If collate is true this limits the ability of the driver to do multiple copies
    // and causes the driver (PS) supported n-up to print blank page borders for reverse printing.
    // Therefore we disable collate for 1 page multiple copy jobs or no copies but n-up since
    // collate has no meaning in those cases.
    //
    if ((pDevmode->dmFields & DM_COLLATE) && pDevmode->dmCollate == DMCOLLATE_TRUE)
    {
        if (dwJobNumberOfCopies > 1)
        {
            // Get the number of pages in the job. This call waits till the
            // last page is spooled.
            __try {

                dwTotalNumberOfPages = GdiGetPageCount(hSpoolHandle);

            } __except (EXCEPTION_EXECUTE_HANDLER) {

                ODS(("PrintEMFJob gave an exceptionPrinter %ws\nDocument %ws\nJobID %u\n", pData->pDevmode->dmDeviceName, pData->pDocument, pData->JobId));
                goto SkipCollateDisable;
            }
            if (dwTotalNumberOfPages > AttributeInfo.dwDrvNumberOfPagesPerSide)
                goto SkipCollateDisable;

        }
        // if copies == 1 and driver n-up we will disable collate
        //
        else if (AttributeInfo.dwDrvNumberOfPagesPerSide <= 1 && dmCollate == DMCOLLATE_TRUE)
            goto SkipCollateDisable;

        pDevmode->dmCollate = DMCOLLATE_FALSE;
        if (pFirstDM && 
            IS_DMSIZE_VALID ( pFirstDM, dmCollate) )
        {
            pFirstDM->dmCollate = DMCOLLATE_FALSE;
        }
    }
SkipCollateDisable:
    // Update the job attributes but only if something has changed. This is an expensive
    // call so we only make a second call to GetJobAttributes if something has changed.
    //
    if (bUpdateAttributes || pDevmode->dmCopies != dmCopies ||
            ((pDevmode->dmFields & DM_COLLATE) && (pDevmode->dmCollate != dmCollate)))
    {
        if (!GetJobAttributes(pData->pPrinterName,
                          pDevmode,
                          &AttributeInfo)) {
            ODS(("GetJobAttributes failed\nPrinter %ws\nDocument %ws\nJobID %u\n", pData->pDevmode->dmDeviceName, pData->pDocument, pData->JobId));
            goto CleanUp;
        }
    }

    // Initialize bReverseOrderPrinting, dwJobNumberOfPagesPerSide,
    // dwDrvNumberOfPagesPerSide, dwNupBorderFlags, dwJobNumberOfCopies,
    // dwDrvNumberOfCopies and bCollate

    dwJobNumberOfPagesPerSide = AttributeInfo.dwJobNumberOfPagesPerSide;
    dwDrvNumberOfPagesPerSide = AttributeInfo.dwDrvNumberOfPagesPerSide;
    dwNupBorderFlags          = AttributeInfo.dwNupBorderFlags;
    dwJobNumberOfCopies       = AttributeInfo.dwJobNumberOfCopies;
    dwDrvNumberOfCopies       = AttributeInfo.dwDrvNumberOfCopies;

    dwJobOrder                = AttributeInfo.dwJobPageOrderFlags & ( NORMAL_PRINT | REVERSE_PRINT);
    dwDrvOrder                = AttributeInfo.dwDrvPageOrderFlags & ( NORMAL_PRINT | REVERSE_PRINT);
    bReverseOrderPrinting     = (dwJobOrder != dwDrvOrder);

    dwJobOrder                = AttributeInfo.dwJobPageOrderFlags & BOOKLET_PRINT;
    dwDrvOrder                = AttributeInfo.dwDrvPageOrderFlags & BOOKLET_PRINT;
    bBookletPrint             = (dwJobOrder != dwDrvOrder);

    EMFAttr.bCollate          = (pDevmode->dmFields & DM_COLLATE) &&
                                  (pDevmode->dmCollate == DMCOLLATE_TRUE);

    bDuplex                   = (pDevmode->dmFields & DM_DUPLEX) &&
                                  (pDevmode->dmDuplex != DMDUP_SIMPLEX);


    BRetrievePvtSettings (pData->pPrinterNameFromOpenData,  
                          &eNupDirection,  
                          &eBookletMode, 
                          &dwMultiPartJob,
                          bBookletPrint );

    if (!dwJobNumberOfCopies) {
        //
        // Some applications can set the copy count to 0.
        // In this case we exit.
        //
        bReturn = TRUE;
        goto CleanUp;
    }

    if (bDuplex) {
        dwDuplexMode = (pDevmode->dmDuplex == DMDUP_HORIZONTAL) ? EMF_DUP_HORZ
                                                                : EMF_DUP_VERT;
    } else {
        dwDuplexMode = EMF_DUP_NONE;
    }

    if (bBookletPrint) {
        if (!bDuplex) {
            // Not supported w/o duplex printing. Use default settings.
            bBookletPrint = FALSE;
            dwDrvNumberOfPagesPerSide = 1;
            dwJobNumberOfPagesPerSide = 1;
        } else {
            // Fixed settings for pages per side.
            dwDrvNumberOfPagesPerSide = 1;
            dwJobNumberOfPagesPerSide = 2;
        }
    }

    // Number of pages per side that the print processor has to play
    dwNumberOfPagesPerSide = (dwDrvNumberOfPagesPerSide == 1)
                                               ? dwJobNumberOfPagesPerSide
                                               : 1;


    if (dwNumberOfPagesPerSide == 1) {
        // if the print processor is not doing nup, don't draw borders
        dwNupBorderFlags = NO_BORDER_PRINT;
    }

    //
    // Color optimization may cause wrong output with duplex
    //
    dwOptimization = (AttributeInfo.dwColorOptimization == COLOR_OPTIMIZATION &&
                                           !bDuplex && dwJobNumberOfPagesPerSide == 1)
                                           ? EMF_PP_COLOR_OPTIMIZATION
                                           : 0;

    // Check for Valid Option for n-up printing
    if (!ValidNumberForNUp(dwNumberOfPagesPerSide)) {
        ODS(("Invalid N-up option\nPrinter %ws\nDocument %ws\nJobID %u\n", pData->pDevmode->dmDeviceName, pData->pDocument, pData->JobId));
        goto CleanUp;
    }

    //
    // From local variables, put the values in EMFAttr.
    // Note: The value for dwTotalNumberOfPages has been initialized
    // to 0xFFFFFFFF which means undetermined. Later on, this value
    // may be overwritten.
    //
    EMFAttr.bBookletPrint             = bBookletPrint;
    EMFAttr.eBookletMode              = eBookletMode;
    EMFAttr.bReverseOrderPrinting     = bReverseOrderPrinting;
    EMFAttr.dwDrvNumberOfPagesPerSide = dwDrvNumberOfPagesPerSide;
    EMFAttr.dwMultiPartJob            = dwMultiPartJob;
    EMFAttr.eNupDirection             = eNupDirection;
    EMFAttr.dwNupBorderFlags          = dwNupBorderFlags;
    EMFAttr.dwJobNumberOfCopies       = dwJobNumberOfCopies;
    EMFAttr.dwDuplexMode              = dwDuplexMode;
    EMFAttr.dwNumberOfPagesPerSide    = dwNumberOfPagesPerSide;
    EMFAttr.dwDrvNumberOfCopies       = dwDrvNumberOfCopies;


    //
    // For reverse, booklet printing, we need to know the total number
    // of pages. So we have to wait till all the pages are spooled.
    //
    if (bReverseOrderPrinting || bBookletPrint) {

       // Get the number of pages in the job. This call waits till the
       // last page is spooled.
       __try {

           dwTotalNumberOfPages= GdiGetPageCount(hSpoolHandle);

       } __except (EXCEPTION_EXECUTE_HANDLER) {

           ODS(("PrintEMFJob gave an exceptionPrinter %ws\nDocument %ws\nJobID %u\n", pData->pDevmode->dmDeviceName, pData->pDocument, pData->JobId));
           goto CleanUp;
       }

        EMFAttr.dwTotalNumberOfPages      = dwTotalNumberOfPages;

        //
        // GetStartPageList for reverse/booklet printing
        // Check for a change of devmode between pages only if Nup and PCL driver
        // If both booklet and reverse printing are present, 
        // we choose booklet.
        //
        if ( bBookletPrint )
        {
            if (!GetStartPageListBooklet(hSpoolHandle,
                                         &EMFAttr,
                                         &pMemoryHead,   //Where memory for the list starts.
                                         &pPageListHead, //where the actual head of list starts.
                                         FALSE,
                                         &bOdd)) {
                 goto CleanUp;
            }
        }
        else if ( bReverseOrderPrinting )
        {
            //
            // Get start page list. For certain "normal" printing scenarios, 
            // we dont really need the list. So pHead will be returned as NULL.
            // (We could still poplulate pHead, but that will mean needlessly
            // going through memory allocation code etc...).
            // But for others ( like reverse printing/booklet printing)
            // it is good to get the page order here and make things simpler 
            // in the future.
            //
            if (!GetStartPageListReverseOrder(hSpoolHandle,
                                  &EMFAttr,
                                  &pMemoryHead, //Where memory for the list starts.
                                  &pPageListHead, //where the actual head of list starts.
                                  FALSE,
                                  &bOdd)) {
                 goto CleanUp;
            }
       }
    }

    // Save the old transformation on hPrinterDC
    if (!SetGraphicsMode(hPrinterDC,GM_ADVANCED) ||
        !GetWorldTransform(hPrinterDC,&OldXForm)) {

         bSetWorldXform = FALSE;
         ODS(("Transformation matrix can't be set\nPrinter %ws\nDocument %ws\nJobID %u\n", pData->pDevmode->dmDeviceName, pData->pDocument, pData->JobId));
         goto CleanUp;
    }

    // pCopyDM will be used for changing the copy count
    pCopyDM = pFirstDM ? pFirstDM : pDevmode;
    pCopyDM->dmPrintQuality = pDevmode->dmPrintQuality;
    pCopyDM->dmYResolution = pDevmode->dmYResolution;

    bReturn = BPrintEMFJobNow (
                            hSpoolHandle,
                            hPrinterDC,
                            &EMFAttr,
                            bOdd,
                            dwOptimization,
                            pCopyDM,
                            pPageListHead,
                            pData );

    //
    // Preserve the last error
    //
    LastError = bReturn ? ERROR_SUCCESS : GetLastError();


CleanUp:

    if (bSetWorldXform && hPrinterDC) {
       SetWorldTransform(hPrinterDC, &OldXForm);
    }

    FreeSplMem(pMemoryHead);

    if (pDevmode) {
       FreeSplMem(pDevmode);
    }

    __try {
        if (hSpoolHandle) {
           GdiDeleteSpoolFileHandle(hSpoolHandle);
        }

    } __except (EXCEPTION_EXECUTE_HANDLER) {

        ODS(("GdiDeleteSpoolFileHandle failed\nPrinter %ws\nDocument %ws\nJobID %u\n", pData->pDevmode->dmDeviceName, pData->pDocument, pData->JobId));
    }

    SetLastError(LastError);

    return bReturn;
}

/*++
Function Name
    BPrintEMFJobNow

Function Description.

Parameters:
            hSpoolHandle       -- the handle to the spool file
            hPrinterDC         -- the devmode related to this page number is requested.
            pEMFAttr           -- the devmode for the dwPageNumber is placed here.
            bOdd               -- devmode for dwPageNumber-1 is placed here. Can be NULL. (if n
            dwOptimization
            pDevmode
            pPageList
            pData

Return Values:  TRUE if the emf is printed 
                FALSE otherwise
--*/

BOOL 
BPrintEMFJobNow (
        IN      HANDLE                hSpoolHandle,
        IN      HDC                   hPrinterDC,
        IN      PEMF_ATTRIBUTE_INFO   pEMFAttr,
        IN      BOOL                  bOdd,
        IN      DWORD                 dwOptimization,
        IN      LPDEVMODEW            pDevmode,
        IN  OUT PPAGE_NUMBER          pPageList, //Maybe slightly modified on exit.
        IN      PPRINTPROCESSORDATA   pData )
{
    DOCINFOW    DocInfo;
    DWORD       LastError;
    BOOL        bRetVal              = FALSE;
    BOOL        bStartDoc            = FALSE;
    DWORD       dwRemainingCopies    = 0; 
    DWORD       dwJobNumberOfCopies  = pEMFAttr->dwJobNumberOfCopies;
    DWORD       dwDrvNumberOfCopies  = pEMFAttr->dwDrvNumberOfCopies;
    BOOL        bStartNewDocOnCopies = pEMFAttr->dwMultiPartJob;
    HANDLE      hPrinter             = NULL;
    PRINTER_DEFAULTS Defaults        = {NULL, NULL, PRINTER_ACCESS_ADMINISTER};
    BOOL        bMultipleStartDoc    = pEMFAttr->dwMultiPartJob;
    

    __try {

        DocInfo.cbSize = sizeof(DOCINFOW);
        DocInfo.lpszDocName  = pData->pDocument;
        DocInfo.lpszOutput   = pData->pOutputFile;
        DocInfo.lpszDatatype = NULL;
    
        if (!GdiStartDocEMF(hSpoolHandle, &DocInfo)) goto CleanUp;
        bStartDoc = TRUE;

/*++ Only For Longorn and above systems. OEMs may uncomment it but it will work only on longhorn.
        //
        // If for some reason, we need to break a job into multiple documents, 
        // then we have to do something special. e.g. In manual duplex
        // the user may take some time to walk over to the printer
        // and invert the pages, this may cause a TCP timeout and the
        // the job will abandon. To prevent a TCP timeout, we have to 
        // first set JOB_CONTROL_RETAIN flag for the job and then
        // do JOB_CONTROL_RELEASE once everything is printed.
        //
        if ( bMultipleStartDoc )
        {
            if (! OpenPrinterW(pData->pPrinterName,&hPrinter,&Defaults) )
            {
                goto CleanUp;
            }
            SetJobW(hPrinter, pData->JobId, 0, NULL, JOB_CONTROL_RETAIN);
        }
--*/

        if (pEMFAttr->bCollate) {

            dwRemainingCopies = dwJobNumberOfCopies & 0x0000FFFF ;

            while (dwRemainingCopies) {
                //
                // We do a new startDoc only if this is not the first time we are going thru this loop, 
                //
                if ( bStartNewDocOnCopies && ( dwRemainingCopies != (dwJobNumberOfCopies & 0x0000FFFF ) ) )
                {
                    //
                    // End the previous job and start a new one.
                    //
                    if (!GdiEndDocEMF(hSpoolHandle) || !GdiStartDocEMF(hSpoolHandle, &DocInfo) ) 
                    {
                        bStartDoc = FALSE; 
                        goto CleanUp;
                    }
                }

               if (dwRemainingCopies <= dwDrvNumberOfCopies) {
                  SetDrvCopies(hPrinterDC, pDevmode, dwRemainingCopies);
                  dwRemainingCopies = 0;
               } else {
                  SetDrvCopies(hPrinterDC, pDevmode, dwDrvNumberOfCopies);
                  dwRemainingCopies -= dwDrvNumberOfCopies;
               }

               if (!PrintEMFSingleCopy(hSpoolHandle,
                                       hPrinterDC,
                                       pEMFAttr,
                                       pPageList,
                                       bOdd,
                                       dwOptimization,
                                       pDevmode,
                                       pData)) {
                   goto CleanUp;
               }
                
            } //while

        } else {

           if (!PrintEMFSingleCopy(hSpoolHandle,
                                   hPrinterDC,
                                   pEMFAttr,
                                   pPageList,
                                   bOdd,
                                   dwOptimization,
                                   pDevmode,
                                   pData)) {

               goto CleanUp;
           }
        }

    } __except (EXCEPTION_EXECUTE_HANDLER) {

        ODS(("PrintEMFSingleCopy gave an exception\nPrinter %ws\nDocument %ws\nJobID %u\n", pData->pDevmode->dmDeviceName, pData->pDocument, pData->JobId));
        goto CleanUp;
    }

    bRetVal = TRUE;
    
CleanUp:

    //
    // Preserve the last error
    //
    LastError = bRetVal ? ERROR_SUCCESS : GetLastError();
    
    if ( bStartDoc ) {

/*++ Only for longhorn and above systems. IHV's may uncomment it.
        if ( hPrinter && bMultipleStartDoc ) //hPrinter could be NULL if OpenPrinter failed.
        {
            SetJobW(hPrinter, pData->JobId, 0, NULL, JOB_CONTROL_RELEASE);
        }
--*/
        GdiEndDocEMF(hSpoolHandle);
    }

    SetLastError(LastError);

    return bRetVal;
}


/*++
Function Name
    GdiGetDevmodeForPagePvt

Function Description.
    In some cases, GDI's GdiGetDevmodeForPage returns a devmode
    that is based on an old format of devmode. e.g. Win3.1 format. The size of such a devmode
    can be smaller than the latest Devmode. This can lead to unpredictable issues.
    Also, sometimes the devmode returned is even smaller than Win3.1 format (due to possible
    corruption).
    This function is a wrapper around GDI's GdiGetDevmodeForPage and partially takes care of this
    situation by doing an extra checking for devmode.

Parameters:
            hSpoolHandle           -- the handle to the spool file
            dwPageNumber           -- the devmode related to this page number is requested.
            ppCurrDM               -- the devmode for the dwPageNumber is placed here.
            ppLastDM               -- devmode for dwPageNumber-1 is placed here. Can be NULL. (if n
ot NULL)

Return Values:  TRUE if a valid devmode was obtained from GDI
                FALSE otherwise
--*/

BOOL GdiGetDevmodeForPagePvt(
    IN  HANDLE              hSpoolHandle,
    IN  DWORD               dwPageNumber,
    OUT PDEVMODEW           *ppCurrDM,
    OUT PDEVMODEW           *ppLastDM
  )
{


    if ( NULL == ppCurrDM )
    {
        return FALSE;
    }

    *ppCurrDM = NULL;

    if ( ppLastDM )
    {
        *ppLastDM = NULL;
    }

    if (!GdiGetDevmodeForPage(hSpoolHandle,
                              dwPageNumber,
                              ppCurrDM,
                              ppLastDM) )
    {
        ODS(("GdiGetDevmodeForPage failed\n"));
        return FALSE;
    }
    //
    // If GdiGetDevmodeForPage has succeeded, then *ppCurrDM should have valid values
    // Also if ppLastDM is not NULL, then *ppLastDM should also have valid values.
    //
    // GDI guarantees that the size of the devmode is atleast dmSize+dmDriverExtra.
    // So we dont need to check for that. But we still need to check some other dependencies
    //
    //

    if ( NULL  == *ppCurrDM ||
         FALSE == BIsDevmodeOfLeastAcceptableSize (*ppCurrDM)
       )
    {
        return FALSE;
    }

    // 
    // It is possible for GdiGetDevmodeForPage to return TRUE (i.e. success)
    // but still not fill in the *ppLastDM. So NULL *ppLastDM is not an error
    // 

    if ( ppLastDM && *ppLastDM &&
         FALSE == BIsDevmodeOfLeastAcceptableSize (*ppLastDM)
       )
    {

        return FALSE;
    }

    return TRUE;
}


/*++
Function Name
    BIsDevmodeOfLeastAcceptableSize

Function Description.
Parameters:
    pdm  -- the pointer to the devmode.

Return Values:  TRUE if devmode is of least acceptable size.
                FALSE otherwise
--*/

BOOL BIsDevmodeOfLeastAcceptableSize(
    IN PDEVMODE pdm)
{

    if ( NULL == pdm )
    {
        return FALSE;
    }

    if ( IS_DMSIZE_VALID((pdm),dmYResolution) )
    {
        return TRUE;
    }
    return FALSE;
}

/*++
Function Name
    BRetrievePvtSettings

Function Description.
    Gets some job settings from the registry. This is a temporary solution, until a full
    solution based on JobTicket is implemented.
    If any one is reading this in the DDK sample, PLEASE KNOW THAT THIS CODE
    WILL NOT BE IN THE SHIP VERSION OF THE OPERATING SYSTEM. 
    ACCESSING REGISTRY DIRECTLY (LIKE THIS CODE IS DOING) IS A VERY BAD IDEA. 

Parameters:

Return Values:  TRUE if success. 
                FALSE otherwise
                                
--*/

BOOL BRetrievePvtSettings (
            IN  LPCTSTR         lpPrinterName,
            OUT PENupDirection  peNupDirection,
            OUT PEBookletMode   peBookletMode,
            OUT PDWORD          pdwMultiPartJob,
            IN  BOOL            bBookletPrint)
{
    HKEY   hkPrinter  = NULL;
    DWORD  cbData     = 0;
    DWORD  dwDataType = 0;
    BOOL   bRetVal    = FALSE;
    WCHAR  lpSubKey[1024]; 
    HRESULT hr = E_FAIL;
    
    #define CCHOF(x) ( sizeof(x)/sizeof(x[0]) )

    hr = StringCchCopy(lpSubKey, CCHOF(lpSubKey), TEXT("SYSTEM\\CurrentControlSet\\Control\\Print\\Printers\\") );

    if ( wcslen(lpSubKey) + wcslen(lpPrinterName) + 1 < 1024 )
    {
        hr = StringCchCat(lpSubKey, CCHOF(lpSubKey), lpPrinterName);
    }
    else
    {
        //
        // Buffer overrun
        //
        return FALSE;
    }


    if ( ERROR_SUCCESS == 
                    RegOpenKeyEx(  HKEY_LOCAL_MACHINE,
                        lpSubKey,
                         0,
                         KEY_ALL_ACCESS,
                         &hkPrinter) )
    {
        cbData = sizeof (DWORD); 

        //
        // These RegQueryValueEx() calls can fail. That only means the values are not present.
        // Absence of values is not an error.
        //

        if ( peBookletMode )
        {
            DWORD dwBookletMode = 0;
            RegQueryValueEx( hkPrinter,
                             TEXT("BookletMode"),
                             0,
                             &dwDataType, // After func returns, this should be REG_DWORD,
                             (LPBYTE)&dwBookletMode,
                             &cbData );
            *peBookletMode = (EBookletMode)dwBookletMode;
        }

        if ( peNupDirection )
        {
            DWORD dwNupDirection = 0;

            //
            // If both NupDirection and booklet are specified, then BookletMode takes
            // precedence. 
            //
            if ( bBookletPrint )
            {
                //Don't care for nupdirection
            }
            else
            {
                RegQueryValueEx( hkPrinter,
                                 TEXT("NupDirection"),
                                 0,
                                 &dwDataType, // After func returns, this should be REG_DWORD,
                                 (LPBYTE)&dwNupDirection,
                                 &cbData );  
            }
            *peNupDirection = (ENupDirection) dwNupDirection;
        }

        if ( pdwMultiPartJob )
        {
            *pdwMultiPartJob = 0;
            RegQueryValueEx( hkPrinter,
                             TEXT("MultiPartJob"),
                             0,
                             &dwDataType, // After func returns, this should be REG_DWORD,
                             (LPBYTE)pdwMultiPartJob,
                             &cbData );
        }
                              
        RegCloseKey (hkPrinter);
 
    }
    else
    {
        // bRetVal = FALSE;
    }

    return bRetVal;
}


/*++
Function Name
    BPlayEmptyPages

Function Description.
    Plays empty logical pages. e.g. n-up = 4 but 
    app plays only one page. So we'll play 3 empty pages so that printer thinks
    4 pages have been recieved.

Parameters:

Return Values:  TRUE if successful
                FALSE otherwise
--*/

BOOL BPlayEmptyPages(
        IN  HANDLE                 hSpoolHandle,
        IN  PEMF_ATTRIBUTE_INFO    pEMFAttr,
        IN  DWORD                  dwNumPages,
        IN  DWORD                  dwOptimization)
{
    DWORD dwDrvNumberOfPagesPerSide = pEMFAttr->dwDrvNumberOfPagesPerSide;

    ULONG ulNPCtr;  //NumPages loop Counter

    for ( ulNPCtr = 0; ulNPCtr < dwNumPages; ulNPCtr++)
    {
        //
        // To play back an empty page, we need to call
        // GdiStartPageEMF and GdiEndPageEMF.
        //
        if (!GdiStartPageEMF(hSpoolHandle) || !GdiEndPageEMF(hSpoolHandle, dwOptimization))
        {
            ODS(("Start Page / EndPage failed\n"));
        }
    }

    return TRUE;
}

BOOL
BGetPageCoordinatesForNUpFromArray(
                IN  PEMF_ATTRIBUTE_INFO   pEMFAttr,
                IN  PUpdateRect *         ppURect,
                IN  BOOL                  bLandscape)
{
    ENupDirection eNupDirection   = pEMFAttr->eNupDirection;
    DWORD dwNupDirection         = (DWORD)eNupDirection;
    DWORD dwNumberOfPagesPerSide = pEMFAttr->dwNumberOfPagesPerSide;
    DWORD dwIndex; //Index into gUpdateRect array.

    if ( dwNumberOfPagesPerSide > 1 &&
         ValidNumberForNUp( dwNumberOfPagesPerSide ) &&
         dwNupDirection < 4 )
    {
        //
        // Subtract 1 from dwNumberOfPagesPerSide because 
        // dwIndexIntoUpdateRect is 0 indexed
        // Since UpdateRect has matrices for 5 n-up options, they are indexed
        // from 0-4. So the index cannot be more than 4. Also if a n-up is
        // not supported, dwIndex will be 0xFFFFFFFF
        // 
        dwIndex = dwIndexIntoUpdateRect[dwNumberOfPagesPerSide-1];
        if ( dwIndex != 0xFFFFFFFF && dwIndex <= 4) //5 different n-up numbers indexed from 0-4 
        {

            //
            // For 4-up, 9-up, 16-up, the page is easily and equally divided.
            // For 2-up, 6-up, the division depends on whether 
            // it is portrait or landscape.
            //
            if ( (dwNumberOfPagesPerSide == 2 ||
                  dwNumberOfPagesPerSide == 6) && 
                  bLandscape == TRUE )
            {
                //
                // The first MAX_NUP_OPTIONS/2 are for portrait, the next are for landscape.
                //
                dwNupDirection += MAX_NUP_OPTIONS/2;
            }
            *ppURect = (PUpdateRect)&gUpdateRect[dwIndex][dwNupDirection];
            return TRUE; 
        }
        else
        {
            ODS(("n-up specified is improper %d.", dwNumberOfPagesPerSide));
        }
    }
    return FALSE;
}


/*++
Function Name
    BUpdateAttributes

Function Description.
    Sometimes when orientation of pages change within the job, the x,y printable area changes.
    So we need to get the new values.
    Note: Currently this is used only to get the x,y resolution and x,y printable area.
    It may need to be expaned in the future. 

Parameters:

    pEMFAttr : The Job Attributes. 

Return Values:  TRUE if successful
                FALSE otherwise

Assumption:
    1. pEMFAttr will always be valid.
    2. GetDeviceCaps will not return random values. This is a good assumption because MSDN 
       does not define any error return values.
--*/

BOOL
BUpdateAttributes(
    IN     HDC                   hPrinterDC,
    IN OUT PEMF_ATTRIBUTE_INFO   pEMFAttr)
{
    pEMFAttr->lXResolution = GetDeviceCaps(hPrinterDC, LOGPIXELSX); //dpi in x direction.
    pEMFAttr->lYResolution = GetDeviceCaps(hPrinterDC, LOGPIXELSY); //dpi in y direction.
    pEMFAttr->lXPrintArea  = GetDeviceCaps(hPrinterDC, DESKTOPHORZRES);//numpixels in printable area in x direction.
    pEMFAttr->lYPrintArea  = GetDeviceCaps(hPrinterDC, DESKTOPVERTRES);//numpixels in printable area in y direction
    
    return TRUE;
}

