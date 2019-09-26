#include <stdio.h>
#include <string.h>

#define ERR_NOT_A_ROMAN_DIGIT	-1
#define ERR_NOT_A_ROMAN_NUMBER	-2

int roman_digit_value(char c) {
	/**
	 * integer value of a roman digit
	 * @c: roman digit
	 */
	switch (c) {
		case 'i': case 'I': return 1;
		case 'v': case 'V': return 5;
		case 'x': case 'X': return 10;
		case 'l': case 'L': return 50;
		case 'c': case 'C': return 100;
		case 'd': case 'D': return 500;
		case 'm': case 'M': return 1000;
	}
	return ERR_NOT_A_ROMAN_DIGIT;
}

int roman_number_value(char *s) {
	/**
	 * integer value of a roman number
	 * @s: roman number
	 */
	int curr, prev, buff, total;
	prev = buff = total = 0;

	/* when each loop begins:
	 * - prev is last digit value (0 on the first loop);
	 * - buff is sum of previous adjacent equal digits values,
	 *   which means it's a multiple of prev;
	 * - total is sum of all passed digits whose value is no
	 *   more inside buff;
	 *               prev  curr
	 *  M    M    C    C    D    L    X  (2360)
	 *  ------    ------    ^
	 *   total     buff     *s
	 * */
	while (*s) {
		/* convert current digit */
		curr = roman_digit_value(*s);

		/* check for invalid digit */
		if (curr == ERR_NOT_A_ROMAN_DIGIT)
			return ERR_NOT_A_ROMAN_NUMBER;

		if (curr != prev) {
			/* increase or decrease the total by the buffer
			 * depending on which is 'bigger' between current
			 * and previous digit */
			total += (curr < prev ? 1 : -1) * buff;
			buff = 0;
		}

		/* add current digit value to the buffer */
		buff += curr;

		/* prepare for the next loop */
		prev = curr;
		s++;
	}

	/* last buffer is always an addendum: we have to sum it here
	 * becouse when the loops end the last buffer (at least last
	 * digit) is still missing from the total */
	return total + buff;
}

int main(int argc, char **argv) {
	char buff[BUFSIZ];
	int num, len;

	while (fgets(buff, sizeof buff, stdin)) {
		len = strlen(buff);
		if (buff[len - 1] == '\n') {
			buff[len - 1] = '\0';
			len--;
		}

		if (len > 0) {
			num = roman_number_value(buff);

			if (num == ERR_NOT_A_ROMAN_NUMBER)
				fprintf(stderr, "Not a Roman Number: '%s'\n", buff);
			else
				fprintf(stdout, "%d\n", num);
		}
	}
}
