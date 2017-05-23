#include "head/basic.h"

int val_table[26];
int stack_addr[100];
struct b_label labels[100];
struct memory_t structmemory[100];
int code_pos = 0, val_pos = 99, label_pos = 0;



void saveAsm(FILE *file)
{
	int i;

    for (i = 0; i < code_pos; i++) {
        switch (structmemory[i].command) {
            case _READ: //READ
                fprintf(file, "%02d READ %d\n", i, structmemory[i].operand);
                break;

            case _WRITE: //WRITE
                fprintf(file, "%02d WRITE %d\n", i, structmemory[i].operand);
                break;

            case _LOAD: //LOAD
                fprintf(file, "%02d LOAD %d\n", i, structmemory[i].operand);
                break;

            case _STORE: //STORE
                fprintf(file, "%02d STORE %d\n", i, structmemory[i].operand);
                break;

            case _ADD: //ADD
                fprintf(file, "%02d ADD %d\n", i, structmemory[i].operand);
                break;

            case _SUB: //SUB
                fprintf(file, "%02d SUB %d\n", i, structmemory[i].operand);
                break;

            case _DIVIDE: //DIVIDE
                fprintf(file, "%02d DIVIDE %d\n", i, structmemory[i].operand);
                break;

            case _MUL: //MUL
                fprintf(file, "%02d MUL %d\n", i, structmemory[i].operand);
                break;

            case _JUMP: //JUMP
                fprintf(file, "%02d JUMP %d\n", i, structmemory[i].operand);
                break;

            case _JNEG: //JNEG
                fprintf(file, "%02d JNEG %d\n", i, structmemory[i].operand);
                break;

            case _JZ: //JZ
                fprintf(file, "%02d JZ %d\n", i, structmemory[i].operand);
                break;

            case _HALT: //HALT
                fprintf(file, "%02d HALT %d\n", i, structmemory[i].operand);
                break;
            default:break;
        }
    }
    int high, low;
    for (i = val_pos+1; i < 100; i++) {
		if (structmemory[i].command != 0) {
			high = (structmemory[i].command >> 7) & 0x7F;
			low = structmemory[i].command & 0x7F;
			fprintf(file, "%02d = +%02X%02X", i, high, low);
		}
	}
}

int find_label(int label)
{
	int i;
	
	for (i = 0; i < label_pos; i++) {
		if (labels[i].label == label)
			return labels[i].pos;
	}
	return -1;
}

char *get_label_and_keyw(char *str, int *label, char *keyword)
{
	int cnt;
	int i = 0;
	
	cnt = sscanf(str, "%d%s", label, keyword);
	if (cnt != 2)
		return NULL;
	for (; (str[i] == ' ') || (str[i] == '\t'); i++);
	for (; (str[i] != ' ') && (str[i] != '\t'); i++);
	for (; (str[i] == ' ') || (str[i] == '\t'); i++);
	for (; (str[i] != ' ') && (str[i] != '\t'); i++);
	for (; (str[i] == ' ') || (str[i] == '\t'); i++);
	return str + i;
}

int get_keyword_code(char *str)
{
	if (strcmp(str, "REM") == 0)
		return KEYW_REM;
	else if (strcmp(str, "INPUT") == 0)
		return KEYW_INPUT;
	else if (strcmp(str, "OUTPUT") == 0)
		return KEYW_OUTPUT;
	else if (strcmp(str, "GOTO") == 0)
		return KEYW_GOTO;
	else if (strcmp(str, "IF") == 0)
		return KEYW_IF;
	else if (strcmp(str, "LET") == 0)
		return KEYW_LET;
	else if ((strcmp(str, "END") == 0) || (strcmp(str, "END\n") == 0))
		return KEYW_END;
	else
		return -1;
}

int is_delim(char c)
{
	if ((c == ' ') || (c == '\t') || (c == '\0') || (c == '\n'))
		return 0;
	else
		return -1;
}

char *cpy_token(char *token, char *str)
{
	int i;
	
	for (i = 0; (str[i] == ' ') || (str[i] == '\t'); i++);
	str += i;
	for (i = 0; is_delim(str[i]) != 0; i++) {
		token[i] = str[i];
	}
	token[i] = '\0';
	
	return str+i;
}

