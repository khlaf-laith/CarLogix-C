#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Car {
    int id;
    char Type[20];
    char Color[20];
    char Name[20];
    int Phone;
};

static int compare_car_ids(const void *left, const void *right) {
    const struct Car *car1 = left;
    const struct Car *car2 = right;
    return (car1->id > car2->id) - (car1->id < car2->id);
}

void input_data(int n, struct Car c[]) {
    int i = 0, j = 0;
    bool ok = false;
    for (i = 0; i < n; i++) {
        printf("Enter the id car: \n");
        scanf("%d", &c[i].id);
        while (1) {
            ok = false;
            for (j = 0; j < i; j++) {
                if (c[i].id == c[j].id && i != j) {
                    ok = true;
                }
            }
            if (c[i].id > 0 && ok == false) {
                break;
            } else {
                printf("The car ID is invalid or already exists, re-input id!! \n");
                scanf("%d", &c[i].id);
            }
        }
        printf("Enter the type car: \n");
        scanf("%19s", c[i].Type);
        printf("Enter the color car: \n");
        scanf("%19s", c[i].Color);
        printf("Enter the name person: \n");
        scanf("%19s", c[i].Name);
        printf("Enter the Tel person: \n");
        scanf("%d", &c[i].Phone);
        printf("------------------------\n");
    }
    qsort(c, n, sizeof(c[0]), compare_car_ids);
}

void file_storg(struct Car c[], int n, char *file_name) {
    FILE *fptr = fopen(file_name, "wb");
    if (fptr == NULL) {
        printf("Error in create file!!\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        fwrite(&c[i], sizeof(struct Car), 1, fptr);
    }
    fclose(fptr);
}

void display_file(char *file_name) {
    FILE *fptr = fopen(file_name, "rb");
    if (fptr == NULL) {
        printf("File not found or empty!!\n");
        return;
    }
    struct Car c;
    while (fread(&c, sizeof(struct Car), 1, fptr) == 1) {
        printf("The id car: %d \n", c.id);
        printf("The type car: %s \n", c.Type);
        printf("The color car: %s \n", c.Color);
        printf("The name: %s \n", c.Name);
        printf("The Tel: %d \n", c.Phone);
        printf("------------------------\n");
    }
    fclose(fptr);
}

int serche1(char *filename, int x) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        return 1;
    }
    struct Car c;
    while (fread(&c, sizeof(struct Car), 1, f) == 1) {
        if (x == c.id) {
            fclose(f);
            return 0;
        }
    }
    fclose(f);
    return 1;
}

void Add_car(char *filename, struct Car c) {
    FILE *f = fopen(filename, "ab");
    if (f == NULL) {
        printf("ERROR\n");
        return;
    }
    fwrite(&c, sizeof(struct Car), 1, f);
    fclose(f);

    f = fopen(filename, "rb");
    if (f == NULL) return;
    struct Car cars[100];
    int count = 0;
    while (count < 100 && fread(&cars[count], sizeof(cars[count]), 1, f) == 1) {
        count++;
    }
    fclose(f);

    qsort(cars, count, sizeof(cars[0]), compare_car_ids);

    f = fopen(filename, "wb");
    if (f == NULL) return;
    for (int i = 0; i < count; i++) {
        fwrite(&cars[i], sizeof(cars[i]), 1, f);
    }
    fclose(f);
}

struct Date {
    int d;
    int m;
    int y;
};

struct tymp_PIECES {
    int id;
    int count;
    float total_price;
};

struct Prossing {
    int Pro_id;
    int Car_id;
    struct Date d;
    int Count_type_piece;
    struct tymp_PIECES A[100];
    float Cost_pro;
    float total_cost;
};

struct PIECES {
    int piec_id;
    float price;
    char piec_name[20];
};

void Create_file_piec(char *file_name) {
    FILE *fptr = fopen(file_name, "ab");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }
    struct PIECES p;
    int ch;
    bool ok = true;
    do {
        printf("Enter the piece_id:\n");
        scanf("%d", &p.piec_id);
        printf("Enter the piece_price:\n");
        scanf("%f", &p.price);
        printf("Enter the piece_name:\n");
        scanf("%19s", p.piec_name);
        fwrite(&p, sizeof(p), 1, fptr);
        printf("If want input piece next enter (1)\n");
        scanf("%d", &ch);
        ok = (ch == 1);
    } while (ok);
    fclose(fptr);
}

