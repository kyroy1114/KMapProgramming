#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>

#define KMAP_SIZE 16
#define MASK16SIZE 16
#define MASK8SIZE 8
#define MASK4SIZE 4
#define MASK2SIZE 2

using namespace std;

char **str_split(char *str, char delim, int *numSplits)
{
    char **ret;
    int retLen;
    char *c;

    if ((str == NULL) ||
        (delim == '\0'))
    {
        /* Either of those will cause problems */
        ret = NULL;
        retLen = -1;
    }
    else
    {
        retLen = 0;
        c = str;

        /* Pre-calculate number of elements */
        do
        {
            if (*c == delim)
            {
                retLen++;
            }

            c++;
        } while (*c != '\0');

        ret = (char **)malloc((retLen + 1) * sizeof(*ret));
        ret[retLen] = NULL;

        c = str;
        retLen = 1;
        ret[0] = str;

        do
        {
            if (*c == delim)
            {
                ret[retLen++] = &c[1];
                *c = '\0';
            }

            c++;
        } while (*c != '\0');
    }

    if (numSplits != NULL)
    {
        *numSplits = retLen;
    }

    return ret;
}

int *stat = (int*) calloc(KMAP_SIZE, sizeof(int));

void cal_stat(int check_code) {
	for (int k = 0; k < KMAP_SIZE; k++) {
		if (check_code & 1 == 1)
			++stat[k];
		check_code >>= 1;
	}
}

struct ListNode {
    int check_code;
    struct ListNode *next;
};

struct ListNode *temp_node = (struct ListNode*) malloc(sizeof(struct ListNode));

bool covered_node_check(struct ListNode *og_node, int check_code) {
	struct ListNode *current_node = og_node;
    do {
    	if (current_node->check_code && (check_code & current_node->check_code) == check_code)
			return true;
        current_node = current_node->next;
    } while(current_node != NULL);
    return false;
}

void add_node(int covered_check_code) {
	temp_node->next = (struct ListNode*) malloc(sizeof(struct ListNode));
	temp_node = temp_node->next;
	temp_node->check_code = covered_check_code;
	temp_node->next = NULL;
}

bool is_prime_implcnt(int check_code, int target_num) {
	check_code >>= target_num;
	if (check_code & 1)
		return true;
	return false;
}

int cal_covered_size(int check_code) {
	int ct = 0;
	for (int k = 0; k < KMAP_SIZE; k++) {
		if (stat[k] && (check_code & 1))
			ct++;
		check_code >>= 1;
	}
	return ct;
}

int traverse_node(struct ListNode *og_node, int target_num) {
	int covered_size_max = 0;
	int res_check_code = 0;
	temp_node = og_node;
    do {
    	if (temp_node->check_code && is_prime_implcnt(temp_node->check_code, target_num)
		    && covered_size_max < cal_covered_size(temp_node->check_code)) {
		    	covered_size_max = cal_covered_size(temp_node->check_code);
		    	res_check_code = temp_node->check_code;
			}
        temp_node = temp_node->next;
    } while(temp_node != NULL);
    return res_check_code;
}

void clear_stat(int check_code) {
	for (int k = 0; k < KMAP_SIZE; k++) {
		if (check_code & 1)
			stat[k] = 0;
		check_code >>= 1;
	}
}

bool find_min_SOP_over(int *stat) {
	int sum = 0;
	for (int k = 0; k < KMAP_SIZE; k++)
		sum += stat[k];
	if (sum)
		return false;
	return true;
}

void print_min_SOP(int check_code) {
	cout << "[";
	for (int k = 0; k < KMAP_SIZE; k++)
		if ((check_code >> k) & 1) 
			cout << k << ", ";
	cout << "\b\b" << "]" << endl; 
}

int *seq = (int*) malloc(sizeof(int) * 16);

typedef struct {
	bool is_covered;
	int check_code;
    int ones_array[16];
} Mask16;

Mask16 mask_4_x_4 = {
	.is_covered = 1,
	.check_code = 0b1111111111111111,
	.ones_array = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}
};

typedef struct {
	bool is_covered;
	int check_code;
    int ones_array[8];
} Mask8;