int srt_is_empty(char *str)
{
	int i;
	
	for (i = 0; (str[i] == ' ') || (str[i] == '\t'); i++);
	if ((str[i] == '\n') || (str[i] == '\0'))
		return 0;
	else
		return -1;
}

int _test_argv(char *argv[])
{
	char *ptr1;
	
	ptr1 = strrchr(argv[2], '.');
	if ((strcmp(ptr1, ".o") != 0))
		return -1;
	else
		return 0;
}

int is_value(char *str)
{
	if ((str[0] >= 'A') && (str[0] <= 'Z')) {
		if (str[1] == '\0')
			return 0;
		else
			return -1;
	}
	else
		return -1;
}

int get_var_addr(char c)
{
	if ((c >= 'A') && (c <= 'Z')) {
		if (val_table[c-'A'] < 0) {
			val_table[c-'A'] = val_pos;
            structmemory[val_pos].is_val = 1;
            structmemory[val_pos].command = 0;
			val_pos--;
		}
		return val_table[c-'A'];
	}
	else
		return -1;
}

int add_const(int n)
{
    structmemory[val_pos].is_val = 1;
    structmemory[val_pos].command = n;
	val_pos--;
	return val_pos+1;
}

void add_code(int command, int operand)
{
    structmemory[code_pos].is_val = 0;
    structmemory[code_pos].command = command;
    structmemory[code_pos].operand = operand;
	code_pos++;
}

int get_cache_addr(int n)
{
	if (stack_addr[n] < 0) {
		stack_addr[n] = val_pos;
        structmemory[code_pos].is_val = 1;
        structmemory[code_pos].command = 0;
		val_pos--;
	}
	return stack_addr[n];
}

void rpn_pars(char *rpn, int val)
{
	int i = 0;
	int depth = 0;
	int addr;
	int st1, st2;
	
	while (rpn[i] != '\0') {
		if ((rpn[i] >= 'A') && (rpn[i] <= 'Z')) {
			addr = get_cache_addr(depth);
			add_code(_LOAD, get_var_addr(rpn[i]));
			add_code(_STORE, addr);
			depth++;
		}
		if ((rpn[i] == '+') || (rpn[i] == '-') || (rpn[i] == '*') || (rpn[i] == '/')) {
			if (depth < 2) {
				perror("Uncorrect LET statement\n");
				exit(1);
			}
			st1 = get_cache_addr(depth - 1);
			st2 = get_cache_addr(depth - 2);
			add_code(_LOAD, st1);
			switch (rpn[i]) {
				case '+':
					add_code(_ADD, st2);
					break;
				
				case '-':
					add_code(_SUB, st2);
					break;
				
				case '/':
					add_code(_DIVIDE, st2);
					break;
				
				case '*':
					add_code(_MUL, st2);
					break;
			}
			add_code(_STORE, st2);
			depth--;
		}
		i++;
	}
	if (depth != 1) {
		perror("Uncorrect LET statement\n");
		exit(1);
	}
	addr = get_cache_addr(0);
	add_code(_STORE, val);
}

