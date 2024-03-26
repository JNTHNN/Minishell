#include <stdio.h>
#include <stdlib.h>

int main() {
    int status;
    
    // Utilisation de system() pour exécuter la commande grep
    status = system("grep mot_inexistant fichier.txt ");

    // Vérification du statut de terminaison
    if (WIFEXITED(status)) {
        int exit_status = WEXITSTATUS(status); // Obtention du code d'erreur
        printf("Le code d'erreur est : %d\n", exit_status);
		exit(exit_status);
    } else {
        printf("La commande ne s'est pas terminée correctement.\n");
    }

    return 0;
}
