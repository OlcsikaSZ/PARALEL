#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Callback típus, amelyet a feliratkozók hívnak
typedef void (*callback_t)(const char *message);

// A Subscriber struktúra, amely tárolja a callback függvényt
typedef struct Subscriber {
    callback_t callback;  // A feliratkozó callback függvénye
    struct Subscriber *next; // A következő feliratkozó
} Subscriber;

// A Topic struktúra, amely tárolja a feliratkozókat
typedef struct Topic {
    char *name;           // A téma neve
    Subscriber *subscribers;  // A feliratkozók listája
} Topic;

// A téma inicializálása
Topic* create_topic(const char *name) {
    Topic *topic = (Topic*)malloc(sizeof(Topic));
    topic->name = strdup(name);  // Nevet másolunk
    topic->subscribers = NULL;  // Kezdetben nincs feliratkozó
    return topic;
}

// Feliratkozás egy topic-ra
void subscribe(Topic *topic, callback_t callback) {
    Subscriber *new_subscriber = (Subscriber*)malloc(sizeof(Subscriber));
    new_subscriber->callback = callback;
    new_subscriber->next = topic->subscribers;
    topic->subscribers = new_subscriber;
}

// Üzenet publikálása a topic-ra
void publish(Topic *topic, const char *message) {
    Subscriber *subscriber = topic->subscribers;
    while (subscriber != NULL) {
        subscriber->callback(message);  // Minden feliratkozó callback-jét meghívjuk
        subscriber = subscriber->next;
    }
}

// Példa callback függvények
void subscriber_1_callback(const char *message) {
    printf("Subscriber 1 received: %s\n", message);
}

void subscriber_2_callback(const char *message) {
    printf("Subscriber 2 received: %s\n", message);
}

// A téma felszabadítása
void free_topic(Topic *topic) {
    free(topic->name);
    Subscriber *subscriber = topic->subscribers;
    while (subscriber != NULL) {
        Subscriber *temp = subscriber;
        subscriber = subscriber->next;
        free(temp);
    }
    free(topic);
}

int main() {
    // Téma létrehozása
    Topic *tech_topic = create_topic("Technology");

    // Feliratkozók hozzáadása
    subscribe(tech_topic, subscriber_1_callback);
    subscribe(tech_topic, subscriber_2_callback);

    // Üzenet publikálása
    printf("Publishing a message to the 'Technology' topic...\n");
    publish(tech_topic, "New tech trends in 2025!");

    // Téma és feliratkozók felszabadítása
    free_topic(tech_topic);

    return 0;
}