Mask8 mask_2_x_4[] = {
	{ .is_covered = 1,
	  .check_code = 0b0101010101010101,
	  .ones_array = {2, 6, 14, 10, 0, 4, 12, 8} },
	{ .is_covered = 1,
	  .check_code = 0b0011001100110011,
	  .ones_array = {0, 4, 12, 8, 1, 5, 13, 9} },
	{ .is_covered = 1,
	  .check_code = 0b1010101010101010,
	  .ones_array = {1, 5, 13, 9, 3, 7, 15, 11} },
	{ .is_covered = 1,
	  .check_code = 0b1100110011001100,
	  .ones_array = {3, 7, 15, 11, 2, 6, 14, 10} }
};

Mask8 mask_4_x_2[] = {
	{ .is_covered = 1,
	  .check_code = 0b0000111100001111,
	  .ones_array = {8, 9, 11, 10, 0, 1, 3, 2} },
	{ .is_covered = 1,
	  .check_code = 0b0000000011111111,
	  .ones_array = {0, 1, 3, 2, 4, 5, 7, 6} },
	{ .is_covered = 1,
	  .check_code = 0b1111000011110000,
	  .ones_array = {4, 5, 7, 6, 12, 13, 15, 14} },
	{ .is_covered = 1,
	  .check_code = 0b1111111100000000,
	  .ones_array = {12, 13, 15, 14, 8, 9, 11, 10} }
};

typedef struct {
	bool is_covered;
	int check_code;
    int ones_array[4];
} Mask4;

Mask4 mask_1_x_4[] = {
	{ .is_covered = 1,
	  .check_code = 0b0001000100010001,
	  .ones_array = {0, 4, 12, 8} },
	{ .is_covered = 1,
	  .check_code = 0b0010001000100010,
	  .ones_array = {1, 5, 13, 9} },
	{ .is_covered = 1,
	  .check_code = 0b1000100010001000,
	  .ones_array = {3, 7, 15, 11} },
	{ .is_covered = 1,
	  .check_code = 0b0100010001000100,
	  .ones_array = {2, 6, 14, 10} }
};

Mask4 mask_2_x_2[] = {
	{ .is_covered = 1,
	  .check_code = 0b0000010100000101,
	  .ones_array = {2, 10, 0, 8} },
	{ .is_covered = 1,
	  .check_code = 0b0000000001010101,
	  .ones_array = {2, 6, 0, 4} },
	{ .is_covered = 1,
	  .check_code = 0b0101000001010000,
	  .ones_array = {6, 14, 4, 12} },
	{ .is_covered = 1,
	  .check_code = 0b0101010100000000,
	  .ones_array = {14, 10, 12, 8} },
	{ .is_covered = 1,
	  .check_code = 0b0000001100000011,
	  .ones_array = {8, 0, 9, 1} },
    { .is_covered = 1,
	  .check_code = 0b0000000000110011,
	  .ones_array = {0, 4, 1, 5} },
	{ .is_covered = 1,
	  .check_code = 0b0011000000110000,
	  .ones_array = {4, 12, 5, 13} },
	{ .is_covered = 1,
	  .check_code = 0b0011001100000000,
	  .ones_array = {12, 8, 13, 9} },
	{ .is_covered = 1,
	  .check_code = 0b0000101000001010,
	  .ones_array = {9, 1, 11, 3} },
	{ .is_covered = 1,
	  .check_code = 0b0000000010101010,
	  .ones_array = {1, 5, 3, 7} },
	{ .is_covered = 1,
	  .check_code = 0b1010000010100000,
	  .ones_array = {5, 13, 7, 15} },
	{ .is_covered = 1,
	  .check_code = 0b1010101000000000,
	  .ones_array = {13, 9, 15, 11} },
	{ .is_covered = 1,
	  .check_code = 0b0001100000001100,
	  .ones_array = {11, 3, 10, 2} },
	{ .is_covered = 1,
	  .check_code = 0b0000000011001100,
	  .ones_array = {3, 7, 2, 6} },
	{ .is_covered = 1,
	  .check_code = 0b1100000011000000,
	  .ones_array = {7, 15, 6, 14} },
	{ .is_covered = 1,
	  .check_code = 0b1100110000000000,
	  .ones_array = {15, 11, 14, 10} }
};

