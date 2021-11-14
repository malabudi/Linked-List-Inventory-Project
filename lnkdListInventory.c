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

// Function prototypes
void displayCommands();
void createInventoryLst(struct Inventory *first, struct Inventory *prev, struct Inventory *current, struct Inventory *part, struct Inventory *head);
char askAnotherItem(char choice);
void printInventoryLst(struct Inventory *head);
void selectItem(struct Inventory *head);
void modifyItem(struct Inventory *head);
void deleteItem(struct Inventory *head, struct Inventory *part);
void askItem(struct Inventory *part);
void insertItem(struct Inventory *head, struct Inventory *part, struct Inventory *first);
void saveList(struct Inventory *head);
void addList(struct Inventory *head, struct Inventory *part, struct Inventory *first);


int main()
{
	// Declare a part, first object in linked list, and prev objec in linkedlst Inventory pointers
	struct Inventory *first, *prev, *current, *part, *head;

	// Allocate memory and make first-> and current->next attributes NULL
	first = malloc(sizeof(*first));
	current = malloc(sizeof(*current));
	first->next = NULL;
	current->next = NULL;

	char choice[6];     // Hold user's command
	int isCreated = 0;      // Check if the user created a inventory linked list yet

	printf("\nWelcome To The Inventory Program:");

	// Display a list of commands to the user
	displayCommands();

	while (strcmp(choice, "exit") != 0)
    {
        scanf("\n%s", choice);

        // Create a new linked list while maintaining numerical order by part number
        if (strcmp(choice, "create") == 0)
        {
            if (isCreated == 0)
            {
                createInventoryLst(first, prev, current, part, head);

                isCreated = 1;      // A new list has been created, so set this bool to true
            }
            else
            {
                printf("\nYou have already created an inventory list.\n");
            }
        }
        // Print the entire linked list
        else if (strcmp(choice, "print") == 0)
        {
            if (isCreated)
                printInventoryLst(head);
            else
                printf("\nCan not print the list, you have not created one.\n");
        }
        // Select a item from the linked list and print it
        else if (strcmp(choice, "select") == 0)
        {
            if (isCreated)
                selectItem(head);
            else
                printf("\nCan not select a item in the list, you have not created one.\n");
        }
        // Modify a item from the linked by updating qty and price
        else if (strcmp(choice, "modify") == 0)
        {
            if (isCreated)
                modifyItem(head);
            else
                printf("\nCan not modify the list, you have not created one.\n");
        }
        else if (strcmp(choice, "delete") == 0)
        {
            if (isCreated)
                deleteItem(head, part);
            else
                printf("\nCan not delete a item in the list, you have not created one.\n");
        }
        else if (strcmp(choice, "insert") == 0)
        {
            if (isCreated)
            {
                part = malloc(sizeof(*part));
                askItem(part);

                // call insert item function
                insertItem(head, part, first);
                printf("\nItem successfully inserted\n");
            }
            else
                printf("\nCan not insert a item in the list, you have not created one.\n");
        }
        else if (strcmp(choice, "save") == 0)
        {
            if (isCreated)
                saveList(head);
            else
                printf("\nInventory list not found, unable to save to CSV file.\n");
        }
        else if (strcmp(choice, "add") == 0)
        {
            if (isCreated)
                addList(head, part, first);
            else
                printf("\nCreate a file first before adding an existing list from a CSV file.\n");
        }
        else if(strcmp(choice, "help") == 0)
        	displayCommands();

        // Reset head after every command is called
        head = first->next;
    }

    return 0;
}



// User defined functions
void displayCommands()
{
    // Print all the commands in the program
    printf("\n\"create\"");
    printf("\n\"print\"");
    printf("\n\"select\"");
    printf("\n\"modify\"");
    printf("\n\"delete\"");
    printf("\n\"insert\"");
    printf("\n\"save\"");
    printf("\n\"add\"");
    printf("\n\"exit\"");
    printf("\n\"help\"\n");
}


void createInventoryLst(struct Inventory *first, struct Inventory *prev, struct Inventory *current, struct Inventory *part, struct Inventory *head)
{
    char choice;
    int isSecondIter = 1; // Is the second item created yet

    // Upon first iteration, use previous to hold the first item added into inventory linked list before while loop
    prev = malloc(sizeof(*prev));
    askItem(prev);

    fflush(stdin);

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

        // Allocate memory for the current structure pointer first
        part = malloc(sizeof(*part));

        // Let the user enter values of the Inventory element in the linked list
        askItem(part);
        fflush(stdin);

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


void printInventoryLst(struct Inventory *head)
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
    printf("\n");
}


void selectItem(struct Inventory *head)
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
	        return;
		}

		head = head->next;
	}
	// If a part number has not been found, let the user know and reset head
	printf("\nItem with part number %d not found.\n", partNumber);
}


