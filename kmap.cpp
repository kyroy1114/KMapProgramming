#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

char **str_split(char *str, char delim, int *numSplits)
{
    char **ret;
    int retLen;
    char *c;

    if ((str == NULL) ||
        (delim == '\0'))
    {
        // Either of those will cause problems
        ret = NULL;
        retLen = -1;
    }
    else
    {
        retLen = 0;
        c = str;

        // Pre-calculate number of elements
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

/*void find_max_rectangle(int i, int j, int map[4][4], int count[4][4])
{
    int length = 0; //only 2^k
    int width = 0;
    int max_area = 0;
    //set width
    if (i == 0)
    {
        if (map[1][j] == 1 && map[2][j] == 1 && map[3][j] == 1)
        {
            if (j == 0)
            {
                bool stop = true;
                for (int k = 0; k < 4; k++)
                    for (int m = 0; m < 4; m++)
                        if (map[k][m] == 0)
                            stop = false;
                if (stop)
                {
                    max_area = 16;
                    
                }
                stop = true;
                for (int m = 0; m < 4; m++)
                    if (map[m][1] == 0)
                        stop = false;
                if (stop)
            }
            else if (j == 1)
            {
            }
            else if (j == 2)
            {
            }
            else if (j == 3)
            {
            }
        }
        else if (map[1][j] == 1)
        {
        }
        else if (map[3][j] == 1)
        {
        }
    }
}*/

int dec2bin(int i) {
	int bin = 0;
	for (int j = 0; j < 3; ++j) { 
		int rmd = i % 2;
		bin += rmd * pow(10, j);
		i /= 2;	
	}
	bin += i * pow(10, 3);
	return bin;
}

int t2o(int a, int b){
	int tn = 0;
	a = dec2bin(a); b = dec2bin(b);
	for (int i = 0; i < 4; ++i) {
		if (a % 10 != b % 10) tn += 2*pow(10,i);
		else tn += a % 10 * pow(10,i);
		a /= 10; b /= 10;
	}
	return tn;
}

int v2(int a, int b) {
	int ct0 = 0, tn = 0;
	for (int i = 0; i < 4; ++i) {
		if (a % 10 == b % 10) ++ct0;
		if ((a % 10 == 0 && b % 10 == 2) || (a % 10 == 2 && b % 10 == 0)) tn += 3*pow(10,i);
		else if (a % 10 != b % 10) tn += 2*pow(10,i);
		else tn += a % 10 * pow(10,i);
		a /= 10; b /= 10;
	}
	if (ct0 == 3) return tn;
	else return 3;
}

void op2(int x1, int x2) {
	int act = 0, bct = 0, cct = 0, dct = 0;
	switch (x1) {
		case 0: --act; --bct; --cct; --dct; break;
		case 1: --act; --bct; --cct; ++dct; break;
		case 2: --act; --bct; ++cct; --dct; break;
		case 3: --act; --bct; ++cct; ++dct; break;
		case 4: --act; ++bct; --cct; --dct; break;
		case 5: --act; ++bct; --cct; ++dct; break;
		case 6: --act; ++bct; ++cct; --dct; break;
		case 7: --act; ++bct; ++cct; ++dct; break;
		case 8: ++act; --bct; --cct; --dct; break;
		case 9: ++act; --bct; --cct; ++dct; break;
		case 10: ++act; --bct; ++cct; --dct; break;
		case 11: ++act; --bct; ++cct; ++dct; break;
		case 12: ++act; ++bct; --cct; --dct; break;
		case 13: ++act; ++bct; --cct; ++dct; break;
		case 14: ++act; ++bct; ++cct; --dct; break;
		case 15: ++act; ++bct; ++cct; ++dct; break;
		default: break;
	}
	switch (x2) {
		case 0: --act; --bct; --cct; --dct; break;
		case 1: --act; --bct; --cct; ++dct; break;
		case 2: --act; --bct; ++cct; --dct; break;
		case 3: --act; --bct; ++cct; ++dct; break;
		case 4: --act; ++bct; --cct; --dct; break;
		case 5: --act; ++bct; --cct; ++dct; break;
		case 6: --act; ++bct; ++cct; --dct; break;
		case 7: --act; ++bct; ++cct; ++dct; break;
		case 8: ++act; --bct; --cct; --dct; break;
		case 9: ++act; --bct; --cct; ++dct; break;
		case 10: ++act; --bct; ++cct; --dct; break;
		case 11: ++act; --bct; ++cct; ++dct; break;
		case 12: ++act; ++bct; --cct; --dct; break;
		case 13: ++act; ++bct; --cct; ++dct; break;
		case 14: ++act; ++bct; ++cct; --dct; break;
		case 15: ++act; ++bct; ++cct; ++dct; break;
		default: break;
	}
	if (x1 == 0) printf("simplification of group 0 -> ");
	else if (x1 == 1 || x1 == 2 || x1 == 8) printf("simplification of group 1 -> ");
	else if (x1 == 7 || x1 == 11 || x1 == 13 || x1 == 14) printf("simplification of group 3 -> ");
	else if (x1 == 15) printf("simplification of group 4 -> ");
	else printf("simplification of group 2 -> ");
	if (act == 2) printf("a");
	else if (act == -2) printf("a'");
	if (bct == 2) printf("b");
	else if (bct == -2) printf("b'");
	if (cct == 2) printf("c");
	else if (cct == -2) printf("c'");
	if (dct == 2) printf("d");
	else if (dct == -2) printf("d'");
	printf("\n");
}

void op4(int x1, int x2, int x3, int x4) {
	int act = 0, bct = 0, cct = 0, dct = 0;
	switch (x1) {
		case 0: --act; --bct; --cct; --dct; break;
		case 1: --act; --bct; --cct; ++dct; break;
		case 2: --act; --bct; ++cct; --dct; break;
		case 3: --act; --bct; ++cct; ++dct; break;
		case 4: --act; ++bct; --cct; --dct; break;
		case 5: --act; ++bct; --cct; ++dct; break;
		case 6: --act; ++bct; ++cct; --dct; break;
		case 7: --act; ++bct; ++cct; ++dct; break;
		case 8: ++act; --bct; --cct; --dct; break;
		case 9: ++act; --bct; --cct; ++dct; break;
		case 10: ++act; --bct; ++cct; --dct; break;
		case 11: ++act; --bct; ++cct; ++dct; break;
		case 12: ++act; ++bct; --cct; --dct; break;
		case 13: ++act; ++bct; --cct; ++dct; break;
		case 14: ++act; ++bct; ++cct; --dct; break;
		case 15: ++act; ++bct; ++cct; ++dct; break;
		default: break;
	}
	switch (x2) {
		case 0: --act; --bct; --cct; --dct; break;
		case 1: --act; --bct; --cct; ++dct; break;
		case 2: --act; --bct; ++cct; --dct; break;
		case 3: --act; --bct; ++cct; ++dct; break;
		case 4: --act; ++bct; --cct; --dct; break;
		case 5: --act; ++bct; --cct; ++dct; break;
		case 6: --act; ++bct; ++cct; --dct; break;
		case 7: --act; ++bct; ++cct; ++dct; break;
		case 8: ++act; --bct; --cct; --dct; break;
		case 9: ++act; --bct; --cct; ++dct; break;
		case 10: ++act; --bct; ++cct; --dct; break;
		case 11: ++act; --bct; ++cct; ++dct; break;
		case 12: ++act; ++bct; --cct; --dct; break;
		case 13: ++act; ++bct; --cct; ++dct; break;
		case 14: ++act; ++bct; ++cct; --dct; break;
		case 15: ++act; ++bct; ++cct; ++dct; break;
		default: break;
	}
	switch (x3) {
		case 0: --act; --bct; --cct; --dct; break;
		case 1: --act; --bct; --cct; ++dct; break;
		case 2: --act; --bct; ++cct; --dct; break;
		case 3: --act; --bct; ++cct; ++dct; break;
		case 4: --act; ++bct; --cct; --dct; break;
		case 5: --act; ++bct; --cct; ++dct; break;
		case 6: --act; ++bct; ++cct; --dct; break;
		case 7: --act; ++bct; ++cct; ++dct; break;
		case 8: ++act; --bct; --cct; --dct; break;
		case 9: ++act; --bct; --cct; ++dct; break;
		case 10: ++act; --bct; ++cct; --dct; break;
		case 11: ++act; --bct; ++cct; ++dct; break;
		case 12: ++act; ++bct; --cct; --dct; break;
		case 13: ++act; ++bct; --cct; ++dct; break;
		case 14: ++act; ++bct; ++cct; --dct; break;
		case 15: ++act; ++bct; ++cct; ++dct; break;
		default: break;
	}
	switch (x4) {
		case 0: --act; --bct; --cct; --dct; break;
		case 1: --act; --bct; --cct; ++dct; break;
		case 2: --act; --bct; ++cct; --dct; break;
		case 3: --act; --bct; ++cct; ++dct; break;
		case 4: --act; ++bct; --cct; --dct; break;
		case 5: --act; ++bct; --cct; ++dct; break;
		case 6: --act; ++bct; ++cct; --dct; break;
		case 7: --act; ++bct; ++cct; ++dct; break;
		case 8: ++act; --bct; --cct; --dct; break;
		case 9: ++act; --bct; --cct; ++dct; break;
		case 10: ++act; --bct; ++cct; --dct; break;
		case 11: ++act; --bct; ++cct; ++dct; break;
		case 12: ++act; ++bct; --cct; --dct; break;
		case 13: ++act; ++bct; --cct; ++dct; break;
		case 14: ++act; ++bct; ++cct; --dct; break;
		case 15: ++act; ++bct; ++cct; ++dct; break;
		default: break;
	}
	if (x1 == 0) printf("simplification of group 0 -> ");
	else if (x1 == 1 || x1 == 2 || x1 == 8) printf("simplification of group 1 -> ");
	else if (x1 == 7 || x1 == 11 || x1 == 13 || x1 == 14) printf("simplification of group 3 -> ");
	else if (x1 == 15) printf("simplification of group 4 -> ");
	else printf("simplification of group 2 -> ");
	if (act == 4) printf("a");
	else if (act == -4) printf("a'");
	if (bct == 4) printf("b");
	else if (bct == -4) printf("b'");
	if (cct == 4) printf("c");
	else if (cct == -4) printf("c'");
	if (dct == 4) printf("d");
	else if (dct == -4) printf("d'");
	printf("\n");
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

    int index[4][4] = {{0, 4, 12, 8},
                       {1, 5, 13, 9},
                       {3, 7, 15, 11},
                       {2, 6, 14, 10}};
    int count[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            count[i][j] = 0;
    
    int *map10 = (int*) malloc(sizeof(int) * 16);
    map10[0] = map[0][0];
    map10[1] = map[1][0];
    map10[2] = map[3][0];
    map10[3] = map[2][0];
    map10[4] = map[0][1];
    map10[5] = map[1][1];
    map10[6] = map[3][1];
    map10[7] = map[2][1];
    map10[8] = map[0][3];
    map10[9] = map[1][3];
    map10[10] = map[3][3];
    map10[11] = map[2][3];
    map10[12] = map[0][2];
    map10[13] = map[1][2];
    map10[14] = map[3][2];
    map10[15] = map[2][2];
    
    //Find 1's
    int ct1 = 0;
	for (int i = 0; i < 16; ++i) if (map10[i] == 1) ++ct1;
	int *one = (int*) malloc(sizeof(int) * ct1);
	int j = 0;
	for (int i = 0; i < 16; ++i) {
		if (map10[i] == 1) { one[j] = i; ++j; }
	}
	
	//Forming column 2 using bitwise
	int ct2 = 0;
	for (int i = 0; i < ct1-1; ++i) {
		for (int j = i+1; j < ct1; ++j) {
			if ((one[i] ^ one[j]) == 1 || (one[i] ^ one[j]) == 2 || (one[i] ^ one[j]) == 4 || (one[i] ^ one[j]) == 8) ++ct2;
		}
	}
	int four[ct2][2]; int k = 0;
	for (int i = 0; i < ct1-1; ++i) {
		for (int j = i+1; j < ct1; ++j) {
			if ((one[i] ^ one[j]) == 1 || (one[i] ^ one[j]) == 2 || (one[i] ^ one[j]) == 4 || (one[i] ^ one[j]) == 8) {
				four[k][0] = one[i]; four[k][1] = one[j]; ++k;
			}
		}
	}
	
	//Forming column 3
	int ct3 = 0;
	for (int i = 0; i < ct2-1; ++i) {
		for (int j = i+1; j < ct2; ++j) {
			if (four[i][0] == four[j][0]) continue;
			bool p = 1;
			int cln3 = v2(t2o(four[i][0],four[i][1]), t2o(four[j][0],four[j][1]));
			for (int k = 0; k < 4; ++k) {
				if (cln3 % 10 == 3) p = 0;
				cln3 /= 10;
			}
			if ((four[i][0] > four[i][1]) || four[i][1] > four[j][0] || four[j][0] > four[j][1] || four[i][0] > four[j][1]) p = 0;
			if (p == 1) ct3 += 4;
		}
	}
	int *two = (int*) malloc(sizeof(int) * ct3);
	int x = 0;
	for (int i = 0; i < ct2-1; ++i) {
		for (int j = i+1; j < ct2; ++j) {
			if (four[i][0] == four[j][0]) continue;
			bool p = 1;
			int cln3 = v2(t2o(four[i][0],four[i][1]), t2o(four[j][0],four[j][1]));
			for (int k = 0; k < 4; ++k) {
				if (cln3 % 10 == 3) p = 0;
				cln3 /= 10;
			}
			if ((four[i][0] > four[i][1]) || four[i][1] > four[j][0] || four[j][0] > four[j][1] || four[i][0] > four[j][1]) p = 0;
			if (p == 1) { two[x] = four[i][0]; two[x+1] = four[i][1]; two[x+2] = four[j][0]; two[x+3] = four[j][1]; x+=4; }
		}
	}
	
	//Elimiate repeated terms
	int four_cp[ct2][2], ct4 = 0;
	for (int i = 0; i < ct2; ++i) { four_cp[i][0] = four[i][0]; four_cp[i][1] = four[i][1]; }
	for (int i = 0; i < ct2; ++i)
		for (int j = 0; j < ct3; j+=4) {
			if (four_cp[i][0] == two[j] || four_cp[i][0] == two[j+1] || four_cp[i][0] == two[j+2] || four_cp[i][0] == two[j+3]) ++ct4;
			if (four_cp[i][1] == two[j] || four_cp[i][1] == two[j+1] || four_cp[i][1] == two[j+2] || four_cp[i][1] == two[j+3]) ++ct4;
			if (ct4 >= 2) { four_cp[i][0] = -100; four_cp[i][1] = -100; }
			ct4 = 0;
		}
	
	//Print column 2 & column 3
	for (int i = 0; i < ct2; ++i) if (four_cp[i][0] > 0 && four_cp[i][1] > 0) printf("[%d, %d]\n", four_cp[i][0], four_cp[i][1]);
	for (int i = 0; i < ct3; i+=4) printf("[%d, %d, %d, %d]\n", two[i], two[i+1], two[i+2], two[i+3]);
	
	//Compute times of index, to form prime implicants chart
	int *bar = (int*) calloc(16, sizeof(int));
	for (int i = 0; i < ct2; ++i) {
		for (int j = 0; j < 16; ++j) {
			if (four_cp[i][0] == j)	++bar[j];
			if (four_cp[i][1] == j) ++bar[j];
		}
	}
	
	//Find essential terms
	for (int i = 0; i < ct3; ++i) for (int j = 0; j < 16; ++j) if (two[i] == j) ++bar[j];
	int ct5 = 0;
	for (int i = 0; i < 16; ++i) if (bar[i] == 1) ++ct5;
	int *single = (int*) malloc(sizeof(int) * ct5);
	j = 0;
	for (int i = 0; i < 16; ++i) {
		if (j == ct5) break;
		if (bar[i] == 1) { single[j] = i; ++j; }
	}
	
	//Print essential prime implicants
	printf("\n");
	for (int i = 0; i < ct5; ++i) {
		for (int j = 0; j < ct2; ++j) {
			if (four_cp[i][0] == single[i] || four_cp[i][1] == single[i]) op2(four_cp[i][0], four_cp[i][1]);
			bar[four_cp[i][0]] = -100; bar[four_cp[i][1]] = -100;
		}
		for (int j = 0; j < ct3; j+=4) {
			if (two[j] == single[i] || two[j+1] == single[i] || two[j+2] == single[i] || two[j+3] == single[i]) op4(two[j], two[j+1], two[j+2], two[j+3]);
			bar[two[j]] = -100; bar[two[j+1]] = -100; bar[two[j+2]] = -100; bar[two[j+3]] = -100; 
		}
	}
	
	//Print remaining essential prime implicants
	int ct6 = 0;
	for (int i = 0; i < 16; ++i) if (bar[i] > 0) ++ct6;
	int *rn = (int*) malloc(sizeof(int) * ct6);
	j = 0;
	for (int i = 0; i < 16; ++i) {
		if (j == ct6) break;
		if (bar[i] > 0) { rn[j] = i; ++j; }
	}
	int ed = ct6, mc = 0; bool pn = 1;
	while (ed > 0) {
		for (int i = 0; i < ct2; ++i) {
			if (pn == 0) break;
			for (int j = 0; j < ct6; ++j) {
				if (pn == 0) break;
				if (four_cp[i][0] == rn[j]) ++mc;
				if (four_cp[i][1] == rn[j]) ++mc;
				if (mc == ct6) { op2(four_cp[i][0], four_cp[i][1]); pn = 0; }
				else if (mc == ed && pn == 1) {
					op2(four_cp[i][0], four_cp[i][1]);
					for (int k = 0; k < ct6; ++k) {
						if (four_cp[i][0] == rn[k]) rn[k] = -100;
						if (four_cp[i][1] == rn[k]) rn[k] = -100;
					}
				}
			}
			mc = 0; 
		}
		--ed;
	}	
	return 0;
}