int parse_line(char *str, int key_w)
{
	char *ptr;
	char token[256];
	char rpn[256];
	int readen, label;
	int if_val1, if_val2; // Адресс первой и второй переменной логического выр.
	int if_jmp, num;
	char sign;
	int keyw;
	int val; // LET val
	
	switch (key_w) {
		case KEYW_INPUT:
			ptr = cpy_token(token, str);
			if ((!srt_is_empty(ptr)) && (!is_value(token))) {
				add_code(_READ, get_var_addr(token[0])); // READ
			}
			else {
				perror("Not a valid value\n");
				exit(1);
			}
			break;
		
		case KEYW_OUTPUT:
			ptr = cpy_token(token, str);
			if ((!srt_is_empty(ptr)) && (!is_value(token))) {
				add_code(_WRITE, get_var_addr(token[0])); // WRITE
			}
			else {
				perror("Not a valid value\n");
				exit(1);
			}
			break;
		
		case KEYW_GOTO:
			readen = sscanf(str, "%d", &label);
			if (readen == 1) {
				int addr;
				
				addr = find_label(label);
				if (addr < 0) {
					perror("Label not found!\n");
					exit(1);
				}
				add_code(_JUMP, addr); // JUMP
			}
			else  {
				perror("Not a valid value\n");
				exit(1);
			}
			break;
		
		case KEYW_END:
			add_code(_HALT, 0); // HALT
			break;
		
		case KEYW_IF:
			ptr = cpy_token(token, str);
			if (is_value(token) == 0) {
				if_val1 = get_var_addr(token[0]);
			}
			else if (sscanf(token, "%d", &num) == 1) {
				if_val1 = add_const(num);
			}
			else {
				perror("Not a value or number!\n");
				exit(1);
			}
			
			ptr = cpy_token(token, ptr);
			if (strcmp(token, "<") == 0)
				sign = '<';
			else if (strcmp(token, ">") == 0)
				sign = '>';
			else if (strcmp(token, "=") == 0)
				sign = '=';
			else {
				perror("Unknown logical operation!\n");
				exit(1);
			}
			
			ptr = cpy_token(token, ptr);
			if (is_value(token) == 0) {
				if_val2 = get_var_addr(token[0]);
			}
			else if (sscanf(token, "%x", &num) == 1) {
				if_val2 = add_const(num);
			}
			else {
				perror("Not a value or number!\n");
				exit(1);
			}
			
			switch (sign) {
				case '>':
					add_code(_LOAD, if_val1);
					add_code(_SUB, if_val2);
					add_code(_JNEG, code_pos + 2);
					break;
				
				case '<':
					add_code(_LOAD, if_val2);
					add_code(_SUB, if_val1);
					add_code(_JNEG, code_pos + 2);
					break;
				
				case '=':
					add_code(_LOAD, if_val1);
					add_code(_SUB, if_val2);
					add_code(_JZ, code_pos + 2);
					break;
            }
			if_jmp = code_pos + 1;
			add_code(_JUMP, 0);
			ptr = cpy_token(token, ptr);
			keyw = get_keyword_code(token);
			if (keyw < 0) {
				perror("Unknown operator!\n");
				exit(1);
			}
			if (keyw == KEYW_IF) {
				perror("Multiple if!\n");
				exit(1);
			}
			parse_line(ptr, keyw);
            structmemory[if_jmp].operand = code_pos;
			break;
			
			case KEYW_LET:
				ptr = cpy_token(token, str);
				if (!is_value(token)) {
					val = get_var_addr(token[0]);
				}
				else {
					perror("Not a valid value\n");
					exit(1);
				}
				ptr = cpy_token(token, ptr);
				if (strcmp(token, "=") != 0) {
					perror("Uncorrect LET statement!\n");
					exit(1);
				}
				translate_to_rpn(rpn, ptr);
				rpn_pars(rpn, val);
				break;
        default:break;
    }
	return 0;
}

int basic(int argc, char *argv[])
{
	FILE *input, *output;
	char asm_filename[256];
	char line[256], keyw_str[256];
	char *str;
	int i;
	int label, keyw;
	
	if (argc != 3) {
		perror("Incorrect arguments!\n");
		exit(1);
	}
	if (_test_argv(argv) != 0) {
		perror("Incorrect arguments!\n");
		exit(1);
	}
	strcpy(asm_filename, argv[1]);
	strcat(asm_filename, ".sa");
	if ((input = fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "Cannot open file:%s", argv[2]);
		exit(1);
	}
	if ((output = fopen(asm_filename, "wb")) == NULL) {
		fprintf(stderr, "Cannot open file:%s", asm_filename);
		exit(1);
	}
	
	for (i = 0; i < 26; i++)
		val_table[i] = -1;
	for (i = 0; i < 100; i++)
		stack_addr[i] = -1;
	while (fgets(line, 256, input)) {
		if (srt_is_empty(line) == 0)
			continue;
		str = get_label_and_keyw(line, &label, keyw_str);
		if (str == NULL) {
			perror("Unknown operator!\n");
			exit(1);
		}
		keyw = get_keyword_code(keyw_str);
		if (keyw < 0) {
			perror("Unknown operator!\n");
			exit(1);
		}
		labels[label_pos].label = label;
		labels[label_pos].pos = code_pos;
		label_pos++;
		parse_line(str, keyw);
	}
	saveAsm(output);
	fclose(output);
	fclose(input);
	char *arg[3];
	arg[2] = asm_filename;
	arg[1] = argv[2];
	int flg = asembler(3, arg);
	return flg;
}