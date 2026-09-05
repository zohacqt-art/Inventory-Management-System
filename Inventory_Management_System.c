// CS-131 MUHAMMAD MUTAHHAR KHAN

#include <stdio.h>
#include <string.h>
#define maxProducts 50              // described the max products limit that can be added in the inventory
#define FILE_NAME "inventory.dat"   // described the file name

void menu();
void addProduct();
void deleteProduct();
void sellProduct();
void bill(int, int);
void lowStockReport();
void saveInventory();
void loadInventory();
void displayItems();
void updateItem();

// creating a structure that wil store information about the product
struct Product
{
    int id;
    char name[60];
    int quantity;
    float price;
};

struct Product products[maxProducts];
int count = 0;

int main()
{
    // login details:
    char username[] = "AdminMember";
    char password[] = "admin@678";

    char user[20];
    char pass[20];

    while (1)
    {

        printf("Enter Username (or type exit to quit): ");
        scanf(" %[^\n]", user);

        if (strcmp(user, "exit") == 0)
            return 0;

        if (strcmp(user, username) == 0)
        {

            printf("Enter Password: ");
            scanf(" %[^\n]", pass);

            if (strcmp(pass, password) == 0)
            {
                printf("Login Successful!\n");

                while (1)
                {

                    menu();
                    int option;
                    printf("Enter your option: ");
                    scanf("%d", &option);

                    switch (option)
                    {
                    case 1:
                        addProduct();
                        break;
                    case 2:
                        deleteProduct();
                        break;
                    case 3:
                        displayItems();
                        break;
                    case 4:
                        sellProduct();
                        break;
                    case 5:
                        updateItem();
                        break;
                    case 6:
                        lowStockReport();
                        break;
                    case 7:
                        saveInventory();
                        break;
                    case 8:
                        loadInventory();
                        break;
                    case 9:
                        printf("You exited the program successfully.\n");
                        return 0;
                    default:
                        printf("Invalid option!\n");
                    }
                }
            }
            else
            {
                printf("Incorrect Password! Try again.\n");
            }
        }
        else
        {
            printf("Incorrect Username! Try again.\n");
        }
    }

    return 0;
}

void menu()
{
    printf("<----INVETORY MANAGEMENT SYSTEM---->\n");
    printf("1. Add Product\n");
    printf("2. Delete Product\n");
    printf("3. Display Product\n");
    printf("4. Sell Product\n");
    printf("5. Update Product\n");
    printf("6. Low Stock Report\n");
    printf("7. Save Inventory\n");
    printf("8. Load Inventory\n");
    printf("9. Exit\n");
}

void addProduct() // Function to Add a Product
{
    if (count == maxProducts) // checkng whether the inventory is full or not
    {
        printf("Maximum Limit Reached\n");
        return;
    }
    printf("Enter Product ID: ");
    scanf("%d", &products[count].id);
    printf("Enter Product Name: ");
    scanf(" %[^\n]", products[count].name);
    printf("Enter Product Quantity: ");
    scanf("%d", &products[count].quantity);
    printf("Enter Product Price: ");
    scanf("%f", &products[count].price);
    count++;

    printf("This Product has been added successfully.\n\n");
}

void deleteProduct() // Function to Delete a product
{
    int ID, index = -1;
    printf("Enter Product ID: ");
    scanf("%d", &ID);

    // Step 1: Find product index
    for (int i = 0; i < count; i++)
    {
        if (products[i].id == ID)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Product not found!\n\n");
        return;
    }

    // Step 2: Shift items left
    for (int i = index; i < count - 1; i++)
    {
        products[i] = products[i + 1];
    }
    count--;

    printf("Product deleted successfully.\n\n");
}

void bill(int i, int quantity) // Function to Generate the Bill
{
    printf("\n<---- GENERATED BILL ---->\n");
    printf("ID: %d\nNAME: %s\nQUANTITY: %d\n\nTOTAL PRICE= %.3f\n\n", products[i].id, products[i].name, quantity, (products[i].price) * quantity);
    printf("\n<------------------------>\n\n");
    printf("The bill is generated successfully!\n\n");
}


// CS-101 AYESHA DANIYAL

// Function to sell a product
void sellProduct()
{
    int id, quantity, i;
    printf("Enter product ID to sell: ");
    scanf("%d", &id);

    // Find the product in the inventory
    for (i = 0; i < count; i++)
    {
        if (products[i].id == id)
        {
            printf("Enter quantity to sell: ");
            scanf("%d", &quantity);
            if (quantity <= products[i].quantity)
            {
                bill(i, quantity);
                printf("Product sold successfully!\n\n");
                products[i].quantity -= quantity;
            }
            else
            {
                printf("Insufficient stock!\n\n");
            }
            return;
        }
    }
    printf("Product not found!\n\n");
}

// Function to generate low stock report
void lowStockReport()
{
    int threshold, i, found = 0;
    printf("Enter low stock threshold: ");
    scanf("%d", &threshold);
    printf("Low Stock Report:\n");

    for (i = 0; i < count; i++)
    {

        if (products[i].quantity < threshold)    //below threshold
        {
            printf("ID: %d, Name: %s, Quantity: %d is below threshold.\n\n", products[i].id, products[i].name, products[i].quantity);
            found = 1;
        }
        else if (products[i].quantity == threshold)  //equals to threshold
        {
            printf("ID: %d, Name: %s, Quantity: %d is equal to threshold.\n\n", products[i].id, products[i].name, products[i].quantity);
            found = 1;
        }
}
    if(found==0)  //if enough stock is available
    {
         printf("Everything is above threshold.\n");
    }
}

// Function to save inventory to file
void saveInventory()
{
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "%d\n", count);
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d %s %d %f\n", products[i].id, products[i].name, products[i].quantity, products[i].price);
    }
    fclose(file);

    printf("Inventory saved to file successfully!\n\n");
}

// Function to load inventory from file
void loadInventory()
{

    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL)
    {
        printf("No inventory file found!\n");
        return;
    }

    fscanf(file, "%d", &count);
    fgetc(file);
    for (int i = 0; i < count; i++)
    {
        fscanf(file, "%d\t%s\t%d\t%f\n", &products[i].id, products[i].name, &products[i].quantity, &products[i].price);
    }
    fclose(file);

    printf("Inventory loaded from file successfully!\n\n");
}


// CS-143 MUHAMMAD MOOSA IQBAL

void updateItem()
{
    int id, found = 0;
    printf("Enter Item ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++)
    {
        //enter information to update
        if (products[i].id == id)
        {
            found = 1;
            printf("Enter new quantity: ");
            scanf("%d", &products[i].quantity);
            printf("Enter new price: ");
            scanf("%f", &products[i].price);
            printf("Item updated successfully!\n\n");
            break;
        }
    }

    if (!found)
        printf("Item not found!\n");
}

void displayItems()
{

    printf("\n%-10s %-20s %-10s %-10s\n", "ID", "Name", "Quantity", "Price");
    printf("--------------------------------------------------\n");

    //displays the product id,name,quantity,price:
    for (int i = 0; i < count; i++)
    {
        printf("%-10d %-20s %-10d %-10.2f\n\n", products[i].id, products[i].name, products[i].quantity, products[i].price);
    }
}