void Display_pieces(char *file_name) {
    FILE *fptr = fopen(file_name, "rb");
    if (fptr == NULL) {
        printf("File not found!\n");
        return;
    }
    struct PIECES p;
    while (fread(&p, sizeof(p), 1, fptr) == 1) {
        printf("The piece_id is: %d\n", p.piec_id);
        printf("The piece_price is: %.2f\n", p.price);
        printf("The piece_name is: %s\n", p.piec_name);
        printf("------------------------\n");
    }
    fclose(fptr);
}

int serche_peci(char *filename, int x) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        return 1;
    }
    struct PIECES p;
    while (fread(&p, sizeof(struct PIECES), 1, f) == 1) {
        if (x == p.piec_id) {
            fclose(f);
            return 0;
        }
    }
    fclose(f);
    return 1;
}

float price(char *filename, int x) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        return 0.0f;
    }
    struct PIECES p;
    while (fread(&p, sizeof(struct PIECES), 1, f) == 1) {
        if (x == p.piec_id) {
            fclose(f);
            return p.price;
        }
    }
    fclose(f);
    return 0.0f;
}

void Create_file_Prossing(char *file_name, char *file_name1, char *filename2) {
    FILE *fptr = fopen(file_name, "ab");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }
    struct Prossing p;
    int ch;
    bool ok = true;
    float sum_cost;
    do {
        sum_cost = 0.0f;
        printf("Enter the Pro_id:\n");
        scanf("%d", &p.Pro_id);
        printf("Enter the Car_id:\n");
        scanf("%d", &p.Car_id);
        while (1) {
            if (serche1(file_name1, p.Car_id) == 1) {
                printf("The car is not found please re-enter:\n");
                scanf("%d", &p.Car_id);
            } else {
                break;
            }
        }
        printf("Enter the Date (day month year):\n");
        scanf("%d %d %d", &p.d.d, &p.d.m, &p.d.y);
        printf("Enter the Count_type_piece:\n");
        scanf("%d", &p.Count_type_piece);
        for (int i = 0; i < p.Count_type_piece; i++) {
            printf("Enter id pieces to type %d:\n", i + 1);
            scanf("%d", &p.A[i].id);
            while (1) {
                if (serche_peci(filename2, p.A[i].id) == 1) {
                    printf("The piece is not found please re-enter:\n");
                    scanf("%d", &p.A[i].id);
                } else {
                    break;
                }
            }
            printf("Enter count pieces to type %d:\n", i + 1);
            scanf("%d", &p.A[i].count);
            p.A[i].total_price = p.A[i].count * price(filename2, p.A[i].id);
            sum_cost += p.A[i].total_price;
        }
        printf("Enter the Cost_pro:\n");
        scanf("%f", &p.Cost_pro);
        p.total_cost = p.Cost_pro + sum_cost;
        fwrite(&p, sizeof(p), 1, fptr);
        printf("If want input processing next enter (1)\n");
        scanf("%d", &ch);
        ok = (ch == 1);
    } while (ok);
    fclose(fptr);
}

void Display_prossing(char *file_name) {
    FILE *fptr = fopen(file_name, "rb");
    if (fptr == NULL) return;
    struct Prossing p;
    while (fread(&p, sizeof(p), 1, fptr) == 1) {
        printf("The Pro_id: %d\n", p.Pro_id);
        printf("The Car_id: %d\n", p.Car_id);
        printf("The Date: %d/%d/%d\n", p.d.d, p.d.m, p.d.y);
        printf("The Count_type_piece: %d\n", p.Count_type_piece);
        printf("------------------------\n");
        for (int i = 0; i < p.Count_type_piece; i++) {
            printf("The id pieces to type %d: %d \n", i + 1, p.A[i].id);
            printf("The count pieces to type %d: %d \n", i + 1, p.A[i].count);
        }
        printf("The Cost_pro: %.2f$\n", p.Cost_pro);
        printf("The Total cost: %.2f$\n", p.total_cost);
    }
    fclose(fptr);
}