Mask4 mask_4_x_1[] = {
	{ .is_covered = 1,
	  .check_code = 0b0000000000001111,
	  .ones_array = {0, 1, 3, 2} },
	{ .is_covered = 1,
	  .check_code = 0b0000000011110000,
	  .ones_array = {4, 5, 7, 6} },
	{ .is_covered = 1,
      .check_code = 0b1111000000000000,
	  .ones_array = {12, 13, 15, 14} },
	{ .is_covered = 1,
	  .check_code = 0b0000111100000000,
	  .ones_array = {8, 9, 11, 10} }
};

typedef struct {
	bool is_covered;
	int check_code;
    int ones_array[2];
} Mask2;

Mask2 mask_1_x_2[] = {
	{ .is_covered = 1,
	  .check_code = 0b0000000100000001,
	  .ones_array = {8, 0} },
	{ .is_covered = 1,
	  .check_code = 0b0000001000000010,
	  .ones_array = {9, 1} },
	{ .is_covered = 1,
	  .check_code = 0b0000100000001000,
	  .ones_array = {11, 3} },
	{ .is_covered = 1,
	  .check_code = 0b0000010000000100,
	  .ones_array = {10, 2} },
	{ .is_covered = 1,
	  .check_code = 0b0000000000010001,
	  .ones_array = {0, 4} },
	{ .is_covered = 1,
	  .check_code = 0b0000000000100010,
	  .ones_array = {1, 5} },
	{ .is_covered = 1,
	  .check_code = 0b0000000010001000,
	  .ones_array = {3, 7} },
	{ .is_covered = 1,
	  .check_code = 0b0000000001000100,
	  .ones_array = {2, 6} },
	{ .is_covered = 1,
	  .check_code = 0b0001000000010000,
	  .ones_array = {4, 12} },
	{ .is_covered = 1,
	  .check_code = 0b0010000000100000,
	  .ones_array = {5, 13} },
	{ .is_covered = 1,
	  .check_code = 0b1000000010000000,
	  .ones_array = {7, 15} },
	{ .is_covered = 1,
	  .check_code = 0b0100000001000000,
	  .ones_array = {6, 14} },
	{ .is_covered = 1,
	  .check_code = 0b0001000100000000,
	  .ones_array = {12, 8} },
	{ .is_covered = 1,
	  .check_code = 0b0010001000000000,
	  .ones_array = {13, 9} },
	{ .is_covered = 1,
	  .check_code = 0b1000100000000000,
	  .ones_array = {15, 11} },
	{ .is_covered = 1,
	  .check_code = 0b0100010000000000,
	  .ones_array = {14, 10} }
};

Mask2 mask_2_x_1[] = {
	{ .is_covered = 1,
	  .check_code = 0b0000000000000101,
	  .ones_array = {2, 0} },
	{ .is_covered = 1,
	  .check_code = 0b0000000001010000,
	  .ones_array = {6, 4} },
	{ .is_covered = 1,
	  .check_code = 0b0101000000000000,
	  .ones_array = {14, 12} },
	{ .is_covered = 1,
	  .check_code = 0b0000010100000000,
	  .ones_array = {10, 8} },
	{ .is_covered = 1,
	  .check_code = 0b0000000000000011,
	  .ones_array = {0, 1} },
	{ .is_covered = 1,
	  .check_code = 0b0000000000110000,
	  .ones_array = {4, 5} },
	{ .is_covered = 1,
	  .check_code = 0b0011000000000000,
	  .ones_array = {12, 13} },
	{ .is_covered = 1,
	  .check_code = 0b0000001100000000,
	  .ones_array = {8, 9} },
	{ .is_covered = 1,
	  .check_code = 0b0000000000001010,
	  .ones_array = {1, 3} },
	{ .is_covered = 1,
	  .check_code = 0b0000000010100000,
	  .ones_array = {5, 7} },
	{ .is_covered = 1,
	  .check_code = 0b1010000000000000,
	  .ones_array = {13, 15} },
	{ .is_covered = 1,
	  .check_code = 0b0000101000000000,
	  .ones_array = {9, 11} },
	{ .is_covered = 1,
	  .check_code = 0b0000000000001100,
	  .ones_array = {3, 2} },
	{ .is_covered = 1,
	  .check_code = 0b0000000011000000,
	  .ones_array = {7, 6} },
	{ .is_covered = 1,
	  .check_code = 0b1100000000000000,
	  .ones_array = {15, 14} },
	{ .is_covered = 1,
	  .check_code = 0b0000110000000000,
	  .ones_array = {11, 10} }
};

typedef struct {
	bool is_covered;
	int check_code;
} Mask1;

