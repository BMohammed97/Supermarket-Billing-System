#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 120

// Function prototype for parsing sales records
void FillSale(char *, char *, char *, char *, char *, int *, float *);

// Structure to hold a single sale record
typedef struct Sale {
    char Receipt_Code[6];
    char Customer_Name[18];
    char Product_Name[24];
    int Qty;
    float Price;
    char Date[13];
} Sale;

int main()
{
    FILE *FileRead;
    FILE *FileWrite;
    Sale Sales[339];
    char Buffer[N];
    char Receipt_Code_before[6] = "";
    float Total = 0;
    int CurrentLine = 1;
    int LineSale = 0;

    // Open the source file for reading
    FileRead = fopen("sales.txt", "r");
    if (FileRead == NULL) {
        return 1;
    } else {
        // Read the file line by line
        while (fgets(Buffer, N, FileRead) != NULL) {
            // Skip the first 2 lines (headers and dividers)
            if (CurrentLine >= 3) {
                FillSale(Buffer, Sales[LineSale].Receipt_Code, Sales[LineSale].Customer_Name,
                         Sales[LineSale].Product_Name, Sales[LineSale].Date, &Sales[LineSale].Qty,
                         &Sales[LineSale].Price);
                LineSale++;
            }
            CurrentLine++;
        }
        fclose(FileRead);
    }

    // Open the destination file for writing formatted invoices
    FileWrite = fopen("SalesWriteBons.txt", "w");
    int i = 0;

    if (FileWrite == NULL) {
        return 1;
    } else {
        // Initialize with the first record's receipt code
        strcpy(Receipt_Code_before, Sales[0].Receipt_Code);

        // Loop through all processed sales records
        while (!strcmp(Receipt_Code_before, Sales[i].Receipt_Code) && i < 339) {
            // Print receipt header
            fprintf(FileWrite, "\n_________________________________________________\n");
            fprintf(FileWrite, "\t%s\n%s\t\t%s\n", Sales[i].Customer_Name, Sales[i].Receipt_Code, Sales[i].Date);

            // Loop and print all items under the same receipt code
            while (!strcmp(Receipt_Code_before, Sales[i].Receipt_Code)) {
                fprintf(FileWrite, "\n%-6d %-20s %6.2f %6.2f", Sales[i].Qty, Sales[i].Product_Name,
                        Sales[i].Price, Sales[i].Qty * Sales[i].Price);
                Total += Sales[i].Qty * Sales[i].Price;
                i++;
            }

            // Print receipt total footer and reset total for the next invoice
            fprintf(FileWrite, "\n\nTotal -------->>>>\t%.2f", Total);
            Total = 0;

            // Move to the next receipt code
            strcpy(Receipt_Code_before, Sales[i].Receipt_Code);
        }
        fclose(FileWrite);
    }

    return 0;
}

// Function to extract structured data fields from the text buffer line
void FillSale(char *Buffer, char *Receipt_Code, char *Customer_Name, char *Product_Name,
              char *Date, int *Qty, float *Price) {
    int i = 0;

    // 1. Extract Receipt Code (Fixed width: 5 chars from index 0)
    for (int i = 0; i < 5; i++) {
        Receipt_Code[i] = Buffer[i];
    }
    Receipt_Code[5] = '\0';

    // 2. Extract Customer Name (Starts at index 29, breaks on double spaces)
    for (i = 0; i < 17; i++) {
        Customer_Name[i] = Buffer[i + 29];
        if ((Buffer[i + 29] == ' ') && (Buffer[i + 1 + 29] == ' '))
            break;
    }
    Customer_Name[i] = '\0';

    // 3. Extract Product Name (Starts at index 55, breaks on double spaces)
    for (i = 0; i < 23; i++) {
        Product_Name[i] = Buffer[i + 55];
        if ((Buffer[i + 55] == ' ') && (Buffer[i + 1 + 55] == ' '))
            break;
    }
    Product_Name[i] = '\0';

    // 4. Extract Quantity (Starts at index 80, breaks on double spaces)
    char Qty_Val_String[6];
    for (i = 0; i < 5; i++) {
        Qty_Val_String[i] = Buffer[i + 80];
        if ((Buffer[i + 80] == ' ') && (Buffer[i + 1 + 80] == ' '))
            break;
    }
    Qty_Val_String[i] = '\0';
    *Qty = atoi(Qty_Val_String); // Convert string to integer

    // 5. Extract Unit Price (Starts at index 87, breaks on double spaces)
    char Price_Val_String[11];
    for (i = 0; i < 10; i++) {
        Price_Val_String[i] = Buffer[i + 87];
        if ((Buffer[i + 87] == ' ') && (Buffer[i + 1 + 87] == ' '))
            break;
    }
    Price_Val_String[i] = '\0';
    *Price = atof(Price_Val_String); // Convert string to float

    // 6. Extract Date, convert short month name format, and format final string
    int day, month, year;
    char Date_Val_String[11];
    const char *Months[] = {"", "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
                            "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

    for (i = 0; i < 10; i++) {
        Date_Val_String[i] = Buffer[i + 16];
        if ((Buffer[i + 16] == ' ') && (Buffer[i + 1 + 16] == ' '))
            break;
    }
    Date_Val_String[i] = '\0';

    sscanf(Date_Val_String, "%d-%d-%d", &day, &month, &year);
    snprintf(Date, 13, "%02d %s %04d", day, Months[month], year);
}
