#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "solar_data.txt"
#define MAX_PLANETS 100

struct Planet {
    char name[30];
    float distance;   
    float diameter;   
    int moons;
};


void menu();
void addPlanet(struct Planet *p, int *count);
void displayPlanets(struct Planet *p, int count);
void searchPlanet(struct Planet *p, int count, char name[]);
void updatePlanet(struct Planet *p, int count);
void deletePlanet(struct Planet *p, int *count);
void saveToFile(struct Planet *p, int count);
void loadFromFile(struct Planet *p, int *count);


int main() {
    struct Planet planets[MAX_PLANETS];
    int count = 0, choice;
    char searchName[30];

    loadFromFile(planets, &count);

    while (1) {
        menu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Exiting.\n");
            break;
        }
     getchar();

 switch (choice) {
    case 1:
        addPlanet(planets, &count);
         break;
     case 2:
         displayPlanets(planets, count);
          break;
     case 3:
        printf("Enter planet name to search: ");
         fgets(searchName, sizeof(searchName), stdin);
        searchName[strcspn(searchName, "\n")] = '\0';
         searchPlanet(planets, count, searchName);
                break;
     case 4:
         updatePlanet(planets, count);
             break;
    case 5:
        deletePlanet(planets, &count);
        break;
     case 6:
        saveToFile(planets, count);
         break;
     case 7:
          printf("Exiting... Data saved.\n");
          saveToFile(planets, count);
            exit(0);
    default:
         printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}


void menu() {
    printf("\n========== SOLAR SYSTEM MANAGEMENT =========\n");
    printf("1. Add Planet\n");
    printf("2. Display All Planets\n");
    printf("3. Search Planet\n");
    printf("4. Update Planet Details\n");
    printf("5. Delete Planet\n");
    printf("6. Save Data to File\n");
    printf("7. Exit\n");
    printf("=========================================\n");
}


void addPlanet(struct Planet *p, int *count) {
    if (*count >= MAX_PLANETS) {
        printf("Database full! Cannot add more planets.\n");
        return;
    }

    struct Planet *ptr = &p[*count];

    printf("Enter planet name: ");
    fgets(ptr->name, sizeof(ptr->name), stdin);
    ptr->name[strcspn(ptr->name, "\n")] = '\0';

    printf("Enter distance from Sun (in million km): ");
    scanf("%f", &ptr->distance);
    printf("Enter diameter (in km): ");
    scanf("%f", &ptr->diameter);
    printf("Enter number of moons: ");
    scanf("%d", &ptr->moons);
    getchar();

    (*count)++;
    printf("Planet added successfully!\n");
}

void displayPlanets(struct Planet *p, int count) {
    if (count == 0) {
        printf("No planet data available.\n");
        return;
    }

    printf("\n%-5s %-15s %-15s %-15s %-10s\n", "No.", "Name", "Distance", "Diameter", "Moons");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-5d %-15s %-15.2f %-15.2f %-10d\n",
               i + 1, p[i].name, p[i].distance, p[i].diameter, p[i].moons);
    }
}


void searchPlanet(struct Planet *p, int count, char name[]) {
    for (int i = 0; i < count; i++) {
        if (strcasecmp(p[i].name, name) == 0) {
            printf("\nPlanet Found:\n");
            printf("Name: %s\nDistance from Sun: %.2f million km\nDiameter: %.2f km\nMoons: %d\n",
                   p[i].name, p[i].distance, p[i].diameter, p[i].moons);
            return;
        }
    }
    printf("Planet '%s' not found.\n", name);
}


void updatePlanet(struct Planet *p, int count) {
    char name[30];
    printf("Enter planet name to update: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

 for (int i = 0; i < count; i++) {
     if (strcasecmp(p[i].name, name) == 0) {
        printf("Updating details for %s:\n", p[i].name);
         printf("Enter new distance (million km): ");
         scanf("%f", &p[i].distance);
         printf("Enter new diameter (km): ");
        scanf("%f", &p[i].diameter);
          printf("Enter new number of moons: ");
          scanf("%d", &p[i].moons);
             getchar();
            printf("Planet updated successfully!\n");
            return;
        }
    }
    printf("Planet '%s' not found.\n", name);
}

void deletePlanet(struct Planet *p, int *count) {
    char name[30];
    printf("Enter planet name to delete: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    for (int i = 0; i < *count; i++) {
        if (strcasecmp(p[i].name, name) == 0) {
            for (int j = i; j < *count - 1; j++) {
                p[j] = p[j + 1];
            }
            (*count)--;
            printf("Planet '%s' deleted successfully.\n", name);
            return;
        }
    }
    printf("Planet '%s' not found.\n", name);
}

void saveToFile(struct Planet *p, int count) {
    FILE *fp = fopen("solar_system.txt", "w");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%.2f,%.2f,%d\n",
                p[i].name, p[i].distance, p[i].diameter, p[i].moons);
    }
    fclose(fp);
    printf("Data saved to '%s' successfully.\n", *fp);
}


void loadFromFile(struct Planet *p, int *count) {
    FILE *fp = fopen("solar_system.txt", "r");
    if (!fp) {
        printf("No previous data found. Starting fresh.\n");
        return;
    }

    while (fscanf(fp, "%s,%f,%f,%d\n",
             p[*count].name,
            &p[*count].distance,
             &p[*count].diameter,
             &p[*count].moons) == 4) {
        (*count)++;
        if (*count >= MAX_PLANETS) break;
    }
    fclose(fp);
    printf("Loaded %d records from '%s'.\n", *count, *fp);
}