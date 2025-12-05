#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#define INPUT_FILE_LEN 4531
//#define INPUT_FILE_LEN 10
#define MAX_LINE_LEN 32

enum Direction {
	LEFT,
	RIGHT,
};

struct Rotation {
	enum Direction dir;
	int amount;
};

static bool read_rotations_from_file(struct Rotation *r, FILE *fp) {
	for (int i = 0; i < INPUT_FILE_LEN; i++) {
		int ch = fgetc(fp);
		if (ch == 'R') { r[i].dir = RIGHT; }
		else if (ch == 'L') { r[i].dir = LEFT; }

		// large enough for any line.
		char buf[MAX_LINE_LEN];
		if (!fgets(buf, MAX_LINE_LEN, fp)) {
			return false;
		}

		char *end;
		r[i].amount = (int)strtol(buf, &end, 10);

		assert(*end == '\n' || *end == EOF);
	}

	return true;
}

static int rotate(int dial, struct Rotation rotation) {
	int result = 0;
	switch (rotation.dir) {
	case LEFT:
		result = dial - rotation.amount;
		if (result < 0) { result %= 100; };
		break;
	case RIGHT:
		result = dial + rotation.amount;
		if (result > 99) { result %= 100; }
	}
	
	if (result < 0) { result += 100; }
	if (result > 99) { result -= 100; }
	
	return result;
}

static int day2_count_zeros(int dial, struct Rotation rotation) {
	int zero_count = 0;

	for (int k = 0; k < rotation.amount; k++) {
		switch (rotation.dir) {
		case LEFT:
			dial--;
			if (dial == 0) { zero_count++; }
			if (dial < 0) { dial = 99; }
			break;
		case RIGHT: 
			dial++;
			if (dial == 100) dial = 0;
			if (dial == 0) { zero_count++; }
			break;
		}
	}

	if (dial == 0) { zero_count--; }

	return zero_count;
}

int main(int argc, char **argv) {
	FILE *fp = fopen("day1_input.txt", "r");
	//FILE *fp = fopen("day1_test_input.txt", "r");

	if (!fp) {
		printf("Couldn't read file.\n");
		return EXIT_FAILURE;
	}

	struct Rotation rotations[INPUT_FILE_LEN];

	if (!read_rotations_from_file(rotations, fp)) {
		printf("Couldn't parse rotations from file.\n");
		return EXIT_FAILURE;
	}

	int dial = 50;
	int zero_counter = 0;
	int zero_counter_day2 = 0;
	
	for (int i = 0; i < INPUT_FILE_LEN; i++) {
		zero_counter_day2 += day2_count_zeros(dial, rotations[i]);
		
		dial = rotate(dial, rotations[i]);
		if (dial == 0) { zero_counter++; };
	}

	printf("Answer: The dial points to zero %d times. For day2: %d\n", zero_counter, zero_counter + zero_counter_day2);

	fclose(fp);
	
	return 0;
}
