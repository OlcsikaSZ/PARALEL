int search(Node *head, int key) {
    Node *current = head;
    while (current != NULL) {
        if (current->data == key) {
            return 1;  // Element found
        }
        current = current->next;
    }
    return 0;  // Element not found
}