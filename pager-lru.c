/*
 * File: pager-lru.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * This file contains the skeleton for an LRU pager
 */

#include <stdio.h> 
#include <stdlib.h>
#include "simulator.h"

void pageit(Pentry q[MAXPROCESSES]) { 

    /* Static vars */
    static int initialized = 0;
    static int tick = 1; // artificial time
    static int timestamps[MAXPROCESSES][MAXPROCPAGES];

    /* Local vars */
    int proc;
    int page;
    int leastRecentTick;
    /* initialize timestamp array on first run */
    if (!initialized) {
        for (proc=0; proc < MAXPROCESSES; proc++) {
            for (page=0; page < MAXPROCPAGES; page++) {
                timestamps[proc][page] = 0; 
            }
        }
        initialized = 1;
    }
    
    /* TODO: Implement LRU Paging */
    for (int proc = 0; proc < MAXPROCESSES; proc++) {

        if (q[proc].active == 1){ //if our page is active:
            int page = q[proc].pc/PAGESIZE; // program counter for process and current page the PC is on
            timestamps[proc][page] = tick; //since we just accessed our page we can increment tick
            if (q[proc].pages[page] != 1){ //if we are in memory then we are done, if we are not memory then
                if(!pagein(proc,page)){ //if pagein faults then we need to do LRU

                    //now we will just find the least recently used
                    leastRecentTick = tick;
                    int page_number = page;
                    for (int vic = 0; vic < MAXPROCPAGES; vic++) { 
                        if (q[proc].pages[vic] && timestamps[proc][vic] < leastRecentTick) {
                            leastRecentTick = timestamps[proc][vic];
                            page_number = vic;
                        }
                    }

                   pageout(proc, page_number);

                }
            }


        }
         

    }

    /* advance time for next pageit iteration */
    tick++;
} 
