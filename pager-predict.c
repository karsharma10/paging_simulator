#include <stdio.h> 
#include <stdlib.h>

#include "simulator.h"



// Got a detailed overview from Panav's Office Hours:
//A majority of code inspiration that given from him :)

void pageit(Pentry q[MAXPROCESSES]) { 
    
    /* This file contains the stub for a predictive pager */
    /* You may need to add/remove/modify any part of this file */

    /* Static vars */
    static int initialized = 0;
    //static int tick = 1; // artificial time

    //_______________________________________________________
    //this will be our state matrix, where we will be able to store a processes's page, that that processes's page is marked as 1, then we know that it should be in memory
    //so at the end we will be looping through the state matrix to find what processes's are marked as 1 and pagein those ones. If its marked as zero then we pageout since we don't 
    //want it in memory:
    static int state_matrix[MAXPROCESSES][MAXPROCPAGES]; 
    //_______________________________________________________

    //As in our predictive method from the diagram we need to make sure that we can figure out what future pages to add into memory. To do so, we need to make sure we know the
    //current pc counter, and the previous pc counter. This will also help us to know the program type and see if there are jumps.
    static int previous_and_currentPC[MAXPROCESSES][2]; //its 2 because we will have current,previous

    //_______________________________________________________
    //As defined in recitation, in order to implement a fast pagein algoirthm we need to identify the program type for that specific process so we can better assume what pages to put in memory
    static int type_of_program[MAXPROCESSES];
    //_______________________________________________________


    /* Local vars */
    

    /* initialize static vars on first run */
    if(!initialized){
	/* Init complex static vars here */
        for (int proc=0; proc < MAXPROCESSES; proc++) { //so what we will do here is that we will make sure our previous_and_currentPC and type_of_program values are set to zero
            previous_and_currentPC[proc][0] = 0;
            previous_and_currentPC[proc][1] = 0;
            type_of_program[proc] = 0;
        }
	    initialized = 1;
    }

    //now we need to intialize our state matrix, we want to make sure that we set it to zero everytime pageit is called. This is because we want to make sure that when we loop through
    //each process we want our state_matrix to still set the process that needs to be in memory as 1, just in case that a page isn't able to be put into memory
    for (int proc=0; proc < MAXPROCESSES; proc++) {
            for (int page=0; page < MAXPROCPAGES; page++) {
                state_matrix[proc][page] = 0; 
            }
        }
    /* TODO: Implement Predictive Paging */
    //fprintf(stderr, "pager-predict not yet implemented. Exiting...\n");
    //exit(EXIT_FAILURE);

    for (int proc = 0; proc < MAXPROCESSES; proc++) { //loop through each process
        if (q[proc].active != 1) continue; //we only select processes that are active, so if its not active then we go to the next iteration.

        int pc = q[proc].pc; 	//program counter for current process	            	
        int page = pc/PAGESIZE; 	//current page the PC is on

        //now we go into our state matrix, and set that current process and page value as 1 since we know we need to add that into memory
        state_matrix[proc][page] = 1;

        //this will help see how to identify if:
        //1: if we are at the end of the current process
        //2: to identify what type of program we are executing

        
        //now we need to set our previous_and_currentPC arrary to have our previous program counter at that current proccess
        previous_and_currentPC[proc][0] = previous_and_currentPC[proc][1];
        //now we need to set our previous_and_currentPC array to have our current program counter at the current process:
        previous_and_currentPC[proc][1] = pc;

        //now looking at programs.c we can see how to identify we are at the end of a program is done
        //ex:
        //if previous program counter is 504 and current is 0
        //if previous program counter is 1911 and current is 0
        //if previous program counter is 1685 and current is 0
        //if previous program counter is 1684 and current is 0
        //if previous program counter is 1130 and current is 0
        //if previous program counter is 1534 and current is 0
        //so now what we do is that we reset the type of program because we don't want to use the same method to resolve pagin method:
        //we want to restart identification because we can assume that we want to restart identification, since we know that we are at the end of the program
        //we have 40 programs total and only 20 slots. 

        if(previous_and_currentPC[proc][0] == 1534 && previous_and_currentPC[proc][1] == 0){
            type_of_program[proc] = 0;
        }
        if(previous_and_currentPC[proc][0] == 1130 && previous_and_currentPC[proc][1] == 0){
            type_of_program[proc] = 0;
        }
        if(previous_and_currentPC[proc][0] == 1684 && previous_and_currentPC[proc][1] == 0){
            type_of_program[proc] = 0;
        }
        if(previous_and_currentPC[proc][0] == 1685 && previous_and_currentPC[proc][1] == 0){
            type_of_program[proc] = 0;
        }
        if(previous_and_currentPC[proc][0] == 1911 && previous_and_currentPC[proc][1] == 0){
            type_of_program[proc] = 0;
        }
        if(previous_and_currentPC[proc][0] == 504 && previous_and_currentPC[proc][1] == 0){
            type_of_program[proc] = 0;
        }
        

        //now we need to identify the type of the program, so we check if at that given proc if we have identitified the program type
        //found in office hours by looking at programs.c:
        if(type_of_program[proc] == 0){ //if the program type at the process is equal to 0, then we know that we have not yet identitified that process:

            //lets start off by idenitifying if its program 5:
            if(previous_and_currentPC[proc][0] == 503 && previous_and_currentPC[proc][1] == 0){
                type_of_program[proc] = 5;
            }
            else if(previous_and_currentPC[proc][0] == 501 && previous_and_currentPC[proc][1] == 0){
                type_of_program[proc] = 5;
            }

            else if(previous_and_currentPC[proc][0] == 500 && previous_and_currentPC[proc][1] == 503){
                type_of_program[proc] = 5;
            }


            //now to identify program 4, we can hadle that below in our switch statment. 

            //now to identify program 3:
            else if(previous_and_currentPC[proc][0] == 1683 && previous_and_currentPC[proc][1] == 0){
                type_of_program[proc] = 3;
            }
            else if(previous_and_currentPC[proc][0] == 1682 && previous_and_currentPC[proc][1] == 1166){
                type_of_program[proc] = 3;
            }

            //now to identitfy program 2:
            else if(previous_and_currentPC[proc][0] == 1129 && previous_and_currentPC[proc][1] == 0){
                type_of_program[proc] = 2;
            }
            
            //now to identify program 1:
            else if(previous_and_currentPC[proc][0] == 1533 && previous_and_currentPC[proc][1] == 0){
                type_of_program[proc] = 1;
            }

            else if(previous_and_currentPC[proc][0] == 1401 && previous_and_currentPC[proc][1] == 1533){
                type_of_program[proc] = 1;
            }

            else if(previous_and_currentPC[proc][0] == 500 && previous_and_currentPC[proc][1] == 1402){
                type_of_program[proc] = 1;
            }


        }

        
        //now that we have identified that processes, we can go ahead and predict what pages should be in memory

        switch (type_of_program[proc]) //so we will do a swtich statment on the type of program
        {
        //we have space for 20 programs total, and 5 programs so should have about 4 pages for a given program for program. 

        case 5: //if our current type of program is 5:
            //we only need to add the next 4 pages into memory, so we can just:
            //so if we look at program 5, we can see that 500/128 = about 4 so we want to page in 4 pages just so that we are safe and the whole program. 
            for(int k =0; k < 4; k++){  //loop through 4
                state_matrix[proc][k] = 1;  //at that current proc and page we will mark it as 'safe' which means that it should be in memory.
            }
            break;
        case 3: //if our current program type is 3 then:

        //since from programs.c we can see that we will assume the jumps are at page 13, and to get to page 13 we must before get to page 12 so we can:
        //so we mark page 0, 9, and 13 as safe
            if(page == 12){ //if the program type is 3 and the page we are at is 12, then we should def page in 13, but also 0 or 9 depending if we are at the start or end of the loop.
            // which would be the outter or linner loop iteration.

                //so know that we will hit page 12 before page 13, so we will add page 9 and 0. 

                state_matrix[proc][0] = 1; //mark 0 as safe depedning on the loop condition
                state_matrix[proc][13] = 1; //mark 13 as also something that needs to be added into memory
                state_matrix[proc][9] = 1;  //mark 9 as something that needs to be added into memory depending on the loop
            }
            else if(page == 13){ //if the program type we are at is 3 and the page is 13 then we should page in 0 and 1 if we are the end of of the outer loop iteration
                // if we at the inner loop interation then we should add 9 or 10:

                //we know that we should page in 9 and 0 from programs.c so just to be safe and be father in, we should page in 1 and 10 since those pages come after 9 and 0.
                state_matrix[proc][0] = 1;
                state_matrix[proc][1] =1 ;
                state_matrix[proc][10] = 1;
                state_matrix[proc][9] = 1;

            }
            else{ //if we are at neither than we just page in the next two pages just as a standard measure:
                //we can assume that we are not hitting a jump so we can add in the next two pages into memory. 
                state_matrix[proc][page+1] = 1; //mark next page to be put into memory 
                state_matrix[proc][page+2] = 1; //mark 2 page to be put into memory
            }
            break;

        case 2:
        //short program type, we know that since we jump or finish at page 8, we are going to start at page 7 so we know we can go to page 8 from page 8 we can jump
        //to page 0 from page 8. 
            if(page == 7){ //if we are program type 2 and page 7 we have a high probability of a loop, so we need to mark 8 and 0 as something to put into memory
                state_matrix[proc][0] = 1;
                state_matrix[proc][8] = 1;
            }
            else if(page == 8){ //if we are page 8, then we should page in 0 and 1 because we will most likely loop back to 0, so for safety measures we can add 0 and 1
                state_matrix[proc][0] = 1; //its ok to add 1 again even tho in page 7 we already marked it as safe since being redudant doesn't hurt
                state_matrix[proc][1] = 1; //page in 1 beacuse thats the next page from 0.
            }
            else{ //just page in the next two pages if we are not in the other pages, just our linear case we add next to pages. 
                state_matrix[proc][page+1] = 1; //mark next page to be put into memory 
                state_matrix[proc][page+2] = 1; //mark 2 page to be put into memory
            }
            break;
        case 1: //if the program type is 1:
            if(page == 2){ //if we are page 2, we think about branching, so we need page+1 =3, and 4 and 10 as well. those are both likely so we mark them
                //we are paging two in advance, 

                //for page 2 we will go to page 3, and on page 3 we can jump to page 10 or go to page 4 so we add those well in advance
                state_matrix[proc][3] = 1;
                state_matrix[proc][10] = 1;
                state_matrix[proc][4] = 1;
        
            }
            else if(page == 3){ //if we are at program type 1 and at page 3 then we know that we have been at page 2, from branch 10 or 11, so we should mark 4, 10 from page 2 and mark 10 and 11:
                //its ok to mark redudant pages as safe, because if we do not they will be marked as zero and will not be paged in:

                //from page 3, we can either go to page 4 or page 10. From page 4 we will go to page 5 From page 10 we will go to page 11. 
                state_matrix[proc][4] = 1;
                state_matrix[proc][10] = 1;
                state_matrix[proc][11] = 1;
                state_matrix[proc][5] =1;

            }
            else if(page == 10){ //at page 10 the next pages are 11 and 12, however from office hours page 12 is very short so we should get ahead and page in 0 and 4:

                //from page 10 we will go to page 11, from page 11 we can jump to 0 so we go two pages in advance.

                state_matrix[proc][0] = 1;
                //state_matrix[proc][4] = 1;
                state_matrix[proc][11] = 1;
               // state_matrix[proc][12] = 1;


            }
            else if(page == 11){ //mark 12 as safe, however we know page 12 is short so we can add more pages as safety measure or else they will be removed:

                //state_matrix[proc][12] = 1;
                //state_matrix[proc][5] =1;
                //state_matrix[proc][4] = 1;

                //from page 11 we can jump to page 0, so we will page in 0, and to predict future we can page in the next page after 0 which is 1.
                state_matrix[proc][0] = 1;
                state_matrix[proc][1] = 1;

            }
            else{ //just page in next two pages as deault:
                state_matrix[proc][page+1] = 1;
                state_matrix[proc][page+2] = 1;

            }
            break;

        default:
            //if we are in deafult case if either:
            //1) havent idenitified the process yet
            //2) or we are in program type 4, program type is a linear program so we can just page in the next to pages of where we are currently at into memory since those are the next pages
            //from office hours
            state_matrix[proc][page+1] = 1;
            state_matrix[proc][page+2] =1;
            break;
        }



    /* advance time for next pageit iteration */
    //tick++;
    }
    //now that we have built our state matrix, lets go thorugh the state matrix and if at the current proc and page we will pageit into memory:
    for (int proc=0; proc < MAXPROCESSES; proc++) {
        for (int page=0; page < MAXPROCPAGES; page++) {
            if(state_matrix[proc][page] == 1){
                pagein(proc,page);
            }
            else{ //equal to zero so we pageout
                pageout(proc,page);

            }
        }


    }
} 
