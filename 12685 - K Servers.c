#include <stdio.h>
#include <stdlib.h>

int main() {
	int k, m, **pendding;

	scanf("%d%d", &k, &m);

	pendding = (int**)malloc((k + 1) * sizeof(int*));

	for (int i = 1; i <= k; i++) {
		pendding[i] = (int*)calloc(1, (m + 1) * sizeof(int));
	}

	for (int i = 0; i < m; i++) {
		int option, sid, rid, from, to;
		scanf("%d", &option);
		switch (option) {
		case 1:
			scanf("%d%d", &sid, &rid);
			pendding[sid][0]++;
			pendding[sid][pendding[sid][0]] = rid;
			break;
		case 2:
			scanf("%d", &sid);
			if (pendding[sid][0] > 0) {
				for (int j = 1; j < pendding[sid][0]; j++) {
					pendding[sid][j] = pendding[sid][j + 1];
				}
				pendding[sid][0]--;
			}
			break;
		case 3:
			scanf("%d%d", &to, &from);
			if (pendding[from][0] > 0) {
				for (int j = 1; j <= pendding[from][0]; j++) {
					pendding[to][0]++;
					pendding[to][pendding[to][0]] = pendding[from][j];
				}
				pendding[from][0] = 0;
			}
			break;
		}
	}

	for (int i = 1; i <= k; i++) {
		for (int j = 1; j <= pendding[i][0]; j++) {
			printf("%d", pendding[i][j]);
			if (j != pendding[i][0])
				printf(" ");
		}
		printf("\n");
	}

	return 0;
}