void Display_prossing_car(char *file_name, int x) {
    FILE *fptr = fopen(file_name, "rb");
    if (fptr == NULL) {
        printf("File not found!\n");
        return;
    }
    struct Prossing p;
    float sum = 0.0f;
    while (fread(&p, sizeof(p), 1, fptr) == 1) {
        if (p.Car_id == x) {
            printf("The processing_id: %d\n", p.Pro_id);
            sum += p.total_cost;
        }
    }
    printf("The Total cost is %.2f$\n", sum);
    fclose(fptr);
}

int comper_Date(struct Date d1, struct Date d2) {
    if (d1.y > d2.y) return 1;
    if ((d1.y == d2.y) && (d1.m > d2.m)) return 1;
    if ((d1.y == d2.y) && (d1.m == d2.m) && (d1.d > d2.d)) return 1;
    if ((d1.y == d2.y) && (d1.m == d2.m) && (d1.d == d2.d)) return 2;
    return 0;
}

void Display_car_prossing(char *file_name, struct Date d) {
    FILE *fptr = fopen(file_name, "rb");
    if (fptr == NULL) {
        printf("File not found!\n");
        return;
    }
    struct Prossing p;
    while (fread(&p, sizeof(p), 1, fptr) == 1) {
        if (comper_Date(p.d, d) == 1) {
            printf("The car_id: %d\n", p.Car_id);
        }
    }
    fclose(fptr);
}

void Delete_car(char *file_name, int x) {
    struct Car c;
    FILE *fptr = fopen(file_name, "rb");
    if (fptr == NULL) return;
    FILE *fptr2 = fopen("file_temp.bin", "wb");
    while (fread(&c, sizeof(struct Car), 1, fptr) == 1) {
        if (c.id != x) {
            fwrite(&c, sizeof(struct Car), 1, fptr2);
        }
    }
    fclose(fptr);
    fclose(fptr2);

    fptr = fopen(file_name, "wb");
    fptr2 = fopen("file_temp.bin", "rb");
    while (fread(&c, sizeof(struct Car), 1, fptr2) == 1) {
        fwrite(&c, sizeof(struct Car), 1, fptr);
    }
    fclose(fptr);
    fclose(fptr2);
    remove("file_temp.bin");
}

void Delete_pieces(char *file_name, int x) {
    struct PIECES c;
    FILE *fptr = fopen(file_name, "rb");
    if (fptr == NULL) return;
    FILE *fptr2 = fopen("file_temp.bin", "wb");
    while (fread(&c, sizeof(struct PIECES), 1, fptr) == 1) {
        if (c.piec_id != x) {
            fwrite(&c, sizeof(struct PIECES), 1, fptr2);
        }
    }
    fclose(fptr);
    fclose(fptr2);

    fptr = fopen(file_name, "wb");
    fptr2 = fopen("file_temp.bin", "rb");
    while (fread(&c, sizeof(struct PIECES), 1, fptr2) == 1) {
        fwrite(&c, sizeof(struct PIECES), 1, fptr);
    }
    fclose(fptr);
    fclose(fptr2);
    remove("file_temp.bin");
}

void saerch_person(char *filename, char name[]) {
    printf("The cars for person: %s \n", name);
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        printf("The file is not found \n");
        return;
    }
    struct Car c;
    bool ok = true;
    while (fread(&c, sizeof(struct Car), 1, f) == 1) {
        if (strcmp(name, c.Name) == 0) {
            printf("The car ID: %d\n", c.id);
            ok = false;
        }
    }
    if (ok) {
        printf("The person does not have cars \n");
    }
    fclose(f);
}

struct Node {
    struct Prossing p;
    struct Node *next;
};

bool is_empty(struct Node *start) {
    return (start == NULL);
}

void print_list(struct Node *start) {
    if (is_empty(start)) {
        printf("The List is empty \n");
        return;
    }
    struct Node *temp = start;
    while (temp != NULL) {
        printf("The Pro_id: %d\n", temp->p.Pro_id);
        printf("The Car_id: %d\n", temp->p.Car_id);
        printf("The Date: %d/%d/%d\n", temp->p.d.d, temp->p.d.m, temp->p.d.y);
        printf("The Count_type_piece: %d\n", temp->p.Count_type_piece);
        for (int i = 0; i < temp->p.Count_type_piece; i++) {
            printf("The id pieces to type %d: %d \n", i + 1, temp->p.A[i].id);
            printf("The count pieces to type %d: %d \n", i + 1, temp->p.A[i].count);
        }
        printf("The Cost_pro: %.2f$\n", temp->p.Cost_pro);
        printf("The Total cost: %.2f$\n", temp->p.total_cost);
        printf("------------------------\n");
        temp = temp->next;
    }
}