Mask1 mask_1_x_1[] = {
	{ .is_covered = 1,
	  .check_code = 0b0000000000000001 },
	{ .is_covered = 1,
	  .check_code = 0b0000000000000010 },
	{ .is_covered = 1,
	  .check_code = 0b0000000000000100 },
	{ .is_covered = 1,
	  .check_code = 0b0000000000001000 },
	{ .is_covered = 1,
	  .check_code = 0b0000000000010000 },
	{ .is_covered = 1,
	  .check_code = 0b0000000000100000 },
	{ .is_covered = 1,
	  .check_code = 0b0000000001000000 },
	{ .is_covered = 1,
	  .check_code = 0b0000000010000000 },
	{ .is_covered = 1,
	  .check_code = 0b0000000100000000 },
	{ .is_covered = 1,
	  .check_code = 0b0000001000000000 },
	{ .is_covered = 1,
	  .check_code = 0b0000010000000000 },
	{ .is_covered = 1,
	  .check_code = 0b0000100000000000 },
	{ .is_covered = 1,
	  .check_code = 0b0001000000000000 },
	{ .is_covered = 1,
	  .check_code = 0b0010000000000000 },
	{ .is_covered = 1,
	  .check_code = 0b0100000000000000 },
	{ .is_covered = 1,
	  .check_code = 0b1000000000000000 }
};

void scan_mask_size_16(void) {
    for (int k = 0; k < MASK16SIZE; k++)
    	if (seq[mask_4_x_4.ones_array[k]] == 0) {	
    		mask_4_x_4.is_covered = 0;
    		break;
		}
	if (mask_4_x_4.is_covered) {
		cal_stat(mask_4_x_4.check_code);
		add_node(mask_4_x_4.check_code);
	}    	
}

void scan_mask_size_8(void) {
	for (int i = 0; i < sizeof(mask_2_x_4)/sizeof(mask_2_x_4[0]); i++)
		for (int j = 0; j < MASK8SIZE; j++)
    		if (seq[mask_2_x_4[i].ones_array[j]] == 0) {	
    			mask_2_x_4[i].is_covered = 0;
    			break;
			}
	for (int i = 0; i < sizeof(mask_2_x_4)/sizeof(mask_2_x_4[0]); i++)
		if (mask_2_x_4[i].is_covered && mask_4_x_4.is_covered)
			mask_2_x_4[i].is_covered = 0;
	for (int i = 0; i < sizeof(mask_2_x_4)/sizeof(mask_2_x_4[0]); i++) {
		if (mask_2_x_4[i].is_covered) {
			cal_stat(mask_2_x_4[i].check_code);
			add_node(mask_2_x_4[i].check_code);
		}
	}
	
	
	for (int i = 0; i < sizeof(mask_4_x_2)/sizeof(mask_4_x_2[0]); i++)
		for (int j = 0; j < MASK8SIZE; j++)
    		if (seq[mask_4_x_2[i].ones_array[j]] == 0) {	
    			mask_4_x_2[i].is_covered = 0;
    			break;
			}
	for (int i = 0; i < sizeof(mask_4_x_2)/sizeof(mask_4_x_2[0]); i++)
		if (mask_4_x_2[i].is_covered && mask_4_x_4.is_covered)
			mask_4_x_2[i].is_covered = 0;
	for (int i = 0; i < sizeof(mask_4_x_2)/sizeof(mask_4_x_2[0]); i++) {
		if (mask_4_x_2[i].is_covered) {
			cal_stat(mask_4_x_2[i].check_code);
			add_node(mask_4_x_2[i].check_code);
		}
	}
}

