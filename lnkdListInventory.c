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
void displayCommands();
void createInventoryLst(struct Inventory *first, struct Inventory *prev, struct Inventory *current, struct Inventory *part, struct Inventory *head);
void printInventoryLst(struct Inventory *head, struct Inventory *first);



int main()
{
	// Declare a part, first object in linked list, and prev objec in linkedlst Inventory pointers
	struct Inventory *first, *prev, *current, *part, *head;

	// Allocate memory and make first-> and current->next attributes NULL
	first = malloc(sizeof(*first));
	current = malloc(sizeof(*current));
	first->next = NULL;
	current->next = NULL;

	// Hold user's command
	char choice[6];

	printf("\nWelcome To The Inventory Program:");
	printf("\nPlease select a command\n");

	// Display a list of commands to the user
	while (strcmp(choice, "exit") != 0)
    {
        displayCommands();
        scanf("\n%s", choice);

        // Create a new linked list while maintaining numerical order by part number
        if (strcmp(choice, "create") == 0)
        {
            createInventoryLst(first, prev, current, part, head);

            // Set head to be the head node after creation
            head = first->next;
        }
        // Print the entire linked list
        else if (strcmp(choice, "print") == 0)
            printInventoryLst(head, first);
    }

    return 0;
}



// User defined functions
void displayCommands()
{
    // Print all the commands in the program
    printf("\n\n\"create\"");
    printf("\n\"print\"");
    printf("\n\"exit\"");
    printf("\n\n");
}


void createInventoryLst(struct Inventory *first, struct Inventory *prev, struct Inventory *current, struct Inventory *part, struct Inventory *head)
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
    {
        first->next = prev;
        head = first->next;
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
        return;

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
                // Set the current item to point to the part item that the user most recently entered
                prev->next = part;

                // Prepare for the next item being created
                current = part;
            }
        }
        // If the item that the user just entered is greater than the one before it in part number
        else if (current->partNumber < part->partNumber)
        {
            // Set the current item to point to the part item that the user most recently entered
            current->next = part;

            // Prepare for the next item being created
            prev = current;
            current = part;
        }
        // If the item that the user entered is less than the first item in the linked list
        else if (first->next->partNumber > part->partNumber)
        {
            // Link the part item that the user just entered to the item after it (The old first node)
            part->next = first->next;

            // Give first the address for the item with the smallest part number that the user just entered
            first->next = part;
        }
        // If the next item inputted is out of order from the part number in the linked list but its so deep prev and current shouldnt need to change
        else
        {
            // Traverse through the linked list until the item that the user created is placed in the list
            while (head->partNumber < part->partNumber)
            {
                // Once it has found a spot where item can be in numerical order
                if (head->next->partNumber > part->partNumber)
                {
                    // Link part to the bigger part number item first
                    part->next = head->next;

                    // link the item before part to the current part
                    head->next = part;

                    // reset head
                    head = first->next;

                    break;
                }
                head = head->next;
            }
        }

        // Ask the user if they want to add another inventory
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
            break;
    }
}


void printInventoryLst(struct Inventory *head, struct Inventory *first)
{
    // traverse through the linked list and print the data from the list until the last item, then exit the while loop
    while (head != NULL)
    {
        // Print the data in the item
        printf("\nPart Number: %d", head->partNumber);
        printf("\nQuantity: %d", head->quantity);
        printf("\nPrice: $%.2f", head->price);
        printf("\n--------------------");

        // Once all the data is printed, traverse to the next item in the list
        head = head->next;
    }

    // Reset head
    head = first->next;
}