void insert_list(struct Node **start, struct Prossing p1) {
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->p = p1;
    temp->next = NULL;

    if (*start == NULL) {
        *start = temp;
        return;
    }
    struct Node *pre = NULL;
    struct Node *crr = *start;
    while (crr != NULL && crr->p.Car_id <= p1.Car_id) {
        pre = crr;
        crr = crr->next;
    }
    if (pre == NULL) {
        temp->next = *start;
        *start = temp;
    } else {
        pre->next = temp;
        temp->next = crr;
    }
}

void free_list(struct Node **start) {
    struct Node *temp;
    while (*start != NULL) {
        temp = *start;
        *start = (*start)->next;
        free(temp);
    }
}

struct Node *head = NULL;

void convert_file_2_list(char name[]) {
    free_list(&head);
    FILE *f = fopen(name, "rb");
    if (f == NULL) {
        printf("The file not found\n");
        return;
    }
    struct Prossing p;
    while (fread(&p, sizeof(struct Prossing), 1, f) == 1) {
        insert_list(&head, p);
    }
    fclose(f);
}

void type_piece(char *filename, int x, char *out_name) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        strcpy(out_name, "#");
        return;
    }
    struct PIECES p;
    while (fread(&p, sizeof(struct PIECES), 1, f) == 1) {
        if (x == p.piec_id) {
            strcpy(out_name, p.piec_name);
            fclose(f);
            return;
        }
    }
    fclose(f);
    strcpy(out_name, "#");
}

void display_tyep_car(char *filename, char *filename1, char *filename2) {
    FILE *f = fopen(filename, "rb");
    FILE *f1 = fopen(filename1, "rb");
    if (f == NULL || f1 == NULL) {
        printf("ERROR opening files\n");
        return;
    }
    struct Prossing p;
    struct Car c;
    char p_name[20];
    while (fread(&p, sizeof(struct Prossing), 1, f) == 1) {
        bool ok = false;
        for (int i = 0; i < p.Count_type_piece; i++) {
            type_piece(filename2, p.A[i].id, p_name);
            if (strcmp(p_name, "form") == 0 || strcmp(p_name, "tire") == 0) {
                ok = true;
            }
        }
        if (ok) {
            rewind(f1);
            while (fread(&c, sizeof(struct Car), 1, f1) == 1) {
                if (p.Car_id == c.id) {
                    printf("The type car which changed tires/forms: %s \n", c.Type);
                }
            }
        }
    }
    fclose(f);
    fclose(f1);
}

struct Most {
    int id;
    int count;
};

void most_pices(char *filename, char *filename1) {
    FILE *f = fopen(filename, "rb");
    FILE *f1 = fopen(filename1, "rb");
    if (f == NULL || f1 == NULL) {
        printf("Files not found!\n");
        return;
    }
    struct Most m[100];
    struct PIECES p;
    int counter = 0;
    while (fread(&p, sizeof(struct PIECES), 1, f1) == 1 && counter < 100) {
        m[counter].id = p.piec_id;
        m[counter].count = 0;
        counter++;
    }
    fclose(f1);

    struct Prossing p1;
    while (fread(&p1, sizeof(struct Prossing), 1, f) == 1) {
        for (int i = 0; i < p1.Count_type_piece; i++) {
            for (int j = 0; j < counter; j++) {
                if (p1.A[i].id == m[j].id) {
                    m[j].count += p1.A[i].count;
                }
            }
        }
    }
    fclose(f);

    int max = 0;
    for (int i = 0; i < counter; i++) {
        if (m[i].count > max) {
            max = m[i].count;
        }
    }
    for (int i = 0; i < counter; i++) {
        if (m[i].count == max && max > 0) {
            printf("The id piece most used: %d (Count: %d)\n", m[i].id, max);
        }
    }
}