void scan_mask_size_4(struct ListNode *og_node) {
	for (int i = 0; i < sizeof(mask_1_x_4)/sizeof(mask_1_x_4[0]); i++)
		for (int j = 0; j < MASK4SIZE; j++)
    		if (seq[mask_1_x_4[i].ones_array[j]] == 0) {	
    			mask_1_x_4[i].is_covered = 0;
    			break;
			}
	for (int i = 0; i < sizeof(mask_1_x_4)/sizeof(mask_1_x_4[0]); i++)
		if (mask_1_x_4[i].is_covered && covered_node_check(og_node, mask_1_x_4[i].check_code))
				mask_1_x_4[i].is_covered = 0;
	for (int i = 0; i < sizeof(mask_1_x_4)/sizeof(mask_1_x_4[0]); i++) {
		if (mask_1_x_4[i].is_covered) {
			cal_stat(mask_1_x_4[i].check_code);
			add_node(mask_1_x_4[i].check_code);
		}
	}	
	
	
	for (int i = 0; i < sizeof(mask_2_x_2)/sizeof(mask_2_x_2[0]); i++)
		for (int j = 0; j < MASK4SIZE; j++)
    		if (seq[mask_2_x_2[i].ones_array[j]] == 0) {	
    			mask_2_x_2[i].is_covered = 0;
    			break;
			}
	for (int i = 0; i < sizeof(mask_2_x_2)/sizeof(mask_2_x_2[0]); i++)
			if (mask_2_x_2[i].is_covered && covered_node_check(og_node, mask_2_x_2[i].check_code))
					mask_2_x_2[i].is_covered = 0;
	for (int i = 0; i < sizeof(mask_2_x_2)/sizeof(mask_2_x_2[0]); i++) {
		if (mask_2_x_2[i].is_covered) {
			cal_stat(mask_2_x_2[i].check_code);
			add_node(mask_2_x_2[i].check_code);
		}
	}
	
	
	for (int i = 0; i < sizeof(mask_4_x_1)/sizeof(mask_4_x_1[0]); i++)
		for (int j = 0; j < MASK4SIZE; j++)
    		if (seq[mask_4_x_1[i].ones_array[j]] == 0) {	
    			mask_4_x_1[i].is_covered = 0;
    			break;
			}
	for (int i = 0; i < sizeof(mask_4_x_1)/sizeof(mask_4_x_1[0]); i++)
			if (mask_4_x_1[i].is_covered && covered_node_check(og_node, mask_4_x_1[i].check_code))
					mask_4_x_1[i].is_covered = 0;
	for (int i = 0; i < sizeof(mask_4_x_1)/sizeof(mask_4_x_1[0]); i++) {
		if (mask_4_x_1[i].is_covered) {
			cal_stat(mask_4_x_1[i].check_code);
			add_node(mask_4_x_1[i].check_code);
		}
	}
}

void scan_mask_size_2(struct ListNode *og_node) {
	for (int i = 0; i < sizeof(mask_1_x_2)/sizeof(mask_1_x_2[0]); i++)
		for (int j = 0; j < MASK2SIZE; j++)
    		if (seq[mask_1_x_2[i].ones_array[j]] == 0) {	
    			mask_1_x_2[i].is_covered = 0;
    			break;
			}
	for (int i = 0; i < sizeof(mask_1_x_2)/sizeof(mask_1_x_2[0]); i++)
			if (mask_1_x_2[i].is_covered && covered_node_check(og_node, mask_1_x_2[i].check_code))
					mask_1_x_2[i].is_covered = 0;
	for (int i = 0; i < sizeof(mask_1_x_2)/sizeof(mask_1_x_2[0]); i++) {
		if (mask_1_x_2[i].is_covered) {
			cal_stat(mask_1_x_2[i].check_code);
			add_node(mask_1_x_2[i].check_code);
		}
	}
	
	
	for (int i = 0; i < sizeof(mask_2_x_1)/sizeof(mask_2_x_1[0]); i++)
		for (int j = 0; j < MASK2SIZE; j++)
    		if (seq[mask_2_x_1[i].ones_array[j]] == 0) {	
    			mask_2_x_1[i].is_covered = 0;
    			break;
			}
	for (int i = 0; i < sizeof(mask_2_x_1)/sizeof(mask_2_x_1[0]); i++)
		for (int j = 0; j < sizeof(mask_4_x_1)/sizeof(mask_4_x_1[0]); j++)
			if (mask_2_x_1[i].is_covered && covered_node_check(og_node, mask_2_x_1[i].check_code))
					mask_2_x_1[i].is_covered = 0;
	for (int i = 0; i < sizeof(mask_2_x_1)/sizeof(mask_2_x_1[0]); i++) {
		if (mask_2_x_1[i].is_covered) {
			cal_stat(mask_2_x_1[i].check_code);
			add_node(mask_2_x_1[i].check_code);
		}
	}
}

