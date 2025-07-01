#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void createFile();
void readFile();
void updateFile();
void deleteFile();
void copyFile();
void mergeFiles();
void compareFiles();
void searchInFile();



int main() {
    int val;

    do {
        printf("\nFile Management System:\n");
        printf("1. Create File\n");
        printf("2. Read File\n");
        printf("3. Update File\n");
        printf("4. Delete File\n");
        printf("5. Copy File\n");
        printf("6. Merge Files\n");
        printf("7. Compare Files\n");
        printf("8. Search in File\n");
        printf("9. Exit\n");
        printf("Enter option: ");
        scanf("%d", &val);
        getchar();

        switch (val) {
            case 1: createFile(); break;
            case 2: readFile(); break;
            case 3: updateFile(); break;
            case 4: deleteFile(); break;
            case 5: copyFile(); break;
            case 6: mergeFiles(); break;
            case 7: compareFiles(); break;
            case 8: searchInFile(); break;
            case 9: printf("Exiting...\n"); break;
            default: printf("Invalid option.\n");
        }
    } while (val != 9);

    return 0;
}




void createFile() {
    char filename[100], content[1000];
    FILE *file;

    printf("Enter filename to create: ");
    scanf("%s", filename);
    getchar();
    
    file = fopen(filename, "r");

    if(file != NULL){
        printf("File name already exists.\n");
        fclose(file);
        return;
    }

    file = fopen(filename, "w");

    printf("Enter content :\n");
    fgets(content, sizeof(content), stdin);
    fputs(content, file);
    fclose(file);
    printf("File created.\n");
}



void readFile() {
    char filename[100], ch;
    FILE *file;

    printf("Enter filename to read: ");
    scanf("%s", filename);
    
    file = fopen(filename, "r");
    if (!file) {
        perror("Error");
        return;
    }

    printf("\nFile content:\n");
    while ((ch = fgetc(file)) != EOF)
        putchar(ch);
    fclose(file);
}




void updateFile() {
    char filename[100], content[1000];
    FILE *file;

    printf("Enter filename to update: ");
    scanf("%s", filename);
    getchar();

    file = fopen(filename, "r");

    if(!file){
        printf("File not found.\n");
        return;
    }
    
    file = fopen(filename, "w");
    if (!file) {
        perror("Error");
        return;
    }

    printf("Enter content to update:\n");
    fgets(content, sizeof(content), stdin);
    fputs(content, file);
    fclose(file);
    printf("File updated.\n");
}



void deleteFile() {
    char filename[100];
    
    printf("Enter filename to delete: ");
    scanf("%s", filename);

    if (remove(filename) == 0)
        printf("File deleted successfully.\n");
    else
        perror("Error deleting file");
}



void copyFile() {
    char src[100], dest[100];
    char ch;
    FILE *first, *second;

    printf("Enter source filename: ");
    scanf("%s", src);
    
    first = fopen(src, "r");
    if (!first) {
        printf("File not found\n");
        return;
    }

    printf("Enter destination filename: ");
    scanf("%s", dest);

    second = fopen(dest, "r");
    if(second != NULL){
        printf("Destination file already exists.\n");
        return;
    }

    second = fopen(dest, "w");

    while ((ch = fgetc(first)) != EOF){
        fputc(ch, second);
    }

    fclose(first);
    fclose(second);
    printf("File copied.\n");
}



void mergeFiles() {

    char file1[100], file2[100], dest[100];
    char ch;
    FILE *first, *second, *third;

    printf("Enter first filename: ");
    scanf("%s", file1);

    first = fopen(file1, "r");
    if (!first) {
        printf("File not found\n");
        return;
    }

    printf("Enter second filename: ");
    scanf("%s", file2);

    second = fopen(file2, "r");
    if (!second) {
        printf("File not found\n");
        return;
    }


    printf("Enter destination filename: ");
    scanf("%s", dest);

    third = fopen(dest, "r");
    if (third != NULL) {
        printf("File already exists.\n");
        return;
    }

    third = fopen(dest, "w");

    while ((ch = fgetc(first)) != EOF){
        fputc(ch, third);
    }
    while ((ch = fgetc(second)) != EOF){
        fputc(ch, third);
    }

    fclose(first);
    fclose(second);
    fclose(third);
    printf("Both files merged into one.\n");
}



void compareFiles() {
    char file1[100], file2[100];
    char line1[1000], line2[1000];
    FILE *first, *second;
    int lineNum = 1, isDifferent = 0;

    printf("Enter first filename: ");
    scanf("%s", file1);

    first = fopen(file1, "r");
    if (!first) {
        printf("First file not found\n");
        return;
    }

    printf("Enter second filename: ");
    scanf("%s", file2);

    second = fopen(file2, "r");
    if (!second) {
        printf("Second file not found\n");
        return;
    }

    while (fgets(line1, sizeof(line1), first) && fgets(line2, sizeof(line2), second)) {
        if (strcmp(line1, line2) != 0) {
            printf("Difference at line %d:\n", lineNum);
            printf("File1: %s\n", line1);
            printf("File2: %s\n", line2);
            isDifferent = 1;
        }
        lineNum++;
    }

    if (!isDifferent)
        printf("Files are identical.\n");

    fclose(first);
    fclose(second);
}



void searchInFile() {
    char filename[100], keyword[1000], line[1000];
    FILE *file;
    int found = 0, lineNum = 1;

    printf("Enter filename to search in: ");
    scanf("%s", filename);
    getchar(); 

    file = fopen(filename, "r");
    if (!file) {
        printf("File not found.\n");
        return;
    }

    printf("Enter word or phrase to search: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    printf("Search Results : \n");
 
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, keyword)) {
            printf("Line %d: %s\n", lineNum, line);
            found = 1;
        }
        lineNum++;
    }

    if (!found){
        printf("'%s' not found in file '%s'.\n", keyword, filename);
    }

    fclose(file);
}
