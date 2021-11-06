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

	// Allocate memory and make first-> and current->next attributes NULL
	first = malloc(sizeof(*first));
	current = malloc(sizeof(*current));
	first->next = NULL;
	current->next = NULL;

	// Hold user's command
	char choice[6];

	printf("\nLinked List Inventory Program:");
	printf("\nPlease select a command\n");
	scanf("\n%s", choice);

	//if (strcmp(choice, "create") == 0)
    //{
        // Ask the user information about the inventory structure in current
        createLinkedLst(first, prev, current, part);
    //}
}



// User defined functions
void createLinkedLst(struct Inventory *first, struct Inventory *prev, struct Inventory *current, struct Inventory *part)
{
    char choice;
    int isSecondIter = 1; // Is the second item created yet

    // Upon first iteration, use previous to hold the first item added into inventory linked list before while loop
    prev = malloc(sizeof(*prev));

    printf("\nPart Number: ");
    scanf("\n%d", &prev->partNumber);

    printf("\nQuantity: ");
    scanf("\n%d", &prev->quantity);

    printf("\nPrice: ");
    scanf("\n%f", &prev->price);

    // Set next in the current Inventory structure to NULL for now
    prev->next = NULL;


    // first->next == NULL means that the program is on its first iteration and there is not first object yet, so assign first to the current address
    if (first->next == NULL)
        first->next = prev;


    // Ask the user if they want to add another inventory (part) --PUT IN SEPERATE FUNCTION--
    printf("\nWould you like to add another inventory (Y/N)? ");
    scanf("\n%c", &choice);


    // set choice to uppercase
    if (choice > 96 && choice < 123)
        choice -= 32;


    // Data validation
    while (choice != 'Y' && choice != 'N')
    {
        printf("\nInvalid input");

        printf("\nWould you like to add another inventory (Y/N)? ");
        scanf("\n%c", &choice);

        // set choice to uppercase
        if (choice > 96 && choice < 123)
            choice -= 32;
    }


    // Break out of loop if user does not want to add another object
    if (choice == 'N')
    {
        //DEBUG
        printf("\n%x", first->next);
        printf("\n%d->%x", first->next->partNumber, first->next->next);

        return;
    }

    // Run the while loop if the user wants to add more inventory items
    while (choice == 'Y')
    {
        // Let the user enter values of the Inventory element in the linked list
        // Allocate memory for the current structure pointer first
        part = malloc(sizeof(*part));

        printf("\nPart Number: ");
        scanf("\n%d", &part->partNumber);

        printf("\nQuantity: ");
        scanf("\n%d", &part->quantity);

        printf("\nPrice: ");
        scanf("\n%f", &part->price);

        // Set next in the current Inventory structure to NULL for now
        part->next = NULL;


        // Second iteration if current is null, current will then equal to part and prev will point to part
        if (isSecondIter)
        {
            isSecondIter = 0; // Set this to false so this if statement wont run again

            if (prev->partNumber < part->partNumber)
            {
                printf("\nBefore: %x-%x", current, part);
                printf("\n%d", prev->partNumber); // DEBUG
                // Set the current item to point to the part item that the user most recently entered
                prev->next = part;

                // Prepare for the next item being created
                current = part;
                printf("\nAfter: %x-%x", current, part);
            }
        }
        else if (current->partNumber < part->partNumber)
        {
            printf("\n%d", current->partNumber);
            // Set the current item to point to the part item that the user most recently entered
            current->next = part;

            // Prepare for the next item being created
            prev = current;
            current = part;
        }
        // If the next item inputted is less than current item in the list but greater than previous item before current
        else if (current->partNumber > part->partNumber && prev->partNumber < part->partNumber)
        {
            // prev will now point to part which part will then point to current
            prev->next = part;
            part->next = current;

            // Now swap the part and current addresses so they will be in proper order
            current = prev->next;
            part = current->next;
        }



        // Ask the user if they want to add another inventory (part) --PUT IN SEPERATE FUNCTION--
        printf("\nWould you like to add another inventory (Y/N)? ");
        scanf("\n%c", &choice);

        // set choice to uppercase
        if (choice > 96 && choice < 123)
            choice -= 32;

        // Data validation
        while (choice != 'Y' && choice != 'N')
        {
            printf("\nInvalid input");

            printf("\nWould you like to add another inventory (Y/N)? ");
            scanf("\n%c", &choice);

            // set choice to uppercase
            if (choice > 96 && choice < 123)
                choice -= 32;
        }

        // Break out of loop if user does not want to add another object
        if (choice == 'N')
        {
            //DEBUG
            printf("\n%x", first->next);
            printf("\n%d->%x", first->next->partNumber, first->next->next);
            printf("\n%d->%x", first->next->next->partNumber, first->next->next->next);
            printf("\n%d->%x", first->next->next->next->partNumber, first->next->next->next->next);
            printf("\n%d->%x", first->next->next->next->next->partNumber, first->next->next->next->next->next);


            break;
        }
    }
}
