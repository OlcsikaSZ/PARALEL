#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// A Promise struktúra, amely tárolja az eredményt vagy hibát
typedef struct {
    bool has_value;  // Van-e már eredmény
    int value;       // Az eredmény (ha van)
    const char *error; // Hibaüzenet (ha van)
} Promise;

// Inicializálás, ami üres Promise-t hoz létre
void init_promise(Promise *p) {
    p->has_value = false;
    p->value = 0;
    p->error = NULL;
}

// Ellenőrizzük, hogy van-e már eredmény
bool has_value(Promise *p) {
    return p->has_value;
}

// Eredmény lekérése, ha van
int* get_value(Promise *p) {
    if (p->has_value) {
        return &p->value;
    }
    return NULL; // Ha nincs eredmény
}

// Hiba lekérése, ha van
const char* get_error(Promise *p) {
    return p->error;
}

// Eredmény beállítása
void set_value(Promise *p, int value) {
    p->has_value = true;
    p->value = value;
}

// Hiba beállítása
void set_error(Promise *p, const char *error_message) {
    p->has_value = false;
    p->error = error_message;
}

// Teszteléshez egy számítási függvény, ami sikeres eredményt ad
void perform_calculation(Promise *p) {
    // Egy egyszerű számítás: 5 + 5
    int result = 5 + 5;
    set_value(p, result);
}

// Teszteléshez egy hibát generáló függvény
void perform_failing_calculation(Promise *p) {
    set_error(p, "Hiba történt a számítás során!");
}

int main() {
    Promise p;
    init_promise(&p);

    // Számítás végrehajtása
    perform_calculation(&p);

    // Ellenőrizzük, hogy van-e eredmény
    if (has_value(&p)) {
        printf("A számítás eredménye: %d\n", *get_value(&p));
    } else {
        printf("Nincs eredmény.\n");
    }

    // Most hibát generálunk
    perform_failing_calculation(&p);

    // Ellenőrizzük, hogy van-e hiba
    if (!has_value(&p)) {
        printf("Hiba: %s\n", get_error(&p));
    }

    return 0;
}