void print_main_menu(void) {
    printf("\t\t\t|--------------------------------|\n");
    printf("\t\t\t|   CAR LOGIX MANAGEMENT SYSTEM  |\n");
    printf("\t\t\t|--------------------------------|\n");
    printf("\n press 1- To add new multi cars......\n");
    printf(" press 2- To add new car......\n");
    printf(" press 3- To display ALL CARS......\n");
    printf(" press 4- To delete car......\n");
    printf(" press 5- To add new Pieces......\n");
    printf(" press 6- To display All pieces......\n");
    printf(" press 7- To delete Piece......\n");
    printf(" press 8- To Add new processing......\n");
    printf(" press 9- To Search of person and return car's......\n");
    printf(" press 10- To Print processing of Linked List......\n");
    printf(" press 11- To Display processing to car and return Total cost......\n");
    printf(" press 12- To Display Cars processing after date......\n");
    printf(" press 13- To Display Type cars changed Tires/Forms......\n");
    printf(" press 14- To Print Pieces Most used......\n");
    printf(" press 15- EXIT ^_^ \n");
    printf("-------------------------------------------------------------\n");
}

void clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void choiser(void) {
    printf("\nIf you want to return to the MAIN MENU enter (1) OR enter any other number to exit Program: ");
    int x;
    scanf("%d", &x);
    if (x == 1) {
        clear_screen();
    } else {
        printf("THANKS TO YOU..... :)\n");
        exit(0);
    }
}

void requrset_list(void) {
    int n, c, x;
    char name_person[20];
    struct Date d;
    char name[20]  = "CAR_FILE.bin";
    char name1[20] = "PROSSING_FILE.bin";
    char name2[20] = "PIECE_FILE.bin";

    while (1) {
        print_main_menu();
        printf("Enter your choice please ^_^:\t");
        if (scanf("%d", &c) != 1) {
            while (getchar() != '\n');
            continue;
        }
        printf("\n");
        clear_screen();
        switch (c) {
        case 1: {
            printf("Enter the number of cars: \n");
            scanf("%d", &n);
            struct Car C[n];
            input_data(n, C);
            file_storg(C, n, name);
            choiser();
            break;
        }
        case 2: {
            struct Car new_car;
            printf("Enter the id car: \n");
            scanf("%d", &new_car.id);
            while (1) {
                if (new_car.id > 0 && serche1(name, new_car.id) == 1) {
                    break;
                } else {
                    printf("ID exists or invalid! Re-enter the id car: \n");
                    scanf("%d", &new_car.id);
                }
            }
            printf("Enter the type car: \n");
            scanf("%19s", new_car.Type);
            printf("Enter the color car: \n");
            scanf("%19s", new_car.Color);
            printf("Enter the name person: \n");
            scanf("%19s", new_car.Name);
            printf("Enter the Tel person: \n");
            scanf("%d", &new_car.Phone);
            Add_car(name, new_car);
            choiser();
            break;
        }
        case 3:
            printf(".........THE CARS.........\n");
            display_file(name);
            choiser();
            break;
        case 4:
            printf("Enter the id car want deleted: \n");
            scanf("%d", &x);
            Delete_car(name, x);
            choiser();
            break;
        case 5:
            Create_file_piec(name2);
            choiser();
            break;
        case 6:
            Display_pieces(name2);
            choiser();
            break;
        case 7:
            printf("Enter the id piece want deleted: \n");
            scanf("%d", &x);
            Delete_pieces(name2, x);
            choiser();
            break;
        case 8:
            Create_file_Prossing(name1, name, name2);
            choiser();
            break;
        case 9:
            printf("Enter the name person to return car's: \n");
            scanf("%19s", name_person);
            saerch_person(name, name_person);
            choiser();
            break;
        case 10:
            convert_file_2_list(name1);
            printf("........from LIST.........\n");
            print_list(head);
            choiser();
            break;
        case 11:
            printf("Enter the id car: \n");
            scanf("%d", &x);
            Display_prossing_car(name1, x);
            choiser();
            break;
        case 12:
            printf("Enter the Date (day month year):\n");
            scanf("%d %d %d", &d.d, &d.m, &d.y);
            Display_car_prossing(name1, d);
            choiser();
            break;
        case 13:
            display_tyep_car(name1, name, name2);
            choiser();
            break;
        case 14:
            printf("The most piece used is: \n");
            most_pices(name1, name2);
            choiser();
            break;
        case 15:
            printf("THANKS TO YOU..... :)\n");
            return;
        default:
            printf("\nERROR WRONG CHOICE -_-\n");
            printf("Enter Right Choice In The Next Time ^_^\n\n");
            choiser();
        }
    }
}

int main(void) {
    requrset_list();
    return 0;
}
