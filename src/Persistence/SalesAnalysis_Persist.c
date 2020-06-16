#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Common/list.h"
#include "../Service/SalesAnalysis.h"
#include "../Service/Sale.h"
#include "../Common/common.h"
#include "../Service/Play.h"
#include "../Persistence/EntityKey_Persist.h"

static const char SALE_DATA_FILE[] = "Sale.dat";

int Sale_Perst_SelByTicketID (int ticket_id, sale_t *sale){
	assert(NULL!=sale);

	FILE *fp = fopen(SALE_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	sale_t data;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&data, sizeof(sale_t), 1, fp)) {
			if (ticket_id == data.ticket_id) {
				*sale = data;
				found = 1;
				break;
			};

		}
	}
	fclose(fp);

	return found;
}