void scan_mask_size_1(struct ListNode *og_node) {
	for (int i = 0; i < sizeof(mask_1_x_1)/sizeof(mask_1_x_1[0]); i++)
    	if (seq[i] == 0)	
    		mask_1_x_1[i].is_covered = 0;
	for (int i = 0; i < sizeof(mask_1_x_1)/sizeof(mask_1_x_1[0]); i++)
		for (int j = 0; j < sizeof(mask_1_x_2)/sizeof(mask_1_x_2[0]); j++)
			if (mask_1_x_1[i].is_covered && covered_node_check(og_node, mask_1_x_1[i].check_code))
					mask_1_x_1[i].is_covered = 0;
	for (int i = 0; i < sizeof(mask_1_x_1)/sizeof(mask_1_x_1[0]); i++) {
		if (mask_1_x_1[i].is_covered) {
			cal_stat(mask_1_x_1[i].check_code);
			add_node(mask_1_x_1[i].check_code);
		}
	}
}

int main()
{
    fstream file;
    file.open("test.txt", ios::in);
    char buffer[200];
    for (int i = 0; i < 200; i++)
        buffer[i] = '\0';
    file.getline(buffer, sizeof(buffer), '\n');
    char **split;
    int num;
    split = str_split(buffer, '+', &num);
    int map[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            map[i][j] = 0;
    for (int i = 0; i < num; i++)
    {
        int flag_row = 0;
        int flag_col = 0;
        
        int table_a[2];
        int table_b[2];
        table_a[0] = table_a[1] = table_b[0] = table_b[1] = 0;
        for (int j = 0; split[i][j] != '\0'; j++)
        {
            if (split[i][j] == 'a')
                table_a[0] = 1;
            if (split[i][j] == 'b')
                table_b[0] = 1;
            if (split[i][j] == '\'')
            {
                if (split[i][j - 1] == 'a')
                {
                    table_a[0] = 0;
                    table_a[1] = 1;
                }
                else if (split[i][j - 1] == 'b')
                {
                    table_b[0] = 0;
                    table_b[1] = 1;
                }
            }
        }
        if (table_a[0] == 1 && table_a[1] == 0 && table_b[0] == 0 && table_b[1] == 0) //case a
            flag_row = 1;
        else if (table_a[0] == 0 && table_a[1] == 1 && table_b[0] == 0 && table_b[1] == 0) //case a'
            flag_row = 2;
        else if (table_b[0] == 1 && table_b[1] == 0 && table_a[0] == 0 && table_a[1] == 0) //case b
            flag_row = 3;
        else if (table_b[0] == 0 && table_b[1] == 1 && table_a[0] == 0 && table_a[1] == 0) //case b'
            flag_row = 4;
        else if (table_a[0] == 1 && table_b[0] == 1) //case ab
            flag_row = 5;
        else if (table_a[0] == 1 && table_b[1] == 1) //case ab'
            flag_row = 6;
        else if (table_a[1] == 1 && table_b[0] == 1) //case a'b
            flag_row = 7;
        else if (table_a[1] == 1 && table_b[1] == 1) //case a'b'
            flag_row = 8;
        
        table_a[0] = table_a[1] = table_b[0] = table_b[1] = 0;
        for (int j = 0; split[i][j] != '\0'; j++)
        {
            if (split[i][j] == 'c')
                table_a[0] = 1;
            if (split[i][j] == 'd')
                table_b[0] = 1;
            if (split[i][j] == '\'')
            {
                if (split[i][j - 1] == 'c')
                {
                    table_a[0] = 0;
                    table_a[1] = 1;
                }
                else if (split[i][j - 1] == 'd')
                {
                    table_b[0] = 0;
                    table_b[1] = 1;
                }
            }
        }
        if (table_a[0] == 1 && table_a[1] == 0 && table_b[0] == 0 && table_b[1] == 0) //case c
            flag_col = 1;
        else if (table_a[0] == 0 && table_a[1] == 1 && table_b[0] == 0 && table_b[1] == 0) //case c'
            flag_col = 2;
        else if (table_b[0] == 1 && table_b[1] == 0 && table_a[0] == 0 && table_a[1] == 0) //case d
            flag_col = 3;
        else if (table_b[0] == 0 && table_b[1] == 1 && table_a[0] == 0 && table_a[1] == 0) //case d'
            flag_col = 4;
        else if (table_a[0] == 1 && table_b[0] == 1) //case cd
            flag_col = 5;
        else if (table_a[0] == 1 && table_b[1] == 1) //case cd'
            flag_col = 6;
        else if (table_a[1] == 1 && table_b[0] == 1) //case c'd
            flag_col = 7;
        else if (table_a[1] == 1 && table_b[1] == 1) //case c'd'
            flag_col = 8;
        /*
        flag = 0:0,1,2,3
        flag = 1:2,3
        flag = 2:0,1
        flag = 3:1,2
        flag = 4:0,3
        flag = 5:2
        flag = 6:3
        flag = 7:1
        flag = 8:0
        */
        vector<int> row;
        vector<int> col;
        switch (flag_col)
        {
        case 0:
            row.push_back(0);
            row.push_back(1);
            row.push_back(2);
            row.push_back(3);
            break;
        case 1:
            row.push_back(2);
            row.push_back(3);
            break;
        case 2:
            row.push_back(0);
            row.push_back(1);
            break;
        case 3:
            row.push_back(1);
            row.push_back(2);
            break;
        case 4:
            row.push_back(0);
            row.push_back(3);
            break;
        case 5:
            row.push_back(2);
            break;
        case 6:
            row.push_back(3);
            break;
        case 7:
            row.push_back(1);
            break;
        case 8:
            row.push_back(0);
            break;
        }
        switch (flag_row)
        {
        case 0:
            col.push_back(0);
            col.push_back(1);
            col.push_back(2);
            col.push_back(3);
            break;
        case 1:
            col.push_back(2);
            col.push_back(3);
            break;
        case 2:
            col.push_back(0);
            col.push_back(1);
            break;
        case 3:
            col.push_back(1);
            col.push_back(2);
            break;
        case 4:
            col.push_back(0);
            col.push_back(3);
            break;
        case 5:
            col.push_back(2);
            break;
        case 6:
            col.push_back(3);
            break;
        case 7:
            col.push_back(1);
            break;
        case 8:
            col.push_back(0);
            break;
        }
        for (int k = 0; k < row.size(); k++)
            for (int m = 0; m < col.size(); m++)
                map[row[k]][col[m]] = 1;
    }
    cout << "\t   K Map" << endl;
    cout << "  \\ AB|" << endl;
    cout << "CD \\  | 00 | 01 | 11 | 10" << endl;
    cout << "------+----+----+----+-----" << endl;
    for (int k = 0; k < 4; k++)
    {
    	switch (k) {
    		case 0: cout << "   00 |"; break;
    		case 1: cout << "   01 |"; break;
    		case 2: cout << "   11 |"; break;
    		case 3: cout << "   10 |"; break;
		}
        for (int m = 0; m < 4; m++)
            cout << "  " << map[k][m] << " |";
        cout << endl;
        if (k < 3) cout << "------+----+----+----+----|" << endl;
        else cout << "---------------------------" << endl << endl;
    }
    
    seq[0] = map[0][0];
    seq[1] = map[1][0];
    seq[2] = map[3][0];
    seq[3] = map[2][0];
    seq[4] = map[0][1];
    seq[5] = map[1][1];
    seq[6] = map[3][1];
    seq[7] = map[2][1];
    seq[8] = map[0][3];
    seq[9] = map[1][3];
    seq[10] = map[3][3];
    seq[11] = map[2][3];
    seq[12] = map[0][2];
    seq[13] = map[1][2];
    seq[14] = map[3][2];
    seq[15] = map[2][2];
    
    struct ListNode *og_node = (struct ListNode*) malloc(sizeof(struct ListNode));
	og_node->check_code = 0;
	og_node->next = NULL;
	temp_node = og_node;
	
	scan_mask_size_16();
	scan_mask_size_8();
	scan_mask_size_4(og_node);
	scan_mask_size_2(og_node);
	scan_mask_size_1(og_node);
	
	int stat_min = KMAP_SIZE;
	int target_num = KMAP_SIZE;
	
	cout << "Minimum SOP Form: " << endl;
	
	while (!find_min_SOP_over(stat)) {
		for (int k = 0; k < KMAP_SIZE; k++)
			if (stat[k] < stat_min && stat[k]) {
				stat_min = stat[k];
				target_num = k;
			}
		//cout << traverse_node(og_node, target_num) << endl;
		print_min_SOP(traverse_node(og_node, target_num));
		clear_stat(traverse_node(og_node, target_num));
		stat_min = KMAP_SIZE;
	}



	return 0;
}

