// Q.2 Write the simulation program to implement demand paging and show the page scheduling
// and total number of page faults for the following given page reference string. Give input n=3 as
// the number of memory frames.
// Reference String : 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2
// i. Implement LRU

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Check if page is already in memory frames
int isPageInMemory(int page, int* memory, int num_frames) {
    for (int i = 0; i < num_frames; i++) {
        if (memory[i] == page) {
            return 1;  // Page found in memory
        }
    }
    return 0;  // Page not found
}

// Find the index of the Least Recently Used (LRU) page to replace
int findLRUPage(int* memory, int* page_references, int num_frames, int current_index) {
    int page_to_replace = -1;
    int min_index = current_index;

    // For each page currently in memory
    for (int i = 0; i < num_frames; i++) {
        int page = memory[i];

        // Search backward from current index to find when page was last used
        for (int j = current_index - 1; j >= 0; j--) {
            if (page_references[j] == page) {
                // Keep track of the page with the oldest last use (minimum j)
                if (j < min_index) {
                    min_index = j;
                    page_to_replace = i;
                }
                break;  // Found last use, no need to look further
            }
        }
    }

    // If no page found in past references (all -1 or new pages), replace first frame by default
    if (page_to_replace == -1) {
        page_to_replace = 0;
    }

    return page_to_replace;
}

int main() {
    char reference_string[] = "7,0,1,2,0,3,0,4,2,3,0,3,2";
    int num_frames = 3;
    int page_references[100];
    int memory[3] = {-1, -1, -1};  // Initialize frames to -1 (empty)
    int page_faults = 0;
    int num_references = 0;

    // Parse reference string into page_references array
    char* token = strtok(reference_string, ",");
    while (token != NULL) {
        page_references[num_references] = atoi(token);
        num_references++;
        token = strtok(NULL, ",");
    }

    // Process each page reference
    for (int i = 0; i < num_references; i++) {
        // If page not in memory, it's a page fault
        if (!isPageInMemory(page_references[i], memory, num_frames)) {
            page_faults++;

            // If there are empty frames, place page in the first empty frame
            if (i < num_frames) {
                memory[i] = page_references[i];
            } else {
                // Otherwise find the least recently used page and replace it
                int page_to_replace = findLRUPage(memory, page_references, num_frames, i);
                memory[page_to_replace] = page_references[i];
            }

            // Print page fault event with current memory frames
            printf("Page %d -> Frames: %d, %d, %d\n", page_references[i], memory[0], memory[1], memory[2]);
        }
    }

    // Print total number of page faults
    printf("Total Page Faults: %d\n", page_faults);

    return 0;
}
