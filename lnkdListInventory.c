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
char askAnotherItem(char choice);
void printInventoryLst(struct Inventory *head, struct Inventory *first);
void selectItem(struct Inventory *head, struct Inventory *first);



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
	
	// Display a list of commands to the user
	displayCommands();
	
	printf("\nPlease select a command: ");

	
	while (strcmp(choice, "exit") != 0)
    {
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
        else if (strcmp(choice, "select") == 0)
        	selectItem(head, first);
        else if(strcmp(choice, "help") == 0)
        	displayCommands();
    }

    return 0;
}



// User defined functions
void displayCommands()
{
    // Print all the commands in the program
    printf("\n\n\"create\"");
    printf("\n\"print\"");
    printf("\n\"select\"");
    printf("\n\"exit\"");
    printf("\n\"help\"\n");
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

	// Ask the user if they want to add another item
	choice = askAnotherItem(choice);

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
        if (isSecondIter && prev->partNumber < part->partNumber)
        {
            isSecondIter = 0; // Set this to false so this if statement wont run again
            
            // Set the current item to point to the part item that the user most recently entered
            prev->next = part;

            // Prepare for the next item being created
            current = part;
        }
        // If the item that the user entered is less than the first item in the linked list
        else if (first->next->partNumber > part->partNumber)
        {
        	// If we are creating our second item
        	if (isSecondIter)
        	{
        		isSecondIter = 0;
        		
        		// Link the part item that the user just entered to the item after it (The old first node)
	            part->next = first->next; 
	
	            // Give first the address for the item with the smallest part number that the user just entered
	            first->next = part;
	            
	            prev = part;
	            
	            current = part->next;
			}
			else
			{
	            part->next = first->next;
	
	            first->next = part;
			}
        }
        // If the item being added to the list is greater than previous but less than current
        else if (prev->partNumber < part->partNumber && current->partNumber > part->partNumber)
        {
        	// break the current links from prev to current and link part in between them
        	prev->next = part;
        	
        	part->next = current;
        	
        	// let prev hold the address to the item that the user just entered
        	prev = part;
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
        
        // Ask the user if they want to add another inventory item in the linked list
        choice = askAnotherItem(choice);
        
        if (choice == 'N')
            break;
    }
    
    printf("\nInventory list created.\n");
}


char askAnotherItem(char choice)
{
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

    return choice;
}


void printInventoryLst(struct Inventory *head, struct Inventory *first)
{
	printf("\n--------------------");
	
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
    printf("\n");
}


void selectItem(struct Inventory *head, struct Inventory *first)
{
	int partNumber;
	
	// Ask the user for the item they would like to print, then use head to traverse through the linked list
	printf("\nPlease enter the part number for the item you would like to print: ");
	scanf("\n%d", &partNumber);
	
	while (head != NULL)
	{
		// Print the selected item if a part number for the item has been found
		if (head->partNumber == partNumber)
		{
			printf("\n--------------------");
			printf("\nPart Number: %d", head->partNumber);
	        printf("\nQuantity: %d", head->quantity);
	        printf("\nPrice: $%.2f", head->price);
	        printf("\n--------------------\n");
	        
	        head = first->next;
	        return;
		}
		
		head = head->next;	
	}
	
	// If a part number has not been found, let the user know and reset head
	printf("\nThe item with the part number %d is not found!", partNumber);
	head = first->next;
}
