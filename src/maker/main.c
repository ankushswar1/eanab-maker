#include "printf.h"
#include "uart.h"
#include "timer.h"
#include "magstripe.h"
#include "interrupts.h"
#include "malloc.h"
#include "storage.h"
#include "communicator.h"

void main(void) 
{
    timer_init();
    uart_init();
    storage_init();
    communicator_init(COMMUNICATOR_MODE_MAKER);
    magstripe_init(MAGSTRIPE_CLOCK, MAGSTRIPE_DATA);
    interrupts_global_enable();

    printf("Hello from the maker!\n");

    while (1) {
        // Swipe ==> start pipeline for drink prep
        magstripe_card_t *card = magstripe_read_next_card();

        // fixme: temporarily set to 123 for testing
        // char *user = card->track_2->pan;
        char *user = malloc(5);
        user = "123";

        printf("Looks like %s wants to get a drink!\n", user);

        if (!storage_has_key(user)) {
            // fixme: flash a red led? some way to indicate error state
            printf("Oh no, we couldn't find a saved drink for %s. :(\n", user);
            continue;
        }

        storage_ingredients_t *ingredients = (storage_ingredients_t *)storage_get_key(user);
        printf("Nice, we're gonna make %d/%d/%d/%d!\n", ingredients[0], ingredients[1], ingredients[2], ingredients[3]);
        
        // fixme
        // - check breathalyzer
        // - make drink
    }
}