void modifyItem(struct Inventory *head)
{
    int partNumber, newQty, newPrice;

    printf("\nPlease enter the part number for the item you would like to modify: ");
    scanf("\n%d", &partNumber);

    // Traverse through the linked list until the item with the inputted part number has been found
    while (head != NULL)
    {
        if (head->partNumber == partNumber)
        {
            // Ask the user for the new quantity and price that they would like to modify in the item they have selected
            printf("\nPlease enter the quantity of the item: ");
            scanf("\n%d", &newQty);
            printf("\nPlease enter the price of the item: ");
            scanf("\n%d", &newPrice);

            // Update the qty and price in the item and let the user know it was successful
            head->quantity = newQty;
            head->price = newPrice;
            printf("\nThe item with part number %d has successfully modified\n", partNumber);
            return;
        }

        head = head->next;
    }
    printf("\nItem with part number %d not found.\n", partNumber);
}


void deleteItem(struct Inventory *head, struct Inventory *part)
{
    struct Inventory *temp;     // Have it hold the address for the item before head
    int partNumber;

    printf("\nPlease enter the part number for the item you would like to delete: ");
    scanf("\n%d", &partNumber);

    while (head != NULL)
    {
        // look ahead one item and compare part number to not lose the address of the item before the one the user wants to delete
        if (head->partNumber == partNumber)
        {
            // Link the node before the one being deleted to the one that is in front of that node
            temp->next = head->next;

            // Free the item being deleted in memory
            free(head);

            printf("\nItem deleted\n");
            return;
        }

        temp = head;    // Give it the address for head before head traverses up a node
        head = head->next;
    }

    printf("\nItem with part number %d not found.\n", partNumber);
}


void askItem(struct Inventory *item)
{
    // Ask the user information about the item and put it into the structure
    printf("\nPart Number: ");
    scanf("\n%d", &item->partNumber);
    printf("\nQuantity: ");
    scanf("\n%d", &item->quantity);
    printf("\nPrice: ");
    scanf("\n%f", &item->price);
    item->next = NULL;
}


void insertItem(struct Inventory *head, struct Inventory *part, struct Inventory *first)
{
    while (head != NULL)
    {
        // First check if the new item is less than the first one, if so insert and make it the new first item
        if (part->partNumber < first->next->partNumber)
        {
            part->next = first->next;
            first->next = part;
            return;
        }
        // If the user enters a part number larger than the last item of the list, link the last item to the new item
        else if (head->next == NULL)
        {
            head->next = part;
            return;
        }
        // When we find that the item is within the list by part number, insert it and link it like so
        else if (part->partNumber < head->next->partNumber)
        {
            part->next = head->next;
            head->next = part;
            return;
        }

        head = head->next;
    }

    printf("\nInsertion failed.");
}


void saveList(struct Inventory *head)
{
    // Save the inventory linked list to a CSV file
    FILE *filePtr;

    char fileName[50];
    int isFirstLine = 1;

    // Ask for file name and open it in write mode with strcat inside to concatenate the file name with .csv
    fflush(stdin);
    printf("\nWhat would you like to name your file: ");
    fgets(fileName, 50, stdin);

    fileName[strcspn(fileName, "\n")] = '\0';

    strcat(fileName, ".csv");
    filePtr = fopen(fileName, "w");

    printf("\nSaving to %s file...", fileName);

    while (head != NULL)
    {
        // add a \n before adding new CSVs after the first line
        if (!isFirstLine)
            fprintf(filePtr, "\n");

        // write to file the partNumber, quantity, and price as the linked list iterates
        fprintf(filePtr, "%d,%d,%.2f", head->partNumber, head->quantity, head->price);
        head = head->next;

        isFirstLine = 0;
    }

    fclose(filePtr);
    printf("\n%s saved.\n", fileName);
}


void addList(struct Inventory *head, struct Inventory *part, struct Inventory *first)
{
    // add the list from the CSV file into the current list into the program
    FILE *filePtr;

    char fileName[50];

    // Ask for the file name to add to the current list
    fflush(stdin);
    printf("\nPlease enter the name of the file (do not inclue .csv): ");
    fgets(fileName, 50, stdin);

    fileName[strcspn(fileName, "\n")] = '\0';

    strcat(fileName, ".csv");
    filePtr = fopen(fileName, "r");

    // Check if file exists
    if (filePtr == NULL)
    {
        printf("\nError: File not found.\n");
        return;
    }
    // Break out of loop when the program has no more lines to read in the csv file
    while (!feof(filePtr))
    {
        // use fscanf to read each comma separated value and assign them to the attributes in the part structure
        part = malloc(sizeof(*part));
        fscanf(filePtr, "%d,%d,%f", &part->partNumber, &part->quantity, &part->price);
        part->next = NULL;

        // call insert item function to individually insert each item from the CSV file
        insertItem(head, part, first);

        head = first->next;
    }

    fclose(filePtr);
    printf("\nAdded the list from %s to the program\n", fileName);
}
