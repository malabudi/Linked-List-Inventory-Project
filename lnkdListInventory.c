#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initialize inventory structure
struct Inventory
{
	int partNumber;
	int quantity;
	float price;
	struct Inventory *next; 	// Hold a address for the "next" object to link to the next object in line inside the linked list
};

// Fucntion protoypes
void createLinkedLst(struct Inventory *first, struct Inventory *prev, struct Inventory *current, struct Inventory *part);


int main()
{
	// Declare a part, first object in linked list, and prev objec in linkedlst Inventory pointers
	struct Inventory *first, *prev, *current, *part;

	// Make first's next attribute NULL
	first = malloc(sizeof(*first));
	first->next = NULL;

	// Hold user's command
	char choice[6];

	printf("\nLinked List Inventory Program:");
	printf("\nPlease select a command\n");
	scanf("\n%s", choice);

	if (strcmp(choice, "create") == 0)
    {
        // Ask the user information about the inventory structure in current
        createLinkedLst(first, prev, current, part);
    }
}



// User defined functions
void createLinkedLst(struct Inventory *first, struct Inventory *prev, struct Inventory *current, struct Inventory *part)
{
    char choice = 'Y';

    /*
    // Data validation
    while (choice != 'Y' && choice != 'N')
    {
        printf("\nInvalid input");

        printf("\nWould you like to add another inventory (Y/N)? ");
        scanf("\n%c", &choice);

        // set choice to uppercase
        if (choice > 96 && choice < 123)
            choice -= 32;
    }*/


    // Run the while loop if the user wants to add more inventory items
    while (choice == 'Y')
    {
        // Let the user enter values of the Inventory element in the linked list
        // Allocate memory for the current structure pointer first (current)
        current = malloc(sizeof(*current));

        printf("\nPart Number: ");
        scanf("\n%d", &current->partNumber);

        printf("\nQuantity: ");
        scanf("\n%d", &current->quantity);

        printf("\nPrice: ");
        scanf("\n%f", &current->price);

        // Set next in the current Inventory structure to NULL for now
        //current->next = NULL;

        // Ask the user if they want to add another inventory (part)
        //printf("\nWould you like to add another inventory (Y/N)? ");
        //scanf("\n%c", &choice);

        part = malloc(sizeof(*part));

        printf("\nPart Number: ");
        scanf("\n%d", &part->partNumber);

        printf("\nQuantity: ");
        scanf("\n%d", &part->quantity);

        printf("\nPrice: ");
        scanf("\n%f", &part->price);

        //part->next = NULL;

        // Assign first to part if the first object pointer is null meaning the program is on its first iteration upon creating the lnkedLst
        if (first->next == NULL)
        {
            // Check which part number is smaller among current and part, if so give first the address to the inventory w/ the smallest part num
            if (current->partNumber > part->partNumber)
                first = part;
            else
                first = current;
        }
    }
}
